/**==================================================
--    Author     :   YOUSSEF ADEL YOUSSEF
--  Description  :   Application
==================================================**/


#ifndef APP_H_
#define APP_H_

/*
* ================================================================
*                         Reference Macros
* ================================================================
*/

#define F_CPU 1000000U

#include "../HAL/BUTTON/BUTTON.h"
#include "../HAL/LED/LED.h"

/* Enumeration Status */
typedef enum{
	APP_RETURN_OK,
	APP_RETURN_ERROR
}EN_APPStatus_t;

/********************************************************************************************************/

/*
* ================================================================
*           APIs Supported by "Application DRIVER"
* ================================================================
*/

EN_APPStatus_t APP_init(void);
EN_APPStatus_t APP_start(void);



#endif /* APP_H_ */