/*************************************************
 * Module 	  : Keypad
 *
 * File name  : keypad.h
 *
 * Created on : Apr 21, 2019
 *
 * Author     : Hesham Hafez & Ahmed El-Dakhly
 *************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

/*************************************************
 * 				Included libraries
 *************************************************/
#include"keypad_cfg.h"
#include "scheduler.h"


extern uint8 Score;
extern uint8 ProgramSteps;

/************************************************
 * 				Functions Deceleration
 ************************************************/
#define IDLE 		0
#define PRESSED 	1
#define RELEASED 	2
#define PREPRESSED 	3
#define PRERELEASED 4

extern void KeyPad_Init(void);
extern uint8 KeyPad_getPressedKey(void);
extern void ButtonTask(void);
extern void Key_PressedTask(void);

#endif /* KEYPAD_H_ */
