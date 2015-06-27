#include "pch.hpp"
#include "Renderer.hpp"
using Vajra::Graphics::Renderer;
using Vajra::Graphics::RenderManager;

Renderer::Renderer(void)
{
}

Renderer::~Renderer(void)
{
}

void Renderer::DrawRectangle( const Vector& topLeft, const float& width, const float& height, const Vector& scale, const float& rotation )
{
    DrawRectangle( topLeft.X(), topLeft.Y(), width, height, scale, rotation );
}

void Renderer::DrawRectangle( const Vector& topLeft, const Vector& bottomRight, const Vector& scale, const float& rotation )
{
    const float width = bottomRight.X() - topLeft.X();
    const float height = bottomRight.Y() - topLeft.Y();
    DrawRectangle( topLeft.X(), topLeft.Y(), width, height, scale, rotation );
}

void Renderer::DrawTexturedRectangle( const Texture* texture, const Vector& topLeft, const float& width, const float& height, const Vector& scale, const float& rotation )
{
    DrawTexturedRectangle( texture, topLeft.X(), topLeft.Y(), width, height, scale, rotation );
}

void Renderer::DrawTexturedRectangle( const Texture* texture, const Vector& topLeft, const Vector& bottomRight, const Vector& scale, const float& rotation )
{
    const float width = bottomRight.X() - topLeft.X();
    const float height = bottomRight.Y() - topLeft.Y();
    DrawTexturedRectangle( texture, topLeft.X(), topLeft.Y(), width, height, scale, rotation );
}


#if defined( _WIN32 )

#include "DirectX/D3DRenderer.hpp"
using Vajra::Graphics::DirectX::D3DRenderer;

Renderer& RenderManager::GetRenderer(void)
{
    return ( D3DRenderer::GetInstance() );
}

#elif defined( _MACOS ) || defined( _LINUX )

#include "DirectX/GLRenderer.hpp"
using Vajra::Graphics::OpenGL::GLRenderer;

Renderer& RenderManager::GetRenderer(void)
{
    return ( GLRenderer::GetInstance() );
}

#endif
