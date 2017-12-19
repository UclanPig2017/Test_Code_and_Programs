
#include "cmsis_os.h"                                           // CMSIS RTOS header file
#include "stm32F10x.h"

/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
extern uint16_t sample; 
 
void Output (void const *argument);                             // thread function
osThreadId tid_Output;                                          // thread id
osThreadDef (Output, osPriorityNormal, 1, 0);                   // thread object

int Init_Output (void) {

  tid_Output = osThreadCreate (osThread(Output), NULL);
  if (!tid_Output) return(-1);
  return(0);
}

void Output (void const *argument) {

  while (1) {
    osSignalWait(0x05, osWaitForever);													
		DAC->DHR12R1  = sample;
    osThreadYield ();                                           // suspend thread
  }
}
