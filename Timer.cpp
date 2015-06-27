#include "pch.hpp"
#include "Timer.hpp"
using Vajra::Core::Timer;

#if defined( _WIN32 )

#include "Win32/Win32Timer.hpp"
using Vajra::Core::Win32::Win32Timer;

Timer* Timer::Create( const std::string& name )
{
    return new Win32Timer( name );
}

#elif defined( _MACOS )

#include "Mac/MacTimer.hpp"
using Vajra::Core::Mac::MacTimer;

Timer* Timer::Create( const std::string& name )
{
    return new MacTimer( name );
}

#elif defined( _LINUX )

#include "Linux/LinuxTimer.hpp"
using Vajra::Core::Linux::LinuxTimer;

Timer* Timer::Create( const std::string& name )
{
    return new LinuxTimer( name );
}

#endif
