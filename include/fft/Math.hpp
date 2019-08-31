#pragma once
#include "fft/Base.hpp"

namespace fft {
template <typename T>
T sgn( const T &val ) {
    return ( T( 0 ) < val ) - ( val < T( 0 ) );
}


template <typename T>
T vec_len( const sf::Vector2<T>& v ) {
    return std::sqrt( v.x * v.x + v.y * v.y );
}
template <typename T>
T vec_len_sqr( const sf::Vector2<T>& v ) {
    return v.x * v.x + v.y * v.y;
}
template <typename T>
sf::Vector2<T> vec_norm( const sf::Vector2<T>& v ) {
    return v / std::sqrt( v.x * v.x + v.y * v.y );
}
template <typename T>
sf::Vector2<T> vec_comp_quot( const sf::Vector2<T>& left, const sf::Vector2<T>& right ) {
    return sf::Vector2<T>( left.x / right.x, left.y / right.y );
}
template <typename T>
sf::Vector2<T> vec_comp_prod( const sf::Vector2<T>& left, const sf::Vector2<T>& right ) {
    return sf::Vector2<T>( left.x * right.x, left.y * right.y );
}

template <typename T>
sf::Vector2<T> vec_rotate_90( const sf::Vector2<T>& vec ) {
    return sf::Vector2<T>( -vec.y, vec.x );
}
template <typename T>
sf::Vector2<T> vec_rotate_270( const sf::Vector2<T>& vec ) {
    return sf::Vector2<T>( vec.y, -vec.x );
}
template <typename T>
sf::Vector2<T> vec_rotate_rad( const sf::Vector2<T>& vec, float radians ) {
    float c = std::cos( radians ), s = std::sin( radians );
    return sf::Vector2<T>( vec.x * c - vec.y * s, vec.x * s + vec.y * c );
}
template <typename T>
sf::Vector2<T> vec_rotate_deg( const sf::Vector2<T>& vec, float degrees ) {
    return vec_rotate_rad( vec, degrees * M_PI / 180.f );
}

template <typename T>
T vec_scalar_prod( const sf::Vector2<T>& left, const sf::Vector2<T>& right ) {
    return left.x * right.x + left.y * right.y;
}

template <typename T>
sf::Vector2<T> vec_is_right_orientated( const sf::Vector2<T>& left, const sf::Vector2<T>& right ) {
    return vec_scalar_prod( left, vec_rotate_90( right ) );
}

template <typename T>
/// Calculate the part of \p b in the direction of \p a
sf::Vector2<T> vec_partion( const sf::Vector2<T>& a, const sf::Vector2<T>& b ) {
    return vec_scalar_prod( a, b ) / vec_scalar_prod( a, a ) * a;
}
template <typename T>
/// Calculate an orthogonal vector to \p a from \p b
sf::Vector2<T> vec_orth( const sf::Vector2<T>& a, const sf::Vector2<T>& b ) {
    return b - vec_partion(a, b);
}
} // namespace fft
