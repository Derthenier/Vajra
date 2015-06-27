#include "pch.hpp"
#include "D3DTexture.hpp"
using Vajra::Graphics::DirectX::D3DTexture;

#include "D3DRenderer.hpp"
using Vajra::Graphics::RenderManager;

#include "../Logger.hpp"
using Vajra::Core::Logger;

#include <d3d9.h>
#include <d3dx9.h>

D3DTexture::D3DTexture( const std::string& name )
: Texture( name )
, m_texture( NULL )
, m_width( static_cast< unsigned int >( -1 ) )
, m_height( static_cast< unsigned int >( -1 ) )
{
}

D3DTexture::~D3DTexture(void)
{
    if( NULL != m_texture )
        m_texture->Release();
}

void D3DTexture::Load(void)
{
    LPDIRECT3DDEVICE9 device = static_cast< D3DRenderer& >( RenderManager::GetRenderer() ).GetDevice();
    HRESULT hr = D3DXCreateTextureFromFile( device, m_name.c_str(), &m_texture );
    if( FAILED( hr ) )
    {
        Logger::GetInstance().Write( Vajra::Core::LogError, "Failed to load '%s' in D3DTexture::Load", m_name.c_str() );
        m_width = 0;
        m_height = 0;
        return;
    }

    D3DSURFACE_DESC desc;
    m_texture->GetLevelDesc( 0, &desc );

    m_width = desc.Width;
    m_height = desc.Height;
}

const unsigned int& D3DTexture::Width(void) const
{
    return m_width;
}

const unsigned int& D3DTexture::Height(void) const
{
    return m_height;
}
