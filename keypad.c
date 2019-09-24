/*************************************************
 * Module 	  : Keypad
 *
 * File name  : keypad.c
 *
 * Created on : Apr 21, 2019
 *
 * Author     : Hesham Hafez & Ahmed El-Dakhly
 *************************************************/

/*************************************************
 * 				Included libraries
 *************************************************/
#include"keypad.h"
static uint8 Press_count 	= 1;
static uint8 Release_count = 10;
static uint8 g_row;
static uint8 g_return;
uint8 ProgramSteps=0;
uint8 Score=0;
static uint8 Answers[]={YES,NO,NO,YES,YES};
/************************************************
 * 				Functions Definition
 ************************************************/


#if(N_COL==3)
#if(N_ROW == 3)
static uint8 KeyPad_3x3_switch(uint8 row, uint8 col);
#elif(N_ROW == 4)
static uint8 KeyPad_4x3_switch(uint8 row, uint8 col);
#endif
#endif

#if(N_COL==4)
static uint8 KeyPad_4x4_switch(uint8 row, uint8 col);
#endif


void KeyPad_Init(void)
{
	DIO_SetPinDirection(DIO_PIN18,INPUT);
	DIO_SetPinDirection(DIO_PIN19,INPUT);
	DIO_SetPinDirection(DIO_PIN20,INPUT);
	DIO_SetPinDirection(DIO_PIN21,OUTPUT);
	DIO_SetPinDirection(DIO_PIN22,OUTPUT);
	DIO_SetPinDirection(DIO_PIN23,OUTPUT);
	DIO_WritePin(DIO_PIN18,HIGH);
	DIO_WritePin(DIO_PIN19,HIGH);
	DIO_WritePin(DIO_PIN20,HIGH);
	DIO_WritePin(DIO_PIN21,LOW);
	DIO_WritePin(DIO_PIN22,LOW);
	DIO_WritePin(DIO_PIN23,LOW);
}

uint8 KeyPad_getPressedKey(void)
{
static uint8 once=0;
if(once<20)
{
	once++;
	return 0;
}
	uint8 row,col;
	for(col=0;col<N_COL;col++)
	{
		KEYPAD_PORT_DIR = (0b00100000<<col);
		KEYPAD_PORT_OUT = (~(0b00100000<<col));

		for(row=START_ROW;row<END_ROW;row++)
		{
			if(GET_BIT(KEYPAD_PORT_IN,row) == 0)
			{
				g_row = row;
				SOS_CreateTask(PRIORITY_2,4,ButtonTask);
#if(N_COL ==3)
#if(N_ROW == 3)
				return KeyPad_3x3_switch(row-START_ROW,col);
#elif(N_ROW==4)
				return KeyPad_4x3_switch(row-START_ROW,col);
#endif
#elif(N_COL ==4)
				return KeyPad_4x4_switch(row-START_ROW,col);
#endif
			}
		}
	}
}

#if(N_COL==3)
#if(N_ROW == 4)
static uint8 KeyPad_4x3_switch(uint8 row,uint8 col)
{
	uint8 ReturnVal = 0;
	switch(row)
	{
	case 0:
		switch(col)
		{
		case 0: ReturnVal = R1C1;
		break;
		case 1: ReturnVal = R1C2;
		break;
		case 2: ReturnVal = R1C3;
		break;
		}
		break;

		case 1:
			switch(col)
			{
			case 0: ReturnVal = R2C1;
			break;
			case 1: ReturnVal = R2C2;
			break;
			case 2: ReturnVal = R2C3;
			break;
			}
			break;
			case 2:
				switch(col)
				{
				case 0: ReturnVal = R3C1;
				break;
				case 1: ReturnVal = R3C2;
				break;
				case 2: ReturnVal = R3C3;
				break;
				}
				break;
				case 3:
					switch(col)
					{
					case 0: ReturnVal = R4C1;
					break;
					case 1: ReturnVal = R4C2;
					break;
					case 2: ReturnVal = R4C3;
					break;
					}
					break;
	}
	return ReturnVal;
}
#elif (N_ROW == 3)
static uint8 KeyPad_3x3_switch(uint8 row, uint8 col)
{
	uint8 ReturnVal = 0;
	DIO_SetPinDirection(DIO_PIN12,1);
	DIO_WritePin(DIO_PIN12,1);

	switch(row)
	{
	case 0:
		switch(col)
		{
		case 0: ReturnVal = R1C1;
		break;
		case 1: ReturnVal = R1C2;
		break;
		case 2: ReturnVal = R1C3;
		break;
		}
		break;
		case 1:
			switch(col)
			{
			case 0: ReturnVal = R2C1;
			break;
			case 1: ReturnVal = R2C2;
			break;
			case 2: ReturnVal = R2C3;
			break;
			}
			break;
			case 2:
				switch(col)
				{
				case 0: ReturnVal = R3C1;
				break;
				case 1: ReturnVal = R3C2;
				break;
				case 2: ReturnVal = R3C3;
				break;
				}
				break;
	}
	return ReturnVal;
}

#endif
#elif(N_COL==4)
static uint8 KeyPad_4x4_switch(uint8 row,uint8 col)
{
	uint8 ReturnVal = 0;
	switch(row)
	{
	case 0:
		switch(col)
		{
		case 0: ReturnVal = R1C1;
		break;
		case 1: ReturnVal = R1C2;
		break;
		case 2: ReturnVal = R1C3;
		break;
		case 3: ReturnVal = R1C4;
		break;
		}
		break;

		case 1:
			switch(col)
			{
			case 0: ReturnVal = R2C1;
			break;
			case 1: ReturnVal = R2C2;
			break;
			case 2: ReturnVal = R2C3;
			break;
			case 3: ReturnVal = R2C4;
			break;
			}
			break;
			case 2:
				switch(col)
				{
				case 0: ReturnVal = R3C1;
				break;
				case 1: ReturnVal = R3C2;
				break;
				case 2: ReturnVal = R3C3;
				break;
				case 3: ReturnVal = R3C4;
				break;
				}
				break;
				case 3:
					switch(col)
					{
					case 0: ReturnVal = R4C1;
					break;
					case 1: ReturnVal = R4C2;
					break;
					case 2: ReturnVal = R4C3;
					break;
					case 3: ReturnVal = R4C4;
					break;
					}
					break;
	}
	return ReturnVal;
}
#endif

void ButtonTask(void)
{
	static uint8 Button_State = PREPRESSED;
	switch(Button_State)
	{
	case PREPRESSED:
		if(GET_BIT(KEYPAD_PORT_IN,g_row) == 0)
		{
			Press_count++;
			if(Press_count == 10)
			{
				Button_State = PRESSED;
			}
			else
			{
				/*Do Nothing*/
			}
		}
		break;
	case PRESSED:
		if(GET_BIT(KEYPAD_PORT_IN,g_row) == 0)
		{
			/*Do Nothing*/
		}
		else
		{
			if((g_return==YES)||(g_return==NO))
			{
				if(g_return==Answers[ProgramSteps])
				{
					Score++;
				}
				ProgramSteps++;
			}
			Button_State = PRERELEASED;
		}
		Press_count = 1;
		break;
	case PRERELEASED:
		if(GET_BIT(KEYPAD_PORT_IN,g_row) == 1)
		{
			Release_count--;
			if(Release_count == 1)
			{
				Button_State = RELEASED;
			}
			else
			{
				/*Do Nothing*/
			}
		}
		break;
	case RELEASED:
		Release_count = 10;
		Button_State = PREPRESSED;
		SOS_DeleteTask(ButtonTask);
		break;
	default:
		break;
	}
}

void Key_PressedTask(void)
{
	g_return = KeyPad_getPressedKey();
}

