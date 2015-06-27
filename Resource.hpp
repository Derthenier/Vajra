#pragma once

#ifndef _VAJRA_VERSION_2_RESOURCE_HPP_
#define _VAJRA_VERSION_2_RESOURCE_HPP_

#include <string>
#include <map>

#include "Singleton.hpp"
#include "IdManager.hpp"

namespace Vajra
{
    namespace Core
    {
        class Resource
        {
        public:
            Resource( const std::string& name, const bool& manageMe = true );
            virtual ~Resource(void);

            virtual void Load(void) = 0;

            virtual const std::string& GetResourceName(void) const { return m_name; }
            virtual const std::string& GetResourceId(void) const { return m_id; }

        protected:
            std::string m_id;
            std::string m_name;
        };

        class ResourceManager : public Vajra::Core::Singleton< ResourceManager >
        {
            friend class Vajra::Core::Singleton< ResourceManager >;

        public:
            typedef std::map< std::string, Resource* > ResourceMap;

            virtual ~ResourceManager(void);

            void ManageResource( Resource* res );
            void ReleaseAllResources(void);

            template< class T >
            T* GetResource( const std::string& name );

            template< class T >
            const T* GetResource( const std::string& name ) const;

            template< class T >
            T* Load( const std::string& name );

        private:
            ResourceManager(void) { }
            ResourceManager& operator = ( const ResourceManager& rm ) { }

        private:
            ResourceMap m_resources;
        };

        template< class T >
        T* ResourceManager::GetResource( const std::string& name )
        {
            std::string id = Vajra::Core::IdManager::GetId( name );
            ResourceMap::iterator itr = m_resources.find( id );
            if( itr == m_resources.end() )
                return NULL;
            return dynamic_cast< T* >( itr->second );
        }

        template< class T >
        const T* ResourceManager::GetResource( const std::string& name ) const
        {
            std::string id = Vajra::Core::IdManager::GetId( name );
            ResourceMap::const_iterator itr = m_resources.find( id );
            if( itr == m_resources.end() )
                return NULL;
            return dynamic_cast< const T* >( itr->second );
        }

        template< class T >
        T* ResourceManager::Load( const std::string& name )
        {
            T* res = GetResource< T >( name );
            if( res == NULL )
                res = T::Create( name );
            res->Load();
            return res;
        }
    }
}

#endif //_VAJRA_VERSION_2_RESOURCE_HPP_
