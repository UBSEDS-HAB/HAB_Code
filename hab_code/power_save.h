#ifndef __POWER_SAVE_H__
#define __POWER_SAVE_H__

void power_down(void);

/*
Register values for 
Setups up 
*/
enum sleep_time {
    SLEEP_MS_16 = 0x0,
    SLEEP_MS_32 = 0x1,
    SLEEP_MS_64 = 0x2,
    SLEEP_MS_125 = 0x3,
    SLEEP_MS_250 = 0x4, 
    SLEEP_MS_500 = 0x5,
    SLEEP_S_1 = 0x6,
    SLEEP_S_2 = 0x7,
    SLEEP_S_4 = 0x20,
    SLEEP_S_8 = 0x21,
};

#endif