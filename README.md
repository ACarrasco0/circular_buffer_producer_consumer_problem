# Circular Buffer Producer–Consumer

## Description

This project implements a producer–consumer system in C using:
- a circular buffer
- pthreads
- mutexes and condition variables

Multiple producer threads generate data continuously and push it into a shared buffer. A single consumer thread processes the data.

---

## Objective

- Simulate a real-time data pipeline
- Measure latency, throughput, and data loss
- Compare two consumer strategies:
  - direct consumption
  - batch consumption (half-buffer mode)

---

## How it works

### Producer
- Generates data periodically
- Pushes data into the circular buffer
- Multiple producers can run simultaneously

### Consumer
- Only one consumer thread
- Waits for data using a condition variable
- Processes data from the buffer

---

## Consumer modes

### Direct mode (`mode = 1`)

The consumer processes all available data immediately as soon as it wakes up.

![Direct mode](docs/consumer_direct/direct.png)

---

### Half mode (`mode = 0`)

The consumer waits until the buffer reaches at least half capacity before processing in batches.

![Half mode](docs/consumer/half/half.png)

---

### Configuration

Buffer size:
producer_consumer_init(1024);

Producer speed (delay in microseconds):
generate_producer_thread(&thread, 100);

Consumer mode:
generate_consumer_thread(&thread, mode);

---

### Architecture

- multiple producer threads
- single consumer thread
- shared circular buffer
- mutex-protected access
- Data processing statistics, minimum overhead
- condition variable for synchronization

---

### Conclusions

- The system runs without data loss
- Throughput is stable in both consumer modes
- Half-buffer mode does not significantly improve performance in this setup
- Latency variation is mainly caused by OS scheduling and synchronization overhead, not by buffer logic