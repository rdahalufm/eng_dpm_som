#define __EXTENSIONS__
#ifndef __USE_XOPEN_EXTENDED
#  define __USE_XOPEN_EXTENDED
#endif

#include "psnprintf.h"
#include <string.h>

/* fix for compiler warnings */
#define UNUSEDARG(x) ((void)(x))

int psnprintf(char *str, size_t n, const char *format, ...)
{
    va_list args;
    int ret;
    
    va_start(args, format);
    ret = pvsnprintf(str, n, format, args);
    va_end(args);
    return ret;
}

#define STATE_NONE 0
#define STATE_OPERATOR 1 /* Just received % */
#define STATE_FLAG 2     /* Just received a flag or prefix or width */
#define STATE_WIDTH 3
#define STATE_BEFORE_PRECISION 4 /* just got dot */
#define STATE_PRECISION 5 /* got at least one number after dot */
#define STATE_PREFIX 6   /* just received prefix (h, l or L) */

#define UNKNOWN_WIDTH 0
#define VARIABLE_WIDTH -2
#define UNKNOWN_PRECISION -1
#define VARIABLE_PRECISION -2

/* Following macros give reusable switch cases, used in combination
 * depending on current state. Sucks to do these as macros, but should 
 * give the compiler lots of freedom to optimize.
 */
#define CHECK_FLAG \
    case '-':  \
        flags |= FLAG_LEFT_ALIGN; \
        state = STATE_FLAG; \
        break; \
    case '+': \
        flags |= FLAG_SIGNED; \
        state = STATE_FLAG; \
        break; \
    case '0': \
        flags |= FLAG_ZERO_PAD; \
        state = STATE_FLAG; \
        break; \
    case ' ': \
        flags |= FLAG_SIGN_PAD; \
        state = STATE_FLAG; \
        break; \
    case '#': \
        flags |= FLAG_HASH; \
        state = STATE_FLAG; \
        break;
        
#define CHECK_WIDTH \
    case '1': \
    case '2': \
    case '3': \
    case '4': \
    case '5': \
    case '6': \
    case '7': \
    case '8': \
    case '9': \
        width = *pfmt - '0'; /* convert to integer */ \
        state = STATE_WIDTH; \
        break; \
    case '*': \
        width = VARIABLE_WIDTH; \
        state = STATE_WIDTH; \
        break;

#define CHECK_PRECISION \
    case '.': \
        precision = 0; \
        state = STATE_BEFORE_PRECISION; \
        break; 

#define CHECK_PREFIX \
    case 'h': \
    case 'l': \
    case 'L': \
        if ((('h' == pfmt[0]) && ('h' == pfmt[1])) || \
            (('l' == pfmt[0]) && ('l' == pfmt[1]))) \
        { \
            dblPrefix = 1; \
            pfmt++; \
        } \
        prefix = *pfmt; \
        state = STATE_PREFIX; \
        break;

#define GET_VARS \
    if (width == VARIABLE_WIDTH) \
        width = va_arg(ap, int); \
    if (precision == VARIABLE_PRECISION) \
        precision = va_arg(ap, int);

#define CHECK_TYPE \
    case 'd': \
    case 'i': \
    case 'u': \
    case 'o': \
    case 'x': \
    case 'X': \
    case 'p': \
        GET_VARS \
        ncount += pvsnfmt_int(&pinsertion, &nmax, *pfmt, flags, width, precision, prefix, &ap); \
        state = STATE_NONE; \
        break; \
    case 'e': \
    case 'E': \
    case 'f': \
    case 'g': \
    case 'c': \
        GET_VARS \
        ncount += pvsnfmt_char(&pinsertion, &nmax, *pfmt, flags, width, precision, prefix, &ap); \
        state = STATE_NONE; \
        break; \
    case 's': \
        GET_VARS \
        ncount += pvsnfmt_str(&pinsertion, &nmax, *pfmt, flags, width, precision, prefix, &ap); \
        state = STATE_NONE; \
        break; \
    case 'n': \
        *(va_arg(ap, int *)) = ncount; \
        state = STATE_NONE; \
        break;

#define PUTCHAR(ch) \
    if (nmax > 1) \
    { \
        *pinsertion++ = ch;  \
        nmax--; \
    } \
    ncount++;
        
static char dblPrefix = 0;                      /* double length prefix hh or ll */

int pvsnprintf(char *str, size_t nmax, const char *format, va_list ap)
{
    /* nmax gives total size of buffer including null
     * null is ALWAYS added, even if buffer too small for format 
     * (contrary to C99)
     */
     
    char *pinsertion = str;
    const char *pfmt = format;
    int ncount = 0;     /* number of characters printed so far */
    int state = STATE_NONE;
    char flags = 0;
    int width = 0;
    int precision = 0;
    char prefix = 0;

    dblPrefix = 0;
    
    while (*pfmt)
    {
        switch (state)
        {
        case STATE_NONE:
            switch (*pfmt)
            {
            case '%':
                state = STATE_OPERATOR;
                flags = FLAG_DEFAULT;
                width = UNKNOWN_WIDTH;
                precision = UNKNOWN_PRECISION;
                prefix = '\0';
                break;
                
            default:
                PUTCHAR(*pfmt)
            }
            break;
            
        case STATE_OPERATOR:
            switch (*pfmt)
            {
                CHECK_FLAG
                CHECK_WIDTH
                CHECK_PRECISION
                CHECK_PREFIX
                CHECK_TYPE
            default:
                PUTCHAR(*pfmt) /* Unknown format, just print it (e.g. "%%") */
                state = STATE_NONE;
            }
            break;

        case STATE_FLAG:
            switch (*pfmt)
            {
                CHECK_FLAG
                CHECK_WIDTH
                CHECK_PRECISION
                CHECK_PREFIX
                CHECK_TYPE
            }
            break;
        
        case STATE_WIDTH:
            if (*pfmt >= '0' && *pfmt <= '9' && width != -1)
            {
                width = width * 10 + (*pfmt - '0');
                break;
            }
            switch (*pfmt)
            {
                CHECK_PRECISION
                CHECK_PREFIX
                CHECK_TYPE
            }
            break;
            
        case STATE_BEFORE_PRECISION:
            if (*pfmt >= '0' && *pfmt <= '9')
            {
                precision = *pfmt - '0';
                state = STATE_PRECISION;
            }
            else if (*pfmt == '*')
            {
                precision = VARIABLE_PRECISION;
                state = STATE_PRECISION;
            }
            switch (*pfmt)
            {
                CHECK_PREFIX
                CHECK_TYPE
            }
            break;
            
        case STATE_PRECISION:
            if (*pfmt >= '0' && *pfmt <= '9' && precision != -1)
            {
                precision = precision * 10 + (*pfmt - '0');
                break;
            }
            switch (*pfmt)
            {
                CHECK_PREFIX
                CHECK_TYPE
            }
            break;
            
        case STATE_PREFIX:
            switch (*pfmt)
            {
                CHECK_TYPE
            }
            
            
        } /* switch state */
        pfmt++;
        
    } /* while *pfmt */
    
    /* Add null if there is room
     * NOTE there is always room even if str doesn't fit unless
     * nmax initially passed in as 0.  fmt functions take care to
     * always leave at least one free byte at end.
     */
    if (nmax > 0)
        *pinsertion = '\0';
    
    return ncount;
}

int pvsnfmt_char(char **pinsertion, size_t *nmax, const char fmt, int flags, 
                 int width, int precision, char prefix, va_list *ap)
{
    UNUSEDARG(fmt);
    UNUSEDARG(flags);
    UNUSEDARG(width);
    UNUSEDARG(precision);
    UNUSEDARG(prefix);

    if (*nmax > 1)
    {
        *(*pinsertion)++ = (char) va_arg(*ap, int);
        (*nmax)--;
    }
    return 1;
}

/* strnlen not available on all platforms.. maybe autoconf it? */
size_t pstrnlen(const char *s, size_t count)
{
    const char *p = s;
    while (*p && count-- > 0)
        p++;
    
    return p - s;
}
    
/* Format a string into the buffer.  Parameters:
 *   **pinsertion   Pointer to pointer to buffer (can be reference to NULL)
 *   *nmax          Pointer to size of buffer.  This is may be modified
 *   fmt            Format character ('s')
 *   flags          0 or combination of flags (see .h file for #defines)
 *   width          Width of string, as defined in printf
 *   precision      Precision of string, as defined in printf
 *   ap             Argument list
 */
    
int pvsnfmt_str(char **pinsertion, size_t *nmax, const char fmt, int flags, 
                int width, int precision, char prefix, va_list *ap)
{
    const char *str = va_arg(*ap, const char *);
    int nprinted;
    size_t len;
    size_t pad = 0;

    UNUSEDARG(fmt);
    UNUSEDARG(prefix);
    
    /* Get width magnitude, set aligment flag */
    if (width < 0)
    {
        width = -width;
        flags |= FLAG_LEFT_ALIGN;
    }
    
    /* Truncate due to precision */
    if (precision < 0)
        len = strlen(str);
    else
        len = pstrnlen(str, precision);
        
    /* Determine padding length */
    if (width > (int) len)
        pad = width - len;
    
    /* Exit if just counting (not printing) */
    if (*nmax <= 1)
        return len + pad;
    
    /* If right-aligned, print pad */
    if ( !(flags & FLAG_LEFT_ALIGN) )
    {
        char padchar;
        if (flags & FLAG_ZERO_PAD)
            padchar = '0';
        else
            padchar = ' ';
        
        if (*nmax - 1 < pad)
            nprinted = *nmax - 1;
        else
            nprinted = pad;
        
        memset(*pinsertion, padchar, nprinted);
        *pinsertion += nprinted;
        *nmax -= nprinted;
    }

    /* Output string */
    if (*nmax <= 1)
        nprinted = 0;
    else if (*nmax - 1 < len)
        nprinted = *nmax - 1;
    else
        nprinted = len;
        
    memcpy(*pinsertion, str, nprinted);
    *pinsertion += nprinted;
    *nmax -= nprinted;
    
    /* If left aligned, add pad */
    if (flags & FLAG_LEFT_ALIGN)
    {
        if (*nmax <= 1)
            nprinted = 0;
        else if (*nmax - 1 < pad)
            nprinted = *nmax - 1;
        else
            nprinted = pad;
            
        memset(*pinsertion, ' ', nprinted);
        *pinsertion += nprinted;
        *nmax -= nprinted;
    }
    
    return len + pad; /* Return total length of pad + string even if some
                       * was truncated
                       */
}

/* Format an integer into the buffer.  Parameters:
 *   **pinsertion   Pointer to pointer to buffer (can be reference to NULL)
 *   *nmax          Pointer to size of buffer.  This is may be modified
 *   fmt            Format character (one of "diuoxX")
 *   flags          0 or combination of flags (see .h file for #defines)
 *   width          Width of integer, as defined in printf
 *   precision      Precision of integer, as defined in printf
 *   ap             Argument list
 */

int pvsnfmt_int(char **pinsertion, size_t *nmax, char fmt, int flags, 
                int width, int precision, char prefix, va_list *ap)
{
    long int number = 0;
    unsigned long int unumber = 0;
    char numbersigned = 1; 
    char iszero = 0; /* bool */
    int base = 0;
    int len = 0; /* length of number component (no sign or padding) */
    char char10 = 0;
    char sign = 0;
    size_t widthpad = 0;
    int addprefix = 0; /* optional "0x" = 2 */
    int totallen = 0;
    char is64bit = 0;
    long long int number64 = 0;
    unsigned long long int unumber64 = 0;

    /* Stack used to hold digits, which are generated backwards
     * and need to be popped off in the correct order
     */
    char numstack[22];    /* largest 64 bit number has 22 octal digits */
    char *stackpos = numstack;
    
#define PUSH(x) \
    *stackpos++ = x
    
#define POP() \
    *(--stackpos)
      
    /* Retrieve value */
    switch (prefix)
    {
    case 'h':
        switch (fmt)
        {
            case 'd':
            case 'i':
                if (0 != dblPrefix)
                {
                    number = (signed char) va_arg(*ap, int);
                }
                else
                {
                    number = (signed short int) va_arg(*ap, int);
                }
                break;
            case 'u':
            case 'o':
            case 'x':
            case 'X':
                if (0 != dblPrefix)
                {
                    unumber = (unsigned char) va_arg(*ap, int);
                }
                else
                {
                    unumber = (unsigned short int) va_arg(*ap, int);
                }
                numbersigned = 0;
                break;
             case 'p':
                unumber = (unsigned long) va_arg(*ap, void *);
                numbersigned = 0;
        }
        break;
    case 'l':
        switch (fmt)
        {
            case 'd':
            case 'i':
                if (0 != dblPrefix)
                {
                    number64 = va_arg(*ap, signed long long int);
                    is64bit = 1;
                }
                else
                {
                    number = va_arg(*ap, signed long int);
                }
                break;
            case 'u':
            case 'o':
            case 'x':
            case 'X':
                if (0 != dblPrefix)
                {
                    unumber64 = va_arg(*ap, unsigned long long int);
                    is64bit = 1;
                }
                else
                {
                    unumber = va_arg(*ap, unsigned long int);
                }
                numbersigned = 0;
                break;
             case 'p':
                unumber = (unsigned long) va_arg(*ap, void *);
                /* sba, port: disabled to avoid CLANG warning */
                /* numbersigned = numbersigned; */
        }
        break;
    default:
        switch (fmt)
        {
            case 'd':
            case 'i':
                number = va_arg(*ap, signed int);
                break;
            case 'u':
            case 'o':
            case 'x':
            case 'X':
                unumber = va_arg(*ap, unsigned int);
                numbersigned = 0;
                break;
             case 'p':
                unumber = (unsigned long) va_arg(*ap, void *);
                numbersigned = 0;
         }
    } /* switch fmt to retrieve number */

    if (fmt == 'p')
    {
        fmt = 'x';
        flags |= FLAG_HASH;
    }
    
    /* Discover base */
    switch (fmt)
    {
        case 'd':
        case 'i':
        case 'u':
            base = 10;
            break;
        case 'o':
            base = 8;
            break;
        case 'X':
            base = 16;
            char10 = 'A';
            break;
        case 'x':
            base = 16;
            char10 = 'a';
    }

    if (numbersigned)
    {    
        if (!is64bit && (number < 0))
        {
            /* Deal with negativity */
            sign = '-';
            number = -number;
        }
        else if (is64bit && (number64 < 0))
        {
            /* Deal with negativity */
            sign = '-';
            number64 = -number64;
        }
        else if (flags & FLAG_SIGNED)
        {
            sign = '+';
        }
        else if (flags & FLAG_SIGN_PAD)
        {
            sign = ' ';
        }
    }
    
    /* Create number */
    if (numbersigned && !is64bit)
    {     
        if (number == 0)
            iszero = 1;
        do
        {
            PUSH(number % base);
            number /= base;
            len++;
        } while (number != 0);
    }
    else if (numbersigned && is64bit)
    {
        if (number64 == 0)
            iszero = 1;
        do
        {
            PUSH(number64 % base);
            number64 /= base;
            len++;
        } while (number64 != 0);
    }
    else if (!numbersigned && !is64bit)
    {
        if (unumber == 0)
            iszero = 1;
        do
        {
            PUSH(unumber % base);
            unumber /= base;
            len++;
        } while (unumber != 0);
    }
    else
    {
        if (unumber64 == 0)
            iszero = 1;
        do
        {
            PUSH(unumber64 % base);
            unumber64 /= base;
            len++;
        } while (unumber64 != 0);
    }

    /* Octal hash character (alternate form) */
    if (fmt == 'o' && (flags & FLAG_HASH) && precision <= len &&
        precision != 0 && !iszero )
    {
        precision = len + 1;
    }

    /* Determine width of sign, if any. */
    if ( (fmt == 'x' || fmt == 'X') && (flags & FLAG_HASH) && !iszero )
        addprefix = 2;
    else if (sign != 0)
        addprefix = 1;

    /* Make up precision (zero pad on left) */
    while (len < precision)
    {
        PUSH(0);
        len++;
    }
       

    if (len + addprefix < width)
    {
        totallen = width;
        widthpad = width - (len + addprefix);
    }
    else
        totallen = len + addprefix;
           
    if (*nmax <= 1)
        return totallen;

    /* Write sign or "0x" */
    if (flags & FLAG_ZERO_PAD)
    {
        if (addprefix == 2) /* 0x */
        {
            if (*nmax > 1)
            {
                *(*pinsertion)++ = '0';
                (*nmax)--;
            }
            if (*nmax > 1)
            {
                *(*pinsertion)++ = fmt;
                (*nmax)--;
            }
        }
        else if (addprefix == 1) /* sign */
        {
            if (*nmax > 1)
            {
                *(*pinsertion)++ = sign;
                (*nmax)--;
            }
        }
    }

    /* Width pad */
    if ( !(flags & FLAG_LEFT_ALIGN) )
    {
        if (*nmax <= 1)
            widthpad = 0;
        else if (*nmax + 1 < widthpad)
            widthpad = *nmax - 1;
        
        if (flags & FLAG_ZERO_PAD)
            memset(*pinsertion, '0', widthpad);
        else
            memset(*pinsertion, ' ', widthpad);

        *pinsertion += widthpad;
        *nmax -= widthpad;
    }
    
    /* Write sign or "0x" */
    if ( !(flags & FLAG_ZERO_PAD) )
    {
        if (addprefix == 2) /* 0x */
        {
            if (*nmax > 1)
            {
                *(*pinsertion)++ = '0';
                (*nmax)--;
            }
            if (*nmax > 1)
            {
                *(*pinsertion)++ = fmt;
                (*nmax)--;
            }
        }
        else if (addprefix == 1) /* sign */
        {
            if (*nmax > 1)
            {
                *(*pinsertion)++ = sign;
                (*nmax)--;
            }
        }
    }
    
    /* Write number */
    if (*nmax <= 1)
        len = 0;
    else if (*nmax + 1 < (unsigned int) len)
        len = *nmax - 1;
    
    for (; len > 0; len--)
    {
        char n = POP();
        if (n <= 9)
            *(*pinsertion)++ = n + '0';
        else
            *(*pinsertion)++ = n - 10 + char10;
    }        
    *nmax -= len;
    
    if (flags & FLAG_LEFT_ALIGN)
    {
        if (*nmax <= 1)
            widthpad = 0;
        else if (*nmax + 1 < widthpad)
            widthpad = *nmax - 1;
            
        memset(*pinsertion, ' ', widthpad);
        *pinsertion += widthpad;
        *nmax -= widthpad;
    }
        
    return totallen;
}
