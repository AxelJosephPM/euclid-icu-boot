#include "tc_queue.h"

void tc_queue_init(t_tc_queue* queue)
{
  queue -> insert_index = 0;
  queue -> extract_index = 0;

  for (u32 i = 0; i < BUFFER_SIZE; i++)
  {
    queue -> buffer[i] = (t_queue_element){0}; // Initialize the i-th packet in the buffer with all fields set to zero.
  }                                            // This uses a compound literal, available from ISO C99.
}

bool tc_queue_is_empty(const t_tc_queue* queue) // Every extract checks the tc_queue_is_empty condition.
{
  bool value = FALSE;

  if (queue -> extract_index - queue -> insert_index == 0)
  {
    value = TRUE;
  }
  return value; // Returns true if the queue is empty (extract and insert indices are equal).
}

bool tc_queue_is_full(const t_tc_queue* queue) // Every insert checks the tc_queue_is_full condition.
{
  bool value = FALSE;
  
  if (queue -> extract_index >= queue -> insert_index && queue -> extract_index - queue -> insert_index == 1)
  {
    value =TRUE;
  }
  if (queue -> extract_index < queue -> insert_index && queue -> extract_index + (NUM_ITEMS +1) - queue -> insert_index == 1) 
  {
    value = TRUE;
  }
  return value; // Returns true if the queue is full (one slot is always left empty to differentiate full from empty).
}

bool tc_queue_insert_item(t_tc_queue* queue, const u8 item[], const u32 item_size) // Copies "item" into the buffer at the current insert position.         
{
  bool frst_verif = FALSE;
  bool item_could_be_inserted = FALSE;

  frst_verif = tc_queue_is_full(queue);

  if (frst_verif == TRUE)
  {
    item_could_be_inserted = FALSE;
  }

  if (frst_verif != TRUE)
  {
    for (u32 i = 0; i < item_size; i++)
    {
      queue -> buffer[queue -> insert_index].data[i] = item[i];
    }

    queue -> buffer[queue -> insert_index].num_bytes = item_size;

    queue -> insert_index = queue -> insert_index + 1; // Increment index "insert".

    if (queue -> insert_index == NUM_ITEMS + 1) // return index "insert" to 0.
    {
      queue -> insert_index = 0;
    }
    
    item_could_be_inserted = TRUE; 
  }

  return item_could_be_inserted; // Return TRUE (item was inserted correctly); FALSE if the queue was full.
}

u32 tc_queue_extract_item(t_tc_queue* queue, u8 item[]) // Copies the next item from the queue buffer into the user-provided array "item".
{
  bool frst_verif = FALSE;
  u32 result;

  frst_verif = tc_queue_is_empty(queue);

  if (frst_verif == TRUE)
  {
    result = 0;
  }

  if (frst_verif != TRUE)
  {
    result = queue -> buffer[queue -> extract_index].num_bytes;

    for (u32 i = 0; i < result; i++)
    {
      item[i] = queue -> buffer[queue -> extract_index].data[i];
    }

    queue -> extract_index = queue -> extract_index + 1; // Increment index "extract".

    if (queue -> extract_index == NUM_ITEMS + 1)
    {
      queue -> extract_index = 0;
    }
  }
  return result; // Returns the number of bytes extracted. Returns 0 if queue was empty.
}