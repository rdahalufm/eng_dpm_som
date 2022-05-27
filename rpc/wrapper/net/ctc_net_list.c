#include <goal_includes.h>
#include "ctc_net_list.h"


/****************************************************************************/
/** get id of given channel
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_drvCtcChannelId(
    GOAL_DRV_NET_CHANNEL_LIST_T *pListChan,     /**< channel list */
    GOAL_NET_CHAN_T *pChanHandle,               /**< channel handle */
    uint32_t *pId                               /**< [out] channel id */
)
{
    GOAL_STATUS_T res;                          /* result */
    GOAL_DRV_NET_CHANNEL_LIST_T *pEntry;        /* channel list entry */

    res = GOAL_ERR_NOT_FOUND;

    GOAL_LL_FOREACH(pListChan, pEntry) {
        if (pEntry->pChannel == pChanHandle) {
            *pId = pEntry->id;
            res = GOAL_OK;
            break;
        }
    }

    return res;
}


/****************************************************************************/
/** get list entry of given channel
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_drvCtcChannelEntry(
    GOAL_DRV_NET_CHANNEL_LIST_T *pListChan,     /**< channel list */
    GOAL_NET_CHAN_T *pChanHandle,               /**< channel handle */
    GOAL_DRV_NET_CHANNEL_LIST_T **ppEntry       /**< [out] channel list entry */
)
{
    GOAL_STATUS_T res;                          /* result */
    GOAL_DRV_NET_CHANNEL_LIST_T *pEntry;        /* channel list entry */

    res = GOAL_ERR_NOT_FOUND;

    GOAL_LL_FOREACH(pListChan, pEntry) {
        if (pEntry->pChannel == pChanHandle) {
            *ppEntry = pEntry;
            res = GOAL_OK;
            break;
        }
    }

    return res;
}


/****************************************************************************/
/** get channel of given id
 *
 * @retval GOAL_OK successful
 * @retval other failed
 */
GOAL_STATUS_T goal_drvCtcChannelEntryById(
    GOAL_DRV_NET_CHANNEL_LIST_T *pListChan,     /**< channel list */
    uint32_t id,                                /**< channel id */
    GOAL_DRV_NET_CHANNEL_LIST_T **ppEntry       /**< [out] channel list entry */
)
{
    GOAL_STATUS_T res;                          /* result */
    GOAL_DRV_NET_CHANNEL_LIST_T *pEntry;        /* channel list entry */

    res = GOAL_ERR_NOT_FOUND;

    GOAL_LL_FOREACH(pListChan, pEntry) {
        if (pEntry->id == id) {
            *ppEntry = pEntry;
            res = GOAL_OK;
            break;
        }
    }

    return res;
}
