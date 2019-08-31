#pragma once
#include "fft/Base.hpp"

namespace fft {
/// Takes a svg file and outputs a path of points
void vectorize( const String &path, std::vector<sf::Vector2f> &out, size_t interpolation_steps );
} // namespace fft