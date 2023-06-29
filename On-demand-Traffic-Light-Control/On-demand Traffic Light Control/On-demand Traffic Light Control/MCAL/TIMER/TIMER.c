/**==================================================
--    Author     :   YOUSSEF ADEL YOUSSEF
--  Description  :   Timer Driver
==================================================**/

/*
* ================================================================
*                         Includes
* ================================================================
*/

#include "TIMER.h"

/********************************************************************************************************/


/* Overflow Counter for TIMER0 */
uint8 Timer_OverFlow;

// Declaring Extern Variables to be accessed by Timer Driver
extern uint8 Count;
extern uint8 First_Click;

// Pointer to Function to Save the Address of the Function Passed to CALLBACK FUNCTION
void static (*Callback_Ptr)(uint8 PortName, uint8 PinNum);

// CALLBACK FUNCTION that Takes the Address of Toggle Function from Upper Layers and Execute it in timer0 Overflow to Blink Yellow Lights
void setcallback(void (*cbvar)(uint8 PortName , uint8 PinNum))
{
	Callback_Ptr = cbvar;
}


/*
 * ================================================================
 *                    APIs Function Definitions
 * ================================================================
 */

/**================================================================
 * @Fun				- TIMER0_Init
 * @Brief 			- Initialize TIMER0
 * @Ret_Val 		- TIMER0_Init_State
 * @Note			- None
 ===============================================================**/

EN_TIMERStatus_t TIMER0_Init()
{
	EN_TIMERStatus_t TIMER0_Init_State = TIMER_RETURN_ERROR;
	/* Select Normal Mode */
	Clear_Pin(TCCR0, 3);
	Clear_Pin(TCCR0, 6);
	
	TIMER0_Set_Initial_Value(Init_Value);
	
	TIMER0_Init_State = TIMER_RETURN_ERROR;
	
	return TIMER0_Init_State;
}


/**================================================================
 * @Fun				- TIMER0_Set_Initial_Value
 * @Brief 			- Set Timer/Counter Register Value
 * @Ret_Val 		- TIMER0_Set_Initial_Value_state
 * @Note			- None
 ===============================================================**/

EN_TIMERStatus_t TIMER0_Set_Initial_Value(uint8 Val)
{
	EN_TIMERStatus_t TIMER0_Set_Initial_Value_state = TIMER_RETURN_ERROR;
	TCNT0 = Val;
	
	TIMER0_Set_Initial_Value_state = TIMER_RETURN_ERROR;
	return TIMER0_Set_Initial_Value_state;
}


/**================================================================
 * @Fun				- TIMER0_Stop
 * @Brief 			- Stop TIMER0
 * @Ret_Val 		- TIMER0_Stop_State
 * @Note			- None
 ===============================================================**/

EN_TIMERStatus_t TIMER0_Delay()
{
	EN_TIMERStatus_t TIMER0_Delay_State = TIMER_RETURN_ERROR;
	
	/* Set Configuration to Start TIMER0 */
	/* Set Clock Selection by 1024 Prescaler */
	Set_Pin(TCCR0,0);
	Set_Pin(TCCR0,2);
		
	/* Waiting the Overflow Counter to Become 20 */
	while(Timer_OverFlow <20);
	
	
	/* Set Configuration to Stop TIMER0 */
	/* Set Control Register to 0 (No Prescaler) to Stop the Timer */
	TCCR0 = 0;
		
	/* Reset Overflow Counter */
	Timer_OverFlow = 0;
	
	TIMER0_Delay_State = TIMER_RETURN_OK;
	return TIMER0_Delay_State;
}


/**================================================================
 * @Fun				- TIMER0_Reset
 * @Brief 			- Reset All Values for TIMER0
 * @Ret_Val 		- TIMER0_Reset_State
 * @Note			- None
 ===============================================================**/

EN_TIMERStatus_t TIMER0_Reset()
{
	EN_TIMERStatus_t TIMER0_Reset_State = TIMER_RETURN_ERROR;
	
	TIMER0_Set_Initial_Value(Init_Value);
	Timer_OverFlow = 0; 
	
	TIMER0_Reset_State = TIMER_RETURN_OK;
	return TIMER0_Reset_State;
}



/**================================================================
 * @Fun				- TIMER0 ISR
 * @Brief 			- TIMER0 Interrupt Service Routine
 * @Ret_Val 		- None
 * @Note			- None
 ===============================================================**/

ISR(TIMER0_OVF)
{
	/* Reset Initial Value to begin Count Again in the Next Timer Cycle */
	TIMER0_Set_Initial_Value(Init_Value);
	
	/* Incrementing Overflow Variable */
	Timer_OverFlow++;
	
	/* Blinking Yellow Lights Only in Phase_2 and Phase_4 */
	if(Count== phase_2 || Count == phase_4)
	{
		/* Only Blink Cars Yellow light in normal Mode */
		if(!First_Click)
		{
			Callback_Ptr(CAR_Light, LED_Yellow);
		}
		/* Blink Both Car and PED Yellow Lights in Pedestrian Mode */
		else if(First_Click)
		{
			Callback_Ptr(CAR_Light, LED_Yellow);
			Callback_Ptr(PED_Light, LED_Yellow);
		}
	}
}