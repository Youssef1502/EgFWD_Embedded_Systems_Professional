/**==================================================
--    Author     :   YOUSSEF ADEL YOUSSEF
--  Description  :   Common Macros
==================================================**/

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/* Bit Manipulation */
#define Set_Pin(x,n)		x |= (1<<n)
#define Clear_Pin(x,n)		x &= ~(1<<n)
#define Togggle_Pin(x,n)	x ^= (1<<n)
#define Get_Pin(x,n)		( (x&(1<<n)) >> n)


/* PORT Names to Pass to Functions to access Required Port*/
#define PORT_A		 'A'
#define PORT_B		 'B'
#define PORT_C		 'C'
#define PORT_D		 'D'


/* LEDs & Switch Port Name */
#define CAR_Light			PORT_A
#define PED_Light			PORT_B
#define INDICATION_Light	PORT_C
#define BUTTON_port			PORT_D


/* LED Pin Names */
#define LED_Green		0
#define LED_Yellow		1
#define LED_Red			2


/* Button Pin Name */
#define BUTTON_pin		0


/* Modes Pin Name */
#define Normal_Mode_pin		0
#define PED_Mode_Pin		1


/* Execution Phases */
#define phase_1			0
#define phase_2			1
#define phase_3			2
#define phase_4			3


#endif /* COMMON_MACROS_H_ */