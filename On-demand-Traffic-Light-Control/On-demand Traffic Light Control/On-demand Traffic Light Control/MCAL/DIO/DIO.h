/**==================================================
--    Author     :   YOUSSEF ADEL YOUSSEF
--  Description  :   DIO Driver
==================================================**/


#ifndef DIO_H_
#define DIO_H_

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

/* Pin Directions */
#define IN		0
#define OUT		1

/* Pin States */
#define LOW		0
#define HIGH	1

/* Enumeration Status */
typedef enum{
	DIO_RETURN_OK,
	DIO_RETURN_ERROR
}EN_DIOStatus_t;

/********************************************************************************************************/

/*
* ================================================================
*           APIs Supported by "MCAL DIO DRIVER"
* ================================================================
*/

EN_DIOStatus_t DIO_Init(uint8 PortName , uint8 PinNum , uint8 Direction);
EN_DIOStatus_t DIO_Write(uint8 PortName , uint8 PinNum , uint8 State);
EN_DIOStatus_t DIO_Toggle(uint8 PortName , uint8 PinNum);
EN_DIOStatus_t DIO_Read(uint8 PortName , uint8 PinNum , uint8 * Result);

#endif /* DIO_H_ */