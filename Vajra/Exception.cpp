#include "pch.hpp"
#include "Exception.hpp"
using Vajra::Core::VajraException;

#include <cstdarg>
#include <sstream>

VajraException::VajraException( const std::string& message )
: std::exception( message.c_str() )
, m_location( "" )
, m_message( message )
, m_combinedMessage( m_location )
{
    m_combinedMessage += m_message;
}

VajraException::VajraException( const std::string& location, const std::string& message )
: std::exception( message.c_str() )
, m_location( location )
, m_message( message )
, m_combinedMessage( m_location )
{
    m_combinedMessage += m_message;
}

VajraException::~VajraException(void)
{
    m_location.clear();
    std::string().swap( m_location );
    m_message.clear();
    std::string().swap( m_message );
    m_combinedMessage.clear();
    std::string().swap( m_combinedMessage );
}

const std::string& VajraException::Message(void) const
{
    return m_message;
}

const std::string& VajraException::Location(void) const
{
    return m_location;
}

const char* VajraException::what(void) const
{
    return m_combinedMessage.c_str();
}
