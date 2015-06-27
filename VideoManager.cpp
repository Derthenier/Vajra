#include "pch.hpp"
#include "Logger.hpp"
#include "VideoManager.hpp"
using Vajra::Video::VideoSystem;

#include <fstream>

VideoSystem::VideoSystem(void)
	: m_videos()
	, m_ready( false )
{
}

VideoSystem::~VideoSystem(void)
{
}

void VideoSystem::Load( const std::string& loadFile )
{
	std::string path = loadFile;
	if( loadFile.empty() )
	{
		path = "path to default asset loading file";
	}

	std::ifstream file( path.c_str() );
	while( !file.eof() )
	{
		std::string pathToVideoFile;
		std::string name;

		file >> pathToVideoFile;
		std::string::size_type idx = pathToVideoFile.rfind( '/' );
		if( idx != std::string::npos )
		{
			name = pathToVideoFile.substr( idx + 1 );
			m_videos.insert( std::make_pair( name, pathToVideoFile ) );
		}
		else
		{
			std::ostringstream osstr;
			osstr << path << " should contain paths to video files. Found invalid string '" << pathToVideoFile << "'.";
			Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, osstr.str().c_str() );
		}
	}
}

/*
void VideoSystem::Initialize(void)
{
	HRESULT hr = CoInitialize( NULL );
	if( FAILED( hr ) )
	{
		Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, "Failed to initialize COM in VideoSystem::Initialize" );
		m_ready = false;
		return;
	}

	// Create the filter graph
	hr = CoCreateInstance( CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, ( void ** ) &m_pGraph );
	if( FAILED( hr ) )
	{
		Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, "Failed to create the Filter Graph Manager in VideoSystem::Initialize" );
		m_ready = false;
		return;
	}

	// Query the interfaces
	hr = m_pGraph->QueryInterface( IID_IMediaControl, ( void ** ) &m_pControl );
	if( FAILED( hr ) )
	{
		Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, "Failed to create the Media Control in VideoSystem::Initialize" );
		m_ready = false;
		return;
	}

	hr = m_pGraph->QueryInterface( IID_IMediaEvent, ( void ** ) &m_pEvent );
	if( FAILED( hr ) )
	{
		Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, "Failed to create the Media Event in VideoSystem::Initialize" );
		m_ready = false;
		return;
	}

	m_ready = true;
}

void VideoSystem::Shutdown(void)
{
	{
		m_videos.clear();
		std::map< std::string, std::string >().swap( m_videos );
	}

	if( m_pEvent != NULL )
	{
		m_pEvent->Release();
		m_pEvent = NULL;
	}

	if( m_pControl != NULL )
	{
		m_pControl->Release();
		m_pControl = NULL;
	}

	if( m_pGraph != NULL )
	{
		m_pGraph->Release();
		m_pGraph = NULL;
	}

	CoUninitialize();
}

void VideoSystem::Play( const std::string& name )
{
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

	HRESULT hr = m_pGraph->RenderFile( pathToVideoFile, NULL );
	if( FAILED( hr ) )
	{
		std::ostringstream osstr;
		osstr << "Failed to Render File '" << name << "' in VideoSystem::PlayVideo";
		Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, osstr.str().c_str() );
		return;
	}

	hr = m_pControl->Run();
	if( FAILED( hr ) )
	{
		std::ostringstream osstr;
		osstr << "Failed to play file '" << name << "' in VideoSystem::PlayVideo";
		Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, osstr.str().c_str() );
		return;
	}

	delete [] pathToVideoFile;
}

void VideoSystem::Pause( const std::string& name )
{
}

void VideoSystem::Resume( const std::string& name )
{
}

void VideoSystem::Stop( const std::string& name )
{
}
*/



#if defined( _WIN32 )

#include "Win32/Win32VideoSystem.hpp"

VideoSystem& Vajra::Video::VideoManager::GetVideoSystem(void)
{
	return ( Vajra::Video::Win32::Win32VideoSystem::GetInstance() );
}

#endif