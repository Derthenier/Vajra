#pragma once

#ifndef _VAJRA_VERSION_2_MATH_HPP_
#define _VAJRA_VERSION_2_MATH_HPP_

namespace Vajra
{
    namespace Math
    {
        template< typename Type >
        class MathHelper
        {
        public:
            static const Type& PI;
            static const Type& TWO_PI;
            static const Type& HALF_PI;

        private:
            MathHelper(void) { }
            MathHelper( const MathHelper& mh ) { }
            ~MathHelper(void) { }
            MathHelper& operator = ( const MathHelper& mh ) { }
        };

        typedef MathHelper<float> MathF;
        typedef MathHelper<double> MathD;

        template<> const float& MathF::PI       = 3.1415926535897932384626433832795f;
        template<> const float& MathF::TWO_PI   = 6.2831853071795864769252867665590f;
        template<> const float& MathF::HALF_PI  = 1.5707963267948966192313216916398f;

        template<> const double& MathD::PI      = 3.1415926535897932384626433832795;
        template<> const double& MathD::TWO_PI  = 6.2831853071795864769252867665590;
        template<> const double& MathD::HALF_PI = 1.5707963267948966192313216916398;
    }
}

#endif //_VAJRA_VERSION_2_MATH_HPP_
