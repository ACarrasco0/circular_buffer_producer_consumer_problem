#include <assert.h>
#include <stdio.h>
#include "stats.h"
#include "system_mock.h"
#include "mutex_mock.h"

// asumimos DATA_T es struct, no puntero
static DATA_T make_data(uint64_t timestamp)
{
    DATA_T d;
    d.timestamp = timestamp;
    return d;
}

void test_init()
{
    set_mock_time(1000);

    data_stats_init();

    data_stats_deinit();

    printf("test_init OK\n");
}

void test_number_generated()
{
    data_stats_init();

    uint64_t a = get_number_data_generated();
    uint64_t b = get_number_data_generated();
    uint64_t c = get_number_data_generated();

    assert(a == 0);
    assert(b == 1);
    assert(c == 2);

    data_stats_deinit();

    printf("test_number_generated OK\n");
}

void test_processing_basic()
{
    set_mock_time(1000);
    data_stats_init();

    DATA_T d1 = make_data(900);
    DATA_T d2 = make_data(800);

    data_processing(d1);
    set_mock_time(1100);
    data_processing(d2);

    assert(data_stats.num_processed_samples == 2);
    assert(data_stats.diff_max > 0);

    data_stats_deinit();

    printf("test_processing_basic OK\n");
}

void test_deinit()
{
    data_stats_init();
    data_stats_deinit();

    // doble free safety
    data_stats_deinit();

    printf("test_deinit OK\n");
}

int main()
{
    test_init();
    test_number_generated();
    test_processing_basic();
    test_deinit();

    printf("ALL TESTS PASSED\n");
    return 0;
}