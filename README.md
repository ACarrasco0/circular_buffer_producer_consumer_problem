# Circular Buffer Producer–Consumer

## Requirements

- GCC or another C compiler compatible with the Makefile
- `make`
- POSIX threads (`pthread`)

## Quick Start

```sh
make run
```

The program is interactive and will ask for:

- Buffer size
- Number of producers
- Producer delay
- Consumer mode (`0` = half, `1` = direct)

## Description

This project implements a producer–consumer system in C with a circular buffer, pthreads, mutexes, and condition variables.

## Objective

- Simulate a real-time data pipeline
- Measure latency, throughput, and data loss
- Compare direct and batch consumer modes

## How it works

- Producers generate data and push it into the shared buffer.
- One consumer waits for available data and processes it.
- Mutexes and condition variables coordinate access.

## Consumer Modes

### Direct mode (`mode = 1`)

The consumer processes all available data as soon as it wakes up.

![Direct mode](docs/consumer_direct.png)

### Half mode (`mode = 0`)

The consumer waits until the buffer reaches at least half capacity before processing.

![Half mode](docs/consumer_half.png)

### Runtime prompt

The program asks for the runtime configuration when it starts.

![Half mode](docs/main_asking.png)

```sh
make
```

Builds the executable `app`.

```sh
./app
```

Stop with `Ctrl + C`.

## Tests

To run unit tests:

```sh
make test
```

Builds and runs `test_runner`.

```sh
./test_runner
```

## Clean

To remove compiled files and binaries:

```sh
make clean
```

Deletes build files and the binaries `app` and `test_runner`.

## Project Structure

```text
app
main.c
Makefile
test_runner
TODO
inc/
  circular_buffer.h
  mutex.h
  p_c_ctx.h
  producer_consumer.h
  stats.h
  system.h
src/
  circular_buffer.c
  mutex.c
  producer_consumer.c
  stats.c
  system.c
tests/
  circular_buffer_test.c
  stats_test.c
  mocks/
    mutex_mock.c
    mutex_mock.h
    system_mock.c
    system_mock.h
```

## Conclusions

- The system runs without data loss.
- Throughput is stable in both consumer modes.
- Half mode does not significantly improve performance here.
- Most latency variation comes from scheduling and synchronization overhead.