#pragma once

#ifndef _VAJRA_VERSION_2_WIN32TIMER_HPP_
#define _VAJRA_VERSION_2_WIN32TIMER_HPP_

#include "../Timer.hpp"

namespace Vajra
{
    namespace Core
    {
        namespace Win32
        {
            class Win32Timer :  public Vajra::Core::Timer
            {
            public:
                Win32Timer( const std::string& name = std::string( "Unnamed" ) );
                virtual ~Win32Timer(void);

                virtual const float& GetDelta(void) const;
                virtual const float& GetFPS(void) const;

                virtual void Start(void);
                virtual void Pause(void);
                virtual void Resume(void);
                virtual void Stop(void);

                float GetDuration(void) const;

            private:
                virtual void Initialize(void);
                virtual void Update(void);

                __int64 m_frequency;
                __int64 m_startTime;
                __int64 m_prevTime;
                __int64 m_endTime;
                float m_invFrequency;
                float m_delta;
                float m_fps;
                std::string m_name;
            };
        }
    }
}

#endif //_VAJRA_VERSION_2_WIN32TIMER_HPP_
