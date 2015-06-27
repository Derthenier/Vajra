#include "pch.hpp"
#include "../Definitions.hpp"
#include "Win32Timer.hpp"
#include <windows.h>


using Vajra::Core::Timer;
using Vajra::Core::Win32::Win32Timer;

Win32Timer::Win32Timer( const std::string& name )
: Timer( name )
, m_frequency( 0 )
, m_startTime( 0 )
, m_prevTime( 0 )
, m_endTime( 0 )
, m_invFrequency( 0.0f )
, m_delta( 0.0f )
, m_fps( 0.0f )
, m_name( name )
{
}

Win32Timer::~Win32Timer(void)
{
    m_frequency = 0;
    m_startTime = 0;
    m_prevTime = 0;
    m_endTime = 0;
    m_invFrequency = 0.0f;
    m_delta = 0.0f;
    m_fps = 0.0f;
}

const float& Win32Timer::GetDelta(void) const
{
    return m_delta;
}

const float& Win32Timer::GetFPS(void) const
{
    return m_fps;
}

void Win32Timer::Initialize(void)
{
    // Get the clock frequency ( ticks per second )
    QueryPerformanceFrequency( ( LARGE_INTEGER* )&m_frequency );

    // Get the start time
    QueryPerformanceCounter( ( LARGE_INTEGER* )&m_startTime );
    m_prevTime = m_startTime;

    m_invFrequency = 1.0f / static_cast< float >( m_frequency );
}

void Win32Timer::Update(void)
{
    __int64 currentTime = 0;       // The current frame count

    // Get the current count
    QueryPerformanceCounter( ( LARGE_INTEGER* )&currentTime );

    // Compute the number of seconds that have elapsed
    // since the last call to Update
    m_delta = static_cast< float >( currentTime - m_prevTime ) * m_invFrequency;

    // Compute the fps
    m_fps = 1.0f / m_delta;

    // Reset the timer
    m_prevTime = currentTime;
}

void Win32Timer::Start(void)
{
}

void Win32Timer::Pause(void)
{
}

void Win32Timer::Resume(void)
{
}

void Win32Timer::Stop(void)
{
    QueryPerformanceCounter( ( LARGE_INTEGER* )&m_endTime );
}

float Win32Timer::GetDuration(void) const
{
    return static_cast< float >( m_endTime - m_startTime ) * m_invFrequency;
}
