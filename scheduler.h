/******************************************************************************
 *
 * Module: OS Scheduler
 *
 * File Name: scheduler.h
 *
 * Description: Header file of OS Scheduler
 *
 * Created on: Sep 16, 2019
 *
 * Author: Hesham Hafez
 *
 *******************************************************************************/

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

/*******************************************************************************
 *                       	Included Libraries                                 *
 *******************************************************************************/
#include "scheduler_cfg.h"
#include "Timer.h"
#include <avr/interrupt.h>

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/*****************************Scheduler Modes***********************************/
typedef enum
{
	SOS_READY_MODE,
	SOS_RUNING_MODE,
	SOS_WAITING_MODE
}EnmSosModes_t;

/*****************************Tasks Priority***********************************/
typedef enum
{
	PRIORITY_0,
	PRIORITY_1,
	PRIORITY_2,
	PRIORITY_3,
	PRIORITY_4,
	PRIORITY_5,
	PRIORITY_6,
	PRIORITY_7,
	PRIORITY_8,
	PRIORITY_9
}EnmSosPriority_t;
/******************************** Return Status ***************************************/
typedef enum
{
	OK,
	RESERVED_TASK,
}EnmSosStatus_t;

/*******************************************************************************
 *                         Configurations Structures                           *
 *******************************************************************************/

/********************* Scheduler Configuration Structure ***********************/
typedef struct
{
	EnmSosModes_t 		Mode;
	uint16				Periodicity;
	void (*Task_Ptr) (void);
}StrSosTaskConfig_t;

extern StrSosTaskConfig_t SOS_Config;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*******************************************************************************
 * Function Name:	SOS_Init
 *
 * Description: 	Initialize the OS Scheduler
 *
 * Inputs:			NULL
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
void SOS_Init(void);

/*******************************************************************************
 * Function Name:	SOS_DeInit
 *
 * Description: 	Disable the OS Scheduler
 *
 * Inputs:			NULL
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
void SOS_DeInit(void);

/*******************************************************************************
 * Function Name:	SOS_CreateTask
 *
 * Description: 	Create Scheduled Task
 *
 * Inputs:			*Priority of the Task
 *					*periodicity of the Task
 *					*pointer to the task function
 *
 * Outputs:			NULL
 *
 * Return:			Status to check function execution
 *******************************************************************************/
EnmSosStatus_t SOS_CreateTask(EnmSosPriority_t a_Priority, uint16 a_periodicity, void (* Task_Select_Ptr)(void));

/*******************************************************************************
 * Function Name:	SOS_Run
 *
 * Description: 	Run the ready Tasks
 *
 * Inputs:			NULL
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
void SOS_Run(void);

/*******************************************************************************
 * Function Name:	SOS_DeleteTask
 *
 * Description: 	Delete selected Tasks
 *
 * Inputs:			pointer to the task function that wanted to be deleted
 *
 * Outputs:			NULL
 *
 * Return:			NULL
 *******************************************************************************/
void SOS_DeleteTask(void (*DeletedTask_Ptr)(void));


#endif /* SCHEDULER_H_ */
