#pragma once

#ifndef _VAJRA_VERSION_2_WIDGET_HPP_
#define _VAJRA_VERSION_2_WIDGET_HPP_

#include <string>
#include <map>
#include "Vector.hpp"

namespace Vajra
{
    namespace UI
    {
        class UIManager;

        enum UIState
        {
            UI_Idle = 0,
            UI_Enabled = 1,
            UI_Active = 2,
            UI_Inactive = 3,
            UI_Disabled = 4
        };

        class Widget
        {
            friend class Vajra::UI::UIManager;

        public:
            virtual ~Widget(void);

            virtual std::string GetType(void) const = 0;

            virtual UIState GetCurrentState(void) const = 0;

            virtual void SetIdleState(void) = 0;
            virtual void SetEnabledState(void) = 0;
            virtual void SetActiveState(void) = 0;
            virtual void SetInactiveState(void) = 0;
            virtual void SetDisabledState(void) = 0;

            virtual void SetState( const UIState& state );

            virtual void SetPosition( const Vajra::Math::Vector& position );
            virtual const Vajra::Math::Vector& GetPosition(void) const;

            virtual void SetSize( const Vajra::Math::Vector& size );
            virtual const Vajra::Math::Vector& GetSize(void) const;

            virtual void SetScale( const Vajra::Math::Vector& scale );
            virtual const Vajra::Math::Vector& GetScale(void) const;

            virtual void Update( float delta ) = 0;
            virtual void Render( float delta ) = 0;

            virtual bool HandleInput(void) = 0;

        protected:
            Widget( const std::string& name );

			virtual void SetProperty( const std::string& propertyName, const std::string& propertyValue ) = 0;

            std::string m_name;

            Vajra::Math::Vector m_position;
            Vajra::Math::Vector m_size;
            Vajra::Math::Vector m_scale;

            Vajra::UI::UIState m_state;
        };
    }
}

#endif //_VAJRA_VERSION_2_WIDGET_HPP_
