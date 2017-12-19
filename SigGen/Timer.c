
#include "cmsis_os.h"                                           // CMSIS RTOS header file
#include "stm32F10x.h"
#define ARM_MATH_CM3
#include "arm_math.h"

/*----------------------------------------------------------------------------
 *      Timer: Sample timer functions
 *---------------------------------------------------------------------------*/
static void Timer2_Callback (void const *arg);                  // prototype for timer callback function
static osTimerId id2;                                           // timer id
static osTimerDef (Timer2, Timer2_Callback);                    // define timers
uint16_t sample; 
extern osThreadId tid_Output;

// Periodic Timer Function
static void Timer2_Callback (void const *arg)
{
	//Sawtooth
	/*
	static int i = 0;
 	GPIOA->ODR ^= 1UL<<9;
	i++;
	if (i>9) i=0;
	sample = 1 * 400;
	osSignalSet(tid_Output, 0x05);
	*/
	
	//Sine
	static float32_t i = 0;
	i++;
	sample = (int)(arm_sin_f32(i/5) * 1000 + 2014);
	osSignalSet(tid_Output, 0x05);
}

// Example: Create and Start timers
void Init_Timers (void) {
  osStatus status;                                              // function return status
 
  // Create periodic timer
  id2 = osTimerCreate (osTimer(Timer2), osTimerPeriodic, NULL);
  if (id2 != NULL) {    // Periodic timer created
    // start timer with periodic 10ms interval
    status = osTimerStart (id2, 10);            
    if (status != osOK) {
      // Timer could not be started
    }
  }
}
