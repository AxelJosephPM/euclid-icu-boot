#ifndef HW_MAP_H_INCLUDED
#define HW_MAP_H_INCLUDED


#define PROM_START_ADDR      0x00000000

#define RAM_START_ADDR       0x1FFF0000
#define RAM_SIZE             (256*1024)
#define RAM_END_ADDR         (RAM_START_ADDR + RAM_SIZE - 1)

// systick registers.
#define SYSTICK_CTRL_ADDR    0xE000E010
#define SYSTICK_RELOAD_ADDR  0xE000E014

#endif 
