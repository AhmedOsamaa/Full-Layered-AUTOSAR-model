 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Ahmed Osama
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

/*  ID for the AUTOSAR company 
 *  In this case my ID will be = 1000*/
#define PORT_VENDOR_ID   (1000U)

/*  PORT MODULE ID   */
#define PORT_MODULE_ID (15U)

/*  PORT INSTANCE ID  */
#define PORT_INSTANCE_ID    (0U)

/*
 *  Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION       (1U)
#define PORT_SW_MINOR_VERSION       (0U)
#define PORT_SW_PATCH_VERSION       (0U)

/* 
 *  AUTOSAR VERSION 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/* 
 *  Macros for PORT status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/*include Standard AUTOSAR types*/
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Dio.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Port_Cfg.h does not match the expected version"
#endif


/* Software Version checking between Dio_Cfg.h and Dio.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
#error "The SW version of Dio_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"

/* ARRAY OF STRCUTURES[43 - 4 = 39]
     STRUCTURE CONTAINS 8 PARAMETERS
*/

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for port initialise funciton */
#define PORT_INIT_SID                         (uint8)0x00

/* Service ID for Set pin direction function */
#define PORT_SET_PIN_DIRECTION_SID            (uint8)0x01

/* Service ID for Refresh Port Direction function */
#define PORT_REFRESH_PORT_DIRECTION_SID       (uint8)0x02

/* Service ID for Port Get version info function */
#define PORT_GET_VERSION_INFO_TYPE_SID        (uint8)0x03

/* Service ID for Port Get Pin Mode function */
#define PORT_SET_PIN_MODE_SID                 (uint8)0x04


/*******************************************************************************
 *                            DET Error Codes                                  *
 *******************************************************************************/

/*  Invalid Port Pin ID requested   */
#define PORT_E_PARAM_PIN                  (uint8)0x0A

/*  Port Pin not configured as changeable   */
#define PORT_E_DIRECTION_UNCHANGEABLE     (uint8)0x0B  

/*  API Port_init service called with wrong parameter   */
#define PORT_E_PARAM_CONFIG               (uint8)0x0C

/*  API Port_SetPinMode service called with invalid mode    */
#define PORT_E_PARAM_INVALID_MODE         (uint8)0x0D

/*  API Port_SetPinMode service called when mode is unchangeable    */
#define PORT_E_MODE_UNCHANGEABLE          (uint8)0x0E

/*  API service called without module initization    */
#define PORT_E_UNINIT                     (uint8)0x0F

/*  APIs called with a Null pointer     */
#define PORT_E_PARAM_POINTER              (uint8)0x10

/*******************************************************************************
 *                            Module Data Types                                *
 *******************************************************************************/

/* Description: uint8 to hold the number of the PORT */
typedef uint8 Port_PortType;

/* Description: uint8 to hold the number of the PIN */
typedef uint8 Port_PinType;

/* Description: uint8 to hold initial value of the pin when used for DIO   */
typedef enum 
{
    PORT_PIN_LOW,
    PORT_PIN_HIGH
}Port_LevelInitVal;

/* Description: enum to hold the Port Pin level val from Port Pin list*/
typedef enum
{
    PORT_PIN_LEVEL_LOW,
    PORT_PIN_LEVEL_HIGH
}Port_PinLevelValue;

/* Description: Enum to hold PIN direction  */
typedef enum
{
    PORT_PIN_IN,
    PORT_PIN_OUT
}Port_PinDirectionType;

/* Description: enum to hold the mode of the PIN   */
typedef uint8 Port_PinModeType;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,
    PULL_UP,
    PULL_DOWN
}Port_InternalResistor;

/* Parameter to indicate if the mode is changeable on a port pin during runtime.  */
typedef uint8 Port_PinModeChangeable;

/* Parameter to indicate if the Direction is changeable on a port pin during runtime.  */
typedef uint8 Port_PinDirectionChangeable;


/* Description: Structure to configure each individual PIN:
 *	1. the number of the pin abd the PORT: PORT_PA0.
 *  2. the direction of pin --> INPUT or OUTPUT
 *  3. the internal resistor --> Disable, Pull up or Pull down
 *  4. the initial level of the Pin
 *  5. the mode of the pin
 *  6. the pin mode chandeability of the pin
 */
typedef struct 
{ 
    Port_PinType pin_num;                                    /* Port/Pin number: PORT_PA0, PORT_PB3....*/
    Port_PinDirectionType direction;                         /* Pin Direction: input, output*/
    Port_InternalResistor resistor;                          /* incase of input: Pullup / Pulldown resistor*/
    Port_LevelInitVal initial_value;                         /* incase of output: initial value*/
    Port_PinModeType mode;                                   /* Pin mode: GPIO, ADC, CAN....*/
    Port_PinModeChangeable adjustability_mode;               /* Pin mode is adjustable or not*/
    Port_PinDirectionChangeable adjustability_direction;     /* Pin Direction is adjustable or not*/
}Port_ConfigPin;

/* Structure passed to the initialisation function */
typedef struct
{
    /* array of pointers to the pin configuration structure */
    Port_ConfigPin pin[PORT_CONFIGURED_PINS];
}Port_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* Function to initialise the Port Driver module*/
void Port_Init(const Port_ConfigType* ConfigPtr);

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
/* Function to set the port's pin direction */
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);
#endif

/* Function to refresh port direction */
void Port_RefreshPortDirection(void);

#if (PORT_VERSION_INFO_API == STD_ON)
/* Function to return the version information on this module */
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo);
#endif

#if (PORT_SET_PIN_MODE_API == STD_ON)
/* Function to set the port pin mode */
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType);
#endif

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

 /* Extern PB structures to be used by Dio and other modules */
extern const Port_ConfigType Port_PinConfiguration;


/*******************************************************************************
 *                       Port Definitions                                      *
 *******************************************************************************/


#define PORT_PA0                        (0U)
#define PORT_PA1                        (1U)
#define PORT_PA2                        (2U)
#define PORT_PA3                        (3U)
#define PORT_PA4                        (4U)
#define PORT_PA5                        (5U)
#define PORT_PA6                        (6U)
#define PORT_PA7                        (7U)
#define PORT_PB0                        (8U)
#define PORT_PB1                        (9U)
#define PORT_PB2                        (10U)
#define PORT_PB3                        (11U)
#define PORT_PB4                        (12U)
#define PORT_PB5                        (13U)
#define PORT_PB6                        (14U)
#define PORT_PB7                        (15U)
#define PORT_PC0                        (16U)
#define PORT_PC1                        (17U)
#define PORT_PC2                        (18U)
#define PORT_PC3                        (19U)
#define PORT_PC4                        (20U)
#define PORT_PC5                        (21U)
#define PORT_PC6                        (22U)
#define PORT_PC7                        (23U)
#define PORT_PD0                        (24U)
#define PORT_PD1                        (25U)
#define PORT_PD2                        (26U)
#define PORT_PD3                        (27U)
#define PORT_PD4                        (28U)
#define PORT_PD5                        (29U)
#define PORT_PD6                        (30U)
#define PORT_PD7                        (31U)
#define PORT_PE0                        (32U)
#define PORT_PE1                        (33U)
#define PORT_PE2                        (34U)
#define PORT_PE3                        (35U)
#define PORT_PE4                        (36U)
#define PORT_PE5                        (37U)
#define PORT_PF0                        (40U)
#define PORT_PF1                        (41U)
#define PORT_PF2                        (42U)
#define PORT_PF3                        (43U)
#define PORT_PF4                        (44U)


#define PORT_A                        (0U)
#define PORT_B                        (1U)
#define PORT_C                        (2U)
#define PORT_D                        (3U)
#define PORT_E                        (4U)
#define PORT_F                        (5U)
#define PORT_G                        (6U)

#define PORT_PIN_00                        (0U)
#define PORT_PIN_01                        (1U)
#define PORT_PIN_02                        (2U)
#define PORT_PIN_03                        (3U)
#define PORT_PIN_04                        (4U)
#define PORT_PIN_05                        (5U)
#define PORT_PIN_06                        (6U)
#define PORT_PIN_07                        (7U)

/*******************************************************************************
 *                       Port Functions                                        *
 *******************************************************************************/

#define PORT_DIO_MODE                    (0U)
#define PORT_ALTERNATIVE_FUNCTION_01     (1U)
#define PORT_ALTERNATIVE_FUNCTION_02     (2U)
#define PORT_ALTERNATIVE_FUNCTION_03     (3U)
#define PORT_ALTERNATIVE_FUNCTION_04     (4U)
#define PORT_ALTERNATIVE_FUNCTION_05     (5U)
#define PORT_ALTERNATIVE_FUNCTION_06     (6U)
#define PORT_ALTERNATIVE_FUNCTION_07     (7U)
#define PORT_ALTERNATIVE_FUNCTION_08     (8U)
#define PORT_ALTERNATIVE_FUNCTION_09     (9U)
#define PORT_ALTERNATIVE_FUNCTION_10     (10U)
#define PORT_ALTERNATIVE_FUNCTION_11     (11U)
#define PORT_ALTERNATIVE_FUNCTION_12     (12U)
#define PORT_ALTERNATIVE_FUNCTION_13     (13U)
#define PORT_ALTERNATIVE_FUNCTION_14     (14U)
#define PORT_ADC_MODE    (15U)




#endif /* PORT_H */
