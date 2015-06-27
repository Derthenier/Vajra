#pragma once

#ifndef _VAJRA_VERSION_2_TRANSFORM_COMPONENT_HPP_
#define _VAJRA_VERSION_2_TRANSFORM_COMPONENT_HPP_

#include "Vector.hpp"
using Vajra::Math::Vector;

namespace Vajra
{
    namespace Graphics
    {
        class TransformComponent
        {
        public:
            TransformComponent(void);
            TransformComponent( const Vector& position, const float& rotation = 0.0f, const float& scale = 1.0f );
            virtual ~TransformComponent(void);

            virtual void SetPosition( const Vector& position );
            virtual void UpdatePosition( const Vector& relativePosition );
            virtual void UpdatePosition( const float& relativeX = 0.0f, const float& relativeY = 0.0f, const float& relativeZ = 0.0f );
            virtual const Vector& GetPosition(void) const;

            virtual void SetSize( const Vector& size );
            virtual void UpdateSize( const Vector& relativeSize );
            virtual const Vector& GetSize(void) const;

            virtual void SetRotation( const float& rotation );
            virtual void UpdateRotation( const float& relativeRotation = 0.0f );
            virtual const float& GetRotation(void) const;

            virtual void SetScale( const Vector& scale );
            virtual void UpdateScale( const Vector& relativeScale );
            virtual void UpdateScale( const float& scaleX = 1.0f, const float& scaleY = 1.0f, const float& scaleZ = 1.0f );
            virtual const Vector& GetScale(void) const;

            virtual void Update( float delta, const Vector& linearSpeed, float angularSpeed );

        protected:
            TransformComponent( const TransformComponent& tc ) { }
            TransformComponent& operator = ( const TransformComponent& tc ) { }

        protected:
            Vector m_position;
            Vector m_size;
            Vector m_scale;
            float m_rotation;
        };
    }
}

#endif //_VAJRA_VERSION_2_TRANSFORM_COMPONENT_HPP_
