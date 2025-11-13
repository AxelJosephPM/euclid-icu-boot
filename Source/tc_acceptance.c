#include "tc_acceptance.h"
#include "user_types.h"
#include "tc_queue.h"
#include "isocheck.h"

extern u32 major_frame_cnt; // (Reflecting the number of seconds).
extern u32 comm_frame_cnt;
extern u32 accepted_tc_cnt; // (Number of accepted TCs).
extern u32 rejected_tc_cnt; // (Number of rejected TCs).
extern u32 executed_tc_cnt; // (Number of executed TCs).
extern t_tc_queue tc_queue;

static bool execution_allowed = FALSE; // Flag indicating whether the current telecommand (TC) is allowed to execute.
static u8 incoming_tc[ELEMENT_SIZE]; // Buffer to store the currently received telecommand (TC) extracted from the queue.
static u32 tc_size; // Size in bytes of the current telecommand (TC) stored in incoming_tc.

// Checks if there is a telecommand (TC) in the queue and extracts it if available.
void check_and_extract_tc_item(void)
{
  bool is_empty;

  // Check whether the TC queue is empty.
  is_empty = tc_queue_is_empty(&tc_queue);

  // If there is a TC available, extract it and allow execution.
  if (is_empty == FALSE)
  {
    // Extract one TC from the queue into the incoming_tc buffer and store its size.
    tc_size = tc_queue_extract_item(&tc_queue, incoming_tc);

    // Allow execution of the extracted TC.
    execution_allowed = TRUE;
  }
}

// Performs TC(6,2) acceptance checks, including checksum and field validation.
void check_tc_acceptance(void)
{
  u16 iso_checkval;

  // Only proceed if execution is currently allowed.
  if (execution_allowed == TRUE)
  {
    // Calculate ISO checksum of the entire TC message excluding the last 2 checksum bytes.
    iso_checkval = calculate_iso_checksum(incoming_tc, tc_size - TC62_CHECKSUM_SIZE);

    // Compare calculated checksum with the one appended at the end of the message.
    if (iso_checkval == ((incoming_tc[tc_size - 2] << 8) | incoming_tc[tc_size - 1])) 
    {
      // Extract fields from the incoming TC packet.
      u8 service_type = incoming_tc[TC_SERVICE_TYPE_INDEX];
      u8 service_subtype = incoming_tc[TC_SERVICE_SUBTYPE_INDEX];
      u16 num_bytes = (incoming_tc[TC_NUM_BYTES_MSB_INDEX] << 8) |
                       incoming_tc[TC_NUM_BYTES_LSB_INDEX];
      u32 address = (incoming_tc[TC_ADDRESS_MSB_INDEX] << 24) |
                    (incoming_tc[TC_ADDRESS_BYTE2_INDEX] << 16) |
                    (incoming_tc[TC_ADDRESS_BYTE1_INDEX] << 8) |
                     incoming_tc[TC_ADDRESS_LSB_INDEX];

      // Validate service type, subtype, data size, and memory address range.
      if (service_type == 6 &&
          service_subtype == 2 &&
          num_bytes >= 1 && num_bytes <= 992 &&
          address >= 0x1FFF0000 && address <= 0x2002FFFF &&
          (address + num_bytes - 1) <= 0x2002FFFF)
      {
        // All checks passed: accept the TC and allow execution.
        execution_allowed = TRUE;
        accepted_tc_cnt++;
      }
      else 
      {
        // TC is invalid due to incorrect parameters: reject it.
        execution_allowed = FALSE;
        rejected_tc_cnt++;
      }
    }
    else 
    {
      // Checksum mismatch: reject the TC.
      execution_allowed = FALSE;
      rejected_tc_cnt++;
    }
  }
}

// Executes a TC(6,2) command: loads data into RAM at a given address.
void tc_execute(void)
{
  // Only execute the command if it's allowed.
  if (execution_allowed == TRUE)
  {
    // Extract the number of bytes to load from the TC packet (2 bytes, big endian).
    u16 num_bytes = (incoming_tc[TC_NUM_BYTES_MSB_INDEX] << 8) |
                     incoming_tc[TC_NUM_BYTES_LSB_INDEX];

    // Extract the RAM start address from the TC packet (4 bytes, big endian).
    u32 address = (incoming_tc[TC_ADDRESS_MSB_INDEX] << 24) |
                  (incoming_tc[TC_ADDRESS_BYTE2_INDEX] << 16) |
                  (incoming_tc[TC_ADDRESS_BYTE1_INDEX] << 8) |
                   incoming_tc[TC_ADDRESS_LSB_INDEX];

    // Cast the extracted address to a byte pointer.
    u8* tc_dest = (u8*)address;

    // Copy each byte of the data field from the TC packet into the target RAM location.
    for (u32 i = 0; i < num_bytes; i++)
    {
      tc_dest[i] = incoming_tc[TC62_HEADER_SIZE + i];
    }

    // Increment the counter of successfully executed TCs.
    executed_tc_cnt++;
  }
}
