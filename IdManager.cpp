#include "pch.hpp"
#include "IdManager.hpp"
using Vajra::Core::IdManager;

std::map< std::string, std::string > IdManager::s_ids;

IdManager::IdManager(void)
{
}

IdManager::~IdManager(void)
{
}

std::string IdManager::CreateId( const std::string& name )
{
    //return boost::uuids::uuid::create( s_generator.operator ()(), name.c_str(), static_cast< int >( name.length() ) ).to_string();
	boost::uuids::uuid one = boost::uuids::random_generator()();
	return std::string( ( const char* )( one.data ) );
}

const std::string& IdManager::GetId( const std::string& name )
{
    if( s_ids.find( name ) == s_ids.end() )
        s_ids.insert( std::make_pair( name, CreateId( name ) ) );
    return s_ids[ name ];
}
