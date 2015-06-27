#include "pch.hpp"
#include "../Definitions.hpp"
#include "../Exception.hpp"
#include "../Logger.hpp"
#include "Win32Application.hpp"
using Vajra::Core::Win32::Win32Application;

#include "Win32InputSystem.hpp"
using Vajra::Input::Win32::Win32InputSystem;

LRESULT CALLBACK Win32Application::WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    Win32InputSystem& input = static_cast< Win32InputSystem& >( Vajra::Input::InputManager::GetInput() );
    Vajra::Input::InputSystem::Callback callback = NULL;

    switch( msg )
    {
    case WM_PAINT:
        ValidateRect( hwnd, NULL );
        return 0;
        break;

    case WM_DESTROY:
        PostQuitMessage( 0 );
        return 0;
        break;

	//case WM_KEYDOWN:
	//	callback = input.KeyDownCallback( static_cast< unsigned int >( wParam ) );
	//	if( callback != NULL )
	//		callback();
	//	break;

	//   case WM_KEYUP:
	//       callback = input.KeyUpCallback( static_cast< unsigned int >( wParam ) );
	//       if( callback != NULL )
	//           callback();
	//       break;

	//   case WM_LBUTTONDOWN:
	//   case WM_MBUTTONDOWN:
	//   case WM_RBUTTONDOWN:
	//       callback = input.ButtonDownCallback( static_cast< unsigned int >( wParam ) );
	//       if( callback != NULL )
	//           callback();
	//       break;

	//   case WM_LBUTTONUP:
	//   case WM_MBUTTONUP:
	//   case WM_RBUTTONUP:
	//       callback = input.ButtonUpCallback( static_cast< unsigned int >( wParam ) );
	//       if( callback != NULL )
	//           callback();
	//       break;

    default:
        return DefWindowProc( hwnd, msg, wParam, lParam );
        break;
    }

    return DefWindowProc( hwnd, msg, wParam, lParam );
}

void Win32Application::DefaultRunFrame( float delta )
{
    static bool setTitleOnlyOnce = false;
    if( !setTitleOnlyOnce )
    {
        Win32Application& app = static_cast< Win32Application& >( ApplicationManager::GetApplication() );
        app.SetTitle( "Default RunFrame Called" );
        setTitleOnlyOnce = true;
    }
}

Win32Application::Win32Application(void)
: Vajra::Core::Singleton< Win32Application >()
, Vajra::Core::Application()
, m_window( NULL )
, m_quitting( false )
{
}

Win32Application::~Win32Application(void)
{
}

void Win32Application::SetAttributes( HINSTANCE hInstance, HICON hIcon )
{
    m_instance = hInstance;
    m_icon = hIcon;
}

const HWND& Win32Application::GetAppWindow(void) const
{
    return m_window;
}

const HINSTANCE& Win32Application::GetAppInstance(void) const
{
	return m_instance;
}

void Win32Application::Initialize( const bool& isFullscreen )
{
    WNDCLASSEX wc;
    ZeroMemory( &wc, sizeof( WNDCLASSEX ) );

    wc.cbSize        = sizeof( WNDCLASSEX );
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.hInstance     = m_instance;
    wc.hIcon         = m_icon;
    wc.hIconSm       = m_icon;
    wc.hCursor       = LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground = ( HBRUSH )GetStockObject( BLACK_BRUSH );
    wc.lpfnWndProc   = Win32Application::WndProc;
    wc.lpszClassName = GetAppName().c_str();
    wc.lpszMenuName  = NULL;

    RegisterClassEx( &wc );

    if( isFullscreen )
    {
        m_window = CreateWindowEx( WS_EX_TOPMOST,
            GetAppName().c_str(), GetAppName().c_str(),
            WS_POPUP | WS_SYSMENU | WS_VISIBLE,
            CW_USEDEFAULT, CW_USEDEFAULT,
            0, 0,
            NULL,
            NULL,
            m_instance,
            NULL );
    }
    else
    {
        m_window = CreateWindow(
            GetAppName().c_str(), GetAppName().c_str(),
            ( WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX ),
            CW_USEDEFAULT, CW_USEDEFAULT,
            m_width, m_height,
            NULL,
            NULL,
            m_instance,
            NULL );
    }

    if( NULL == m_window )
    {
        DEFINE_ERROR( "Failed to create window." );
       // Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogCritical, "Failed to create window" );
       // std::ostringstream buf;
       // buf << __FILE__ << " (" << __LINE__ << ")";
       // throw Vajra::Core::VajraException( buf.str(), "Failed to create window" );
    }

    ShowWindow( m_window, SW_SHOW );
    UpdateWindow( m_window );
}

void Win32Application::Run( const Vajra::Core::Timer* const timer )
{
    MSG msg;
    ZeroMemory( &msg, sizeof( MSG ) );

    if( NULL == RunFrame )
        RunFrame = Win32Application::DefaultRunFrame;

    while( !m_quitting )
    {
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        {
            if( WM_QUIT == msg.message )
                m_quitting = true;
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        else
        {
            RunFrame( timer->GetDelta() );
        }

        Sleep( 10 );
    }
}

void Win32Application::Shutdown(void)
{
    PostQuitMessage( 0 );
}

void Win32Application::SetTitle( const std::string& title )
{
    SetWindowText( m_window, title.c_str() );
}
