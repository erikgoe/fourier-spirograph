#pragma once
#include "fft/Base.hpp"

namespace fft {
void fft( std::vector<float> &in, std::vector<float> &out_r, std::vector<float> &out_i ) {
    for ( int i = 0; i < out_r.size(); i++ ) {
        out_r[i] = 0;
        out_i[i] = 0;
        for ( int j = 0; j < in.size(); j++ ) {
            float comp = 2.f * M_PI * i * j / in.size();
            out_r[i] += in[j] * std::cos( comp );
            out_i[i] += in[j] * -1 * std::sin( comp );
        }
        out_r[i] = std::abs( out_r[i] );
        out_i[i] = std::abs( out_i[i] );
        out_r[i] = std::sqrt( out_r[i] * out_r[i] + out_i[i] * out_i[i] );
    }
}
void fft_distance( std::vector<float> &in, std::vector<float> &out ) {
    for ( int i = 0; i < out.size(); i++ ) {
        float x = 0, y = 0;
        for ( int j = 0; j < in.size(); j++ ) {
            float comp = 2.f * M_PI * i * j / in.size();
            x += in[j] * std::cos( comp );
            y += in[j] * -1 * std::sin( comp );
        }
        out[i] = std::sqrt( x * x + y * y );
    }
}
} // namespace fft
