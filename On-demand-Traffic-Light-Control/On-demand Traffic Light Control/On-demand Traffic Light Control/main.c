/**==================================================
--    Author     :   YOUSSEF ADEL YOUSSEF
--  Description  :   On-demand Traffic Light Control
==================================================**/

/*
* ================================================================
*                         Includes
* ================================================================
*/

#include "Application/APP.h"

/********************************************************************************************************/

/*
 * ================================================================
 *                    APIs Function Definitions
 * ================================================================
 */

int main(void)
{
	/* Call Initial Function to Initialize All System Drivers */
	APP_init();
	
	while (1)
	{
		/* APP_start Function Refers to the Normal Mode so it is Work All the time
		Until Interrupt is happened to Make this System Work in pedestrian Mode */
		APP_start();
		
	}
}
