
#ifndef UTILS_HPP
#define UTILS_HPP

#include <chrono>
#include <shm_interface.h>
#include <time.h>

Timestamp getCurrentTimestamp();
uint64_t  getSysRTC();

#endif // UTILS_HPP
