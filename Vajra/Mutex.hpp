#pragma once

#ifndef _VAJRA_VERSION_2_MUTEX_HPP
#define _VAJRA_VERSION_2_MUTEX_HPP

#include <boost/thread/mutex.hpp>

namespace Vajra
{
    namespace Threads
    {
        typedef boost::mutex Mutex;

        class MutexLock
        {
        public:
            MutexLock( Mutex& m );
            MutexLock( Mutex* m );
            ~MutexLock(void);

        private:
            MutexLock(void);
            MutexLock( const MutexLock& lock );
            MutexLock& operator = ( const MutexLock& lock ) { }

        private:
            Mutex& m_mutex;
        };
    }
}

#endif //_VAJRA_VERSION_2_MUTEX_HPP
