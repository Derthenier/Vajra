#pragma once

#ifndef _VAJRA_VERSION_2_VECTOR_HPP_
#define _VAJRA_VERSION_2_VECTOR_HPP_

namespace Vajra
{
    namespace Math
    {
        class Vector
        {
        public:
            static const Vector& One;
            static const Vector& Zero;
            static const Vector& UnitX;
            static const Vector& UnitY;
            static const Vector& UnitZ;

        public:
            /* Creation and Destruction */
            explicit Vector( float X = 0.0f, float Y = 0.0f, float Z = 0.5f );
            Vector( const Vector& v );
            ~Vector(void);

            /* Assignment Operator */
            Vector& operator = ( const Vector& v );
            const float& operator [] ( int index ) const;
            float& operator [] ( int index );

            /* Arithmetic Operators */
            Vector operator + ( const Vector& v ) const;
            Vector& operator += ( const Vector& v );
            Vector operator - ( const Vector& v ) const;
            Vector& operator -= ( const Vector& v );
            Vector operator * ( const float& scale ) const;
            Vector& operator *= ( const float& scale );
            Vector operator / ( const float& scale ) const;
            Vector& operator /= ( const float& scale );
            Vector operator - (void) const;

            /* Boolean Operators */
            const bool operator == ( const Vector& v ) const;
            const bool operator != ( const Vector& v ) const;
            const bool operator <  ( const Vector& v ) const;
            const bool operator <= ( const Vector& v ) const;
            const bool operator >  ( const Vector& v ) const;
            const bool operator >= ( const Vector& v ) const;

            /* Length */
            const float Length(void) const;
            const float LengthSquared(void) const;

            /* Products */
            const float Dot( const Vector& v ) const;
            Vector Cross( const Vector& v ) const;

            /* Maintenance Methods */
            void Reset(void);
            void Normalize(void);

            void Interpolate( const Vector& start, const Vector& end, const float& delta );

            /* Member Access Methods */
            const float& X(void) const { return m_vector[ 0 ]; }
            float& X(void) { return m_vector[ 0 ]; }
            const float& Y(void) const { return m_vector[ 1 ]; }
            float& Y(void) { return m_vector[ 1 ]; }
            const float& Z(void) const { return m_vector[ 2 ]; }
            float& Z(void) { return m_vector[ 2 ]; }

        private:
            float m_vector[3];
        };
    }
}

#endif //_VAJRA_VERSION_2_VECTOR_HPP_
