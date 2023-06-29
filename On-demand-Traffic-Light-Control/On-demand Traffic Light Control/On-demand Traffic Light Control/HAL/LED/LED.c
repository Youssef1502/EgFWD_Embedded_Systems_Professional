/**==================================================
--    Author     :   YOUSSEF ADEL YOUSSEF
--  Description  :   Led Driver
==================================================**/

/*
* ================================================================
*                         Includes
* ================================================================
*/

#include "LED.h"

/********************************************************************************************************/

/*
 * ================================================================
 *                    APIs Function Definitions
 * ================================================================
 */

/**================================================================
 * @Fun				- LED_Init
 * @Brief 			- Set the LED in the Output Mode
 * @Ret_Val 		- LED_Init_State
 * @Note			- None
 ===============================================================**/
EN_LEDStatus_t LED_Init(uint8 PortName, uint8 PinNum)
{
	EN_LEDStatus_t LED_Init_State = LED_RETURN_ERROR;
	
	DIO_Init(PortName , PinNum , OUT);
	LED_Init_State = LED_RETURN_OK;
	return LED_Init_State;
}



/**================================================================
 * @Fun				- LED_On
 * @Brief 			- Make LED on
 * @Ret_Val 		- LED_On_State
 * @Note			- None
 ===============================================================**/
EN_LEDStatus_t LED_On(uint8 PortName, uint8 PinNum)
{
	EN_LEDStatus_t LED_On_State = LED_RETURN_ERROR;
	
	DIO_Write(PortName , PinNum , HIGH);
	LED_On_State = LED_RETURN_ERROR;
	return LED_On_State;
}




/**================================================================
 * @Fun				- LED_Off
 * @Brief 			- Make LED off
 * @Ret_Val 		- LED_Off_State
 * @Note			- None
 ===============================================================**/
EN_LEDStatus_t LED_Off(uint8 PortName, uint8 PinNum)
{
	EN_LEDStatus_t LED_Off_State = LED_RETURN_ERROR;
	
	DIO_Write(PortName , PinNum , LOW);
	LED_Off_State = LED_RETURN_ERROR;
	return LED_Off_State;
}




/**================================================================
 * @Fun				- LED_Toggle
 * @Brief 			- Toggle LED State
 * @Ret_Val 		- LED_Toggle_State
 * @Note			- None
 ===============================================================**/
EN_LEDStatus_t LED_Toggle(uint8 PortName, uint8 PinNum)
{
	EN_LEDStatus_t LED_Toggle_State = LED_RETURN_ERROR;
	
	DIO_Toggle(PortName , PinNum);
	LED_Toggle_State = LED_RETURN_ERROR;
	return LED_Toggle_State;	
}