#include "pch.hpp"
#include "Definitions.hpp"
#include "GameScreen.hpp"
using Vajra::UI::GameScreen;

#include "Object.hpp"
using Vajra::Graphics::Object;

#include <algorithm>

namespace GameScreenUIFunctors
{
    class UpdateFunctor
    {
    public:
        UpdateFunctor( const float& delta = 0.0f ) : m_delta( delta ) { }
        void operator () ( Vajra::UI::Widget* wid ) { if( wid != NULL ) wid->Update( m_delta ); }
        void operator () ( Object* obj ) { if( obj != NULL && obj->IsVisible() ) obj->Update( m_delta ); }
        void operator () ( std::pair< std::string, GameScreen* > pair ) { if( pair.second != NULL && pair.second->IsVisible() ) pair.second->Update( m_delta ); }
    private:
        float m_delta;
    };

    class RenderFunctor
    {
    public:
        RenderFunctor( const float& delta = 0.0f ) : m_delta( delta ) { }
        void operator () ( Vajra::UI::Widget* wid ) { if( wid != NULL ) wid->Render( m_delta ); }
        void operator () ( Object* obj ) { if( obj != NULL && obj->IsVisible() ) obj->Render( m_delta ); }
        void operator () ( std::pair< std::string, GameScreen* > pair ) { if( pair.second != NULL && pair.second->IsVisible() ) pair.second->Render( m_delta ); }
    private:
        float m_delta;
    };

	class InputHandlerFunctor
	{
	public:
		InputHandlerFunctor( const float& delta = 0.0f ) : m_delta( delta ) { }
		void operator () ( Vajra::UI::Widget* wid ) { if( wid != NULL ) wid->HandleInput(); }
		void operator () ( Object* obj ) { }
		void operator () ( std::pair< std::string, GameScreen* > pair ) { }
	private:
		float m_delta;
	};
}

GameScreen::GameScreen(void)
: m_visible( false )
{
}

GameScreen::~GameScreen(void)
{
    DeleteAllSecond( m_children );
}

void GameScreen::AddGameScreen( const std::string& name, GameScreen* screen )
{
    if( m_children.find( name ) == m_children.end() )
        m_children.insert( std::make_pair( name, screen ) );
}

void GameScreen::RemoveGameScreen( const std::string& name )
{
    std::map< std::string, GameScreen* >::iterator itr = m_children.find( name );
    if( itr != m_children.end() )
        m_children.erase( itr );
}

void GameScreen::AddGameObject( Object* obj )
{
    if( NULL != obj )
        m_objects.push_back( obj );
}

void GameScreen::RemoveGameObject( Object* obj )
{
    if( NULL == obj )
        return;

    std::vector< Object* >::iterator itr = m_objects.begin();
    std::vector< Object* >::iterator end = m_objects.end();
    while( itr != end )
    {
        if( (*itr) == obj )
        {
            m_objects.erase( itr );
            break;
        }

        ++itr;
    }
}

void GameScreen::AddUIElement( Vajra::UI::Widget* widget )
{
    if( NULL != widget )
	{
        m_uiElements.push_back( widget );
	}
	else
	{
		Vajra::Core::Logger::GetInstance().Write(Vajra::Core::LogInformation, "Trying to add ui element that is null.");
	}
}

void GameScreen::RemoveUIElement( Vajra::UI::Widget* widget )
{
    if( NULL == widget )
        return;

    std::vector< Vajra::UI::Widget* >::iterator itr = m_uiElements.begin();
    std::vector< Vajra::UI::Widget* >::iterator end = m_uiElements.end();
    while( itr != end )
    {
        if( (*itr) == widget )
        {
            m_uiElements.erase( itr );
            break;
        }

        ++itr;
    }
}

void GameScreen::Update( float delta )
{
    GameScreenUIFunctors::UpdateFunctor function( delta );

    for_each( m_children.begin(), m_children.end(), function );
    for_each( m_objects.begin(), m_objects.end(), function );
    for_each( m_uiElements.begin(), m_uiElements.end(), function );

	GameScreenUIFunctors::InputHandlerFunctor inputFn( delta );
	for_each( m_children.begin(), m_children.end(), inputFn );
	for_each( m_objects.begin(), m_objects.end(), inputFn );
	for_each( m_uiElements.begin(), m_uiElements.end(), inputFn );
}

void GameScreen::Render( float delta )
{
    GameScreenUIFunctors::RenderFunctor function( delta );

    for_each( m_children.begin(), m_children.end(), function );
    for_each( m_objects.begin(), m_objects.end(), function );
    for_each( m_uiElements.begin(), m_uiElements.end(), function );
}
