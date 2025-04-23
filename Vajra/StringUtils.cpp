#include "StringUtils.hpp"
#include <sstream>
using Vajra::Core::StringBuffer;
using Vajra::Core::StringUtils;

StringBuffer::StringBuffer( const char* str /* = NULL */)
{
	if( str != NULL )
	{
		std::string buffer( str );
		std::string::iterator itr = buffer.begin();
		std::string::iterator end = buffer.end();
		while( itr != end )
		{
			m_buffer.push_back( *itr );
			itr++;
		}
		buffer.clear();
	}
}

StringBuffer& StringBuffer::append( const char* str )
{
	if( str == NULL )
	{
		return *this;
	}

	std::string buffer( str );
	std::string::iterator itr = buffer.begin();
	while( itr != buffer.end() )
	{
		m_buffer.push_back( *itr );
		itr ++;
	}
	return *this;
}


