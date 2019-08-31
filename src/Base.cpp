#include "fft/stdafx.hpp"
#include "fft/Base.hpp"

std::array<String, 128> log_buffer;
size_t log_buffer_offset = 0;

void log( String str ) {
    std::cout << str << std::endl;

    ++log_buffer_offset %= LOG_BUFFER_SIZE;
    log_buffer[log_buffer_offset] = str;
}

std::array<String, LOG_BUFFER_SIZE> &get_log_buffer() {
    return log_buffer;
}

size_t &get_log_buffer_offset() {
    return log_buffer_offset;
}
