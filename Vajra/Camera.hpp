#pragma once

#ifndef _VAJRA_VERSION_2_CAMERA_HPP_
#define _VAJRA_VERSION_2_CAMERA_HPP_

#include "Object.hpp"
#include "Vector.hpp"
using Vajra::Math::Vector;

namespace Vajra
{
    namespace Graphics
    {
        class Camera : public Object
        {
        public:
            static Camera& Create( const std::string& name );

            virtual ~Camera(void);

            virtual void Reset(void) = 0;
            virtual void Move( const float& x, const float& y, const float& z ) = 0;
            virtual void Move( const Vector& translation ) = 0;

            virtual Vector& Position(void) = 0;
            virtual Vector& LookAt(void) = 0;
            virtual Vector& Up(void) = 0;

            virtual const Vector& Position(void) const = 0;
            virtual const Vector& LookAt(void) const = 0;
            virtual const Vector& Up(void) const = 0;

            virtual void Update( float delta ) = 0;
            virtual void Render( float delta ) = 0;

        protected:
            Camera( const std::string& name );

        private:
            Camera( const Camera& camera );
            Camera& operator = ( const Camera& camera );
        };
    }
}

#endif //_VAJRA_VERSION_2_CAMERA_HPP_
