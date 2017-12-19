
#include "cmsis_os.h"                                           // CMSIS RTOS header file
#include "stm32f10x.h"

/*----------------------------------------------------------------------------
 *      Thread 2 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
 
void Thread2 (void const *argument);                             // thread function
osThreadId tid_Thread2;                                          // thread id
osThreadDef (Thread2, osPriorityNormal, 1, 0);                   // thread object

int Init_Thread2 (void) {

  tid_Thread2 = osThreadCreate (osThread(Thread2), NULL);
  if (!tid_Thread2) return(-1);
  
  return(0);
}

void Thread2 (void const *argument) {

  while (1) {
    GPIOA->ODR |= 1UL<<9; //PA9 OFF (HIGH)
		GPIOA->ODR &= ~(1UL<<10); //PA10 ON (LOW)
    //osThreadYield ();                                           // suspend thread
  }
}
