#include "pch.hpp"
#include "Clock.hpp"
using Vajra::Core::Clock;

#if defined( _WIN32 )

#include "Win32/Win32Clock.hpp"
using Vajra::Core::Win32::Win32Clock;

Clock* Clock::Create( const std::string& name )
{
    return new Win32Clock( name );
}

#elif defined( _MACOS )

#include "Mac/MacClock.hpp"
using Vajra::Core::Mac::MacClock;

Clock* Clock::Create( const std::string& name )
{
    return new MacClock( name );
}

#elif defined( _LINUX )

#include "Linux/LinuxClock.hpp"
using Vajra::Core::Linux::LinuxClock;

Clock* Clock::Create( const std::string& name )
{
    return new LinuxClock( name );
}

#endif