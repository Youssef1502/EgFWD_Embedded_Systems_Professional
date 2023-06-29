/**==================================================
--    Author     :   YOUSSEF ADEL YOUSSEF
--  Description  :   Button Driver
==================================================**/

/*
* ================================================================
*                         Includes
* ================================================================
*/

#include "BUTTON.h"

/********************************************************************************************************/

/*
 * ================================================================
 *                    APIs Function Definitions
 * ================================================================
 */


/* Overflow Counter for TIMER0 */
extern uint8 Timer_OverFlow ;

// Declaring Extern Variables to be accessed by Timer Driver
extern uint8 Count;
extern uint8 First_Click;

/**================================================================
 * @Fun				- BUTTON_Init
 * @Brief 			- Set the BUTTON in the Input Mode
 * @Ret_Val 		- LED_Init_State
 * @Note			- None
 ===============================================================**/
EN_BUTTONStatus_t BUTTON_Init(uint8 PortName, uint8 PinNum)
{
	EN_BUTTONStatus_t BUTTON_Init_State = BUTTIN_RETURN_ERROR;
	
	DIO_Init(PortName , PinNum , IN);
	BUTTON_Init_State = BUTTIN_RETURN_ERROR;
	return BUTTON_Init_State;
}



/**================================================================
 * @Fun				- BUTTON_Read
 * @Brief 			- Read Button State from button port [ High / low ]. 
					  A variable must be passed to this function to save the reading state.
 * @Ret_Val 		- LED_Init_State
 * @Note			- None
 ===============================================================**/
EN_BUTTONStatus_t BUTTON_Read(uint8 PortName, uint8 PinNum, uint8* Result)
{
	EN_BUTTONStatus_t BUTTON_Read_State = BUTTIN_RETURN_ERROR;
	
	DIO_Read(PortName , PinNum , Result);
	BUTTON_Read_State = BUTTIN_RETURN_ERROR;
	return BUTTON_Read_State;
}


/**================================================================
 * @Fun				- External Interrupt [ Interrupt Service Routine ]
 * @Brief 			- This ISR refers to Work in pedestrian Mode
 * @Ret_Val 		- None
 * @Note			- None
 ===============================================================**/

ISR(EXT_INT_0)
{
	/* If the First_Click Flag is True (clicked) then the Button Interrupt Won't Do Anything. Thus, Eliminating Double-Click Effect */
	/* INT0 Work With Rising Edge so the Long Press Act as Normal Press */
	
	if(!First_Click)
	{
		/* Open Normal Mode Indication LED
		and Close pedestrian Indication LED */
		LED_Off(INDICATION_Light, Normal_Mode_pin);
		LED_On(INDICATION_Light, PED_Mode_Pin);
		
		/*
		If the Switch Pressed in Phase_1 [ During Car Green LED is Work After Green LED ] :
		Let Car Green Light Remaining Work Will PED Red Light is On
		and also Turn on Car Blink Yellow Light and PED Blink Yellow Light for 5 Sec
		Then Open Car Red Light and Open PED Green Light
		*/
		if(Count == phase_1)
		{
			Timer_OverFlow=20;
		}
		
		/*
		If the Switch Pressed in Phase_2 [ During Car Yellow LED is Work ] :
		Let Car Green Light Remaining Work Will PED Red Light is On
		Then Reset Car Blink Yellow Light to Work with PED Blink Yellow Light for 5 Sec from Beginning
		Then Open Car Red Light and Open PED Green Light
		*/
		else if(Count == phase_2)
		{
			
			// For Synchronous Two Yellow LEDS
			LED_Off(CAR_Light, LED_Yellow);
			LED_Off(PED_Light, LED_Yellow);
			
			TIMER0_Reset();
		}
		
		/*
		If the Switch Pressed in Phase_3 [ During Car Red LED is Work ] :
		Reset Car Red Light Time and also Open PED Green Light for 5 Sec
		*/
		else if(Count == phase_3)
		{
			TIMER0_Reset();
			LED_Off(PED_Light, LED_Red);
			LED_On(PED_Light, LED_Green);
		}
		
		// if pressed in phase_4 it skips cars blinking yellow light remaining wait time and go back to phase_2.
		// turning back the count variable to phase_2 reverses the flow of the cars light from (yellow to green) to (yellow to red) again.
		/*
		If the Switch Pressed in Phase_4 [ During Car Yellow LED is Work After Red LED ] :
		Let Car Blink Yellow Light Work After
		Reset Timer Overflow Value and Back to Phase 2
		Then Reverse the Flow of Car Lights from ( Yellow to Green ) to ( Yellow to Red )
		and also Open the PED Green Light during Car Red Light on
		*/
		else if(Count == phase_4)
		{
			Timer_OverFlow=20;
			Count = phase_2;
		}
		
		/* Set First_Click Variable to 1 Indicates Pedestrian Mode. It is Set Back to 0 When the 4 Phases are Complete */
		First_Click=1;
	}
}


