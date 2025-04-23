#pragma once

#ifndef _VAJRA_VERSION_2_TIMER_HPP_
#define _VAJRA_VERSION_2_TIMER_HPP_

#include <string>

namespace Vajra
{
    namespace Core
    {
        class TimeManager;

        class Timer
        {
        protected:
            friend class TimeManager;

            Timer( const std::string& name = std::string( "Unnamed" ) ) { }
            virtual ~Timer(void) { }
            Timer( const Timer& timer ) { }
            Timer& operator = ( const Timer& timer ) { }

            static Timer* Create( const std::string& name );

            virtual void Initialize(void) = 0;
            virtual void Update(void) = 0;

        public:
            virtual const float& GetDelta(void) const = 0;
            virtual const float& GetFPS(void) const = 0;

            virtual void Start(void) = 0;
            virtual void Pause(void) = 0;
            virtual void Resume(void) = 0;
            virtual void Stop(void) = 0;
        };
    }
}

#endif //_VAJRA_VERSION_2_TIMER_HPP_
