 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller  - Port Driver.
 *
 * Author: Ahmed Osama
 ******************************************************************************/

#include "Port.h"

/*
* Module Version 1.0.0
*/
#define PORT_PBCFG_SW_MAJOR_VERSION       (1U)
#define PORT_PBCFG_SW_MINOR_VERSION       (0U)
#define PORT_PBCFG_SW_PATCH_VERSION       (0U)

/*
 *  AUTOSAR VERSION 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION   (3U)

 /* AUTOSAR Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
#error "The SW version of PBcfg.c does not match the expected version"
#endif

/* PB structure used with Port_Init API */
const Port_ConfigType Port_PinConfiguration = 
{
	/*Port A*/
	PORT_PA0, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
	PORT_PA1, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
    PORT_PA2, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
    PORT_PA3, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
    PORT_PA4, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
    PORT_PA5, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
    PORT_PA6, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
    PORT_PA7, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/

	/*Port B*/
	PORT_PB0, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
	PORT_PB1, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
	PORT_PB2, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
	PORT_PB3, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
	PORT_PB4, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
	PORT_PB5, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
	PORT_PB6, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
	PORT_PB7, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
        
	/*Port C*/
	PORT_PC0, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
	PORT_PC1, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
	PORT_PC2, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
	PORT_PC3, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
	PORT_PC4, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
	PORT_PC5, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
	PORT_PC6, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
	PORT_PC7, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/        

	/*Port D*/
	PORT_PD0, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
	PORT_PD1, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
	PORT_PD2, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
	PORT_PD3, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
	PORT_PD4, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
	PORT_PD5, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
	PORT_PD6, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
	PORT_PD7, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/    
        
	/*Port E*/
	PORT_PE0, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
    PORT_PE1, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
    PORT_PE2, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
    PORT_PE3, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
    PORT_PE4, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
    PORT_PE5, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
        

	/*Port F*/
	PORT_PF0, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
	PORT_PF1, PORT_PIN_OUT, OFF, PORT_PIN_LOW, PORT_DIO_MODE, STD_OFF, STD_OFF, /*LED*/
	PORT_PF2, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
	PORT_PF3, PORT_PIN_IN,PULL_DOWN, PORT_PIN_LOW, PORT_DIO_MODE, STD_ON, STD_ON, /*Default settings*/
	PORT_PF4, PORT_PIN_IN,PULL_UP, PORT_PIN_HIGH, PORT_DIO_MODE, STD_OFF, STD_OFF  /*SW*/
								 
};