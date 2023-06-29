/**==================================================
--    Author     :   YOUSSEF ADEL YOUSSEF
--  Description  :   Timer Driver
==================================================**/


#ifndef TIMER_H_
#define TIMER_H_

/*
* ================================================================
*                         Includes
* ================================================================
*/

#include "../../Utilities/Memory_Map.h"
#include "../../Utilities/Common_Macros.h"
#include "../../Utilities/Std_Types.h"

/********************************************************************************************************/

/*
* ================================================================
*                         Reference Macros
* ================================================================
*/

#define Init_Value	11

#define TIMER0_OVF		__vector_11

//ISR macro
#define ISR(INT_VECT) \
void INT_VECT(void) __attribute__((signal,used));\
void INT_VECT(void)

/* Enumeration Status */
typedef enum{
	TIMER_RETURN_OK,
	TIMER_RETURN_ERROR
}EN_TIMERStatus_t;

/********************************************************************************************************/

/*
* ================================================================
*           APIs Supported by "MCAL TIMER DRIVER"
* ================================================================
*/


EN_TIMERStatus_t TIMER0_Init();
EN_TIMERStatus_t TIMER0_Set_Initial_Value(uint8 Val);
EN_TIMERStatus_t TIMER0_Delay();
EN_TIMERStatus_t TIMER0_Reset();


// CALLBACK FUNCTION to Access LED_Toggle function from Upper Layer (HAL)
void setcallback(void (*cbvar)(uint8 PortName , uint8 PinNum));

#endif /* TIMER_H_ */