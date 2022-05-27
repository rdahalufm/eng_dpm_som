/** @file
 *
 * @brief simple api default configuration
 *
 * This file lists all configuration options with it's default value.
 * They can be overwritten by the application.
 *
 * @copyright
 * Copyright 2010-2021.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */

#ifndef UGOAL_DEFAULT_H_
#define UGOAL_DEFAULT_H_


/****************************************************************************/
/* Defines */
/****************************************************************************/ 

/**< by default ugoal uses stdlib calloc function for heap allocation.
 * by setting this option, a dedicated memory area will be allocated statically
 * as a heap.
 */
#ifndef CONFIG_UGOAL_HEAP_BUFFER
# define CONFIG_UGOAL_HEAP_BUFFER 256
#else
/**< if the ugoal HEAP buffer is used, an HEAP size must be configured. This
 * can be done by the platform.
 */
# ifndef CONFIG_UGOAL_HEAP_BUFFER_SIZE
#  error "Platform needs to specifiy a heap size using CONFIG_UGOAL_HEAP_BUFFER_SIZE"
# endif

/**< if the ugoal HEAP buffer is used, an alignment can be configured */
# ifndef CONFIG_UGOAL_HEAP_BUFFER_ALIGNMENT
#  define CONFIG_UGOAL_HEAP_BUFFER_ALIGNMENT 0
# endif
#endif

/**< enable usage of the datamapper */
#ifndef CONFIG_UGOAL_DATAMAPPER
# define CONFIG_UGOAL_DATAMAPPER 1
#endif

#if CONFIG_UGOAL_DATAMAPPER == 1
# define GOAL_CONFIG_MEDIA_MI_DM 1
# define CONFIG_UGOAL_INSTANCE 1
# define CONFIG_UGOAL_MAINLOOP_REG 1
#else
# define GOAL_CONFIG_MEDIA_MI_DM 0
#endif

#define GOAL_CONFIG_SNMP 1
#define GOAL_CONFIG_MCTC 1
#define GOAL_CONFIG_MCTC_AC 1

/**< for debugging purpose disable any timeout
 * detection on the peer and enable logging.
 * NOTE: logging settings are override-able.
 */
#ifndef CONFIG_UGOAL_DEBUG_SETTINGS
# define CONFIG_UGOAL_DEBUG_SETTINGS 0
#endif

#if CONFIG_UGOAL_DEBUG_SETTINGS == 1
# define CONFIG_UGOAL_TIMEOUT_RPC 0
# define CONFIG_UGOAL_TIMEOUT_MEDIA 0

# ifndef CONFIG_UGOAL_LOGGING
#  define CONFIG_UGOAL_LOGGING 1
# endif
#endif /* CONFIG_UGOAL_DEBUG_SETTINGS */

/**< timeouts for peer-loss detection */
#ifndef CONFIG_UGOAL_TIMEOUT_RPC
# define CONFIG_UGOAL_TIMEOUT_RPC 5000
#endif

#ifndef CONFIG_UGOAL_TIMEOUT_MEDIA
# define CONFIG_UGOAL_TIMEOUT_MEDIA 1000
#endif

/**< enable support for instance handling.
 *
 * usually this is not required. beside that
 * this consumes some memory from the heap.
 * if the datamapper is used, this feature is
 * automatically enabled.
 */
#ifndef CONFIG_UGOAL_INSTANCE
# define CONFIG_UGOAL_INSTANCE 1
#endif

/**< enable basic RPC support */
#ifndef CONFIG_UGOAL_RPC
# define CONFIG_UGOAL_RPC 1
#endif

/**< if enabled main loop functions can be registered,
 * which allow cyclic execution of operations.
 * This required some memory for each registered function (typically 100 Bytes)
 */
#ifndef CONFIG_UGOAL_MAINLOOP_REG
# define CONFIG_UGOAL_MAINLOOP_REG 0
#endif

/**< disable logging */
#ifndef CONFIG_UGOAL_LOGGING
# define CONFIG_UGOAL_LOGGING 0
#endif

#ifndef GOAL_CONFIG_LOGGING
# define GOAL_CONFIG_LOGGING 0
#endif

#ifndef CONFIG_UGOAL_LOGGING_DBG
# define CONFIG_UGOAL_LOGGING_DBG 0
#endif

/**< configure the maximum size of a RPC request
 *
 * for simple fieldbus applications a value of 274
 * is sufficient, however it depends on the module sizes
 * to be handled.
 *
 * 274 bytes are required for a large DCP SetName request with a maximum
 * name length of 240 bytes.
 */
#ifndef CONFIG_UGOAL_RPC_RB_SIZE
# define CONFIG_UGOAL_RPC_RB_SIZE DEFAULT_UGOAL_RPC_RB_SIZE
#endif

/**< configure the maximum amount of requests to be able
 * to store in the RPC ring buffer.
 *
 * for simple fieldbus applications one entry is sufficient
 */
#ifndef CONFIG_UGOAL_RPC_RB_ENTRIES
# define CONFIG_UGOAL_RPC_RB_ENTRIES 1
#endif

/**< configure maximum number of RPC handles
 *
 */
#ifndef CONFIG_UGOAL_RPC_HANDLES
# define CONFIG_UGOAL_RPC_HANDLES 2
#endif

/**< disable automatic mapping of generic data provider
 *
 * application using the datamapper can map this data
 * explicetly. Only simple applications not using the
 * datamapper should set this option
 */
#ifndef GOAL_CONFIG_PNIO_MCTC_DP_AUTO
# define GOAL_CONFIG_PNIO_MCTC_DP_AUTO 0
#endif

/**< disable automatic mapping of APDU status
 *
 * application using the datamapper can map this data
 * explicetly.
 *
 * Generally this data is not required.
 */
#ifndef GOAL_CONFIG_PNIO_MCTC_APDU_AUTO
# define GOAL_CONFIG_PNIO_MCTC_APDU_AUTO 0
#endif

/**< disable EtherCAT ID (via I2C) support */
#ifndef GOAL_CONFIG_MEDIA_MA_ID
# define GOAL_CONFIG_MEDIA_MA_ID 0
#endif

/**< disable EtherCAT DC support */
#ifndef GOAL_CONFIG_MEDIA_MA_EVENT
# define GOAL_CONFIG_MEDIA_MA_EVENT 0
#endif

/**< disable NET support */
#ifndef UGOAL_WRAPPER_NET_MINIMAL
# define UGOAL_WRAPPER_NET_MINIMAL 0
#endif

/**< define endianess */
#ifndef CONFIG_UGOAL_BIG_ENDIAN
# define CONFIG_UGOAL_BIG_ENDIAN 0
#endif

#if CONFIG_UGOAL_BIG_ENDIAN == 1
# define _CPU_BIG_ENDIAN 1
#endif

#endif /* _UGOAL_DEFAULT_H_ */
