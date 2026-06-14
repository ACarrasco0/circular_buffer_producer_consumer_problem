#include <assert.h>
#include <stdio.h>
#include "circular_buffer.h"

static DATA_T make_data(uint8_t value)
{
    return (DATA_T){.id = 0, .timestamp = 0, .data = value};
}

void test_normal_operation()
{
    CIRCULAR_BUFFER_T* cb = cb_init(4);

    assert(cb_is_empty(cb));

    cb_push(cb, make_data(10));
    cb_push(cb, make_data(20));

    assert(!cb_is_empty(cb));
    assert(cb_pop(cb).data == 10);
    assert(cb_pop(cb).data == 20);

    assert(cb_is_empty(cb));

    cb_deinit(cb);

    printf("test_normal_operation OK\n");
}

void test_overflow()
{
    CIRCULAR_BUFFER_T* cb = cb_init(3);

    assert(cb_push(cb, make_data(1)) == 0);
    assert(cb_push(cb, make_data(2)) == 0);
    assert(cb_push(cb, make_data(3)) != 0);


    assert(cb_is_full(cb));

    cb_deinit(cb);

    printf("test_overflow OK\n");
}

void test_underflow()
{
    CIRCULAR_BUFFER_T* cb = cb_init(3);

    assert(cb_is_empty(cb));


    DATA_T value = cb_pop(cb);
    (void)value; // Suppress unused variable warning

    assert(cb_is_empty(cb));

    cb_deinit(cb);

    printf("test_underflow OK\n");
}

void test_wrap_around()
{
    CIRCULAR_BUFFER_T* cb = cb_init(4);

    assert(cb_push(cb, make_data(1)) == 0);
    assert(cb_push(cb, make_data(2)) == 0);
    assert(cb_push(cb, make_data(3)) == 0);

    assert(cb_pop(cb).data == 1);

    assert(cb_push(cb, make_data(4)) == 0);


    assert(cb_pop(cb).data == 2);
    assert(cb_pop(cb).data == 3);
    assert(cb_pop(cb).data == 4);

    assert(cb_is_empty(cb));

    cb_deinit(cb);

    printf("test_wrap_around OK\n");
}

int main()
{
    test_normal_operation();
    test_overflow();
    test_underflow();
    test_wrap_around();

    printf("ALL TESTS PASSED\n");
    return 0;
}