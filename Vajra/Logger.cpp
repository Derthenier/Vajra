#include "pch.hpp"
#include "Logger.hpp"
using Vajra::Core::Logger;
using Vajra::Core::LogLevel;

#include "TimeManager.hpp"

Logger::Logger(void)
: m_logFile()
, m_buffer( NULL )
, m_noLogging( true )
, m_mutex( NULL )
, m_clock( NULL )
{
    m_mutex = new Vajra::Threads::Mutex();
}

Logger::~Logger(void)
{
    if( NULL != m_mutex )
    {
        delete m_mutex;
        m_mutex = NULL;
    }

    if( NULL != m_buffer )
    {
        delete [] m_buffer;
        m_buffer = NULL;
    }

    if( m_logFile.is_open() )
    {
        m_logFile.flush();
        m_logFile.close();
    }

    m_noLogging = true;
}

void Logger::Open( const char* logFilename, Vajra::Core::Clock* clock )
{
    Vajra::Threads::MutexLock lock(m_mutex);

    if( m_logFile.is_open() )
        return;

    m_logFile.open( logFilename );
    m_noLogging = m_logFile.fail();

    if( NULL != clock )
    {
        m_clock = clock;
        m_clock->Start();
    }
}

void Logger::Open( const std::string& logFilename, Vajra::Core::Clock* clock )
{
    Vajra::Threads::MutexLock lock(m_mutex);

    if( m_logFile.is_open() )
        return;

    m_logFile.open( logFilename.c_str() );
    m_noLogging = m_logFile.fail();

    if( NULL != clock )
    {
        m_clock = clock;
        m_clock->Start();
    }
}

void Logger::Write( LogLevel level, const char* format, ... )
{
    va_list args;
    va_start( args, format );
    Write( level, format, args );
    va_end( args );
}

void Logger::Write( const char* format, ... )
{
    va_list args;
    va_start( args, format );
    Write( LogNone, format, args );
    va_end( args );
}

void Logger::Write( LogLevel level, const char* format, va_list args )
{
    Vajra::Threads::MutexLock lock(m_mutex);

    if( !m_noLogging )
    {
        if( NULL != m_buffer )
        {
            delete [] m_buffer;
            m_buffer = NULL;
        }

        m_buffer = new char[ 1024 ];
        vsprintf( m_buffer, format, args );

        if( NULL != m_clock )
        {
            std::string time = m_clock->GetTime().ToString();
            m_logFile << time.c_str() << " >>> ";
        }

        switch( level )
        {
        case LogNone:
            m_logFile << "             " << m_buffer << std::endl;
            break;

        case LogInformation:
            m_logFile << "Information: " << m_buffer << std::endl;
            break;

        case LogWarning:
            m_logFile << "Warning:     " << m_buffer << std::endl;
            break;

        case LogError:
            m_logFile << "Error:       " << m_buffer << std::endl;
            break;

        case LogCritical:
            m_logFile << "CRITICAL:    " << m_buffer << std::endl;
            break;
        }

        delete [] m_buffer;
        m_buffer = NULL;
    }
}
