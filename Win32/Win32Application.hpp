#pragma once

#ifndef _VAJRA_VERSION_2_WIN32APPLICATION_HPP_
#define _VAJRA_VERSION_2_WIN32APPLICATION_HPP_

#include "../Singleton.hpp"
#include "../Application.hpp"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define VAJRA_VIDEO_NOTIFY WM_APP + 1

namespace Vajra
{
    namespace Core
    {
        namespace Win32
        {
            class Win32Application : public Vajra::Core::Singleton< Win32Application >, public Vajra::Core::Application
            {
                friend class Vajra::Core::Singleton< Win32Application >;
                typedef Vajra::Core::Application Base;

            public:
                virtual ~Win32Application(void);

                virtual void Initialize( const bool& isFullscreen );
                virtual void Run( const Vajra::Core::Timer* const timer );

                virtual void SetTitle( const std::string& title );

                void SetAttributes( HINSTANCE hInstance, HICON hIcon );
                const HWND& GetAppWindow(void) const;
				const HINSTANCE& GetAppInstance(void) const;

                virtual void Shutdown(void);

            private:
                Win32Application(void);
                Win32Application( const Win32Application& app ) { }
                Win32Application& operator = ( const Win32Application& app ) { }

                static LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );
                static void DefaultRunFrame( float delta );

            private:
                HWND m_window;
                HINSTANCE m_instance;
                HICON m_icon;
                bool m_quitting;
            };
        }
    }
}

#endif // _VAJRA_VERSION_2_WIN32APPLICATION_HPP_
