#include "pch.hpp"
#include "Definitions.hpp"
#include "Object.hpp"
using Vajra::Graphics::Object;

Object::Object( const std::string& id )
: m_id( id )
{
}

Object::~Object(void)
{
    m_id.clear();
    std::string().swap( m_id );
}

const std::string& Object::GetId(void) const
{
    return m_id;
}

const bool& Object::IsVisible(void) const
{
    return m_visible;
}


using Vajra::Graphics::ObjectManager;

ObjectManager::ObjectManager(void)
{
}

ObjectManager::~ObjectManager(void)
{
    DeleteAllSecond( m_gameObjects );
}

/*void ObjectManager::Update( float delta )
{
    std::map< std::string, Object* >::iterator itr = m_updateable.begin();
    std::map< std::string, Object* >::iterator end = m_updateable.end();
    while( itr != end )
    {
        itr->second->Update( delta );

        ++itr;
    }
}*/

void ObjectManager::AddGameObject( Object& obj )
{
    if( m_gameObjects.find( obj.GetId() ) == m_gameObjects.end() )
        m_gameObjects.insert( std::make_pair( obj.GetId(), &obj ) );
}

void ObjectManager::RemoveGameObject( const std::string& objId )
{
    std::map< std::string, Object* >::iterator itr = m_gameObjects.find( objId );
    if( itr != m_gameObjects.end() )
    {
        m_gameObjects.erase( itr );
    }
}

Object* ObjectManager::GetGameObject( const std::string& objId )
{
    std::map< std::string, Object* >::iterator itr = m_gameObjects.begin();
    std::map< std::string, Object* >::iterator end = m_gameObjects.end();
    while( itr != end )
    {
        Object* obj = itr->second;
        if( objId == obj->GetId() )
            return obj;

        ++itr;
    }

    return NULL;
}