/*
 * main.c
 *
 *  Created on: Sep 23, 2019
 *      Author: hesha
 */



#include "lcd.h"
#include "keypad.h"
#include "scheduler.h"


int main(void)
{
	/*To calculate CPU Load*/
	DIO_SetPinDirection(DIO_PIN12,OUTPUT);
	DIO_SetPinDirection(DIO_PIN13,OUTPUT);
	DIO_SetPinDirection(DIO_PIN14,OUTPUT);
	/*Initialize OS */
	SOS_Init();
	/*Initialize KeyPad */
	KeyPad_Init();
	/*Initialize LCD */
	LCD_init();
	/*OS Tasks*/
	SOS_CreateTask(PRIORITY_1,200,Key_PressedTask);
	SOS_CreateTask(PRIORITY_0,200,LCD_Task);
	/*Enable Global Interrupt*/
	SET_BIT(SREG,I);
	/*Run OS Scheduler*/
	SOS_Run();


}
