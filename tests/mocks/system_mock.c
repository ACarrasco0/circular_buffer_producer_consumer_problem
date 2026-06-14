#include "system_mock.h"

static uint64_t mock_time = 0;

uint64_t get_tiemstamp_in_us(void)
{
    return mock_time;
}

void set_mock_time(uint64_t t)
{
    mock_time = t;
}