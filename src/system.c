
#include "system.h"
#include <time.h>
#include <stdint.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>

volatile uint8_t app_running = 1;       

// I made the timestamps of 64 bits because I do not want to deal with wrap arounds
uint64_t get_tiemstamp_in_us (void) 
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000ULL + (uint64_t)ts.tv_nsec / 1000ULL;
}

/**
* @brief Handle the signal (e.g., SIGINT, SIGTERM) and set the app_running flag to 0
* @param sig (int) The signal number (unused)
* @param info (siginfo_t *) Pointer to siginfo_t structure containing signal information (unused)
* @param ucontext (void *) Pointer to ucontext_t structure containing context information (unused)
* @return void
*/
static void handle_signal(int sig, siginfo_t *info, void *ucontext) {
    // Handle the signal (e.g., SIGINT, SIGTERM) and set the app_running flag to 0
    (void)sig;          // Unused parameter
    (void)info;         // Unused parameter
    (void)ucontext;     // Unused parameter
    printf("Signal received, shutting down...");
    app_running = 0;
}

/**
* @brief Set up signal handlers for SIGINT and SIGTERM
* @return void
*/
void setup_signals(void) {
    struct sigaction sa;
    sa.sa_sigaction = handle_signal;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);   // CTRL+C
    sigaction(SIGTERM, &sa, NULL);  // Termination signal
}