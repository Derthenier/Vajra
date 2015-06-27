#include "pch.hpp"
#include "Definitions.hpp"
#include "Application.hpp"
using Vajra::Core::Application;
using Vajra::Core::ApplicationManager;

Application::Application(void)
{
    RunFrame = NULL;
}

Application::~Application(void)
{
}

void Application::Initialize( const std::string& appName, const int& windowWidth, const int& windowHeight, const bool& isFullscreen )
{
    m_appName = appName;
    m_width = windowWidth;
    m_height = windowHeight;

    Initialize( isFullscreen );
}

const std::string& Application::GetAppName(void) const
{
    return m_appName;
}

const int& Application::GetWindowWidth(void) const
{
    return m_width;
}

const int& Application::GetWindowHeight(void) const
{
    return m_height;
}

#if defined( _WIN32 )

#include "Win32/Win32Application.hpp"
using Vajra::Core::Win32::Win32Application;

Application& ApplicationManager::GetApplication(void)
{
    return ( Win32Application::GetInstance() );
}

#elif defined( _MACOS )

#include "Mac/MacApplication.hpp"
using Vajra::Core::Mac::MacApplication;

Application& ApplicationManager::GetApplication(void)
{
    return ( MacApplicaton::GetInstance() );
}

#elif defined( _LINUX )

#include "Linux/LinuxApplication.hpp"
using Vajra::Core::Linux::LinuxApplication;

Application& ApplicationManager::GetApplication(void)
{
    return ( LinuxApplication::GetInstance() );
}

#endif
