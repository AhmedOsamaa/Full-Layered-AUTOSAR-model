 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Ahmed Osama
 ******************************************************************************/

#include "Port.h"
#include "Port_Regs.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
 /* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif

#endif


STATIC uint8 PORT_Status = PORT_NOT_INITIALIZED;

/************************************************************************************
* Service Name: Port_Init
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to configuration set
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: function to initialise the port driver module
************************************************************************************/
void Port_Init(const Port_ConfigType* ConfigPtr)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* check if the input configuration pointer is not a NULL_PTR */
    if (NULL_PTR == ConfigPtr)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
            PORT_E_PARAM_CONFIG);
    }
    else
#endif
    {
        /*Set the port state equal to initialized*/
        PORT_Status = PORT_INITIALIZED;
        uint8 Port_current ; /*counter that will be used to loop over the structure*/
        for (Port_current = ZERO; Port_current < PORT_CONFIGURED_PINS; Port_current++)
        {
            /* The configuration structure for the current Port and Pin */
            Port_ConfigPin PinConfig = Port_PinConfiguration.pin[Port_current];
            Port_PinType Port_num = PinConfig.pin_num / NUMBER_OF_PINS;
            Port_PinType Pin_num =  PinConfig.pin_num % NUMBER_OF_PINS;

            volatile uint32* PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
            volatile uint32 delay = ZERO;

            switch (Port_num)
            {
            case  PORT_A: PortGpio_Ptr = (volatile uint32*)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                break;
            case  PORT_B: PortGpio_Ptr = (volatile uint32*)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                break;
            case  PORT_C: PortGpio_Ptr = (volatile uint32*)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                break;
            case  PORT_D: PortGpio_Ptr = (volatile uint32*)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                break;
            case  PORT_E: PortGpio_Ptr = (volatile uint32*)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                break;
            case  PORT_F: PortGpio_Ptr = (volatile uint32*)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                break;
            }
            /* Enable clock for PORT and allow time for clock to start*/
            SYSCTL_REGCGC2_REG |= (1 << Port_num);
            delay = SYSCTL_REGCGC2_REG;

            /*Ignore the Jtag pins PC[3-0]*/
            if ((PORT_C == Port_num) && (PORT_PIN_00 == Pin_num)
                || (PORT_C == Port_num) && (PORT_PIN_01 == Pin_num)
                || (PORT_C == Port_num) && (PORT_PIN_02 == Pin_num)
                || (PORT_C == Port_num) && (PORT_PIN_03 == Pin_num))
            {
                continue;
            }
            else if (((PORT_D == Port_num) && (PORT_PIN_07 == Pin_num))
                || ((PORT_F == Port_num) && (PORT_PIN_00 == Pin_num))) /* PD7 or PF0 */
            {
                /* Pointer is type-casted to be of 1 byte, a pointer to char (8 bits), so we can increment by 1s instead of 4s (it's former size)
                   then it's changed back to be 4 bits (32 bits) a pointer to int
                   */
                *(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */
                SET_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET), Pin_num);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
            }
            else
            {
                /* Do Nothing ... No need to unlock the commit register for this pin */
            }

            /*set the functionality of the port-pin according to the passed structure*/
            if (PORT_DIO_MODE == PinConfig.mode)
            {
                /*Set to normal DIO port-pin*/
                CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                /*Shifting by 4 is equivalent to shifting the F by one decimal place, for example pin 1 will shift to 0x000000F0 */
                *(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Pin_num * 4));     /* Clear the PMCx bits for this pin */


                SET_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Pin_num);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */

            }
            else if (PORT_ADC_MODE == PinConfig.mode)
            {
                /*Set to analog mode (ADC)*/
                CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Pin_num);        /* Clear the corresponding bit in the GPIODEN register to Disable digital functionality on this pin */
                CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                /*Shifting by 4 is equivalent to shifting the F by one decimal place, for example pin 1 will shift to 0x000000F0 */
                *(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Pin_num * 4));     /* Clear the PMCx bits for this pin */

                SET_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Pin_num);      /* Set the corresponding bit in the GPIOAMSEL register to set analog functionality on this pin */

            }
            /*For other alternative functions*/
            else
            {
                CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                SET_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Pin_num);             /* set Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */

                 /*Shifting by 4 is equivalent to shifting the F by one decimal place, for example pin 1 will shift to 0x000000F0 */
                *(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Pin_num * 4));     /* Clear the PMCx bits for this pin */

                *(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PinConfig.mode << (Pin_num * 4));      /* Set the PMCx bits for this pin to the selected Alternate function in the configuration structure passed */


                SET_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Pin_num);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */

            }



            /* Set the direction of the port-pin according to the passed structure*/
            if (PORT_PIN_OUT == PinConfig.direction)
            {
                SET_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Pin_num);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

                if (STD_HIGH == PinConfig.initial_value)
                {
                    SET_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_DATA_REG_OFFSET), Pin_num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                }
                else
                {
                    CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_DATA_REG_OFFSET), Pin_num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                }
            }
            else if (PORT_PIN_IN == PinConfig.direction)
            {
                CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

                if (PULL_UP == PinConfig.resistor)
                {
                    SET_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET), Pin_num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                }
                else if (PULL_DOWN == PinConfig.resistor)
                {
                    SET_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET), Pin_num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
                }
                else
                {
                    /*do nothing*/
                }
            }
            else
            {
                /* Do Nothing */
            }

        }
    }
}


/************************************************************************************
* Service Name: Port_SetPinDirection
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Port-Pin ID number (Pin)
*                  Port-Pin Direction (Direction)
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: function to set the Port Pin Direction
************************************************************************************/
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
{

    Port_ConfigPin PinConfig = Port_PinConfiguration.pin[Pin];
    Port_PinType Port_num = PinConfig.pin_num / NUMBER_OF_PINS;
    Port_PinType Pin_num = PinConfig.pin_num / NUMBER_OF_PINS;
  
    boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Driver is initialized before using this function */
    if (PORT_NOT_INITIALIZED == PORT_Status)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
            PORT_SET_PIN_DIRECTION_SID, PORT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
    /* Check if the used channel is within the valid range */
    if (PORT_CONFIGURED_PINS <= Pin)
    {

        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
            PORT_SET_PIN_DIRECTION_SID, PORT_E_PARAM_PIN);
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
    
    if (STD_OFF == PinConfig.adjustability_direction)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, 
            PORT_SET_PIN_DIRECTION_SID, PORT_E_DIRECTION_UNCHANGEABLE);
        error = TRUE;
    }
    else
    {
        /*Do nothing*/
    }
#endif

    /* In-case there are no errors */
    if (FALSE == error)
    {



        volatile uint32* PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
        /*Point to the */
        switch (Port_num)
        {
        case  PORT_A: PortGpio_Ptr = (volatile uint32*)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
            break;
        case  PORT_B: PortGpio_Ptr = (volatile uint32*)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
            break;
        case  PORT_C: PortGpio_Ptr = (volatile uint32*)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
            break;
        case  PORT_D: PortGpio_Ptr = (volatile uint32*)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
            break;
        case  PORT_E: PortGpio_Ptr = (volatile uint32*)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
            break;
        case  PORT_F: PortGpio_Ptr = (volatile uint32*)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
            break;
        }

        /* Set the direction of the port-pin according to the passed structure*/
        if (PORT_PIN_OUT == Direction)
        {
            SET_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Pin_num);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

        }
        else if (PORT_PIN_IN == Direction)
        {
            CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

        }
        else
        {
            /*Do nothing*/
        }
    }
    else
    {
        /* No Action Required */
    }

}
#endif

/************************************************************************************
* Service Name: Port_GetVersionInfo
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): version info - Pointer to where to store the version information of this module
* Return value: None
* Description: Return the version information of this module
************************************************************************************/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if input pointer is not Null pointer */
    if (NULL_PTR == versioninfo)
    {
        /* Report to DET  */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
            PORT_GET_VERSION_INFO_TYPE_SID, PORT_E_PARAM_POINTER);
    }
    else
#endif /* (DIO_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Copy the vendor Id */
        versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
        /* Copy the module Id */
        versioninfo->moduleID = (uint16)PORT_MODULE_ID;
        /* Copy Software Major Version */
        versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
        /* Copy Software Minor Version */
        versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
        /* Copy Software Patch Version */
        versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
    }
}
#endif

/************************************************************************************
* Service Name: Port_SetPinMode
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): Port Pin ID number
*                  New Port Pin mode to be set on port pin
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin mode
************************************************************************************/
#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
{
    boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Driver is initialized before using this function */
    if (PORT_NOT_INITIALIZED == PORT_Status)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
            PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
    /* Check if the used channel is within the valid range */
    if (PORT_CONFIGURED_PINS <= Pin)
    {

        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
            PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PIN);
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }
    if (OFF == Port_PinConfiguration.pin[Pin].adjustability_mode)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
            PORT_SET_PIN_MODE_SID, PORT_E_MODE_UNCHANGEABLE);
        error = TRUE;
    }
    else
    {
        /*Do nothing*/
    }
#endif

    /* In-case there are no errors */
    if (FALSE == error)
    {
        Port_ConfigPin PinConfig = Port_PinConfiguration.pin[Pin];
        Port_PinType Port_num = PinConfig.pin_num / NUMBER_OF_PINS;
        Port_PinType Pin_num = PinConfig.pin_num / NUMBER_OF_PINS;

        volatile uint32* PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
        /*Point to the */
        switch (Port_num)
        {
        case  PORT_A: PortGpio_Ptr = (volatile uint32*)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
            break;
        case  PORT_B: PortGpio_Ptr = (volatile uint32*)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
            break;
        case  PORT_C: PortGpio_Ptr = (volatile uint32*)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
            break;
        case  PORT_D: PortGpio_Ptr = (volatile uint32*)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
            break;
        case  PORT_E: PortGpio_Ptr = (volatile uint32*)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
            break;
        case  PORT_F: PortGpio_Ptr = (volatile uint32*)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
            break;
        }

        if (PORT_DIO_MODE == PinConfig.mode)
        {
            /*Set to normal DIO port-pin*/
            CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Pin_num);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
            /*Shifting by 4 is equivalent to shifting the F by one decimal place, for example pin 1 will shift to 0x000000F0 */
            *(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Pin_num * 4));     /* Clear the PMCx bits for this pin */


            SET_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Pin_num);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */

        }
        else if (PORT_ADC_MODE == PinConfig.mode)
        {
            /*Set to analog mode (ADC)*/
            CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Pin_num);        /* Clear the corresponding bit in the GPIODEN register to Disable digital functionality on this pin */
            CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Pin_num);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
            /*Shifting by 4 is equivalent to shifting the F by one decimal place, for example pin 1 will shift to 0x000000F0 */
            *(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Pin_num * 4));     /* Clear the PMCx bits for this pin */

            SET_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Pin_num);      /* Set the corresponding bit in the GPIOAMSEL register to set analog functionality on this pin */

        }
        /*For other alternative functions*/
        else
        {
            CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Pin_num);         /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            SET_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Pin_num);                  /* set Alternative function for this pin by setting the corresponding bit in GPIOAFSEL register */

             /*Shifting by 4 is equivalent to shifting the F by one decimal place, for example pin 1 will shift to 0x000000F0 */
            *(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Pin_num * 4));       /* Clear the PMCx bits for this pin */

            *(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PinConfig.mode << (Pin_num * 4));      /* Set the PMCx bits for this pin to the selected Alternate function in the configuration structure passed */


            SET_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Pin_num);               /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */

        }
    }
    else
    {
        /* No Action Required */
    }
}
#endif

/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Sync/Async: Synchronous
* Reentrancy: Non Reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refresh port direction
************************************************************************************/
void Port_RefreshPortDirection(void)
{
  boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if the Driver is initialized before using this function */
    if (PORT_NOT_INITIALIZED == PORT_Status)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
            PORT_REFRESH_PORT_DIRECTION_SID, PORT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /* No Action Required */
    }

#endif
    if(FALSE == error)
    {
      uint8 Port_current = ZERO; /*counter that will be used to loop over the structure*/
      for (; Port_current < PORT_CONFIGURED_PINS; Port_current++)
      {
          /* The configuration structure for the current Port and Pin */
          Port_ConfigPin PinConfig = Port_PinConfiguration.pin[Port_current];
          Port_PinType Port_num = PinConfig.pin_num / NUMBER_OF_PINS;
          Port_PinType Pin_num = PinConfig.pin_num % NUMBER_OF_PINS;
          
          volatile uint32* PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
          volatile uint32 delay = ZERO;

          switch (Port_num)
          {
          case  PORT_A: PortGpio_Ptr = (volatile uint32*)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
              break;
          case  PORT_B: PortGpio_Ptr = (volatile uint32*)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
              break;
          case  PORT_C: PortGpio_Ptr = (volatile uint32*)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
              break;
          case  PORT_D: PortGpio_Ptr = (volatile uint32*)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
              break;
          case  PORT_E: PortGpio_Ptr = (volatile uint32*)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
              break;
          case  PORT_F: PortGpio_Ptr = (volatile uint32*)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
              break;
          }
          /*Ignore the Jtag pins PC[3-0]*/
          if ((PORT_C == Port_num) && (PORT_PIN_00 == Pin_num)
              || (PORT_C == Port_num) && (PORT_PIN_01 == Pin_num)
              || (PORT_C == Port_num) && (PORT_PIN_02 == Pin_num)
              || (PORT_C == Port_num) && (PORT_PIN_03 == Pin_num))
          {
              continue;
          }
          else
          {
              /*Do nothing*/
          }
          if (STD_ON == PinConfig.adjustability_direction)
          {
              /* Set the direction of the port-pin according to the passed structure*/
              if (PORT_PIN_OUT == PinConfig.direction)
              {
                  SET_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Pin_num);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

                  if (STD_HIGH == PinConfig.initial_value)
                  {
                      SET_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_DATA_REG_OFFSET), Pin_num);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                  }
                  else
                  {
                      CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_DATA_REG_OFFSET), Pin_num);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                  }
              }
              else if (PORT_PIN_IN == PinConfig.direction)
              {
                  CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Pin_num);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

                  if (PULL_UP == PinConfig.resistor)
                  {
                      SET_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET), Pin_num);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                  }
                  else if (PULL_DOWN == PinConfig.resistor)
                  {
                      SET_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET), Pin_num);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
                  }
                  else
                  {
                      /*Do nothing*/
                  }
              }
              else
              {
                  /* Do Nothing */
              }
          }
          else
          {
              /*Do nothing*/
          }
      }
    }
}
  

