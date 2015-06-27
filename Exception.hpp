#pragma once

#ifndef _VAJRA_VERSION_2_VAJRAEXCEPTION_HPP_
#define _VAJRA_VERSION_2_VAJRAEXCEPTION_HPP_

#include <exception>
#include <string>

namespace Vajra
{
    namespace Core
    {
        class VajraException : public std::exception
        {
        public:
            VajraException( const std::string& message );
            VajraException( const std::string& location, const std::string& message );
            virtual ~VajraException(void) throw();

            const std::string& Message(void) const;
            const std::string& Location(void) const;

            virtual const char* what(void) const;

        private:
            std::string m_location;
            std::string m_message;
            std::string m_combinedMessage;
        };
    }
}

#endif //_VAJRA_VERSION_2_VAJRAEXCEPTION_HPP_
