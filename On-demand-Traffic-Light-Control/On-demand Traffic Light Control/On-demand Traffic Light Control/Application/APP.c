/**==================================================
--    Author     :   YOUSSEF ADEL YOUSSEF
--  Description  :   Application
==================================================**/

/*
* ================================================================
*                   General Macro Switching
* ================================================================
*/

#define Main_Mode
//#define Testing_Mode

/*
* ================================================================
*                         Includes
* ================================================================
*/

#include "APP.h"

/********************************************************************************************************/

/*
 * ================================================================
 *                    APIs Function Definitions
 * ================================================================
 */


/* Count Variable Used to Track Program Execution from phase_1 to phase_4. 
Initial Count Value at phase_1 */
uint8 Count = phase_1;

/* First Click Flag holds [0] When Work in Normal Mode
   and Holds [1] When Work in pedestrian Mode*/
uint8 First_Click=0;


/**================================================================
 * @Fun				- APP_init
 * @Brief 			- This Function Initialize All the System Drivers
 * @Ret_Val 		- LED_Init_State
 * @Note			- None
 ===============================================================**/

EN_APPStatus_t APP_init(void)
{
#ifdef Main_Mode

	EN_APPStatus_t APP_init_State = APP_RETURN_ERROR;
	
	/* Initialize Button Pin from Button Port as Input */
	BUTTON_Init(BUTTON_port, BUTTON_pin);
	
	/* Initialize All LEDs Pins from LEDs Port as Output */
	LED_Init(CAR_Light, LED_Green);
	LED_Init(CAR_Light, LED_Yellow);
	LED_Init(CAR_Light, LED_Red);
	LED_Init(PED_Light, LED_Green);
	LED_Init(PED_Light, LED_Yellow);
	LED_Init(PED_Light, LED_Red);
	
	/* Initialize All LEDs Pins from INDICATION_Light Port as Output */
	LED_Init(INDICATION_Light, Normal_Mode_pin);
	LED_Init(INDICATION_Light, PED_Mode_Pin);
	
	/* Initialize TIMER0 */
	TIMER0_Init();
	
	/* Initialize TIMER0 Interrupt */
	TIMER0_INTERRUPT_Init();
	
	/* Initialize External Interrupt */
	External_INT0_Init();
	
	/* Passing LED Toggle Function to Operate in Timer Driver [ TIMER MCAL ] */
	setcallback(LED_Toggle);
	
	APP_init_State = APP_RETURN_OK;
	return APP_init_State;
	
#endif
}


/**================================================================
 * @Fun				- APP_start
 * @Brief 			- This Function Which the Program Start Execution
 * @Ret_Val 		- APP_start_State
 * @Note			- None
 ===============================================================**/

EN_APPStatus_t APP_start(void)
{	
#ifdef Main_Mode
	EN_APPStatus_t APP_start_State = APP_RETURN_ERROR;
	
	/* This Function Refers to Work in Normal Mode */
	
	/**********************       Phase 1       **********************/
	
	if(Count == phase_1)
	{
		/* Open Normal Mode Indication LED
		and Close pedestrian Indication LED */
		LED_On(INDICATION_Light, Normal_Mode_pin);
		LED_Off(INDICATION_Light, PED_Mode_Pin);
			
		/* Phase 1 Begin with 
		Car Green LED is On
		and PED Red LED is Off */
		LED_On(CAR_Light, LED_Green);
		LED_On(PED_Light, LED_Red);
		
		/* This Function Start a 5 Seconds Delay */
		TIMER0_Delay();
	
		/* Count is Incremented by one to go to Next Phase
		Then Modulus Counter Value by 4 to make this Variable Range from 0-3 */
		Count = (Count+1)%4;
	}
	
	
	
	/**********************       Phase 2       **********************/
	
	if(Count == phase_2)
	{
		/* In this Phase TIMER0 Overflow Interrupt Blink Car Yellow Light in Normal Mode
		and Blink Both Cars and PED Yellow Lights in Pedestrian Mode */
		TIMER0_Delay();
		
		/* Turn Off Both Yellow LEDs at the End of This Phase
		to Ensure this LEDs Becomes off at the End of this Phase  */
		LED_Off(CAR_Light, LED_Yellow);
		LED_Off(PED_Light, LED_Yellow);
		
		Count = (Count+1)%4;
	}
	
	
	
	
	/**********************       Phase 3       **********************/
	
	if(Count == phase_3)
	{
		/* Enter this Condition Only if this System Work in Pedestrian Mode, 
		the System Known it Work in pedestrian Mode when First_Click have Value [1] */
		if(First_Click)
		{
			/* Allow Pedestrians to Cross the Road by Turn on Green Light and Turn off Red Light in Pedestrian Mode */
			LED_On(PED_Light, LED_Green);
			LED_Off(PED_Light, LED_Red);
		}
		
		/* Stop the Cars in Normal Mode by Turn on Red Light and Turn off Green Light */
		LED_Off(CAR_Light, LED_Green);
		LED_On(CAR_Light, LED_Red);
		
		TIMER0_Delay();
		
		Count = (Count+1)%4;
	}
	
	
	
	/**********************       Phase 4       **********************/
	
	/* In this Phase TIMER0 Overflow Interrupt Blink Car Yellow Light in Normal Mode
		and Blink Both Cars and PED Yellow Lights in Pedestrian Mode */
	TIMER0_Delay();
	
	/* Turn off PED Green Light in Case of Pedestrian Mode to Exit and Enter in Normal Mode [ phase_1 ] Again.
	   Also Turn off Car Blinking Yellow Light in case of Normal Mode to Start Again From phase_1.
	   Also Turn off Pedestrian Blinking Yellow Light in case of Pedestrian Mode to Exit and Enter in Normal Mode [ phase_1 ] Again */
	LED_Off(PED_Light, LED_Green);
	LED_Off(CAR_Light, LED_Yellow);
	LED_Off(PED_Light, LED_Yellow);
	
	
	if(Count == phase_4)
	{
		Count = (Count+1)%4;
		
		/* Turn off Cars Red Light in case of Normal Mode to Start Again from [ phase_1 ] */
		LED_Off(CAR_Light, LED_Red);
		
		/* Set  First_Click flag by [0] to Indicate Returning to Normal Mode */
		First_Click=0;
	}
	
	APP_start_State = APP_RETURN_OK;
	return APP_start_State;
#endif

#ifdef Testing_Mode
	
	uint8 * Pin_State ;
	
	/*===================    DIO Driver    ===================*/
	
	/* Test DIO_Init API by Set pin 0 from PORTA as Output and Watching [ DDRA ] Register */
	DIO_Init(PORT_A , LED_Green , OUT);
	
	/* Test DIO_Write API by Turn on pin 0 from PORTA and Watching [ PORTA ] Register */
	DIO_Write(PORT_A , LED_Green , HIGH);
	
	/* Test DIO_Toggle API by Toggle State of pin 0 from PORTA and Watching [ PORTA ] Register */
	DIO_Toggle(PORT_A , LED_Green);
	
	/* Test DIO_Read API by Read State of pin 0 from PORTA and Watching [ PINA ] Register with [ Result ] pointer */
	DIO_Read(PORT_A , LED_Green , Pin_State);
	
	
	
	/*===================    INTERRUPT Driver    ===================*/
	
	/* Test TIMER0_INTERRUPT_Init API by watching TIMER0 Interrupt Registers [ TIMSK ] */
	TIMER0_INTERRUPT_Init();
	
	/* Test External_INT0_Init API by watching External Interrupt Registers [ MCUCR  /  GICR  /  SREG ] */
	External_INT0_Init();
	
	
	
	/*===================    TIMER Driver    ===================*/
	
	/* Test TIMER0_Init API by watching TIMER0 Register [ TCCR0 (have the default values) ] */
	TIMER0_Init();
	
	/* Test TIMER0_Set_Initial_Value API by watching TIMER0 Register [ TCNT0 ] */
	TIMER0_Set_Initial_Value(50);
	
	/* Test TIMER0_Delay API by watching TIMER0 Register and Overflow Variable [ TCCR0 / Timer_OverFlow ] */
	TIMER0_Delay();
	
	/* Test TIMER0_Reset API by watching TIMER0 Register [ TCNT0 ] */
	TIMER0_Reset();



	/*===================    LED Driver    ===================*/
		
	/* Test LED_Init API by Set pin 0 from PORTB as Output and Watching [ DDRB ] Register */
	LED_Init(PORT_B , LED_Green);
		
	/* Test LED_On API by Turn on pin 0 from PORTB and Watching [ PORTA ] Register */
	LED_On(PORT_B , LED_Green);
	
	/* Test LED_Off API by Turn on pin 0 from PORTB and Watching [ PORTA ] Register */
	LED_Off(PORT_B , LED_Green);
		
	/* Test LED_Toggle API by Toggle State of pin 0 from PORTB and Watching [ PORTB ] Register */
	LED_Toggle(PORT_B , LED_Green);
	
	
	
	/*===================    BUTTON Driver    ===================*/
	
	/* Test BUTTON_Init API by Set pin 0 from PORTD as Input and Watching [ DDRD ] Register */
	BUTTON_Init(PORT_D , 0);
	
	/* Test BUTTON_Read API by Read State of pin 0 from PORTD and Watching [ PIND ] Register with [ Result ] pointer */
	BUTTON_Read(PORT_D , 0 , Pin_State);
	
	
	
	/*===================    ISRs    ===================*/
	
	/* Test TIMER0 ISR */
	TIMER0_Delay();
	
	/* To Test External Interrupt Press on crosswalk Button */
	
	
#endif
}