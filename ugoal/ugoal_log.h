/** @file
 *
 * @brief ugoal logging
 *
 * @copyright
 * Copyright 2021.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */

#ifndef _UGOAL_LOG_H_
#define _UGOAL_LOG_H_


/****************************************************************************/
/* Defines */
/****************************************************************************/ 

#ifdef GOAL_CONFIG_LOGGING
# if GOAL_CONFIG_LOGGING == 1
#  undef CONFIG_UGOAL_LOGGING
#  define CONFIG_UGOAL_LOGGING 1
# endif
#endif

#if CONFIG_UGOAL_LOGGING == 1

/* define standard log functions, if not defined by platform */
# ifndef GOAL_LOG_INFO
#  define GOAL_LOG_INFO(...) \
    printf("[INF] %s:%d ", __FILE__, __LINE__); \
    printf(__VA_ARGS__); fflush(stdout); printf("\n");
# endif

# ifndef GOAL_LOG_WARN
#  define GOAL_LOG_WARN(...) \
    printf("[WARN] %s:%d ", __FILE__, __LINE__); \
    printf(__VA_ARGS__); fflush(stdout); printf("\n");
# endif

# ifndef GOAL_LOG_ERR
#  define GOAL_LOG_ERR(...) \
    printf("[ERR] %s:%d ", __FILE__, __LINE__); \
    printf(__VA_ARGS__); fflush(stdout); printf("\n");
# endif

# ifndef GOAL_LOG_EXCEPTION
#  define GOAL_LOG_EXCEPTION(_id, ...) \
    printf("[EXC] "); \
    printf(__VA_ARGS__); fflush(stdout); exit(1);
# endif

# if CONFIG_UGOAL_LOGGING_DBG == 1
#  ifndef GOAL_LOG_DBG
#   define GOAL_LOG_DBG(...) \
        printf("[DBG] "); \
        printf(__VA_ARGS__); fflush(stdout); printf("\n");
#  endif
# else
#  define GOAL_LOG_DBG(...)
# endif

#else /* CONFIG_UGOAL_LOGGING == 1 */

/* define empty functions if logging disabled */
# define GOAL_LOG_INFO(...)
# define GOAL_LOG_WARN(...)
# define GOAL_LOG_ERR(...)
# define GOAL_LOG_EXCEPTION(...)
# define GOAL_LOG_DBG(...)

#endif /* CONFIG_UGOAL_LOGGING == 1 */

#endif /* _UGOAL_LOG_H_ */
