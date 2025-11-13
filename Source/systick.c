
#include "systick.h"
#include "hw_map.h"


void systick_set_control(bool enable, bool tickint, bool clksource)
{
  u32* ptr32 = (u32*)SYSTICK_CTRL_ADDR;
  ptr32[0] = (enable << BIT_ENABLE) | (tickint << BIT_TICKINT) | (clksource << BIT_CLKSOURCE);
}

void systick_set_reload(u32 reload)
{
  u32* ptr32 = (u32*)SYSTICK_RELOAD_ADDR;
  ptr32[0] = reload;
}



#include "milbus.h"
#include "tc_queue.h"

#define INTEGRATION_TESTS

#ifdef INTEGRATION_TESTS
  #include "it_tcmd_test.h"
#endif

extern u32 comm_frame_cnt;
extern u32 major_frame_cnt;
extern t_tc_queue tc_queue;


// Sync Task.
void SysTick_Handler(void)
{
  // Update time counters.
  if (comm_frame_cnt == 49)
  {
    comm_frame_cnt = 0;
    major_frame_cnt++;
  }
  else 
  {
    comm_frame_cnt++;
  }

  // Receive messages from MILBUS.
  u8 msg_received[MAX_LEN_MSGS_MILBUS];
  u16 msg_size = receive_msg_from_milbus(msg_received);

  // Insert messages in TC queue.
  bool msg_could_be_inserted = TRUE;

  while (msg_could_be_inserted == TRUE && msg_size > 0)
  {
    msg_could_be_inserted = tc_queue_insert_item(&tc_queue, msg_received, msg_size);
    msg_size = receive_msg_from_milbus(msg_received);
  }

  #ifdef INTEGRATION_TESTS
    it_tcmd_090_run();
    it_tcmd_090_check();
  #endif

}


