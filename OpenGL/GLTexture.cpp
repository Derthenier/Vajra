#include "pch.hpp"
#include "GLTexture.hpp"
using Vajra::Graphics::OpenGL::GLTexture;
using Vajra::Graphics::Texture;
using Vajra::Core::Resource;

GLTexture::GLTexture( const std::string& name )
: Texture( name )
{
}

GLTexture::~GLTexture(void)
{
}

void GLTexture::Load(void)
{
}
