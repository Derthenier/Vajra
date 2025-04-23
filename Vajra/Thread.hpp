#pragma once

#ifndef _VAJRA_VERSION_2_THREAD_HPP_
#define _VAJRA_VERSION_2_THREAD_HPP_

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

namespace Vajra
{
    namespace Threads
    {
        class Thread
        {
        public:
            Thread(void);
            ~Thread(void);

        private:
            boost::mutex m_mutex;
        };
    }
}

#endif //_VAJRA_VERSION_2_THREAD_HPP_
