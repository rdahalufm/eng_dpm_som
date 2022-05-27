#include "goal_config.h"

#define GOAL_TARGET_PACKED_PRE
#define GOAL_TARGET_PACKED __attribute__((packed))
#define GOAL_TARGET_PACKED_STRUCT_PRE
#define GOAL_TARGET_PACKED_STRUCT_POST
#define GOAL_TARGET_FALLTHROUGH
#define GOAL_TARGET_INLINE inline
#define GOAL_TARGET_WEAK                  __attribute__((weak))

#define GOAL_NETBUF_SIZE 512

#define fseek(...)
#define ftell(...) -1
#define fopen(...) -1

#define CONFIG_UGOAL_HEAP_BUFFER 1
#define CONFIG_UGOAL_HEAP_BUFFER_SIZE 7000



//#if CONFIG_UGOAL_LOGGING == 1
//
//#define GOAL_LOG_INFO(format, ...) {\
//    printf("[INF] %S:%d ", __FILE__, __LINE__); \
//    printf(format, ##__VA_ARGS__); \
//    printf("\n"); \
//}
//
//#define GOAL_LOG_ERR(format, ...) {\
//    printf("[ERR] %S:%d ", __FILE__, __LINE__); \
//    printf(format, ##__VA_ARGS__); \
//    printf("\n"); \
//}
//
//#define GOAL_LOG_WARN(format, ...) {\
//    printf("[WARN] %S:%d ", __FILE__, __LINE__); \
//    printf(format, ##__VA_ARGS__); \
//    printf("\n"); \
//}

#if CONFIG_UGOAL_LOGGING == 1

#define GOAL_LOG_INFO(format, ...) {\
    printf("[INF] %s:%u ", __FILE__, __LINE__); \
    printf(format, ##__VA_ARGS__); \
    printf("\n"); \
}

#define GOAL_LOG_ERR(format, ...) {\
    printf("[ERR] %s:%u ", __FILE__, __LINE__); \
    printf(format, ##__VA_ARGS__); \
    printf("\n"); \
}

#define GOAL_LOG_WARN(format, ...) {\
    printf("[WARN] %s:%u ", __FILE__, __LINE__); \
    printf(format, ##__VA_ARGS__); \
    printf("\n"); \
}


#endif

