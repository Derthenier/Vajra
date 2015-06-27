#include "pch.hpp"
#include "Definitions.hpp"
#include "Logger.hpp"

#include "Resource.hpp"
using Vajra::Core::Resource;
using Vajra::Core::ResourceManager;

#include "IdManager.hpp"
using Vajra::Core::IdManager;

Resource::Resource( const std::string& name, const bool& manageMe )
: m_id( IdManager::GetId( name ) )
, m_name( name )
{
	if( manageMe )
		ResourceManager::GetInstance().ManageResource( this );
}

Resource::~Resource(void)
{
}

ResourceManager::~ResourceManager(void)
{
    DeleteAllSecond( m_resources );
}

void ResourceManager::ReleaseAllResources(void)
{
    DeleteAllSecond( m_resources );
}

void ResourceManager::ManageResource( Resource* res )
{
    if( m_resources.find( res->GetResourceId() ) != m_resources.end() )
    {
        Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogWarning, "Updating of resources in the resource map is not authorized." );
        return;
    }

    m_resources.insert( std::make_pair( res->GetResourceId(), res ) );
}
