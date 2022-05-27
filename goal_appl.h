/** @file
 *
 * @brief GOAL Application Configuration File
 *
 * This file controls various components and settings of the Generic Open
 * Abstraction Layer (GOAL).
 *
 * For details see chapter "Build Configuration" in the documentation.
 *
 * @copyright
 * Copyright 2010-2020 port GmbH Halle/Saale.
 * This software is protected Intellectual Property and may only be used
 * according to the license agreement.
 */

#ifndef GOAL_APPL_CONFIG_H
#define GOAL_APPL_CONFIG_H


/* set identification of the slave */
#ifndef APPL_DD_CUSTOMER_ID
# define APPL_DD_CUSTOMER_ID 0x00000001         /**< customer id */
#endif

#ifndef APPL_DD_MODULE
# define APPL_DD_MODULE ccm_demo                /**< module name */
#endif

#ifndef APPL_PNIO_VENDOR_ID
# define APPL_PNIO_VENDOR_ID 0x02c7             /**< vendor id */
#endif

#ifndef APPL_PNIO_DEVICE_ID
# define APPL_PNIO_DEVICE_ID 0x0300            /**< device id */
#endif

#ifndef APPL_PNIO_VENDOR
# define APPL_PNIO_VENDOR Renesas Electronics          /**< vendor name */
#endif

#define QUOTE(name) #name
#define STRING(macro) QUOTE(macro)

#define APPL_PNIO_VENDOR_NAME STRING(APPL_PNIO_VENDOR)
#define APPL_DD_MODULE_NAME STRING(APPL_DD_MODULE)

#define APPL_DD_FEATURES    GOAL_DD_FEAT_ALL    /**< enabled features of dd */

#endif /* GOAL_APPL_CONFIG_H */
