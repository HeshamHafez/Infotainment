/******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Source file for the LCD driver
 *
 * Author: Hesham Hafez & Ahmed El-Dakhly
 *
 *******************************************************************************/

#include "lcd.h"
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*******************************************************************************
 * Function Name:	LCD_init
 *
 * Description: 	Initialize LCD with Configured mode
 *
 * Inputs:			NULL
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
void LCD_init(void)
{
	LCD_CTRL_PORT_DIR |= (1<<E) | (1<<RS) | (1<<RW); /* Configure the control pins(E,RS,RW) as output pins */

#if (DATA_BITS_MODE == 4)
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT_DIR |= 0xF0; /* Configure the highest 4 bits of the data port as output pins */
#else
	LCD_DATA_PORT_DIR |= 0x0F; /* Configure the lowest 4 bits of the data port as output pins */
#endif
	LCD_sendCommand(FOUR_BITS_DATA_MODE); /* initialize LCD in 4-bit mode */
	LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE); /* use 2-line lcd + 4-bit Data Mode + 5*7 dot display Mode */
#elif (DATA_BITS_MODE == 8)
	LCD_DATA_PORT_DIR = 0xFF; /* Configure the data port as output port */
	LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE); /* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */
#endif

	LCD_sendCommand(CURSOR_OFF); /* cursor off */
	LCD_sendCommand(CLEAR_COMMAND); /* clear LCD at the beginning */
}

/*******************************************************************************
 * Function Name:	LCD_sendCommand
 *
 * Description: 	To send specific Command number to LCD
 *
 * Inputs:			specific Command number (uint8)
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
void LCD_sendCommand(uint8 command)
{
	CLEAR_BIT(LCD_CTRL_PORT,RS); /* Instruction Mode RS=0 */
	CLEAR_BIT(LCD_CTRL_PORT,RW); /* write data to LCD so RW=0 */
	_delay_us(600); /* delay for processing Tas = 50ns */
	SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
	_delay_us(600); /* delay for processing Tpw - Tdws = 190ns */
#if (DATA_BITS_MODE == 4)
	/* out the highest 4 bits of the required command to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (command & 0xF0);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((command & 0xF0) >> 4);
#endif

	_delay_us(600); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	_delay_us(600); /* delay for processing Th = 13ns */
	SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
	_delay_us(600); /* delay for processing Tpw - Tdws = 190ns */

	/* out the lowest 4 bits of the required command to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((command & 0x0F) << 4);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (command & 0x0F);
#endif

	_delay_us(600); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	_delay_us(600); /* delay for processing Th = 13ns */
#elif (DATA_BITS_MODE == 8)
	LCD_DATA_PORT = command; /* out the required command to the data bus D0 --> D7 */
	_delay_us(600); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	_delay_us(600); /* delay for processing Th = 13ns */
#endif
}

/*******************************************************************************
 * Function Name:	LCD_displayCharacter
 *
 * Description: 	To send Data byte to display it on LCD
 *
 * Inputs:			Data byte (uint8)
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
void LCD_displayCharacter(uint8 data)
{
	SET_BIT(LCD_CTRL_PORT,RS); /* Data Mode RS=1 */
	CLEAR_BIT(LCD_CTRL_PORT,RW); /* write data to LCD so RW=0 */
	_delay_us(600); /* delay for processing Tas = 50ns */
	SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
	_delay_us(600); /* delay for processing Tpw - Tdws = 190ns */
#if (DATA_BITS_MODE == 4)
	/* out the highest 4 bits of the required data to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (data & 0xF0);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((data & 0xF0) >> 4);
#endif

	_delay_us(600); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	_delay_us(600); /* delay for processing Th = 13ns */
	SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
	_delay_us(600); /* delay for processing Tpw - Tdws = 190ns */

	/* out the lowest 4 bits of the required data to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((data & 0x0F) << 4);
#else
	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (data & 0x0F);
#endif

	_delay_us(600); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	_delay_us(600); /* delay for processing Th = 13ns */
#elif (DATA_BITS_MODE == 8)
	LCD_DATA_PORT = command; /* out the required command to the data bus D0 --> D7 */
	_delay_us(600); /* delay for processing Tdsw = 100ns */
	CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	_delay_us(600); /* delay for processing Th = 13ns */
#endif
}

/*******************************************************************************
 * Function Name:	LCD_displayString
 *
 * Description: 	To send Data String to display it on LCD
 *
 * Inputs:			Pointer to constant string (uint8*)
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
void LCD_displayString(const uint8 *Str)
{
	uint8 i = 0;
	/*use loop to send string byte by byte to display on LCD*/
	while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}
	/***************** Another Method ***********************
	while((*Str) != '\0')
	{
		LCD_displayCharacter(*Str);
		Str++;
	}		
	 *********************************************************/
}

/*******************************************************************************
 * Function Name:	LCD_goToRowColumn
 *
 * Description: 	To go to specific position on LCD to start displaying
 *
 * Inputs:			column (uint8)
 * 					row (uint8)
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
void LCD_goToRowColumn(uint8 row,uint8 col)
{
	uint8 Address;

	/* first of all calculate the required address */
	switch(row)
	{
	case 0:
		Address=col;
		break;
	case 1:
		Address=col+0x40;
		break;
	case 2:
		Address=col+0x10;
		break;
	case 3:
		Address=col+0x50;
		break;
	}					
	/* to write to a specific address in the LCD 
	 * we need to apply the corresponding command 0b10000000+Address */
	LCD_sendCommand(Address | SET_CURSOR_LOCATION); 
}

/*******************************************************************************
 * Function Name:	LCD_displayStringRowColumn
 *
 * Description: 	To go to specific position on LCD to start displaying Data String
 *
 * Inputs:			column (uint8)
 * 					row (uint8)
 * 					Pointer to constant string (uint8*)
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
void LCD_displayStringRowColumn(uint8 row,uint8 col,const uint8 *Str)
{
	LCD_goToRowColumn(row,col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
}

/*******************************************************************************
 * Function Name:	LCD_clearScreen
 *
 * Description: 	To Clear LCD
 *
 * Inputs:			NULL
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_COMMAND); //clear display 
}

/*******************************************************************************
 * Function Name:	LCD_Task
 *
 * Description: 	LCD Task that will run in OS
 *
 * Inputs:			NULL
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
void LCD_Task(void)
{
	/*Variable to count number to repeat message displays specific numbers*/
	static uint8 once=0;

	 /*Variable to check if Yes or No Key is pressed or Not*/
	static uint8 OldProgramSteps=0;

	/*LED on to calculate CPU Load because of this task*/
	DIO_WritePin(DIO_PIN12,HIGH);

	/*messages strings*/
	uint8 Welcome[8] = "Welcome";
	uint8 Are_You_Ready[15] =  "Are you ready?";
	uint8 Press_1_to_yes[15] = "Press 1 to yes";
	uint8 Press_3_to_no[14] = "Press 3 to no";
	uint8 Start[6] = "Start";
	uint8 Your_Score_Is[16] = "Your Score Is: ";
	uint8 Congratulations[17] = " Congratulations ";
	uint8 To_Play_Again[14] = "To Play Again";
	uint8 Press_On_Reset[15] = "Press On Reset";

	/*array of strings to App Questions*/
	uint8 Question[][16] = {"Do you love H?","Is 1457 prime?",
			"egg > chicken?","egg < chicken?","Is hamada yel3b?"};

	/*determine when display specific string on LCD*/
	if(once<5)
	{
		LCD_displayStringRowColumn(0,4,Welcome);				/*select position of displaying string*/
		once++;													/*Increase counter*/
	}
	else if (once<10)
	{
		LCD_displayStringRowColumn(1,1,Are_You_Ready);			/*select position of displaying string*/
		once++;													/*Increase counter*/
	}
	else if(once==10)
	{
		LCD_clearScreen();										/*Clear LCD*/
		once++;													/*Increase counter*/
	}
	else if(once<15)
	{
		LCD_displayStringRowColumn(0,1,Press_1_to_yes);			/*select position of displaying string */								/*Increase counter*/
		LCD_displayStringRowColumn(1,1,Press_3_to_no);			/*select position of displaying string */
		once++;													/*Increase counter*/
	}
	else if(once==15)
	{
		LCD_clearScreen();										/*Clear LCD*/
		once++;													/*Increase counter*/
	}
	else if(once<20)
	{
		LCD_displayStringRowColumn(0,5,Start);					/*select position of displaying string*/
		once++;													/*Increase counter*/
	}
	else if(once==20||once==21)
	{
		if(once==20)
		{
			LCD_clearScreen();									/*Clear LCD*/
			LCD_displayString(Question[ProgramSteps]);			/*display question string*/
			once++;												/*Increase counter*/
		}
		else if(once==21)
		{
			uint8 *temp =Question[ProgramSteps];				/*temp to get question string to display it*/
			if(OldProgramSteps!=ProgramSteps)
			{

				LCD_clearScreen();								/*Clear LCD*/
				LCD_displayString(temp);						/*display question string*/
			}
			if(ProgramSteps == 5)
			{
				LCD_clearScreen();								/*Clear LCD*/
				LCD_displayStringRowColumn(0,0,Your_Score_Is);	/*display Score string*/
				LCD_displayCharacter(Score+48);					/*display Value*/
				LCD_displayStringRowColumn(1,0,Congratulations);/*display Congratulation string*/
				ProgramSteps=0;									/*return question counter to zero value*/
				once++;											/*Increase counter*/
			}
			OldProgramSteps=ProgramSteps;
		}
	}
	else if(once<30)
	{
		once++;													/*Increase counter*/
	}
	else if(once==30)
	{
		LCD_clearScreen();										/*Clear LCD*/
		LCD_displayStringRowColumn(0,0,To_Play_Again);			/*display string*/
		LCD_displayStringRowColumn(1,0,Press_On_Reset);			/*display string*/
		once++;													/*Increase counter*/
	}
	/*LED off to calculate CPU Load because of this task*/
	DIO_WritePin(DIO_PIN12,LOW);
}

