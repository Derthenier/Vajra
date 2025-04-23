#pragma once

#ifndef _VAJRA_VERSION_2_LOGGER_HPP_
#define _VAJRA_VERSION_2_LOGGER_HPP_

#include <fstream>
#include <string>
#include <cstdarg>
#include "Singleton.hpp"
#include "Mutex.hpp"
#include "Clock.hpp"

namespace Vajra
{
    namespace Core
    {
        enum LogLevel
        {
            LogNone = 0,           // ""
            LogInformation = 1,    // "Info: "
            LogWarning = 2,        // "Warning: "
            LogError = 3,          // "Error: "
            LogCritical = 4        // "Failure: "
        };

        class Logger : public Vajra::Core::Singleton< Logger >
        {
            friend class Vajra::Core::Singleton< Logger >;

        public:
            virtual ~Logger(void);

            void Open( const char* logFilename, Vajra::Core::Clock* clock = NULL );
            void Open( const std::string& logFilename, Vajra::Core::Clock* clock = NULL );

            void Write( LogLevel level, const char* format, ... );
            void Write( const char* format, ... );

        private:
            Logger(void);
            Logger( const Logger& logger ) { }
            Logger& operator = ( const Logger& logger ) { }

            void Write( LogLevel level, const char* format, va_list args );

        private:
            std::ofstream m_logFile;
            char* m_buffer;
            bool m_noLogging;

            Vajra::Threads::Mutex* m_mutex;
            Vajra::Core::Clock* m_clock;
        };
    }
}

#endif //_VAJRA_VERSION_2_LOGGER_HPP_
