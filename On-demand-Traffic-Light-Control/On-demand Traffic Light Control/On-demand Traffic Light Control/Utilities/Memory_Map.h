/**==================================================
--    Author     :   YOUSSEF ADEL YOUSSEF
--  Description  :   Memory Map
==================================================**/


#ifndef MEMORY_MAP_H_
#define MEMORY_MAP_H_

/*
* ================================================================
*                         Includes
* ================================================================
*/

#include "Std_Types.h"


/************************************************************************************************/

/*
* ================================================================
* 						DIO Registers
* ================================================================
*/

// PORTA
#define DDRA (*(volatile uint8*)0x3A)
#define PINA (*(volatile uint8*)0x39)
#define PORTA (*(volatile uint8*)0x3B)

// PORTB
#define DDRB (*(volatile uint8*)0x37)
#define PINB (*(volatile uint8*)0x36)
#define PORTB (*(volatile uint8*)0x38)

// PORTC
#define DDRC (*(volatile uint8*)0x34)
#define PINC (*(volatile uint8*)0x33)
#define PORTC (*(volatile uint8*)0x35)

// PORTD
#define DDRD (*(volatile uint8*)0x31)
#define PIND (*(volatile uint8*)0x30)
#define PORTD (*(volatile uint8*)0x32)

/*
* ================================================================
* 					External Interrupt Registers
* ================================================================
*/

// MCU Control Register
#define MCUCR   (*(volatile uint8*)0x55)

//  MCU Control and Status Register
#define MCUCSR   (*(volatile uint8*)0x54)

// General Interrupt Control Register
#define GICR     (*(volatile uint8*)0x5B)

// General Interrupt Flag Register
#define GIFR    (*(volatile uint8*)0x5A)


/*
* ================================================================
* 						TIMER0 Registers
* ================================================================
*/


// Timer/Counter Control Register
#define TCCR0   (*(volatile uint8*)0x53)

// Timer/Counter Register
#define TCNT0   (*(volatile uint8*)0x52)

// Output Compare Register
#define OCR0    (*(volatile uint8*)0x5C)

// Timer/Counter Interrupt Mask Register
#define TIMSK   (*(volatile uint8*)0x59)

// Timer/Counter Interrupt Flag Register
#define TIFR    (*(volatile uint8*)0x58)


/*
* ================================================================
* 						STATUS REGISTER
* ================================================================
*/

// The AVR Status Register
#define SREG	(*(volatile uint8*)0x5F)


#endif /* MEMORY_MAP_H_ */