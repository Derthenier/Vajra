#pragma once

#ifndef _VAJRA_VERSION_2_D3DCAMERA_HPP_
#define _VAJRA_VERSION_2_D3DCAMERA_HPP_

#include "../Camera.hpp"

namespace Vajra
{
    namespace Graphics
    {
        namespace DirectX
        {
            class D3DCamera : public Vajra::Graphics::Camera
            {
            public:
                D3DCamera( const std::string& name );
                virtual ~D3DCamera(void);

                virtual Vector& Position(void);
                virtual Vector& LookAt(void);
                virtual Vector& Up(void);

                virtual const Vector& Position(void) const;
                virtual const Vector& LookAt(void) const;
                virtual const Vector& Up(void) const;

                virtual void Reset(void);

                virtual void Move( const float& x, const float& y, const float& z );
                virtual void Move( const Vector& translation );

                virtual void Update( float delta );
                virtual void Render( float delta );

            private:
                Vector m_position;
                Vector m_lookAt;
                Vector m_up;
            };
        }
    }
}

#endif //_VAJRA_VERSION_2_D3DCAMERA_HPP_
