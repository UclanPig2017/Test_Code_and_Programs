
#include "cmsis_os.h"                                           // CMSIS RTOS header file
#include "stm32F10x.h"
#define ARM_MATH_CM3
#include "arm_math.h"

/*----------------------------------------------------------------------------
 *      Thread 1 'Output': Takes value and outputs to DAC on GPIOA4
 *---------------------------------------------------------------------------*/
//y0 is Sine Wave Generator Output
extern float32_t y0; 
 
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
		//Wait until signal to go is given by timer function
    osSignalWait(0x05, osWaitForever);	
		DAC->DHR12R1  = (y0*4095/3.3 + 2048);												// Scale Sine Wave value and output to DAC
    osThreadYield ();                                           // suspend thread
  }
}
