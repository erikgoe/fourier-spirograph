#include "fft/stdafx.hpp"
#include "fft/Vectorize.hpp"
#include "fft/Math.hpp"
#include "nanosvg/src/nanosvg.h"

namespace fft {
void vectorize( const String& path, std::vector<sf::Vector2f>& out, size_t interpolation_steps ) {
    // Load from file
    struct NSVGimage* image;
    image = nsvgParseFromFile( path.c_str(), "px", 96 );

    // Translate into vectors
    out.clear();
    for ( auto shape = image->shapes; shape != NULL; shape = shape->next ) {
        for ( auto path = shape->paths; path != NULL; path = path->next ) {
            for ( size_t i = 0; i < path->npts - 1; i += 3 ) {
                float* p = &path->pts[i * 2];

                // Interpolate bezier curve
                sf::Vector2f a( p[0], p[1] ), b( p[2], p[3] ), c( p[4], p[5] ), d( p[6], p[7] );
                for ( size_t i = 0; i < interpolation_steps; i++ ) {
                    float step = static_cast<float>( i ) / interpolation_steps;

                    auto x = vec_lerp( a, b, step );
                    auto y = vec_lerp( b, c, step );
                    auto z = vec_lerp( c, d, step );

                    auto p = vec_lerp( x, y, step );
                    auto q = vec_lerp( y, z, step );

                    out.push_back( vec_lerp( p, q, step ) );
                }
            }
        }
    }

    // Delete
    nsvgDelete( image );
}
} // namespace fft