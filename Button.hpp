#pragma once

#ifndef _VAJRA_VERSION_2_BUTTON_HPP_
#define _VAJRA_VERSION_2_BUTTON_HPP_

#include "Widget.hpp"
#include "Texture.hpp"

namespace Vajra
{
    namespace UI
    {
        class Button : public Widget
        {
			friend class Vajra::UI::UIManager;

        public:
            virtual ~Button(void);

			static std::string Type(void) { return "Button"; }

            virtual std::string GetType(void) const { return Type(); }

            virtual UIState GetCurrentState(void) const { return m_state; }

            virtual void SetIdleState(void) { m_state = Vajra::UI::UI_Idle; }
            virtual void SetEnabledState(void) { m_state = Vajra::UI::UI_Enabled; }
            virtual void SetActiveState(void) { m_state = Vajra::UI::UI_Active; }
            virtual void SetInactiveState(void) { m_state = Vajra::UI::UI_Inactive; }
            virtual void SetDisabledState(void) { m_state = Vajra::UI::UI_Disabled; }

            virtual void Update( float delta );
            virtual void Render( float delta );

            virtual bool HandleInput(void);

            void SetIdleTexture( Vajra::Graphics::Texture* texture );
            void SetActiveTexture( Vajra::Graphics::Texture* texture );
            void SetInactiveTexture( Vajra::Graphics::Texture* texture );

		protected:
            Button( const std::string& name );

			virtual void SetProperty( const std::string& propertyName, const std::string& propertyValue );

        protected:
            Vajra::Graphics::Texture* m_idleTexture;
            Vajra::Graphics::Texture* m_enabledTexture;
            Vajra::Graphics::Texture* m_activeTexture;
            Vajra::Graphics::Texture* m_inactiveTexture;
            Vajra::Graphics::Texture* m_disabledTexture;

            float m_rotation;
        };
    }
}

#endif //_VAJRA_VERSION_2_BUTTON_HPP_
