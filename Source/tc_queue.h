#ifndef TC_QUEUE_H_INCLUDED
#define TC_QUEUE_H_INCLUDED

#include "user_types.h"

#define NUM_ITEMS 5
#define BUFFER_SIZE (NUM_ITEMS + 1)
#define ELEMENT_SIZE 1040

typedef struct
{
    u8 data[ELEMENT_SIZE]; // array where element data are stored; to be handled as a circular buffer.
    u32 num_bytes; // real number of bytes of each element stored in queue.

} t_queue_element;

typedef struct
{
    u32 insert_index; // insert index.
    u32 extract_index; // extract index.
    t_queue_element buffer[BUFFER_SIZE]; // buffer to hold messages.

} t_tc_queue;


void tc_queue_init(t_tc_queue* queue);
bool tc_queue_is_empty(const t_tc_queue* queue);
bool tc_queue_is_full(const t_tc_queue* queue);
bool tc_queue_insert_item(t_tc_queue* queue, const u8 item[], const u32 item_size);
u32 tc_queue_extract_item(t_tc_queue* queue, u8 item[]);


#endif // TC_QUEUE_H_INCLUDED
