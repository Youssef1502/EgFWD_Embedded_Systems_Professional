/**==================================================
--    Author     :   YOUSSEF ADEL YOUSSEF
--  Description  :   Button Driver
==================================================**/


#ifndef BUTTON_H_
#define BUTTON_H_

/*
* ================================================================
*                         Reference Macros
* ================================================================
*/

#include "../LED/LED.h"
#include "../../MCAL/TIMER/TIMER.h"
#include "../../MCAL/INTERRUPT/INTERRUPT.h"


/* Enumeration Status */
typedef enum{
	BUTTON_RETURN_OK,
	BUTTIN_RETURN_ERROR
}EN_BUTTONStatus_t;

/********************************************************************************************************/

/*
* ================================================================
*           APIs Supported by "MCAL BUTTON DRIVER"
* ================================================================
*/



EN_BUTTONStatus_t BUTTON_Init(uint8 PortName, uint8 PinNum);
EN_BUTTONStatus_t BUTTON_Read(uint8 PortName, uint8 PinNum, uint8* Result);


#endif /* BUTTON_H_ */