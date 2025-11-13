
#ifndef TC_ACCEPTANCE_H_INCLUDED
#define TC_ACCEPTANCE_H_INCLUDED


#define TC_SERVICE_TYPE_INDEX 0 // Index of the "Service Type" field (1 byte, fixed value: 6).

#define TC_SERVICE_SUBTYPE_INDEX 1 // Index of the "Service Subtype" field (1 byte, fixed value: 2).

#define TC_NUM_BYTES_MSB_INDEX 2 // Index of the most significant byte of the "Number of Bytes to Load" field (2 bytes, big endian).

#define TC_NUM_BYTES_LSB_INDEX 3 // Index of the least significant byte of the "Number of Bytes to Load" field.

#define TC_ADDRESS_MSB_INDEX 4 // Index of the most significant byte of the "RAM Start Address" field (4 bytes, big endian).

#define TC_ADDRESS_BYTE2_INDEX 5 // Index of the second most significant byte of the "RAM Start Address".

#define TC_ADDRESS_BYTE1_INDEX 6 // Index of the second least significant byte of the "RAM Start Address".

#define TC_ADDRESS_LSB_INDEX 7 // Index of the least significant byte of the "RAM Start Address".

// Total size (in bytes) of the TC(6,2) packet header before the data section.
#define TC62_HEADER_SIZE 8 // Includes: Service Type (1) + Subtype (1) + Num Bytes (2) + RAM Address (4).

#define TC62_CHECKSUM_SIZE 2 // Size (in bytes) of the ISO checksum field at the end of the TC(6,2) packet.


void check_and_extract_tc_item(void);
void check_tc_acceptance(void);
void tc_execute(void);

#endif