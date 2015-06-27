#pragma once

#ifndef _VAJRA_VERSION_2_MEMORYMANAGER_HPP_
#define _VAJRA_VERSION_2_MEMORYMANAGER_HPP_

namespace Vajra
{
    namespace Core
    {
        class MemoryManager
        {
        public:
            MemoryManager(void);
            virtual ~MemoryManager(void);

            void* Allocate( unsigned int size );
            void Free( void* memory );

            const unsigned int& GetTotalAllocated(void) const { return m_totalSizeAllocated; }

        private:
            unsigned int m_totalSizeAllocated;
        };
    }
}

extern Vajra::Core::MemoryManager g_memoryManager;

extern void* operator new( unsigned int size );
extern void operator delete( void* memory );

#endif //_VAJRA_VERSION_2_MEMORYMANAGER_HPP_
