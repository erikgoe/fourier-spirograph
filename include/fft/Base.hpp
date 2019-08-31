#pragma once
#include "fft/stdafx.hpp"

using String = std::string;
using std::to_string;

const int LOG_BUFFER_SIZE = 128;
void log( String );
std::array<String, LOG_BUFFER_SIZE> &get_log_buffer();
size_t &get_log_buffer_offset();

// Declarations
namespace fft {
class Framework;
class GUI;
class HotReloadLogger;
} // namespace fft

// Global control to enable/disable hot reload (required jet-live)
#ifndef DEBUG
#define ENABLE_HOT_RELOAD 1
#else
#define ENABLE_HOT_RELOAD 0
#endif
