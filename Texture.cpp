#include "pch.hpp"
#include "Definitions.hpp"
#include "Texture.hpp"
using Vajra::Graphics::Texture;

#include "IdManager.hpp"

Texture::Texture( const std::string& name )
: Vajra::Core::Resource( name )
{
}

#if defined( _WIN32 )

#include "DirectX/D3DTexture.hpp"
using Vajra::Graphics::DirectX::D3DTexture;

Texture* Texture::Create( const std::string& name )
{
    return new D3DTexture( name );
}

#elif defined( _MACOS ) || defined( _LINUX )

#include "OpenGL/GLTexture.hpp"
using Vajra::Graphics::OpenGL::GLTexture;

Texture* Texture::Create( const std::string& name )
{
    return new GLTexture( name );
}

#endif // defined( _WIN32 )
/*
using Vajra::Graphics::TextureManager;

TextureManager::~TextureManager(void)
{
    DeleteAllSecond( m_textures );
}

Texture* TextureManager::GetTexture( const std::string& name )
{
    std::string id = Vajra::Core::IdManager::GetId( name );
    if( m_textures.find( id ) == m_textures.end() )
    {
        Texture* texture = Texture::Create( name );
        if( NULL != texture )
        {
            texture->Load();
            m_textures.insert( std::make_pair( id, texture ) );
        }

        return texture;
    }
    else
    {
        return m_textures[ id ];
    }

    return NULL;
}*/
