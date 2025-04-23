#pragma once

#ifndef _VAJRA_VERSION_2_CLOCK_HPP_
#define _VAJRA_VERSION_2_CLOCK_HPP_

#include <sstream>
#include <string>

namespace Vajra
{
    namespace Core
    {
        class TimeManager;

        struct ClockData
        {
            long long Year;
            long long Month;
            long long Date;
            long long Hours;
            long long Minutes;
            long long Seconds;
            long long Milliseconds;

            ClockData& operator = ( const ClockData& cd )
            {
                if( this != &cd )
                {
                    Year = cd.Year;
                    Month = cd.Month;
                    Date = cd.Date;
                    Hours = cd.Hours;
                    Minutes = cd.Minutes;
                    Seconds = cd.Seconds;
                    Milliseconds = cd.Milliseconds;
                }

                return *this;
            }

            std::string ToString(void) const
            {
                std::ostringstream oss;
                oss.fill( '0' );

                oss.width( 2 );
                oss << Year;
                oss << "-";

                oss.width( 2 );
                oss << Month;
                oss << "-";

                oss.width( 2 );
                oss << Date;
                oss << "( ";

                oss.width( 2 );
                oss << Hours;
                oss << "h:";

                oss.width( 2 );
                oss << Minutes;
                oss << "m:";

                oss.width( 2 );
                oss << Seconds;
                oss << "s )";

                return oss.str();
            }

            std::string ToTimeString(void) const
            {
                std::ostringstream oss;

                oss.width( 2 );
                oss << Hours;
                oss << "h:";

                oss.width( 2 );
                oss << Minutes;
                oss << "m:";

                oss.width( 2 );
                oss << Seconds;
                oss << "s";

                return oss.str();
            }
        };

        class Clock
        {
        public:
            static Clock* Create( const std::string& name = "Unnamed" );

            virtual void Start(void) = 0;
            virtual void Pause(void) = 0;
            virtual void Resume(void) = 0;
            virtual void Stop(void) = 0;

            virtual const ClockData GetDuration(void) const = 0;
            virtual const ClockData GetTime(void) const = 0;

        protected:
            friend class TimeManager;

            Clock(void) { }
            Clock( const Clock& clock ) { }
            virtual ~Clock(void) { }
            Clock& operator = ( const Clock& clock ) { }
        };
    }
}

#endif //_VAJRA_VERSION_2_CLOCK_HPP_
