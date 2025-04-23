#include "pch.hpp"
#include "Mutex.hpp"
using Vajra::Threads::MutexLock;
using Vajra::Threads::Mutex;

MutexLock::MutexLock(void)
: m_mutex( *( new Mutex() ) )
{
}

MutexLock::MutexLock( const MutexLock& lock )
: m_mutex( lock.m_mutex )
{
}

MutexLock::MutexLock( Mutex& mutex )
: m_mutex( mutex )
{
    m_mutex.lock();
}

MutexLock::MutexLock( Mutex* mutex )
: m_mutex( *mutex )
{
    m_mutex.lock();
}

MutexLock::~MutexLock(void)
{
    m_mutex.unlock();
}
