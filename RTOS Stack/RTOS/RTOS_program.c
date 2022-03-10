#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "TIMER_interface.h"
#include "GIE_interface.h"

#include "RTOS_interface.h"
#include "RTOS_config.h"
#include "RTOS_private.h"

Task_t SystemTasks[TASK_NUM]={{NULL}};

void RTOS_voidStart(void){

	Timer0_u8CompmatchSetCallBack(&voidScheduler);
	GIE_voidEnableGlobal();
	Timer0_voidInit();
}

u8 RTOS_voidCreateTask(u8 Copy_u8Priority,u16 Copy_u16Periodicity,void (*Copy_pvTaskFunc)(void),u16 Copy_u16FirstDelay){

	u8 Local_u8ErrorState=OK;
	if(SystemTasks[Copy_u8Priority].TaskFunc==NULL){
	SystemTasks[Copy_u8Priority].Periodicity=Copy_u16Periodicity;
	SystemTasks[Copy_u8Priority].TaskFunc=Copy_pvTaskFunc;
	SystemTasks[Copy_u8Priority].State=TASK_RESUME;
	SystemTasks[Copy_u8Priority].FirstDelay=Copy_u16FirstDelay;
	}
	else Local_u8ErrorState=NOK;

	return Local_u8ErrorState;
}

static void voidScheduler(void){

	u8 Local_u8TaskCounter;

	//loop on all tasks to check their periodicity
	for(Local_u8TaskCounter=0;Local_u8TaskCounter<TASK_NUM;Local_u8TaskCounter++){
		if(SystemTasks[Local_u8TaskCounter].State==TASK_RESUME){
		if((SystemTasks[Local_u8TaskCounter].FirstDelay)==0){
			//invoke the task function
			if(SystemTasks[Local_u8TaskCounter].TaskFunc != NULL){
				SystemTasks[Local_u8TaskCounter].TaskFunc();
				SystemTasks[Local_u8TaskCounter].FirstDelay=SystemTasks[Local_u8TaskCounter].Periodicity-1;
			}
			else  SystemTasks[Local_u8TaskCounter].FirstDelay--;
		}
	  }
	}

}

void RTOS_voidSuspendTask(u8 Copy_u8Priority){
	SystemTasks[Copy_u8Priority].State=TASK_SUSPENDED;
}

void RTOS_voidResumeTask(u8 Copy_u8Priority){
	SystemTasks[Copy_u8Priority].State=TASK_RESUME;
}

void RTOS_voidDeleteTask(u8 Copy_u8Priority){
	SystemTasks[Copy_u8Priority].TaskFunc=NULL;
}
