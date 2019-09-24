/******************************************************************************
 *
 * Module: OS Scheduler
 *
 * File Name: scheduler.c
 *
 * Description: Source file of OS Scheduler
 *
 * Created on: Sep 16, 2019
 *
 * Author: Hesham Hafez
 *
 *******************************************************************************/

/*******************************************************************************
 *                       	Included Libraries                                 *
 *******************************************************************************/
#include "scheduler.h"
#include "DIO.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/*counter of Timer Ticks */
static volatile uint32 g_Tick_Count = 0u;
/*Array of tasks can be handled*/
static StrSosTaskConfig_t arr[ID_MAX];

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER0_COMP_vect)
{
	g_Tick_Count++;
	uint8 loopcounter;
	/*loop to find a task ready to be executed*/
	for(loopcounter = 0 ; loopcounter<ID_MAX ; loopcounter++)
	{
		/*check if there is a created task or not*/
		if(arr[loopcounter].Task_Ptr != NULL_PTR)
		{
			/*check if the task is ready to be executed by check task Periodicity*/
			if((g_Tick_Count % (arr[loopcounter].Periodicity))==0u)
			{
				/*switch task state to Ready State*/
				arr[loopcounter].Mode = SOS_READY_MODE;
			}
			else
			{
				/*Do Nothing*/
			}
		}
		else
		{
			/*Do Nothing*/
		}

	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
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
void SOS_Init(void)
{
	TIMER_init();
	uint8 LoopCounter = 0;
	/*loop to Initialize the array of tasks*/
	for(LoopCounter = 0u; LoopCounter<ID_MAX; LoopCounter++)
	{
		/*switch task state to Waiting State*/
		arr[LoopCounter].Mode = SOS_WAITING_MODE;
		/*Initialize tasks Periodicity*/
		arr[LoopCounter].Periodicity = 0u;
		/*Initialize the tasks array*/
		arr[LoopCounter].Task_Ptr = NULL_PTR;
	}
}

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
EnmSosStatus_t SOS_CreateTask(EnmSosPriority_t a_Priority, uint16 a_periodicity, void (* Task_Select_Ptr)(void))
{
	/*Return Value*/
	EnmSosStatus_t ReternVal;
	/*To avoid condition of two tasks have same Priority*/
	if(arr[a_Priority].Task_Ptr != NULL_PTR)
	{
		ReternVal = RESERVED_TASK;
	}
	else
	{
		/*create task with its Priority and periodicity*/
		arr[a_Priority].Mode = SOS_WAITING_MODE;
		arr[a_Priority].Periodicity = a_periodicity;
		arr[a_Priority].Task_Ptr = Task_Select_Ptr;

		ReternVal = OK;
	}

	return ReternVal;
}

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
void SOS_Run(void)
{
	uint8 LoopCtr;
	while(1)
	{
		/*loop for searching about ready task to execute*/
		for(LoopCtr = 0; LoopCtr <ID_MAX ;LoopCtr++)
		{
			/*check if the task is ready to execute*/
			if(arr[LoopCtr].Mode == SOS_READY_MODE)
			{
				/*switch task state to Running State*/
				arr[LoopCtr].Mode = SOS_RUNING_MODE;
				/*Run the Task*/
				arr[LoopCtr].Task_Ptr();
				/*wait for another task*/
				arr[LoopCtr].Mode = SOS_WAITING_MODE;
			}
			else
			{
				/*Do Nothing*/
			}
		}
	}
}

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
void SOS_DeleteTask(void (*DeletedTask_Ptr)(void))
{
	uint8 Loopcounter;
	/*loop to find the task that wanted to be deleted*/
	for(Loopcounter = 0; Loopcounter<ID_MAX ; Loopcounter++)
	{
		/*check if the task is the desired task to be deleted*/
		if(arr[Loopcounter].Task_Ptr == DeletedTask_Ptr)
		{
			/*delete the task and get out of the loop*/
			arr[Loopcounter].Task_Ptr = NULL_PTR;
			arr[Loopcounter].Mode= SOS_WAITING_MODE;
			arr[Loopcounter].Periodicity = 0u;
			break;
		}
		else
		{
			/*Do Nothing*/
		}
	}
}

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
void SOS_DeInit(void)
{
	TIMER_Deinit();
	uint8 LoopCounter = 0;
	/*loop to ReInitialize the array of tasks*/
	for(LoopCounter = 0u; LoopCounter<ID_MAX; LoopCounter++)
	{
		/*switch task state to Waiting State*/
		arr[LoopCounter].Mode = SOS_WAITING_MODE;
		/*ReInitialize tasks Periodicity*/
		arr[LoopCounter].Periodicity = 0u;
		/*ReInitialize the tasks array*/
		arr[LoopCounter].Task_Ptr = NULL_PTR;
	}
}




