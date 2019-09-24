 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.h
 *
 * Description: Header file for the LCD driver
 *
 * Author: Hesham Hafez & Ahmed El-Dakhly
 *
 *******************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include "lcd_cfg.h"
#include "scheduler.h"


extern uint8 ProgramSteps;
extern uint8 Score;
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* LCD Commands */
#define CLEAR_COMMAND 					0x01
#define FOUR_BITS_DATA_MODE 			0x02
#define TWO_LINE_LCD_Four_BIT_MODE 		0x28
#define TWO_LINE_LCD_Eight_BIT_MODE 	0x38
#define CURSOR_OFF 						0x0C
#define CURSOR_ON 						0x0E
#define SET_CURSOR_LOCATION 			0x80

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void LCD_init(void);
void LCD_sendCommand(uint8 command);
void LCD_displayCharacter(uint8 data);
void LCD_displayString(const char *Str);
void LCD_clearScreen(void);
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);
void LCD_goToRowColumn(uint8 row,uint8 col);
void LCD_Task(void);
#endif /* LCD_H_ */
