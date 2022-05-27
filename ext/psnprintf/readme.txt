psnprintf
A portable snprintf function
----------------------------

Contents of this file:
 
 1. License
 2. Brief Documentation
 3. Unit tests
 4. Benchmarking program
 5. Known problems / TODO
 6. Contact Details


1. License
----------

This work free for commercial and non-commercial use alike.  See license.txt for details.


2. Documentation
----------------

Copy psnprintf.cpp into your source directory and psnprintf into your
header directory.  In your source files:

   #include "psnprintf.h"

The psnprintf function is defined as:

   int psnprintf(char *str, size_t n, const char *format, ...)

   str is your buffer
   n is the size of your buffer (including NULL)
   format is a printf style format string
   
   Return value is number of characters that would have been printed your
   buffer was large enough.  If the size of your buffer >= the return
   value, the string was completely formatted into the buffer.  Otherwise
   the buffer was completely filled, and the last byte is a terminating
   NULL.

psnprintf does not quite conform to C99 specification as it ALWAYS terminates
your buffer with a NULL, unless n is given as 0 (zero buffer size).


3. Unit tests
-------------
The function is extensively tested with the unit test program provided
in the test/ directory.  See "test/build.txt" for information on how 
to build and run these unit tests on your platform.


4. Benchmarking
---------------
A simple benchmarking program is provided in the test/ directory.  It
compares psnprintf's performance to your system's native sprintf and
snprintf.  In my experiences psnprintf almost always comes out equal
or faster.  See "test/build.txt" for information on how to build and
run the benchmarking program on your platform.


5. Known Problems / TODO
------------------------

 - Unit tests currently fail on Windows due to inconsitency in printf.
   On UNIX sprintf(buf, "%.0f", 0.0) gives "0.0", whereas on Windows
   it gives "0" (which is probably more correct).  Currently psnpritnf
   follows the UNIX convention, though this might change.

 - Some unit tests fail on Linux due to inconsistency in printf.

 - Some unit tests fail on Solaris due to insconsistency in printf.

 - Floating point support not fully implemented.  Format character 'f'
   is available but 'e', 'E', 'g' and 'G' will give no output unless
   the value is special (NaN or Infinity).

 - Both the numerical functions (double and integer) are quite messy
   due to various padding/alignment/precision options.  Should look
   into this to clean it up a bit.

 - Unit testing code is UGLY and was written in a big hurry.  Consists
   of way too many macros and is probably unnecessarily complicated.
   Demands a complete rewrite (perhaps not relying on system's sprintf?)


6. Contact Details
------------------

The author of the function is Alex Holkner.  He can be reached at:

  alex@partiallydisassembled.net

or
  
  aholkner@cs.rmit.edu.au
