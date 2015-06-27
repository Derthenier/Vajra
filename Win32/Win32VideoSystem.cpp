#include "pch.hpp"
#include "Win32VideoSystem.hpp"
using Vajra::Video::VideoSystem;
using Vajra::Video::Win32::Win32VideoSystem;

#include "../Logger.hpp"
#include "Win32Application.hpp"
#include <dshow.h>

Win32VideoSystem::Win32VideoSystem(void)
	: m_graph( NULL )
	, m_control( NULL )
	, m_vw( NULL )
	, m_isPlaying( false )
{
}

Win32VideoSystem::~Win32VideoSystem(void)
{
	Shutdown();
}

void Win32VideoSystem::Initialize(void)
{
	HRESULT hr = CoInitialize( NULL );
	if( FAILED( hr ) )
	{
		Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, "Failed to initialize COM in VideoSystem::Initialize" );
		m_ready = false;
		return;
	}

	// Create the filter graph
	hr = CoCreateInstance( CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, ( void ** ) &m_graph );
	if( FAILED( hr ) )
	{
		Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, "Failed to create the Filter Graph Manager in VideoSystem::Initialize" );
		m_ready = false;
		return;
	}

	// Query the interfaces
	hr = m_graph->QueryInterface( IID_IMediaControl, ( void ** ) &m_control );
	if( FAILED( hr ) )
	{
		Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, "Failed to create the Media Control in VideoSystem::Initialize" );
		m_ready = false;
		return;
	}

	hr = m_graph->QueryInterface( IID_IVideoWindow, ( void ** ) &m_vw );
	if( FAILED( hr ) )
	{
		Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, "Failed to create the Video window in VideoSystem::Initialize" );
		m_ready = false;
		return;
	}
	m_ready = true;
}

void Win32VideoSystem::Shutdown(void)
{
	m_isPlaying = false;

	if( m_vw != NULL )
	{
		m_vw->put_Visible( OAFALSE );
		m_vw->put_Owner( NULL );
		m_vw->Release();
		m_vw = NULL;
	}

	if( m_control != NULL )
	{
		m_control->Release();
		m_control = NULL;
	}

	if( m_graph != NULL )
	{
		m_graph->Release();
		m_graph = NULL;
	}

	CoUninitialize();
}

void Win32VideoSystem::Play( const std::string& name )
{
	if( m_isPlaying )
		return;

	std::map< std::string, std::string >::iterator itr = m_videos.find( name );
	if( !m_ready )
		return;

	if( itr == m_videos.end() )
	{
		std::ostringstream osstr;
		osstr << "Failed to find video file '" << name << "' in VideoSystem::PlayVideo";
		Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, osstr.str().c_str() );
		return;
	}

	int size = MultiByteToWideChar( CP_UTF8, 0, itr->second.c_str(), -1, NULL, 0 );
	wchar_t* pathToVideoFile = new wchar_t[ size ];
	MultiByteToWideChar( CP_UTF8, 0, itr->second.c_str(), -1, pathToVideoFile, size );

	HRESULT hr = m_graph->RenderFile( pathToVideoFile, NULL );
	if( FAILED( hr ) )
	{
		std::ostringstream osstr;
		osstr << "Failed to Render File '" << name << "' in VideoSystem::PlayVideo";
		Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, osstr.str().c_str() );
		return;
	}

	Vajra::Core::Win32::Win32Application& app = static_cast< Vajra::Core::Win32::Win32Application& >( Vajra::Core::ApplicationManager::GetApplication() );
	HWND hwnd = app.GetAppWindow();

	m_vw->put_Owner( ( OAHWND )( hwnd ) );
	m_vw->put_WindowStyle( WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN );
	RECT rect;
	GetClientRect( hwnd, &rect );
	m_vw->SetWindowPosition( rect.left, rect.top, rect.right, rect.bottom );
	m_vw->put_Visible( OATRUE );

	hr = m_control->Run();
	if( FAILED( hr ) )
	{
		std::ostringstream osstr;
		osstr << "Failed to play file '" << name << "' in VideoSystem::PlayVideo";
		Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, osstr.str().c_str() );
		return;
	}

	m_isPlaying = true;

	delete [] pathToVideoFile;
}

void Win32VideoSystem::Pause(void)
{
}

void Win32VideoSystem::Resume(void)
{
}

void Win32VideoSystem::Stop(void)
{
	m_isPlaying = false;
}
