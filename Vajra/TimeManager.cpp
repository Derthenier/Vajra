#include "pch.hpp"
#include "TimeManager.hpp"
#include "Timer.hpp"
#include "Clock.hpp"

using Vajra::Core::TimeManager;
using Vajra::Core::Timer;
using Vajra::Core::Clock;

TimeManager::~TimeManager(void)
{
    for( TimerMap::iterator itr = m_timers.begin(); itr != m_timers.end(); ++itr )
    {
        delete (itr->second);
        itr->second = NULL;
    }
    m_timers.clear();

    for( ClockMap::iterator itr = m_clocks.begin(); itr != m_clocks.end(); ++itr )
    {
        itr->second->Stop();
        delete (itr->second);
        itr->second = NULL;
    }
    m_clocks.clear();

    TimerMap().swap( m_timers );
    ClockMap().swap( m_clocks );
}

const Timer* const TimeManager::GetTimer( const std::string& name )
{
    if( m_timers.find( name ) == m_timers.end() )
    {
        Timer* timer = Timer::Create(name);
        timer->Initialize();
        m_timers.insert( std::make_pair( name, timer ) );
        return timer;
    }
    else
    {
        return m_timers[ name ];
    }
}

Clock* TimeManager::GetClock( const std::string& name )
{
    if( m_clocks.find( name ) == m_clocks.end() )
    {
        Clock* clock = Clock::Create( name );
        m_clocks.insert( std::make_pair( name, clock ) );
        return clock;
    }
    else
    {
        return m_clocks[ name ];
    }
}

void TimeManager::Update(void)
{
    for( TimerMap::iterator itr = m_timers.begin(); itr != m_timers.end(); ++itr )
        itr->second->Update();
}


