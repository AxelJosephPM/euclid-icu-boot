
#ifndef MILBUS_H
#define MILBUS_H

#include "user_types.h"

#define MAX_LEN_MSGS_MILBUS 1024

u16 receive_msg_from_milbus(u8 msg_received[]);
void send_msg_to_milbus(u8 msg_sent[], u16 size);

#endif


