#ifndef SYSTEM_MOCK_H
#define SYSTEM_MOCK_H

#include <stdint.h>

uint64_t get_tiemstamp_in_us(void);
void set_mock_time(uint64_t t);

#endif