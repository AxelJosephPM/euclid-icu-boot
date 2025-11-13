#include "user_types.h"
#include "it_tcmd_test.h"
#include "milbus.h"
#include "isocheck.h"
#include "unity.h"
#include "tc_acceptance.h"

extern u32 major_frame_cnt; // (Reflecting the number of seconds)
extern u32 comm_frame_cnt;
extern u32 accepted_tc_cnt; // (Number of accepted TCs)
extern u32 rejected_tc_cnt; // (Number of rejected TCs)
extern u32 executed_tc_cnt; // (Number of executed TCs)

void it_tcmd_090_run_part11(void)
{
  u16 isocheck_val;

  // TC(6,2) 1: 0x20010000, size 992, data = 0x00++.
  u8 tc1[TC62_HEADER_SIZE + 992 + TC62_CHECKSUM_SIZE] = { 0x06, 0x02, 0x03, 0xE0, 0x20, 0x01, 0x00, 0x00 };
  for (int i = 0; i < 992; i++)
  {
    tc1[TC62_HEADER_SIZE + i] = (u8)(0x00 + i);
  }
  isocheck_val = calculate_iso_checksum(tc1, sizeof(tc1) - TC62_CHECKSUM_SIZE);
  tc1[sizeof(tc1) - 2] = (isocheck_val >> 8);
  tc1[sizeof(tc1) - 1] = isocheck_val;
  send_msg_to_milbus(tc1, sizeof(tc1));

  // TC(6,2) 2: 0x20010400, size 992, data = 0x80++.
  u8 tc2[TC62_HEADER_SIZE + 992 + TC62_CHECKSUM_SIZE] = { 0x06, 0x02, 0x03, 0xE0, 0x20, 0x01, 0x04, 0x00 };
  for (int i = 0; i < 992; i++)
  {
    tc2[TC62_HEADER_SIZE + i] = (u8)(0x80 + i);
  }
  isocheck_val = calculate_iso_checksum(tc2, sizeof(tc2) - TC62_CHECKSUM_SIZE);
  tc2[sizeof(tc2) - 2] = (isocheck_val >> 8);
  tc2[sizeof(tc2) - 1] = isocheck_val;
  send_msg_to_milbus(tc2, sizeof(tc2));
  
  // TC(6,2) 3: 0x20010803, size 3, data = 0xFA, 0xBA, 0xDA.
  u8 tc3[TC62_HEADER_SIZE + 3 + TC62_CHECKSUM_SIZE] = { 0x06, 0x02, 0x00, 0x03, 0x20, 0x01, 0x08, 0x03, 0xFA, 0xBA, 0xDA };
  isocheck_val = calculate_iso_checksum(tc3, sizeof(tc3) - TC62_CHECKSUM_SIZE);
  tc3[sizeof(tc3) - 2] = (isocheck_val >> 8);
  tc3[sizeof(tc3) - 1] = isocheck_val;
  send_msg_to_milbus(tc3, sizeof(tc3));
}

void it_tcmd_090_run_part12(void)
{
  u16 isocheck_val;

  // TC(6,2) 4: 0x20010000, size 993, data = 0xFF++.
  u8 tc4[TC62_HEADER_SIZE + 993 + TC62_CHECKSUM_SIZE] = { 0x06, 0x02, 0x03, 0xE1, 0x20, 0x01, 0x00, 0x00 };
  for (int i = 0; i < 993; i++)
  {
    tc4[TC62_HEADER_SIZE + i] = (u8)(0xFF + i);
  }
  isocheck_val = calculate_iso_checksum(tc4, sizeof(tc4) - TC62_CHECKSUM_SIZE);
  tc4[sizeof(tc4) - 2] = (isocheck_val >> 8);
  tc4[sizeof(tc4) - 1] = isocheck_val;
  send_msg_to_milbus(tc4, sizeof(tc4));

  // TC(6,2) 5: 0x20010000, size 0, data = 0x01.
  u8 tc5[TC62_HEADER_SIZE + 1 + TC62_CHECKSUM_SIZE] = { 0x06, 0x02, 0x00, 0x00, 0x20, 0x01, 0x00, 0x00, 0x01 };
  isocheck_val = calculate_iso_checksum(tc5, sizeof(tc5) - TC62_CHECKSUM_SIZE);
  tc5[sizeof(tc5) - 2] = (isocheck_val >> 8);
  tc5[sizeof(tc5) - 1] = isocheck_val;
  send_msg_to_milbus(tc5, sizeof(tc5));
}

void it_tcmd_090_run_part21(void)
{
  u16 isocheck_val;
  
  // TC(6,2) 1: Load RAM Memory - 0x2002FFFC, size = 5, data = 0x50++.
  u8 tc1[TC62_HEADER_SIZE + 5 + TC62_CHECKSUM_SIZE] = { 0x06, 0x02, 0x00, 0x05,
                                                        0x20, 0x02, 0xFF, 0xFC,
                                                        0x50, 0x51, 0x52, 0x53, 0x54 };
  isocheck_val = calculate_iso_checksum(tc1, sizeof(tc1) - TC62_CHECKSUM_SIZE);
  tc1[sizeof(tc1) - 2] = (isocheck_val >> 8);
  tc1[sizeof(tc1) - 1] = isocheck_val;
  send_msg_to_milbus(tc1, sizeof(tc1));

  // TC(6,2) 2: Load RAM Memory - 0x1FFEFFFC, size = 5, data = 0x05++.
  u8 tc2[TC62_HEADER_SIZE + 5 + TC62_CHECKSUM_SIZE] = { 0x06, 0x02, 0x00, 0x05,
                                                        0x1F, 0xFE, 0xFF, 0xFC,
                                                        0x05, 0x06, 0x07, 0x08, 0x09 };
  isocheck_val = calculate_iso_checksum(tc2, sizeof(tc2) - TC62_CHECKSUM_SIZE);
  tc2[sizeof(tc2) - 2] = (isocheck_val >> 8);
  tc2[sizeof(tc2) - 1] = isocheck_val;
  send_msg_to_milbus(tc2, sizeof(tc2));

  // TC(6,2) 3: Load RAM Memory - 0x20010000, size = 992, data = 0xEE++, bad ISO checksum.
  u8 tc3[TC62_HEADER_SIZE + 992 + TC62_CHECKSUM_SIZE] = { 0x06, 0x02, 0x03, 0xE0, 0x20, 0x01, 0x00, 0x00 };
  for (int i = 0; i < 992; i++)
  {
    tc3[TC62_HEADER_SIZE + i] = (u8)(0xEE + i);
  }
  tc3[sizeof(tc3) - 2] = 0x00; // intentionally bad checksum.
  tc3[sizeof(tc3) - 1] = 0x01;
  send_msg_to_milbus(tc3, sizeof(tc3));

}

void it_tcmd_090_run_part22(void)
{
  u16 isocheck_val;
  
  // TC(6,5) 4: Dump Memory - same structure as first TC(6,2), only subtype changes.
  u8 tc4[TC62_HEADER_SIZE + 5 + TC62_CHECKSUM_SIZE] = { 0x06, 0x05, 0x00, 0x05,
                                                        0x20, 0x02, 0xFF, 0xFC,
                                                        0x50, 0x51, 0x52, 0x53, 0x54 };
  isocheck_val = calculate_iso_checksum(tc4, sizeof(tc4) - TC62_CHECKSUM_SIZE);
  tc4[sizeof(tc4) - 2] = (isocheck_val >> 8);
  tc4[sizeof(tc4) - 1] = isocheck_val;
  send_msg_to_milbus(tc4, sizeof(tc4));

  // TC(17,1) 5: Connection test - same structure, only type and subtype change.
  u8 tc5[TC62_HEADER_SIZE + 5 + TC62_CHECKSUM_SIZE] = { 0x11, 0x01, 0x00, 0x05,
                                                        0x20, 0x02, 0xFF, 0xFC,
                                                        0x50, 0x51, 0x52, 0x53, 0x54 };
  isocheck_val = calculate_iso_checksum(tc5, sizeof(tc5) - TC62_CHECKSUM_SIZE);
  tc5[sizeof(tc5) - 2] = (isocheck_val >> 8);
  tc5[sizeof(tc5) - 1] = isocheck_val;
  send_msg_to_milbus(tc5, sizeof(tc5));
}

void it_tcmd_090_check_funcs(void)
{
  // Verify RAM memory is loaded with correct data as expected, according to each TC(6,2) sent.
  u8* tc11_data =  (u8*)0x20010000;
  u8 expected_tc11[992];
  for (int i = 0; i < 992; i++)
  {
    expected_tc11[i] = (u8)(0x00 + i);
  }
  TEST_ASSERT_EQUAL_HEX8_ARRAY_MESSAGE(expected_tc11 , tc11_data, 992, "FAIL: Mismatch on it_tcmd_090_run_part11 – expected tc1 != actual tc1");
    
  u8* tc12_data =  (u8*)0x20010400;
  u8 expected_tc12[992];
  for (int i = 0; i < 992; i++)
  {
    expected_tc12[i] = (u8)(0x80 + i);
  }
  TEST_ASSERT_EQUAL_HEX8_ARRAY_MESSAGE(expected_tc12 , tc12_data, 992, "FAIL: Mismatch on it_tcmd_090_run_part11 – expected tc2 != actual tc2");

  u8* tc13_data =  (u8*)0x20010803;
  u8 expected_tc13[3] = { 0xFA, 0xBA, 0xDA };
  TEST_ASSERT_EQUAL_HEX8_ARRAY_MESSAGE(expected_tc13 , tc13_data, 3, "FAIL: Mismatch on it_tcmd_090_run_part11 – expected tc3 != actual tc3");

  // Verify TC counters contain correct values: accepted_tc_cnt = 3, rejected_tc_cnt = 7, executed_tc_cnt = 3
  TEST_ASSERT_EQUAL_UINT(3, accepted_tc_cnt);
  TEST_ASSERT_EQUAL_UINT(7, rejected_tc_cnt);
  TEST_ASSERT_EQUAL_UINT(3, executed_tc_cnt);
}

void it_tcmd_090_run(void)
{
  if (major_frame_cnt == 1 && comm_frame_cnt == 10)
  {
    UNITY_BEGIN();

    RUN_TEST(it_tcmd_090_run_part11);
    RUN_TEST(it_tcmd_090_run_part12);

    UNITY_END();
  }

  if (major_frame_cnt == 6 && comm_frame_cnt == 40)
  {
    UNITY_BEGIN();

    RUN_TEST(it_tcmd_090_run_part21);
    RUN_TEST(it_tcmd_090_run_part22);

    UNITY_END();
  }
}


void it_tcmd_090_check(void)
{
  if (major_frame_cnt == 10 && comm_frame_cnt == 0)
  {
    UNITY_BEGIN();

    RUN_TEST(it_tcmd_090_check_funcs);

    UNITY_END();
  }
}
