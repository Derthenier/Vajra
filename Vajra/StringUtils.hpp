#pragma once

#ifndef _VAJRA_VERSION_2_STRINGUTILS_HPP_
#define _VAJRA_VERSION_2_STRINGUTILS_HPP_

#include <string>
#include <vector>

namespace Vajra
{
	namespace Core
	{
		class StringBuffer
		{
		public:
			StringBuffer(const char* str = NULL);

			StringBuffer& append(const char* str);
			std::string toString() const;
		private:
			std::vector<char> m_buffer;
		};

		class StringUtils
		{
		public:

			template< class T >
			static std::string toString( const T& value )
			{
				ostringstream ostr;
				ostr << value;
				return ostr.str();
			}

			template< class T >
			static T fromString( const std::string& value )
			{
				istringstream istr;
				T result;
				return (istr >> result) ? result : (T)0;
			}

			template< class T >
			static std::string combine( const T& list )
			{
				StringBuffer sb;
				T::const_iterator itr = list.begin();
				T::const_iterator end = list.end();
				while(itr != end)
				{
					sb.append(itr->c_str());
					itr++;
				}

				return sb.toString();
			}

		private:
			StringUtils(void) {}
			virtual ~StringUtils(void) {}
		};
	}
}

#endif // _VAJRA_VERSION_2_STRINGUTILS_HPP_
