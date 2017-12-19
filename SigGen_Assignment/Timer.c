
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
float32_t y0; 
extern osThreadId tid_Output;
extern int toggle_period;
extern int period_change;
void Init_Timers (void);

// Periodic Timer Function
static void Timer2_Callback (void const *arg)
{	
	//Sine Wave Generator
	static float32_t y1 = 1.0;
	static float32_t y2 = 1.0;
	y0 = 1.5*y1 - y2;
	y2 = y1;
	y1 = y0;
	//Send signal to output thread
	osSignalSet(tid_Output, 0x05);
	
	//Reset timer if period change
	if (period_change)
	{
		osStatus status; 
		osTimerStop(id2);
		if (status != osOK) {
      // Timer could not be stopped
    }
		osTimerDelete(id2);
		if (status != osOK) {
      // Timer could not be deleted
    }
		Init_Timers();
		period_change = 0;
	}
}

// Example: Create and Start timers
void Init_Timers (void) {
  osStatus status;                                              // function return status
 
  // Create periodic timer
  id2 = osTimerCreate (osTimer(Timer2), osTimerPeriodic, NULL);
  if (id2 != NULL) {    // Periodic timer created
    // start timer with periodic user defined interval
    status = osTimerStart (id2, toggle_period);            
    if (status != osOK) {
      // Timer could not be started
    }
  }
}
