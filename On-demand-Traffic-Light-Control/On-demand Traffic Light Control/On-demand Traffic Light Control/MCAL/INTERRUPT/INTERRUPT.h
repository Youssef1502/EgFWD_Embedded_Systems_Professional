/**==================================================
--    Author     :   YOUSSEF ADEL YOUSSEF
--  Description  :   Interrupt Driver
==================================================**/


#ifndef INTERRUPT_H_
#define INTERRUPT_H_

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

//Enable interrupts
//#define sei()  __asm__ __volatile__ ("sei" ::: "memory")
//#define cli()  __asm__ __volatile__ ("cli" ::: "memory")

//Interrupt vectors
#define EXT_INT_0		__vector_1
#define EXT_INT_1		__vector_2
#define TIMER0_OVF		__vector_11

//ISR macro
#define ISR(INT_VECT) \
void INT_VECT(void) __attribute__((signal,used));\
void INT_VECT(void)

/* Enumeration Status */
typedef enum{
	INTERRUPT_RETURN_OK,
	INTERRUPT_RETURN_ERROR
}EN_INTERRUPTStatus_t;

/********************************************************************************************************/

/*
* ================================================================
*           APIs Supported by "MCAL INTERRUPT DRIVER"
* ================================================================
*/

EN_INTERRUPTStatus_t External_INT0_Init();
EN_INTERRUPTStatus_t TIMER0_INTERRUPT_Init();



#endif /* INTERRUPT_H_ */