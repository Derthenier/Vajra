#pragma once

#ifndef _VAJRA_VERSION_2_D3DRENDERER_HPP_
#define _VAJRA_VERSION_2_D3DRENDERER_HPP_

#include "../Singleton.hpp"
#include "../Renderer.hpp"

#include <vector>
#include <d3dx9math.h>

struct IDirect3D9;
struct IDirect3DDevice9;
struct IDirect3DSurface9;
struct _D3DPRESENT_PARAMETERS_;

namespace Vajra
{
    namespace Graphics
    {
        namespace DirectX
        {
            class D3DRenderer : public Vajra::Core::Singleton< D3DRenderer >, public Renderer
            {
                friend class Vajra::Core::Singleton< D3DRenderer >;

            private:
                struct D3DVertex;
                class D3DVertexBuffer;
                class D3DIndexBuffer;

            public:
                virtual ~D3DRenderer(void);

            public:
                virtual void Initialize( const unsigned int& screenWidth, const unsigned int& screenHeight, const unsigned int& screenBpp, const bool& isFullscreen );

                virtual void Setup( const float& fieldOfView, const float& zNear, const float& zFar );

                virtual void BeginFrame(void);
                virtual void EndFrame(void);

                virtual void DrawPoint( const Vector& position );
                virtual void DrawLine( const Vector& start, const Vector& end );
                virtual void DrawTriangle( const Vector& v1, const Vector& v2, const Vector& v3, const Vector& scale = Vector::One, const float& rotation = 0.0f );
                virtual void DrawCircle( const Vector& center, const float& radius, const int& numSegments );
                virtual void DrawRectangle( const float& x, const float& y, const float& width, const float& height, const Vector& scale = Vector::One, const float& rotation = 0.0f );

                virtual void DrawTexturedRectangle( const Texture* texture, const float& x, const float& y, const float& width, const float& height, const Vector& scale = Vector::One, const float& rotation = 0.0f );

                virtual void DrawString( const std::string& text, const float& x, const float& y, const int& size );

                IDirect3DDevice9* GetDevice(void) const { return m_device; }

                virtual const unsigned int& GetWidth(void) const { return m_width; }
                virtual const unsigned int& GetHeight(void) const { return m_height; }

            private:
                D3DRenderer(void);
                D3DRenderer( const D3DRenderer& d3dRenderer ) { }
                D3DRenderer& operator = ( const D3DRenderer& d3dRenderer ) { }

                void ValidateDevice(void);

            private:
                IDirect3D9* m_d3d;
                IDirect3DDevice9* m_device;
                IDirect3DSurface9* m_backBuffer;

                D3DVertexBuffer* m_vb;
                D3DIndexBuffer* m_ib;

                std::vector< D3DXMATRIX > m_matrixStack;

                _D3DPRESENT_PARAMETERS_* m_presentParameters;

                unsigned int m_width;
                unsigned int m_height;

                float m_fieldOfView;
                float m_zNear;
                float m_zFar;

                bool m_lastFrameHasBeenEnded;
            };
        }
    }
}

#endif //_VAJRA_VERSION_2_D3DRENDERER_HPP_
