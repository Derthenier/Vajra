#pragma once

#ifndef _VAJRA_VERSION_2_GAMESCREEN_HPP_
#define _VAJRA_VERSION_2_GAMESCREEN_HPP_

#include <string>
#include <map>
#include <vector>

#include "Object.hpp"
#include "Widget.hpp"

namespace Vajra
{
    namespace UI
    {
        class GameScreen
        {
        public:
            GameScreen(void);
            virtual ~GameScreen(void);

            virtual void AddGameScreen( const std::string& name, GameScreen* screen );
            virtual void RemoveGameScreen( const std::string& name );

            virtual void AddGameObject( Vajra::Graphics::Object* obj );
            virtual void RemoveGameObject( Vajra::Graphics::Object* obj );

            virtual void AddUIElement( Vajra::UI::Widget* widget );
            virtual void RemoveUIElement( Vajra::UI::Widget* widget );

            virtual void Update( float delta );
            virtual void Render( float delta );

            const bool& IsVisible(void) const { return m_visible; }
            void SetVisibility( const bool& visible ) { m_visible = visible; }
            void MakeVisible(void) { SetVisibility( true ); }
            void MakeInvisible(void) { SetVisibility(false); }

        protected:
            std::map< std::string, GameScreen* > m_children;
            std::vector< Vajra::Graphics::Object* > m_objects;
            std::vector< Vajra::UI::Widget* > m_uiElements;

            bool m_visible;
        };
    }
}

#endif //_VAJRA_VERSION_2_GAMESCREEN_HPP_
