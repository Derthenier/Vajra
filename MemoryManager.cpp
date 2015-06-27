#include "pch.hpp"
#include "MemoryManager.hpp"
using Vajra::Core::MemoryManager;

#include <cstdlib>
#include <new>

MemoryManager g_memoryManager;

MemoryManager::MemoryManager(void)
: m_totalSizeAllocated( 0 )
{
}

MemoryManager::~MemoryManager(void)
{
}

void* MemoryManager::Allocate( unsigned int size )
{
    void* base = malloc( size );
    if( NULL != base )
        m_totalSizeAllocated += size;
    return base;
}

void MemoryManager::Free( void* memory )
{
    ::free( memory );
}



void* operator new ( unsigned int size )
{
    return g_memoryManager.Allocate( size );
}

void operator delete( void* memory )
{
	if( NULL == memory )
		return;
    g_memoryManager.Free( memory );
}
