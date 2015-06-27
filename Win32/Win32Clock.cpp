#include "pch.hpp"
#include "../Definitions.hpp"
#include "Win32Clock.hpp"
#include <windows.h>

using Vajra::Core::Win32::Win32Clock;
using Vajra::Core::Clock;
using Vajra::Core::ClockData;

Win32Clock::Win32Clock( const std::string& name )
: Clock()
, m_frequency( 0 )
, m_startTime( 0 )
, m_endTime( 0 )
, m_duration( 0 )
, m_name( name )
{
}

Win32Clock::~Win32Clock(void)
{
    m_frequency = 0;
    m_startTime = 0;
    m_endTime = 0;
    m_duration = 0;
    m_name.clear();
}

void Win32Clock::Start(void)
{
    // Get the clock frequency ( ticks per second )
    QueryPerformanceFrequency( ( LARGE_INTEGER* )&m_frequency );

    // Get the start time
    QueryPerformanceCounter( ( LARGE_INTEGER* )&m_startTime );
}

void Win32Clock::Pause(void)
{
}

void Win32Clock::Resume(void)
{
}

void Win32Clock::Stop(void)
{
    // Get the end time
    QueryPerformanceCounter( ( LARGE_INTEGER* )&m_endTime );
}

const ClockData Win32Clock::GetDuration(void) const
{
    m_duration = ( m_endTime - m_startTime ) * 1000;
    m_duration = m_duration / m_frequency;

    ClockData cd;

    cd.Hours = m_duration / 3600;

    m_duration = m_duration - ( cd.Hours * 3600 );
    cd.Minutes = m_duration / 60;

    m_duration = m_duration - ( cd.Minutes * 60 );
    cd.Seconds = m_duration;

    return cd;
}

const ClockData Win32Clock::GetTime(void) const
{
    SYSTEMTIME sysTime;
    GetLocalTime( &sysTime );

    ClockData cd =
    {
        static_cast< long long >( sysTime.wYear         ),
        static_cast< long long >( sysTime.wMonth        ),
        static_cast< long long >( sysTime.wDay          ),
        static_cast< long long >( sysTime.wHour         ),
        static_cast< long long >( sysTime.wMinute       ),
        static_cast< long long >( sysTime.wSecond       ),
        static_cast< long long >( sysTime.wMilliseconds )
    };

    return cd;
}
