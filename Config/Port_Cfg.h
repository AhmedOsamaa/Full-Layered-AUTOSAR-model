 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Configuration header for Port module.
 *
 * Author: Ahmed Osama
 ******************************************************************************/

#ifndef PORT_CFG_H
#define PORT_CFG_H

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT                (STD_ON)

/* Pre-compile option for Version Info API */
#define PORT_VERSION_INFO_API                (STD_ON)
   
/*Pre-compile option for enabling set pin direction function API*/
#define PORT_SET_PIN_DIRECTION_API            (STD_ON)

/*Pre-compile option for enabling set pin mode API*/   
#define PORT_SET_PIN_MODE_API                  (STD_ON)

/* Number of configured PINs*/
#define PORT_CONFIGURED_PINS		        (45U)
   

/*Number of Pins Per Port*/
#define NUMBER_OF_PINS				(8U)




#endif /* PORT_CFG_H */
