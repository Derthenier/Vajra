#include "pch.hpp"
#include "D3DCamera.hpp"
using Vajra::Graphics::DirectX::D3DCamera;

#include "D3DRenderer.hpp"
using Vajra::Graphics::DirectX::D3DRenderer;
using Vajra::Graphics::RenderManager;

#include <d3d9.h>
#include <d3dx9.h>

D3DCamera::D3DCamera( const std::string& name )
: Vajra::Graphics::Camera( name )
, m_position( 0, 0, -1 )
, m_lookAt( 0, 0, 0 )
, m_up( 0, 1, 0 )
{
}

D3DCamera::~D3DCamera(void)
{
}

Vector& D3DCamera::Position(void)
{
    return m_position;
}

Vector& D3DCamera::LookAt(void)
{
    return m_lookAt;
}

Vector& D3DCamera::Up(void)
{
    return m_up;
}

const Vector& D3DCamera::Position(void) const
{
    return m_position;
}

const Vector& D3DCamera::LookAt(void) const
{
    return m_lookAt;
}

const Vector& D3DCamera::Up(void) const
{
    return m_up;
}

void D3DCamera::Reset(void)
{
    m_position = Vector::UnitZ * -1.0f;
    m_lookAt = Vector::Zero;
    m_up = Vector::UnitY;
}

void D3DCamera::Move( const float& x, const float& y, const float& z )
{
    m_position += Vector( x, y, z );
}

void D3DCamera::Move( const Vector& translation )
{
    m_position += translation;
}

void D3DCamera::Update( float delta )
{
    if( NULL == this )
        return;

    D3DXMATRIX viewMatrix;
    D3DXVECTOR3 position;
    D3DXVECTOR3 lookAt;
    D3DXVECTOR3 up;

    position.x = m_position.X();
    position.y = m_position.Y();
    position.z = m_position.Z();

    lookAt.x = m_lookAt.X();
    lookAt.y = m_lookAt.Y();
    lookAt.z = m_lookAt.Z();

    up.x = m_up.X();
    up.y = m_up.Y();
    up.z = m_up.Z();

    D3DXMatrixLookAtLH( &viewMatrix, &position, &lookAt, &up );

    LPDIRECT3DDEVICE9 device = static_cast< D3DRenderer& >( RenderManager::GetRenderer() ).GetDevice();
    device->SetTransform( D3DTS_VIEW, &viewMatrix );
}

void D3DCamera::Render( float delta )
{
}
