/**==================================================
--    Author     :   YOUSSEF ADEL YOUSSEF
--  Description  :   DIO Driver
==================================================**/

/*
* ================================================================
*                         Includes
* ================================================================
*/

#include "DIO.h"

/********************************************************************************************************/

/*
 * ================================================================
 *                    APIs Function Definitions
 * ================================================================
 */

/**================================================================
 * @Fun				- DIO_Init
 * @Brief 			- Set pin direction in a specific port [ Input / Output]
 * @Ret_Val 		- DIO_Init_State
 * @Note			- None
 ===============================================================**/
EN_DIOStatus_t DIO_Init(uint8 PortName , uint8 PinNum , uint8 Direction)
{
	EN_DIOStatus_t DIO_Init_State = DIO_RETURN_ERROR;
	switch(PortName)
	{
		case PORT_A:
			if(Direction==OUT)
			{
				Set_Pin(DDRA, PinNum);
			}
			else if(Direction==IN)
			{
				Clear_Pin(DDRA, PinNum);
			}
			DIO_Init_State = DIO_RETURN_OK;
		break;
		
		case PORT_B:
			if(Direction==OUT)
			{
				Set_Pin(DDRB, PinNum);
			}
			else if(Direction==IN)
			{
				Clear_Pin(DDRB, PinNum);
			}
			DIO_Init_State = DIO_RETURN_OK;
		break;
		
		case PORT_C:
			if(Direction==OUT)
			{
				Set_Pin(DDRC, PinNum);
			}
			else if(Direction==IN)
			{
				Clear_Pin(DDRC, PinNum);
			}
			DIO_Init_State = DIO_RETURN_OK;
		break;
		
		case PORT_D:
			if(Direction==OUT)
			{
				Set_Pin(DDRD, PinNum);
			}
			else if(Direction==IN)
			{
				Clear_Pin(DDRD, PinNum);
			}
			DIO_Init_State = DIO_RETURN_OK;
		break;
	}
	return DIO_Init_State;
}



/**================================================================
 * @Fun				- DIO_Write
 * @Brief 			- Set pin state in a specific port [ High / Low]
 * @Ret_Val 		- DIO_Write_State
 * @Note			- None
 ===============================================================**/

EN_DIOStatus_t DIO_Write(uint8 PortName , uint8 PinNum , uint8 State)
{
	EN_DIOStatus_t DIO_Write_State = DIO_RETURN_ERROR;
	switch(PortName)
	{
		case PORT_A:
			if(State==HIGH)
			{
				Set_Pin(PORTA, PinNum);
			}
			else if(State==LOW)
			{
				Clear_Pin(PORTA, PinNum);
			}
			DIO_Write_State = DIO_RETURN_OK;
		break;
		
		case PORT_B:
			if(State==HIGH)
			{
				Set_Pin(PORTB, PinNum);
			}
			else if(State==LOW)
			{
				Clear_Pin(PORTB, PinNum);
			}
			DIO_Write_State = DIO_RETURN_OK;
		break;
		
		case PORT_C:
			if(State==HIGH)
			{
				Set_Pin(PORTC, PinNum);
			}
			else if(State==LOW)
			{
				Clear_Pin(PORTC, PinNum);
			}
			DIO_Write_State = DIO_RETURN_OK;
		break;
		
		case PORT_D:
			if(State==HIGH)
			{
				Set_Pin(PORTD, PinNum);
			}
			else if(State==LOW)
			{
				Clear_Pin(PORTD, PinNum);
			}
			DIO_Write_State = DIO_RETURN_OK;
		break;
	}
	
	return DIO_Write_State;
}



/**================================================================
 * @Fun				- DIO_Toggle
 * @Brief 			- Toggle pin state in a specific port [ High / Low]
 * @Ret_Val 		- DIO_Toggle_State
 * @Note			- None
 ===============================================================**/

EN_DIOStatus_t DIO_Toggle(uint8 PortName , uint8 PinNum)
{
	EN_DIOStatus_t DIO_Toggle_State = DIO_RETURN_ERROR;
	switch(PortName)
	{
		case PORT_A:
			Togggle_Pin(PORTA, PinNum);
			DIO_Toggle_State = DIO_RETURN_OK;
		break;
		
		case PORT_B:
			Togggle_Pin(PORTB, PinNum);
			DIO_Toggle_State = DIO_RETURN_OK;
		break;
		
		case PORT_C:
			Togggle_Pin(PORTC, PinNum);
			DIO_Toggle_State = DIO_RETURN_OK;
		break;
		
		case PORT_D:
			Togggle_Pin(PORTD, PinNum);
			DIO_Toggle_State = DIO_RETURN_OK;
		break;
	}
	
	return DIO_Toggle_State;
}




/**================================================================
 * @Fun				- DIO_Read
 * @Brief 			- Read pin state from a specific port [High / Low]
 * @Ret_Val 		- DIO Status [ OK / ERROR]
 * @Note			- None
 ===============================================================**/

EN_DIOStatus_t DIO_Read(uint8 PortName , uint8 PinNum , uint8 * Result)
{
	EN_DIOStatus_t DIO_Read_State = DIO_RETURN_ERROR;
	switch(PortName)
	{
		case PORT_A:
			*Result = Get_Pin(PINA, PinNum);
			DIO_Read_State = DIO_RETURN_OK;
		break;
		
		case PORT_B:
			*Result = Get_Pin(PINB, PinNum);
			DIO_Read_State = DIO_RETURN_OK;
		break;
		
		case PORT_C:
			*Result = Get_Pin(PINC, PinNum);
			DIO_Read_State = DIO_RETURN_OK;
		break;
		
		case PORT_D:
			*Result = Get_Pin(PIND, PinNum);
			DIO_Read_State = DIO_RETURN_OK;
		break;
	}
	
	return DIO_Read_State;
}