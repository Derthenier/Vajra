#include "pch.hpp"
#include "TransformComponent.hpp"
using Vajra::Graphics::TransformComponent;

TransformComponent::TransformComponent(void)
: m_position()
, m_rotation( 0.0f )
, m_scale( 1.0f )
{
}

TransformComponent::TransformComponent( const Vector& position, const float& rotation, const float& scale )
: m_position( position )
, m_rotation( rotation )
, m_scale( scale )
{
}

TransformComponent::~TransformComponent(void)
{
}

#pragma region Position
void TransformComponent::SetPosition( const Vector& position )
{
    m_position = position;
}

void TransformComponent::UpdatePosition( const Vector& relativePosition )
{
    m_position += relativePosition;
}

void TransformComponent::UpdatePosition( const float& relativeX, const float& relativeY, const float& relativeZ )
{
    Vector relativePosition( relativeX, relativeY, relativeZ );
    m_position += relativePosition;
}

const Vector& TransformComponent::GetPosition(void) const
{
    return m_position;
}
#pragma endregion

#pragma region Size
void TransformComponent::SetSize( const Vector& size )
{
    m_size = size;
}

void TransformComponent::UpdateSize( const Vector& relativeSize )
{
    m_size += relativeSize;
}

const Vector& TransformComponent::GetSize(void) const
{
    return m_size;
}
#pragma endregion

#pragma region Rotation
void TransformComponent::SetRotation( const float& rotation )
{
    m_rotation = rotation;
}

void TransformComponent::UpdateRotation( const float& rotation )
{
    m_rotation += rotation;
}

const float& TransformComponent::GetRotation(void) const
{
    return m_rotation;
}
#pragma endregion

#pragma region Scale
void TransformComponent::SetScale( const Vector& scale )
{
    m_scale = scale;
}

void TransformComponent::UpdateScale( const Vector& scale )
{
    m_scale += scale;
}

void TransformComponent::UpdateScale( const float& scaleX, const float& scaleY, const float& scaleZ )
{
    Vector scale( scaleX, scaleY, scaleZ );
    m_scale += scale;
}

const Vector& TransformComponent::GetScale(void) const
{
    return m_scale;
}
#pragma endregion

void TransformComponent::Update( float delta, const Vector& linearSpeed, float angularSpeed )
{
    m_position += ( linearSpeed  * delta );
    m_rotation += ( angularSpeed * delta );
}
