#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>
extern volatile uint8_t app_running;  

void setup_signals(void);
uint64_t get_tiemstamp_in_us(void);

#endif