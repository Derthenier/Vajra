#pragma once

#ifndef _VAJRA_VERSION_2_WIN32CLOCK_HPP_
#define _VAJRA_VERSION_2_WIN32CLOCK_HPP_

#include "../Clock.hpp"

namespace Vajra
{
    namespace Core
    {
        using Vajra::Core::Clock;
        using Vajra::Core::ClockData;

        namespace Win32
        {
            class Win32Clock : public Clock
            {
            public:
                Win32Clock( const std::string& name );
                virtual ~Win32Clock(void);

                virtual void Start(void);
                virtual void Pause(void);
                virtual void Resume(void);
                virtual void Stop(void);

                virtual const ClockData GetDuration(void) const;
                virtual const ClockData GetTime(void) const;

            private:
                __int64 m_frequency;
                __int64 m_startTime;
                __int64 m_endTime;
                mutable __int64 m_duration;
                std::string m_name;
            };
        }
    }
}

#endif //_VAJRA_VERSION_2_WIN32CLOCK_HPP_
