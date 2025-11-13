
#include "user_types.h"
#include "systick.h"
#include "tc_queue.h"
#include "tc_acceptance.h"

u32 major_frame_cnt; // (Reflecting the number of seconds).
u32 comm_frame_cnt ; // (Current communication frame within a second [0,49]).
u32 accepted_tc_cnt; // (Number of accepted TCs).
u32 rejected_tc_cnt; // (Number of rejected TCs).
u32 executed_tc_cnt; // (Number of executed TCs).
t_tc_queue tc_queue; // (TC queue).

// Main Task.
int main(void)
{
  // systick configuration.
  #define INTERRUPT_PERIOD 400000 // 400000 CPU clock cycles at 20 MHz clock speed.
  bool enable = TRUE;
  bool tickint = TRUE;
  bool internalclk = TRUE;


  systick_set_reload(INTERRUPT_PERIOD);
  systick_set_control(enable, tickint, internalclk);
  

  // Infinite command loop.
  while( TRUE )
  {
    // TC reception.
    check_and_extract_tc_item();

    // TC acceptance and execution.
    check_tc_acceptance();
    tc_execute();

  }

  return 0;
}



