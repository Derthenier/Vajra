#include "pch.hpp"
#include "Camera.hpp"
using Vajra::Graphics::Camera;

#include "IdManager.hpp"

Camera::Camera( const std::string& name )
: Vajra::Graphics::Object( Vajra::Core::IdManager::GetId( std::string( "Camera_" ) + name ) )
{
}

Camera::~Camera(void)
{
}

#if defined( _WIN32 )

#include "DirectX/D3DCamera.hpp"
using Vajra::Graphics::DirectX::D3DCamera;

Camera& Camera::Create( const std::string& name )
{
    return *( new D3DCamera( name ) );
}

#elif defined( _MACOS ) || defined( _LINUX )

Camera& Camera::Create( const std::string& name )
{
}

#endif