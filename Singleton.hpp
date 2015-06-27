#pragma once

#ifndef _VAJRA_VERSION_2_SINGLETON_HPP_
#define _VAJRA_VERSION_2_SINGLETON_HPP_

#include <boost/noncopyable.hpp>
#include <boost/thread/once.hpp>
#include <boost/scoped_ptr.hpp>
#include <string>

namespace Vajra
{
    namespace Core
    {
        #pragma region Singleton< Data >

        template< class Data >
        class Singleton : private boost::noncopyable
        {
        public:
            static Data& GetInstance(void)
            {
                boost::call_once( Create, flag );
                return *__instance;
            }

        protected:
            static void Create(void)
            {
                __instance.reset( new Data() );
            }

            Singleton(void) { }
            Singleton( const Singleton& instance ) { }
            virtual ~Singleton(void) { }
            Singleton& operator = ( const Singleton& instance ) { return *this; }

        private:
            static boost::scoped_ptr< Data > __instance;
            static boost::once_flag flag;
        };

        template< class Data >
        boost::scoped_ptr< Data > Singleton<Data>::__instance( 0 );

        template< class Data >
        boost::once_flag Singleton<Data>::flag = BOOST_ONCE_INIT;

        #pragma endregion
    }
}

#endif //_VAJRA_VERSION_2_SINGLETON_HPP_
