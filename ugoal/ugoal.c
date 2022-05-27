/** @file
 *
 * @brief irj45 cyclic data functions
 *
 * This module provides helper functions to evaluate and generate valid
 * cyclic data for irj45 / mctc.
 *
 * @copyright
 * Copyright 2010-2018.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */

#include "goal_includes.h"
#include "goal_media/goal_mi_mctc.h"
#include "sapi/sapi.h"
#if CONFIG_UGOAL_DATAMAPPER == 1
# include "goal_media/goal_mi_dm.h"
#endif


/****************************************************************************/
/* Defines */
/****************************************************************************/
#define GOAL_TGT_BOARD_SPI_SIZE (128 - sizeof(GOAL_MI_MCTC_SPI_CYCLIC_T)) /**< SPI transfer size */
#define GOAL_TGT_BOARD_RPC_SIZE 50              /**< RPC transfer size */
#define GOAL_TGT_BOARD_RPC_POS  (GOAL_TGT_BOARD_SPI_SIZE - GOAL_TGT_BOARD_RPC_SIZE - 1) /**< RPC partition position */


/****************************************************************************/
/* Local variables */
/****************************************************************************/
static GOAL_MCTC_INST_T *pMctcInst;
extern MCTC_INST_T mctcInst;
#if CONFIG_UGOAL_MAINLOOP_REG == 1
static GOAL_MAIN_LOOP_T *pListLoop;
#endif
#if CONFIG_UGOAL_HEAP_BUFFER == 1
static uint8_t memArea[CONFIG_UGOAL_HEAP_BUFFER_SIZE];  /**< heap buffer */
static uint32_t memFreePtr;                     /**< heap buffer position */
#endif

#if CONFIG_UGOAL_DATAMAPPER == 1
static GOAL_MI_DM_T *mpMiDmRead;                /**< MI DM Read handle */
static GOAL_MI_DM_T *mpMiDmWrite;               /**< MI DM Write handle */
#endif

static uint32_t ledStates;                      /**< local led states */


#if CONFIG_UGOAL_HEAP_BUFFER == 0
/****************************************************************************/
/** Memory allocation function using calloc
 *
 */
GOAL_STATUS_T goal_memCalloc(
    void *ptr,                                  /**< data pointer */
    size_t size                                 /**< data length */
) {
    *((void **) ptr) = calloc(1, size);
    if ( *((void **) ptr) == NULL) {
        goal_logErr("failed to allocate %"FMT_u32" bytes", (uint32_t) size);
    }
    return *((void **) ptr) ? GOAL_OK : GOAL_ERR_ALLOC;
}
#else


/****************************************************************************/
/** Memory allocation function static buffer
 *
 */
GOAL_STATUS_T goal_memCalloc(
    void *ptr,                                  /**< data pointer */
    size_t size                                 /**< data length */
) {
    GOAL_STATUS_T res;                          /* result */

    if ((memFreePtr + size) >= CONFIG_UGOAL_HEAP_BUFFER_SIZE) {
        goal_logErr("failed to allocate %d bytes", size);
        *((void **) ptr) = NULL;
        res = GOAL_ERR_ALLOC;
    }
    else {
#if 0 != CONFIG_UGOAL_HEAP_BUFFER_ALIGNMENT
        /* apply alignment */
        if (0 != (memFreePtr % CONFIG_UGOAL_HEAP_BUFFER_ALIGNMENT)) {
            goal_logInfo("alignment correction");
        }
        memFreePtr += (memFreePtr % CONFIG_UGOAL_HEAP_BUFFER_ALIGNMENT);
#endif
        *((void **) ptr) = &memArea[memFreePtr];
        memFreePtr += size;
        res = GOAL_OK;
     }

    GOAL_LOG_DBG("allocated %d bytes", size);

    return res;
}
#endif


/****************************************************************************/
/** Setup RPC channels in data mapper
 *
 */
GOAL_STATUS_T som_init(
        void
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* return value */

    res = goal_queueBufferInit();
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to allocate buffers");
        return res;
    }

#if CONFIG_UGOAL_DATAMAPPER == 1
    /* create read instance */
    res = goal_miDmNew(&mpMiDmRead, GOAL_MI_MCTC_DIR_PEER_FROM, GOAL_TGT_BOARD_SPI_SIZE, "Read from CC");
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to create MI Dm Output instance");
        return res;
    }

    /* create write instance */
    res = goal_miDmNew(&mpMiDmWrite, GOAL_MI_MCTC_DIR_PEER_TO, GOAL_TGT_BOARD_SPI_SIZE, "Write to CC");
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to create MI Dm Input instance");
        return res;
    }
#endif

    /* we need to initialize MCTC here to enable send and receive */
    res = goal_miMctcOpen(&pMctcInst, GOAL_ID_DEFAULT);
    if (GOAL_RES_ERR(res)) {
        goal_logErr("failed to open MCTC SPI");
        return res;
    }

#if CONFIG_UGOAL_MAINLOOP_REG == 1
    if (GOAL_RES_OK(res)) {
        res = goal_mainLoopReg(sapi_loop);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_mainLoopParamReg((GOAL_FUNC_NORET_T) goal_miMctcRpcSyncLoop, pMctcInst->pPriv);
    }

    if (GOAL_RES_OK(res)) {
        res = goal_mainLoopParamReg(goal_miMctcRpcProcessLoop, pMctcInst->pPriv);
    }
#endif

    return res;
}


/****************************************************************************/
/** mctc loop function
 *
 */
void ugoal_loop(
        void
)
{
    static long long tsToutCyclic = 0;
#if CONFIG_UGOAL_MAINLOOP_REG == 1
    GOAL_MAIN_LOOP_T *pEntry;
#else
    static uint8_t flgSync;
    static uint8_t flgProcess;
    static uint8_t flgAppl;
    static uint8_t flgSapi;
#endif
#if CONFIG_UGOAL_DATAMAPPER == 1
    static uint8_t flgDatamapper;
#endif

    /* do each millisecond */
    if (plat_getMsTimer() > tsToutCyclic) {

        tsToutCyclic = plat_getMsTimer();

#if CONFIG_UGOAL_MAINLOOP_REG == 1
        GOAL_LL_FOREACH(pListLoop, pEntry) {
            if (0 == pEntry->flgExec) {
                pEntry->flgExec = 1;
                pEntry->pFunc(pEntry->pParam);
                pEntry->flgExec = 0;
            }
        }
#else
        /* send cyclic frame and put received RPC frame into ring buffer */
        if (0 == flgSapi) {
            flgSapi = 1;
            sapi_loop();
            flgSapi = 0;
        }

        /* process application */
        if (0 == flgAppl) {
            flgAppl = 1;
            appl_loop();
            flgAppl = 0;
        }

        /* process RPC sync */
        if (0 == flgSync) {
            flgSync = 1;
            goal_miMctcRpcSyncLoop(pMctcInst->pPriv);
            flgSync = 0;
        }

        /* process RPC request/response */
        if (0 == flgProcess) {
            flgProcess = 1;
            goal_miMctcRpcProcessLoop(pMctcInst->pPriv);
            flgProcess = 0;
        }
#endif

#if CONFIG_UGOAL_DATAMAPPER == 1
    if (0 == flgDatamapper) {
        flgDatamapper = 1;
        goal_miDmReadSync(mpMiDmRead, NULL);
        flgDatamapper = 0;
    }
#endif

#if CONFIG_UGOAL_RPC == 1
    plat_ledSet(ledStates);
#endif

    }
}


/****************************************************************************/
/** ugoal ok function
 *
 * This function is used for overloading unused functions from GOAL
 *
 */
GOAL_STATUS_T ugoal_ok(
    void
)
{
    return GOAL_OK;
}


/****************************************************************************/
/** optional memory allocation done indication for platforms
 *
 */
void GOAL_TARGET_WEAK plat_heapAllocDone(
    void
)
{
}


/****************************************************************************/
/** optional appl loop function
 *
 */
void GOAL_TARGET_WEAK appl_loop(
    void
)
{
}


/****************************************************************************/
/** memory allocation done indication
 *
 * This function is called when remote and local setup are done
 *
 */
void goal_memInitDone(
    void
)
{
#if CONFIG_UGOAL_HEAP_BUFFER == 1
    goal_logInfo("HEAP utilization: %"FMT_u32"/%"FMT_u32" (%"FMT_u32"%%).",
        (uint32_t) memFreePtr,
        (uint32_t) CONFIG_UGOAL_HEAP_BUFFER_SIZE,
        ((uint32_t) memFreePtr * 100) / (uint32_t) CONFIG_UGOAL_HEAP_BUFFER_SIZE);
#endif

    plat_heapAllocDone();
}


#if CONFIG_UGOAL_MAINLOOP_REG == 1
/****************************************************************************/
/** main loop registration function
 *
 * This function is called when remote and local setup are done
 *
 */GOAL_STATUS_T goal_mainLoopParamReg(
    GOAL_FUNC_NORET_T pFunc,              /**< loop function */
    void *pParam                                /**< function parameters */
)
{
    GOAL_MAIN_LOOP_T *pEntry;                   /* main loop entry */
    GOAL_STATUS_T res;                          /* result */

    /* allocate loop element */
    res = goal_memCalloc(&pEntry, sizeof(GOAL_MAIN_LOOP_T));
    if (GOAL_RES_ERR(res)) {
        goal_logInfo("failed to allocate main loop element");
        return res;
    }

    /* assign loop element data */
    pEntry->pFunc = pFunc;
    pEntry->pParam = pParam;

    GOAL_LL_APPEND(pListLoop, pEntry);

    return res;
}
#endif


/****************************************************************************/
/** LED open function
 *
 */
GOAL_STATUS_T goal_maLedOpen(
    uint32_t id,                                /**< MA id */
    GOAL_MA_LED_T **ppMaLed                     /**< [out] MA handle */
)
{
    UNUSEDARG(id);
    UNUSEDARG(ppMaLed);

    return GOAL_OK;
}


/****************************************************************************/
/** LED set function
 *
 */
GOAL_STATUS_T goal_maLedSet(
    GOAL_MA_LED_T *pMaLed,                      /**< MA handle */
    uint32_t led,                               /**< led id */
    GOAL_MA_LED_STATE_T state                   /**< led state */
)
{
    UNUSEDARG(pMaLed);
    irj45_setLedState(&ledStates, led, state);

    return GOAL_OK;
}


/****************************************************************************/
/** Open an EVENT MA
 *
 * @retval GOAL_OK successful
 * @retval GOAL_ERR_NULL_POINTER notify handler was null
 * @retval other failed
 */
GOAL_STATUS_T goal_maEventOpen(
    uint32_t id,                                /**< id of EVENT handler to use */
    GOAL_MA_EVENT_T **ppEventHdl,               /**< pointer to store EVENT handler */
    GOAL_BOOL_T flgAutoStart,                   /**< auto start of event generation */
    GOAL_MA_EVENT_NOTIFY fNotify                /**< notify callback */
)
{
    GOAL_STATUS_T res = GOAL_OK;                /* return value */

    UNUSEDARG(id);
    UNUSEDARG(ppEventHdl);

    /* Invoke open function */
    res = plat_eventRegister(flgAutoStart, fNotify);
    if (GOAL_RES_ERR(res)) {
        return res;
    }

    return res;
}


/****************************************************************************/
/** Enable event generation
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_maEventEnable(
    GOAL_MA_EVENT_T *pEventHdl                  /**< MA handle for EVENT */
)
{
    UNUSEDARG(pEventHdl);

    /* enable event */
    return plat_eventEnable();
}


/****************************************************************************/
/** Disable event generation
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_maEventDisable(
    GOAL_MA_EVENT_T *pEventHdl                  /**< MA handle for EVENT */
)
{
    UNUSEDARG(pEventHdl);

    /* disable event */
    return plat_eventDisable();
}


#if GOAL_CONFIG_MEDIA_MA_ID == 1
/****************************************************************************/
/** Open a ID MA
 *
 * this function just the platform initialization function for id switch
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_maIdOpen(
    uint32_t id,                                /**< id of ID handler to use */
    GOAL_MA_ID_T **ppIdHdl                      /**< pointer to store ID handler */
)
{
    UNUSEDARG(id);
    UNUSEDARG(ppIdHdl);

    return plat_idInit();
}


/****************************************************************************/
/** Get an ID
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_maIdGet(
    GOAL_MA_ID_T *pIdHdl,                       /**< MA handle for ID */
    uint32_t *pId                               /**< [out] id value */
)
{
    UNUSEDARG(pIdHdl);

    return plat_idGet(pId);
}
#endif


#ifdef APPL_STANDALONE
/****************************************************************************/
/** Main function
 *
 */
int main() {
    plat_init();
    som_init();
    appl_init();
    while (1) { 
        ugoal_loop();
    }
}
#endif
