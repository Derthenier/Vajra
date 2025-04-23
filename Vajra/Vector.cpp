#include "pch.hpp"
#include "Vector.hpp"
using Vajra::Math::Vector;

#include <cmath>
#include <cstring>

const Vector& Vector::One   = Vector( 1.0f, 1.0f, 1.0f );
const Vector& Vector::Zero  = Vector( 0.0f, 0.0f, 0.0f );
const Vector& Vector::UnitX = Vector( 1.0f, 0.0f, 0.0f );
const Vector& Vector::UnitY = Vector( 0.0f, 1.0f, 0.0f );
const Vector& Vector::UnitZ = Vector( 0.0f, 0.0f, 1.0f );

Vector::Vector( const float X, const float Y, const float Z )
{
    m_vector[ 0 ] = X;
    m_vector[ 1 ] = Y;
    m_vector[ 2 ] = Z;
}

Vector::Vector( const Vector& v )
{
    m_vector[ 0 ] = v.m_vector[ 0 ];
    m_vector[ 1 ] = v.m_vector[ 1 ];
    m_vector[ 2 ] = v.m_vector[ 2 ];
}

Vector::~Vector(void)
{
    m_vector[ 0 ] = m_vector[ 1 ] = m_vector[ 2 ] = 0.0f;
}

Vector& Vector::operator = ( const Vector& v )
{
    if( this == &v )
        return *this;
    m_vector[ 0 ] = v.m_vector[ 0 ];
    m_vector[ 1 ] = v.m_vector[ 1 ];
    m_vector[ 2 ] = v.m_vector[ 2 ];

    return *this;
}

const float& Vector::operator [] ( int index ) const
{
    if( index < 0 )
        index = 0;
    if( index > 2 )
        index = 2;
    return m_vector[ index ];
}

float& Vector::operator [] ( int index )
{
    if( index < 0 )
        index = 0;
    if( index > 2 )
        index = 2;
    return m_vector[ index ];
}

Vector Vector::operator + ( const Vector& v ) const
{
    return Vector( m_vector[ 0 ] + v.m_vector[ 0 ], m_vector[ 1 ] + v.m_vector[ 1 ], m_vector[ 2 ] + v.m_vector[ 2 ] );
}

Vector& Vector::operator += ( const Vector& v )
{
    m_vector[ 0 ] += v.m_vector[ 0 ];
    m_vector[ 1 ] += v.m_vector[ 1 ];
    m_vector[ 2 ] += v.m_vector[ 2 ];
    return *this;
}

Vector Vector::operator - ( const Vector& v ) const
{
    return Vector( m_vector[ 0 ] - v.m_vector[ 0 ], m_vector[ 1 ] - v.m_vector[ 1 ], m_vector[ 2 ] - v.m_vector[ 2 ] );
}

Vector& Vector::operator -= ( const Vector& v )
{
    m_vector[ 0 ] -= v.m_vector[ 0 ];
    m_vector[ 1 ] -= v.m_vector[ 1 ];
    m_vector[ 2 ] -= v.m_vector[ 2 ];
    return *this;
}

Vector Vector::operator * ( const float& scale ) const
{
    return Vector( m_vector[ 0 ] * scale, m_vector[ 1 ] * scale, m_vector[ 2 ] * scale );
}

Vector& Vector::operator *= ( const float& scale )
{
    m_vector[ 0 ] *= scale;
    m_vector[ 1 ] *= scale;
    m_vector[ 2 ] *= scale;
    return *this;
}

Vector Vector::operator / ( const float& scale ) const
{
    return Vector( m_vector[ 0 ] / scale, m_vector[ 1 ] / scale, m_vector[ 2 ] / scale );
}

Vector& Vector::operator /= ( const float& scale )
{
    m_vector[ 0 ] /= scale;
    m_vector[ 1 ] /= scale;
    m_vector[ 2 ] /= scale;
    return *this;
}

Vector Vector::operator - (void) const
{
    return Vector( -m_vector[ 0 ], -m_vector[ 1 ], -m_vector[ 2 ] );
}

const bool Vector::operator == ( const Vector& v ) const
{
    return ( std::memcmp( m_vector, v.m_vector, sizeof( float ) * 3 ) == 0 );
}

const bool Vector::operator != ( const Vector& v ) const
{
    return ( std::memcmp( m_vector, v.m_vector, sizeof( float ) * 3 ) != 0 );
}

const bool Vector::operator < ( const Vector& v ) const
{
    return ( std::memcmp( m_vector, v.m_vector, sizeof( float ) * 3 ) < 0 );
}

const bool Vector::operator <= ( const Vector& v ) const
{
    return ( std::memcmp( m_vector, v.m_vector, sizeof( float ) * 3 ) <= 0 );
}

const bool Vector::operator > ( const Vector& v ) const
{
    return ( std::memcmp( m_vector, v.m_vector, sizeof( float ) * 3 ) > 0 );
}

const bool Vector::operator >= ( const Vector& v ) const
{
    return ( std::memcmp( m_vector, v.m_vector, sizeof( float ) * 3 ) >= 0 );
}

const float Vector::Length(void) const
{
    return std::sqrtf( ( m_vector[ 0 ] * m_vector[ 0 ] ) + ( m_vector[ 1 ] * m_vector[ 1 ] ) + ( m_vector[ 2 ] * m_vector[ 2 ] ) );
}

const float Vector::LengthSquared(void) const
{
    return ( ( m_vector[ 0 ] * m_vector[ 0 ] ) + ( m_vector[ 1 ] * m_vector[ 1 ] ) + ( m_vector[ 2 ] * m_vector[ 2 ] ) );
}

const float Vector::Dot( const Vector& v ) const
{
    return ( ( m_vector[ 0 ] * v.m_vector[ 0 ] ) + ( m_vector[ 1 ] * v.m_vector[ 1 ] ) + ( m_vector[ 2 ] * v.m_vector[ 2 ] ) );
}

Vector Vector::Cross( const Vector& v ) const
{
    Vector result;
    result.m_vector[ 0 ] = m_vector[ 1 ] * v.m_vector[ 2 ] - m_vector[ 2 ] * v.m_vector[ 1 ];
    result.m_vector[ 1 ] = m_vector[ 2 ] * v.m_vector[ 0 ] - m_vector[ 0 ] * v.m_vector[ 2 ];
    result.m_vector[ 2 ] = m_vector[ 0 ] * v.m_vector[ 1 ] - m_vector[ 1 ] * v.m_vector[ 0 ];
    return result;
}

void Vector::Reset(void)
{
    std::memset( m_vector, 0, sizeof( float ) * 3 );
}

void Vector::Normalize(void)
{
    const float length = std::sqrtf( ( m_vector[ 0 ] * m_vector[ 0 ] ) + ( m_vector[ 1 ] * m_vector[ 1 ] ) + ( m_vector[ 2 ] * m_vector[ 2 ] ) );
    m_vector[ 0 ] /= length;
    m_vector[ 1 ] /= length;
    m_vector[ 2 ] /= length;
}

void Vector::Interpolate( const Vector& start, const Vector& end, const float& delta )
{
    m_vector[ 0 ] = start.m_vector[ 0 ] + ( ( end.m_vector[ 0 ] - start.m_vector[ 0 ] ) * delta );
    m_vector[ 1 ] = start.m_vector[ 1 ] + ( ( end.m_vector[ 1 ] - start.m_vector[ 1 ] ) * delta );
    m_vector[ 2 ] = start.m_vector[ 2 ] + ( ( end.m_vector[ 2 ] - start.m_vector[ 2 ] ) * delta );
}
