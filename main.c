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

	SOS_Init();
	KeyPad_Init();
	LCD_init(); /* initialize LCD */
	DIO_SetPinDirection(DIO_PIN12,1);
	DIO_SetPinDirection(DIO_PIN13,1);
	SOS_CreateTask(PRIORITY_1,200,Key_PressedTask);
	SOS_CreateTask(PRIORITY_0,200,LCD_Task);
	DIO_WritePin(DIO_PIN12,1);
	SET_BIT(SREG,I);
	SOS_Run();
//	while(1)
//	{
//		key = 0;
//		key = KeyPad_getPressedKey();
//		LCD_displayCharacter(key+48);
//		//		if(key > 0)
//		//		{
//		//			for(uint16 i=0;i<40000;i++);
//		//		}
//		//		if(key == 1)
//		//		DIO_WritePin(DIO_PIN12,1);
//
//	}

}
