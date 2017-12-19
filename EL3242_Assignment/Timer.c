
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
uint16_t y0; 
extern osThreadId tid_Output;

// Periodic Timer Function
static void Timer2_Callback (void const *arg)
{	
	//Sine
	static float32_t y1 = 1.0;
	static float32_t y2 = 1.0;
	y0 = 1.5*y1 - y2;
	y2 = y1;
	y1 = y0;
	osSignalSet(tid_Output, 0x05);
}

// Example: Create and Start timers
void Init_Timers (void) {
  osStatus status;                                              // function return status
 
  // Create periodic timer
  id2 = osTimerCreate (osTimer(Timer2), osTimerPeriodic, NULL);
  if (id2 != NULL) {    // Periodic timer created
    // start timer with periodic 10ms interval
    status = osTimerStart (id2, 2);            
    if (status != osOK) {
      // Timer could not be started
    }
  }
}
