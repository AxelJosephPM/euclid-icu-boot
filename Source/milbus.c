
#include "user_types.h"
#include "milbus.h"

#define NUM_MSGS_MILBUS 16

static u8 milbus_msgs_data[NUM_MSGS_MILBUS] [MAX_LEN_MSGS_MILBUS];
static u16 milbus_msgs_len [NUM_MSGS_MILBUS];
static u32 milbus_msgs_sent_index = 0;

void send_msg_to_milbus(u8 msg_sent[],u16 size)
{
  milbus_msgs_len[milbus_msgs_sent_index] = size;

  for (u32 i = 0; i < size ; i++)
    milbus_msgs_data[milbus_msgs_sent_index][i] = msg_sent[i];
  
  milbus_msgs_sent_index++;

  if (milbus_msgs_sent_index == NUM_MSGS_MILBUS)
    milbus_msgs_sent_index = 0;
}

u16 receive_msg_from_milbus(u8 msg_received[])
{
  static u32 milbus_msgs_received_index = 0;
  u16 msg_size = 0;
  
  if (milbus_msgs_received_index != milbus_msgs_sent_index)
  {
    msg_size = milbus_msgs_len[milbus_msgs_received_index];
    for (u32 i = 0; i < msg_size ; i++)
      msg_received[i] = milbus_msgs_data[milbus_msgs_received_index][i];
  
    milbus_msgs_received_index++;
    if (milbus_msgs_received_index == NUM_MSGS_MILBUS)
      milbus_msgs_received_index = 0;
  }
  return msg_size;
}