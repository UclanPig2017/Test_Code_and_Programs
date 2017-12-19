#include "cmsis_os.h"                                           // CMSIS RTOS header file
#include "stm32f10x.h"

/*----------------------------------------------------------------------------
 *      Thread 2 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 
 extern int delay_config;
 
void Thread2 (void const *argument);                             // Thread2 function
osThreadId tid_Thread2;                                          // thread id
osThreadDef (Thread2, osPriorityNormal, 1, 0);                   // thread object

int Init_Thread2 (void) {

  tid_Thread2 = osThreadCreate (osThread(Thread2), NULL);
  if (!tid_Thread2) return(-1);
  
  return(0);
}

void Thread2 (void const *argument) {

  while (1) {
    GPIOA->ODR ^= 1UL<<10; // Toggle Pin 10
		osDelay(delay_config);
    osThreadYield ();                                           // suspend thread
  }
}

