#pragma once
#include "fft/Base.hpp"

namespace fft {
void fft( std::vector<float> &in, std::vector<float> &out_r, std::vector<float> &out_i );
void fft_distance( std::vector<float> &in, std::vector<float> &out );

/// Calculates the coefficients \p out for the fourier series to approximate the in "function"
void fft_series( std::vector<sf::Vector2f> &in, std::vector<Complex> &out );
} // namespace fft
