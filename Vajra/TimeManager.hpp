#pragma once

#ifndef _VAJRA_VERSION_2_TIMER_MANAGER_HPP_
#define _VAJRA_VERSION_2_TIMER_MANAGER_HPP_

#include <map>
#include "Singleton.hpp"

namespace Vajra
{
    namespace Core
    {
        class Timer;
        class Clock;

        class TimeManager : public Singleton< TimeManager >
        {
        public:
            typedef std::map< std::string, Timer* > TimerMap;
            typedef std::map< std::string, Clock* > ClockMap;

            virtual ~TimeManager(void);

            const Timer* const GetTimer( const std::string& name );
            Clock* GetClock( const std::string& name );

            void Update(void);

        protected:
            TimeManager(void) { }
            TimeManager(const TimeManager& tm) { }
            TimeManager& operator = ( const TimeManager& tm ) { return *this; }

        private:
            friend class Singleton< TimeManager >;

            TimerMap m_timers;
            ClockMap m_clocks;
        };
    }
}

#endif //_VAJRA_VERSION_2_TIMER_MANAGER_HPP_
