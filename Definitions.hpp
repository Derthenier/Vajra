#pragma once

#ifndef _VAJRA_VERSION_2_DEFINITIONS_HPP_
#define _VAJRA_VERSION_2_DEFINITIONS_HPP_

#ifndef NULL
#define NULL 0
#endif

#ifndef DEFINE_ERROR
#define DEFINE_ERROR(errorMsg) \
        Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogCritical, (errorMsg) ); \
        std::ostringstream buf; \
        buf << __FILE__ << " (" << __LINE__ << ")"; \
        throw Vajra::Core::VajraException( buf.str(), std::string(errorMsg) );
#endif

template< class ITERATOR >
void DeleteSecond( ITERATOR& itr )
{
    if( NULL != itr->second )
    {
        delete itr->second;
        itr->second = NULL;
    }
}

template< class CONTAINER >
void DeleteAllSecond( CONTAINER& c )
{
    CONTAINER::iterator itr = c.begin();
    CONTAINER::iterator end = c.end();
    while( itr != end )
    {
        DeleteSecond( itr );
        ++itr;
    }

    c.erase( c.begin(), c.end() );
    c.clear();
    CONTAINER().swap( c );
}

template< class CONTAINER >
void DeleteSingleContainer( CONTAINER& c )
{
    CONTAINER::iterator itr = c.begin();
    CONTAINER::iterator end = c.end();
    while( itr != end )
    {
        if( NULL != (*itr) )
        {
            delete (*itr);
            (*itr) = NULL;
        }

        ++itr;
    }
}

#endif //_VAJRA_VERSION_2_DEFINITIONS_HPP_
