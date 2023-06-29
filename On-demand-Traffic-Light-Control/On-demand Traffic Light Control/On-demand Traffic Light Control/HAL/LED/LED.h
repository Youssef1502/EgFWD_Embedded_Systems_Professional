/**==================================================
--    Author     :   YOUSSEF ADEL YOUSSEF
--  Description  :   Led Driver
==================================================**/


#ifndef LED_H_
#define LED_H_

/*
* ================================================================
*                         Reference Macros
* ================================================================
*/

#include "../../MCAL/DIO/DIO.h"


/* Enumeration Status */
typedef enum{
	LED_RETURN_OK,
	LED_RETURN_ERROR
}EN_LEDStatus_t;

/********************************************************************************************************/

/*
* ================================================================
*           APIs Supported by "MCAL LED DRIVER"
* ================================================================
*/

EN_LEDStatus_t LED_Init(uint8 PortName, uint8 PinNum);
EN_LEDStatus_t LED_On(uint8 PortName, uint8 PinNum);
EN_LEDStatus_t LED_Off(uint8 PortName, uint8 PinNum);
EN_LEDStatus_t LED_Toggle(uint8 PortName, uint8 PinNum);



#endif /* LED_H_ */