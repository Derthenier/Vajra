#include "pch.hpp"
#include "../Definitions.hpp"
#include "../Exception.hpp"
#include "../Logger.hpp"

#include "D3DRenderer.hpp"
#include "D3DVertexBuffer.hpp"
#include "D3DIndexBuffer.hpp"
using Vajra::Graphics::DirectX::D3DRenderer;

#include "D3DTexture.hpp"
using Vajra::Graphics::DirectX::D3DTexture;

#include <d3d9.h>
#include <d3dx9.h>

#include <sstream>

#include "../Win32/Win32Application.hpp"
using Vajra::Core::ApplicationManager;
using Vajra::Core::Win32::Win32Application;

#define CHECK_DRAW_VALIDITY( drawMethod )\
{\
    if( m_lastFrameHasBeenEnded )\
    {\
        std::stringstream ss;\
        ss << "Can only call '" << drawMethod << "' between BeginFrame() ... EndFrame()";\
        Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, ss.str().c_str() );\
        return;\
    }\
}

#pragma region Helper Functions
namespace Vajra
{
    namespace Graphics
    {
        namespace DirectX
        {
            /* */
            D3DFORMAT GetD3DDeviceCaps( unsigned int adapter, LPDIRECT3D9& d3d, bool fullscreen, D3DCAPS9& caps )
            {
                bool windowed = !fullscreen;
                D3DFORMAT format;
                D3DDEVTYPE type;

                HRESULT hr = d3d->CheckDeviceType( adapter, D3DDEVTYPE_HAL, D3DFMT_X8R8G8B8, D3DFMT_X8R8G8B8, windowed );
                if( FAILED( hr ) )
                {
                    hr = d3d->CheckDeviceType( adapter, D3DDEVTYPE_HAL, D3DFMT_X1R5G5B5, D3DFMT_X1R5G5B5, windowed );
                    if( FAILED( hr ) )
                    {
                        hr = d3d->CheckDeviceType( adapter, D3DDEVTYPE_HAL, D3DFMT_R5G6B5, D3DFMT_R5G6B5, windowed );
                        if( FAILED( hr ) )
                        {
                            type = D3DDEVTYPE_REF;
                            hr = d3d->CheckDeviceType( adapter, D3DDEVTYPE_REF, D3DFMT_X8R8G8B8, D3DFMT_X8R8G8B8, windowed );
                            if( FAILED( hr ) )
                            {
                                hr = d3d->CheckDeviceType( adapter, D3DDEVTYPE_REF, D3DFMT_X1R5G5B5, D3DFMT_X1R5G5B5, windowed );
                                if( FAILED( hr ) )
                                {
                                    hr = d3d->CheckDeviceType( adapter, D3DDEVTYPE_REF, D3DFMT_R5G6B5, D3DFMT_R5G6B5, windowed );
                                    if( FAILED( hr ) )
                                    {
                                        /* No Valid Format for Device Detected */
                                        Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogInformation, "Unable to detect valid format or device." );
                                        return D3DFMT_UNKNOWN;
                                    }
                                    else
                                    {
                                        format = D3DFMT_R5G6B5;
                                    }
                                }
                                else
                                {
                                    format = D3DFMT_X1R5G5B5;
                                }
                            }
                            else
                            {
                                format = D3DFMT_X8R8G8B8;
                            }
                        }
                        else
                        {
                            type = D3DDEVTYPE_HAL;
                            format = D3DFMT_R5G6B5;
                        }
                    }
                    else
                    {
                        type = D3DDEVTYPE_HAL;
                        format = D3DFMT_X1R5G5B5;
                    }
                }
                else
                {
                    type = D3DDEVTYPE_HAL;
                    format = D3DFMT_X8R8G8B8;
                }

                if( FAILED( d3d->GetDeviceCaps( adapter, type, &caps ) ) )
                {
                    Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogInformation, "Failed to get device capabalities" );
                    return D3DFMT_UNKNOWN;
                }

                return format;
            }

            /* */
            void GetBestDisplayMode( unsigned int adapter, LPDIRECT3D9& d3d, D3DFORMAT format, unsigned int requestedWidth, unsigned int requestedHeight, D3DDISPLAYMODE& bestMode )
            {
                unsigned int modeCount = d3d->GetAdapterModeCount( adapter, format );
                d3d->EnumAdapterModes( adapter, format, 0, &bestMode );

                if( bestMode.Width == requestedWidth && bestMode.Height == requestedHeight )
                    return;

                for( unsigned int mode = 1; mode < modeCount; ++mode )
                {
                    D3DDISPLAYMODE displayMode;
                    if( FAILED( d3d->EnumAdapterModes( adapter, format, mode, &displayMode ) ) )
                        continue;

                    if( displayMode.Width > requestedWidth )
                        return;

                    if( displayMode.Width > bestMode.Width )
                    {
                        bestMode.Width = displayMode.Width;
                        bestMode.Height = displayMode.Height;
                        bestMode.RefreshRate = displayMode.RefreshRate;
                    }
                    else if( displayMode.Height > bestMode.Height )
                    {
                        bestMode.Height = displayMode.Height;
                        bestMode.RefreshRate = displayMode.RefreshRate;
                    }
                    else if( displayMode.RefreshRate > bestMode.RefreshRate )
                    {
                        bestMode.RefreshRate = displayMode.RefreshRate;
                    }

                    if( bestMode.Width == requestedWidth && bestMode.Height == requestedHeight )
                        return;
                }
            }
        }
    }
}
#pragma endregion

D3DRenderer::D3DRenderer(void)
: Renderer()
, m_d3d( NULL )
, m_device( NULL )
, m_backBuffer( NULL )
, m_vb( NULL )
, m_ib( NULL )
, m_presentParameters( NULL )
, m_width( static_cast< unsigned int >( -1 ) )
, m_height( static_cast< unsigned int >( -1 ) )
, m_fieldOfView( 0.0f )
, m_zNear( -1.0f )
, m_zFar( -1.0f )
, m_lastFrameHasBeenEnded( true )
{
}

D3DRenderer::~D3DRenderer(void)
{
    m_matrixStack.clear();

    if( NULL != m_presentParameters )
    {
        delete m_presentParameters;
        m_presentParameters = NULL;
    }

    if( NULL != m_ib )
    {
        delete m_ib;
        m_ib = NULL;
    }

    if( NULL != m_vb )
    {
        delete m_vb;
        m_vb = NULL;
    }

    if( NULL != m_device )
    {
        m_device->Release();
        m_device = NULL;
    }

    if( NULL != m_d3d )
    {
        m_d3d->Release();
        m_d3d = NULL;
    }
}

void D3DRenderer::Initialize( const unsigned int& screenWidth, const unsigned int& screenHeight, const unsigned int& screenBpp, const bool& isFullscreen )
{
    // Create Direct3D9 COM Object
    m_d3d = Direct3DCreate9( D3D_SDK_VERSION );
    if( NULL == m_d3d )
    {
        Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogCritical, "Cannot create Direct3D9 Object." );
        throw Vajra::Core::VajraException( "D3DRenderer.cpp (198): ", "Cannot create Direct3D9 Object." );
    }

    // Get handle to the window
    Win32Application& app = static_cast< Win32Application& >( ApplicationManager::GetApplication() );
    HWND window = app.GetAppWindow();

    #pragma region Direct3D9 Device Creation
    D3DCAPS9 caps;
    D3DFORMAT format = Vajra::Graphics::DirectX::GetD3DDeviceCaps( D3DADAPTER_DEFAULT, m_d3d, isFullscreen, caps );

    D3DDISPLAYMODE bestMode;
    Vajra::Graphics::DirectX::GetBestDisplayMode( D3DADAPTER_DEFAULT, m_d3d, format, screenWidth, screenHeight, bestMode );

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof( D3DPRESENT_PARAMETERS ) );

    d3dpp.AutoDepthStencilFormat         = D3DFMT_D16;
    d3dpp.BackBufferCount                = 1;
    d3dpp.BackBufferFormat               = bestMode.Format;
    d3dpp.BackBufferHeight               = bestMode.Height;
    d3dpp.BackBufferWidth                = bestMode.Width;
    d3dpp.EnableAutoDepthStencil         = true;
    d3dpp.Flags                          = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
    d3dpp.FullScreen_RefreshRateInHz     = isFullscreen ? bestMode.RefreshRate : 0;
    d3dpp.hDeviceWindow                  = window;
    d3dpp.MultiSampleQuality             = 0;
    d3dpp.MultiSampleType                = D3DMULTISAMPLE_NONE;
    d3dpp.PresentationInterval           = D3DPRESENT_INTERVAL_IMMEDIATE;
    d3dpp.SwapEffect                     = D3DSWAPEFFECT_DISCARD;
    d3dpp.Windowed                       = !isFullscreen;

    unsigned long behavior;
    if( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
    {
        behavior = D3DCREATE_HARDWARE_VERTEXPROCESSING;
        if( caps.DevCaps & D3DDEVCAPS_PUREDEVICE )
            behavior |= D3DCREATE_PUREDEVICE;
    }
    else
    {
        behavior = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
    }
    #pragma endregion

    // Create the device
    HRESULT hr = m_d3d->CreateDevice( D3DADAPTER_DEFAULT, caps.DeviceType, window, behavior, &d3dpp, &m_device );
    if( FAILED( hr ) )
    {
        Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogCritical, "Failed to create Direct3D9 Device with parameters:\n"
            "\t\t\t\t\t\tDevice Type = %d,\n"
            "\t\t\t\t\t\tAutoDepthStencilFormat = %d,\n"
            "\t\t\t\t\t\tBackBufferCount = %u,\n"
            "\t\t\t\t\t\tBackBufferFormat = %d,\n"
            "\t\t\t\t\t\tBackBufferHeight = %u,\n"
            "\t\t\t\t\t\tBackBufferWidth = %u,\n"
            "\t\t\t\t\t\tEnableAutoDepthStencil = %d,\n"
            "\t\t\t\t\t\tFlags = %u,\n"
            "\t\t\t\t\t\tFullscreen_RefreshRateInHz = %u,\n"
            "\t\t\t\t\t\tMultiSampleQuality = %u,\n"
            "\t\t\t\t\t\tMultiSampleType = %d,\n"
            "\t\t\t\t\t\tPresentationInterval = %u,\n"
            "\t\t\t\t\t\tSwapEffect = %d,\n"
            "\t\t\t\t\t\tWindowed = %d,\n"
            "\t\t\t\t\t\tBehavior = %u",
            static_cast< int >( caps.DeviceType ),
            static_cast< int >( d3dpp.AutoDepthStencilFormat ),
            d3dpp.BackBufferCount,
            static_cast< int >( d3dpp.BackBufferFormat ),
            d3dpp.BackBufferHeight,
            d3dpp.BackBufferWidth,
            static_cast< int >( d3dpp.EnableAutoDepthStencil ),
            d3dpp.Flags,
            d3dpp.FullScreen_RefreshRateInHz,
            d3dpp.MultiSampleQuality,
            static_cast< int >( d3dpp.MultiSampleType ),
            d3dpp.PresentationInterval,
            static_cast< int >( d3dpp.SwapEffect ),
            static_cast< int >( d3dpp.Windowed ),
            behavior );
        throw Vajra::Core::VajraException( "D3DRenderer.cpp (248): ", "Failed to create Direct3D9 Device." );
    }

    // Save the device creation present parameters
    // in case the device has to be reset.
    m_presentParameters = new D3DPRESENT_PARAMETERS;
    CopyMemory( m_presentParameters, &d3dpp, sizeof( D3DPRESENT_PARAMETERS ) );

    // Clear the buffers
    m_device->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 154, 206, 235 ), 1.0f, 0 );

    // Get the back buffer
    hr = m_device->GetBackBuffer( 0, 0, D3DBACKBUFFER_TYPE_MONO, &m_backBuffer );
    if( FAILED( hr ) )
    {
        Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogCritical, "Failed to GetBackBuffer from Direct3D9 Device." );
        throw Vajra::Core::VajraException( "D3DRenderer.cpp (294): ", "Failed to get Backbuffer" );
    }

    // Save the width and height of the back buffer
    m_width = d3dpp.BackBufferWidth;
    m_height = d3dpp.BackBufferHeight;

    // Set up the viewport
    D3DVIEWPORT9 viewport = { 0, 0, m_width, m_height, 1.0f, 1000.0f };
    m_device->SetViewport( &viewport );

    // Create D3D Vertex and Index Buffers
    m_vb = new D3DRenderer::D3DVertexBuffer( *this );
    m_ib = new D3DRenderer::D3DIndexBuffer( *this );

    // Set Render States
    m_device->SetRenderState( D3DRS_LIGHTING, FALSE );
    m_device->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
}

void D3DRenderer::Setup( const float& fieldOfView, const float& zNear, const float& zFar )
{
    m_fieldOfView = fieldOfView;
    m_zNear = zNear;
    m_zFar = zFar;

    D3DXMATRIX identity;
    D3DXMatrixIdentity( &identity );
    m_matrixStack.push_back( identity );

    D3DXMATRIX projectionMatrix;
    ZeroMemory( &projectionMatrix, sizeof( D3DXMATRIX ) );

    float aspect = m_width * 1.0f / m_height;
    float fov = m_fieldOfView * D3DX_PI / 180.0f;

    D3DXMatrixPerspectiveFovLH( &projectionMatrix, fov, aspect, m_zNear, m_zFar );
    m_device->SetTransform( D3DTS_PROJECTION, &projectionMatrix );

    D3DXMATRIX viewMatrix;
    D3DXMatrixLookAtLH( &viewMatrix, &D3DXVECTOR3( 0, 0, -1 ), &D3DXVECTOR3( 0, 0, 0 ), &D3DXVECTOR3( 0, 1, 0 ) );
    m_device->SetTransform( D3DTS_VIEW, &viewMatrix );
}

void D3DRenderer::ValidateDevice(void)
{
    // Test the current state of device
    HRESULT hr = m_device->TestCooperativeLevel();
    if( FAILED( hr ) )
    {
        // If the device is lost, get it next time
        if( D3DERR_DEVICELOST == hr )
        {
            return;
        }

        // If the device is ready to be reset, RESET
        if( D3DERR_DEVICENOTRESET == hr )
        {
            // Release back buffer
            m_backBuffer->Release();

            // Reset device
            hr = m_device->Reset( m_presentParameters );
            if( FAILED( hr ) )
            {
                Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogCritical, "Direct3D9 Device could not be reset with parameters:\n"
                    "\t\t\t\t\t\tAutoDepthStencilFormat = %d,\n"
                    "\t\t\t\t\t\tBackBufferCount = %u,\n"
                    "\t\t\t\t\t\tBackBufferFormat = %d,\n"
                    "\t\t\t\t\t\tBackBufferHeight = %u,\n"
                    "\t\t\t\t\t\tBackBufferWidth = %u,\n"
                    "\t\t\t\t\t\tEnableAutoDepthStencil = %d,\n"
                    "\t\t\t\t\t\tFlags = %u,\n"
                    "\t\t\t\t\t\tFullscreen_RefreshRateInHz = %u,\n"
                    "\t\t\t\t\t\tMultiSampleQuality = %u,\n"
                    "\t\t\t\t\t\tMultiSampleType = %d,\n"
                    "\t\t\t\t\t\tPresentationInterval = %u,\n"
                    "\t\t\t\t\t\tSwapEffect = %d,\n"
                    "\t\t\t\t\t\tWindowed = %d",
                    static_cast< int >( m_presentParameters->AutoDepthStencilFormat ),
                    m_presentParameters->BackBufferCount,
                    static_cast< int >( m_presentParameters->BackBufferFormat ),
                    m_presentParameters->BackBufferHeight,
                    m_presentParameters->BackBufferWidth,
                    static_cast< int >( m_presentParameters->EnableAutoDepthStencil ),
                    m_presentParameters->Flags,
                    m_presentParameters->FullScreen_RefreshRateInHz,
                    m_presentParameters->MultiSampleQuality,
                    static_cast< int >( m_presentParameters->MultiSampleType ),
                    m_presentParameters->PresentationInterval,
                    static_cast< int >( m_presentParameters->SwapEffect ),
                    static_cast< int >( m_presentParameters->Windowed ) );
                throw Vajra::Core::VajraException( "D3DRenderer.cpp (325): ", "Direct3D9 Device could not be reset." );
            }

            // Re-acquire back buffer
            hr = m_device->GetBackBuffer( 0, 0, D3DBACKBUFFER_TYPE_MONO, &m_backBuffer );
            if( FAILED( hr ) )
            {
                Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogCritical, "Failed to GetBackBuffer from Direct3D9 Device." );
                throw Vajra::Core::VajraException( "D3DRenderer.cpp (359): ", "Failed to get Backbuffer" );
            }

            m_device->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 154, 206, 235 ), 1.0f, 0 );
        }
    }
}

void D3DRenderer::BeginFrame(void)
{
    if( !m_lastFrameHasBeenEnded )
    {
        Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, "Failed to end previous render frame." );
        throw Vajra::Core::VajraException( "D3DRenderer.cpp (373): ", "Failed to end previous render frame." );
    }

    ValidateDevice();

    if( NULL == m_device )
    {
        Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, "Failed to render because of invalid device." );
        return;
    }

    m_lastFrameHasBeenEnded = false;

    m_device->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 154, 206, 235 ), 1.0f, 0 );
    m_device->BeginScene();
}

void D3DRenderer::EndFrame(void)
{
    m_device->EndScene();
    m_device->Present( NULL, NULL, NULL, NULL );

    m_lastFrameHasBeenEnded = true;
}

void D3DRenderer::DrawPoint( const Vector& pos )
{
    CHECK_DRAW_VALIDITY( "DrawPoint" );

    m_matrixStack.push_back( m_matrixStack.back() );
    {
        // create a random color
        static unsigned long Color = D3DCOLOR_XRGB( rand() % 255, rand() % 255, rand() % 255 );

        D3DVertex vertices[] =
        {//      X        Y        Z       NX       NY       NZ   DIFFUSE SPECULAR   U     V
            { pos.X(), pos.Y(), pos.Z(), pos.X(), pos.Y(), pos.Z(), Color,       0, 1.0f, 1.0f }
        };

        D3DXMATRIX& world = m_matrixStack.back();
        m_device->SetTransform( D3DTS_WORLD, &world );

        if( FAILED( m_device->SetStreamSource( 0, m_vb->GetVertexBuffer( 1, vertices ), 0, sizeof( D3DVertex ) ) ) )
        {
            Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, "Failed to set stream source on Direct3D9 device." );
            m_vb->Release();
            return;
        }

        if( FAILED( m_device->SetFVF( D3DUntextured_Vertex ) ) )
        {
            Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, "Failed to set flexible vertex format on Direct3D9 device." );
            m_vb->Release();
            return;
        }

        if( FAILED( m_device->DrawPrimitive( D3DPT_POINTLIST, 0, 1 ) ) )
        {
            Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, "Failed to draw primitives on Direct3D9 device." );
            m_vb->Release();
            return;
        }

        m_vb->Release();
    }
    m_matrixStack.pop_back();
}

void D3DRenderer::DrawLine( const Vector& start, const Vector& end )
{
    CHECK_DRAW_VALIDITY( "DrawLine" );

    m_matrixStack.push_back( m_matrixStack.back() );
    {
    }
    m_matrixStack.pop_back();
}

void D3DRenderer::DrawTriangle( const Vector& v1, const Vector& v2, const Vector& v3, const Vector& scale, const float& rotation )
{
    CHECK_DRAW_VALIDITY( "DrawTriangle" );

    m_matrixStack.push_back( m_matrixStack.back() );
    {
        D3DVertex vertices[] =
        {//    X        Y       Z      NX      NY      NZ               DIFFUSE                        SPECULAR          U     V
            { v1.X(), v1.Y(), v1.Z(), v1.X(), v1.Y(), v1.Z(), D3DCOLOR_XRGB( 255,   0,   0 ), D3DCOLOR_XRGB( 0, 0, 0 ), 0.0f, 0.0f },
            { v2.X(), v2.Y(), v2.Z(), v2.X(), v2.Y(), v2.Z(), D3DCOLOR_XRGB( 255, 255,   0 ), D3DCOLOR_XRGB( 0, 0, 0 ), 0.5f, 0.5f },
            { v3.X(), v3.Y(), v3.Z(), v3.X(), v3.Y(), v3.Z(), D3DCOLOR_XRGB(   0,   0, 255 ), D3DCOLOR_XRGB( 0, 0, 0 ), 1.0f, 1.0f }
        };

        const Vector center( ( v1.X() + v2.X() + v3.X() ) / 3.0f,
                             ( v1.Y() + v2.Y() + v3.Y() ) / 3.0f,
                             ( v1.Z() + v2.Z() + v3.Z() ) / 3.0f );

        D3DXMATRIX& world = m_matrixStack.back();

        D3DXMATRIX trans;
        D3DXMATRIX rot;
        D3DXMATRIX sMat;

        D3DXMatrixTranslation( &trans, -center.X(), -center.Y(), -center.Z() );

        D3DXMatrixScaling( &sMat, scale.X(), scale.Y(), scale.Z() );

        D3DXMatrixRotationAxis( &rot, &D3DXVECTOR3( 1.f, 1.f, 0.f ), rotation );

        D3DXMatrixMultiply( &world, &world, &trans );
        D3DXMatrixMultiply( &world, &world, &sMat );
        D3DXMatrixMultiply( &world, &world, &rot );

        D3DXMatrixTranslation( &trans, center.X(), center.Y(), center.Z() );
        D3DXMatrixMultiply( &world, &world, &trans );

        m_device->SetTransform( D3DTS_WORLD, &world );

        m_device->SetStreamSource( 0, m_vb->GetVertexBuffer( 3, vertices ), 0, sizeof( D3DVertex ) );
        m_device->SetFVF( D3DUntextured_Vertex );
        m_device->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 1 );
        m_vb->Release();
    }
    m_matrixStack.pop_back();
}

void D3DRenderer::DrawCircle( const Vector& center, const float& radius, const int& numSegments )
{
    CHECK_DRAW_VALIDITY( "DrawCircle" );

    m_matrixStack.push_back( m_matrixStack.back() );
    {
		D3DVertex* vertices = new D3DVertex[numSegments];
		for(int i = 0; i < numSegments; i++)
		{
		}
    }
    m_matrixStack.pop_back();
}

void D3DRenderer::DrawRectangle( const float& x, const float& y, const float& width, const float& height, const Vector& scale, const float& rotation )
{
    CHECK_DRAW_VALIDITY( "DrawRectangle" );

    m_matrixStack.push_back( m_matrixStack.back() );
    {
        D3DVertex vertices[] =
        {//       X          Y        Z        NX         NY       NZ            DIFFUSE                         SPECULAR          U     V
            { x        , y         , 1.0f, x        , y         , 1.0f, D3DCOLOR_XRGB( 000, 255, 000 ), D3DCOLOR_XRGB( 000, 000, 000 ), 0.0f, 0.0f },
            { x + width, y         , 1.0f, x + width, y         , 1.0f, D3DCOLOR_XRGB( 255, 255, 255 ), D3DCOLOR_XRGB( 000, 000, 000 ), 1.0f, 0.0f },
            { x        , y - height, 1.0f, x        , y - height, 1.0f, D3DCOLOR_XRGB( 255, 255, 255 ), D3DCOLOR_XRGB( 000, 000, 000 ), 0.0f, 1.0f },
            { x + width, y - height, 1.0f, x + width, y - height, 1.0f, D3DCOLOR_XRGB( 255, 000, 255 ), D3DCOLOR_XRGB( 000, 000, 000 ), 1.0f, 1.0f }
        };

        D3DXMATRIX& world = m_matrixStack.back();

        D3DXMATRIX translation;
        D3DXMatrixTranslation( &translation, ( x + width / 2.0f ) * -1.0f, ( y - height / 2.0f ) * -1.0f, -1.0f );

        D3DXMATRIX scaling;
        D3DXMatrixScaling( &scaling, scale.X(), scale.Y(), scale.Z() );

        D3DXMATRIX rot;
        D3DXMatrixRotationAxis( &rot, &D3DXVECTOR3( 1, 1, 1 ), rotation );

        D3DXMatrixMultiply( &world, &world, &translation );
        D3DXMatrixMultiply( &world, &world, &scaling );
        D3DXMatrixMultiply( &world, &world, &rot );

        D3DXMatrixTranslation( &translation, ( x + width / 2.0f ), ( y - height / 2.0f ), 1.0f );
        D3DXMatrixMultiply( &world, &world, &translation );

        m_device->SetTransform( D3DTS_WORLD, &world );

        m_device->SetStreamSource( 0, m_vb->GetVertexBuffer( 4, vertices ), 0, sizeof( D3DVertex ) );
        m_device->SetFVF( D3DUntextured_Vertex );
        if( FAILED( m_device->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 ) ) )
            Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, "DrawRectangle( %.2f, %.2f, %.2f, %2.f, ( %.2f, %.2f, %.2f ), %.2f ) failed.", x, y, width, height, scale.X(), scale.Y(), scale.Z(), rotation );

        m_vb->Release();
    }
    m_matrixStack.pop_back();
}

void D3DRenderer::DrawTexturedRectangle( const Texture* texture, const float& x, const float& y, const float& width, const float& height, const Vector& scale, const float& rotation )
{
    CHECK_DRAW_VALIDITY( "DrawTexturedRectangle" );

    m_matrixStack.push_back( m_matrixStack.back() );
    {
        if( NULL != texture )
            m_device->SetTexture( 0, ( ( D3DTexture*) texture )->Data() );

        D3DVertex vertices[] =
        {//       X          Y        Z        NX         NY       NZ            DIFFUSE                         SPECULAR          U     V
            { x        , y         , 1.0f, x        , y         , 1.0f, D3DCOLOR_XRGB( 255, 255, 255 ), D3DCOLOR_XRGB( 0, 0, 0 ), 0.0f, 0.0f },
            { x + width, y         , 1.0f, x + width, y         , 1.0f, D3DCOLOR_XRGB( 255, 255, 255 ), D3DCOLOR_XRGB( 0, 0, 0 ), 1.0f, 0.0f },
            { x        , y + height, 1.0f, x        , y + height, 1.0f, D3DCOLOR_XRGB( 255, 255, 255 ), D3DCOLOR_XRGB( 0, 0, 0 ), 0.0f, 1.0f },
            { x + width, y + height, 1.0f, x + width, y + height, 1.0f, D3DCOLOR_XRGB( 255, 255, 255 ), D3DCOLOR_XRGB( 0, 0, 0 ), 1.0f, 1.0f },
        };

        D3DXMATRIX& world = m_matrixStack.back();

        D3DXMATRIX translation;
        D3DXMatrixTranslation( &translation, ( x + width / 2.0f ) * -1.0f, ( y + height / 2.0f ) * -1.0f, -1.0f );

        D3DXMATRIX scaling;
        D3DXMatrixScaling( &scaling, scale.X(), scale.Y(), scale.Z() );

        D3DXMATRIX rot;
        D3DXMatrixRotationAxis( &rot, &D3DXVECTOR3( 1, 1, 1 ), rotation );

        D3DXMatrixMultiply( &world, &world, &translation );
        D3DXMatrixMultiply( &world, &world, &scaling );
        D3DXMatrixMultiply( &world, &world, &rot );

        D3DXMatrixTranslation( &translation, ( x + width / 2.0f ), ( y + height / 2.0f ), 1.0f );
        D3DXMatrixMultiply( &world, &world, &translation );

        m_device->SetTransform( D3DTS_WORLD, &world );

        m_device->SetStreamSource( 0, m_vb->GetVertexBuffer( 4, vertices ), 0, sizeof( D3DVertex ) );
        m_device->SetFVF( D3DTextured_Vertex );
        if( FAILED( m_device->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 ) ) )
            Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, "DrawTexturedRectangle( %x, %.2f, %.2f, %.2f, %2.f, ( %.2f, %.2f, %.2f ), %.2f ) failed.", texture, x, y, width, height, scale.X(), scale.Y(), scale.Z(), rotation );

        m_vb->Release();

        if( NULL != texture )
            m_device->SetTexture( 0, NULL );
    }
    m_matrixStack.pop_back();
}

void D3DRenderer::DrawString( const std::string& text, const float& x, const float& y, const int& size )
{
    CHECK_DRAW_VALIDITY( "DrawString" );
}
