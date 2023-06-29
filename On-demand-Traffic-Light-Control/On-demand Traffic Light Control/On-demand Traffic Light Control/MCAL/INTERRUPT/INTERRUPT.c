/**==================================================
--    Author     :   YOUSSEF ADEL YOUSSEF
--  Description  :   Interrupt Driver
==================================================**/


/*
* ================================================================
*                         Includes
* ================================================================
*/

#include "INTERRUPT.h"

/********************************************************************************************************/

/*
 * ================================================================
 *                    APIs Function Definitions
 * ================================================================
 */

/**================================================================
 * @Fun				- External_INT0_Init
 * @Brief 			- Initialize External Interrupt
 * @Ret_Val 		- INTERRUPT_Init_State
 * @Note			- None
 ===============================================================**/

EN_INTERRUPTStatus_t External_INT0_Init()
{
	EN_INTERRUPTStatus_t INTERRUPT_Init_State = INTERRUPT_RETURN_ERROR;
	
	/* Disable Global interrupts by clearing I-bit */
	//Clear_Pin(SREG , 7);
	
	/* Trigger INT0 with Falling Edge */
	Clear_Pin(MCUCR , 0);
	Set_Pin(MCUCR , 1);
	
	/* External Interrupt Request 0 Enable */
	Set_Pin(GICR , 6);
	
	/* Global Interrupt Enable */
	Set_Pin(SREG , 7);
	
	INTERRUPT_Init_State = INTERRUPT_RETURN_OK;
	
	return INTERRUPT_Init_State;
}


/**================================================================
 * @Fun				- TIMER0_INTERRUPT_Init
 * @Brief 			- Initialize TIMER0 Interrupt
 * @Ret_Val 		- TIMER0_INTERRUPT_Init_State
 * @Note			- None
 ===============================================================**/

EN_INTERRUPTStatus_t TIMER0_INTERRUPT_Init()
{		
	EN_INTERRUPTStatus_t TIMER0_INTERRUPT_Init_State = INTERRUPT_RETURN_ERROR;
	
	/* Enable TIMER0 Overflow Interrupt */
	Set_Pin(TIMSK, 0);
	
	TIMER0_INTERRUPT_Init_State = INTERRUPT_RETURN_OK;
	return TIMER0_INTERRUPT_Init_State;
}
