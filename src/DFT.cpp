#include "fft/stdafx.hpp"
#include "fft/DFT.hpp"

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

void fft_series( std::vector<sf::Vector2f> &in, std::vector<Complex> &out ) {
    for ( int i = 0; i < out.size(); i++ ) {
        out[i] = Complex();
        int n = ( i + 1 ) / 2 * ( i % 2 ? 1 : -1 );
        for ( int j = 0; j < in.size(); j++ ) {
            out[i] +=
                Complex( in[j].x, in[j].y ) *
                std::pow<float, float>( M_E, Complex( 0, -n * 2 * M_PI * ( static_cast<float>( j ) / in.size() ) ) );
        }
        out[i] /= static_cast<float>( in.size() );
    }
}
} // namespace fft