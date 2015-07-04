#pragma once

#ifndef _VAJRA_VERSION_2_TEXT_HPP_
#define _VAJRA_VERSION_2_TEXT_HPP_

#include "Widget.hpp"
#include "Texture.hpp"

namespace Vajra
{
	namespace UI
	{
		class Text : public Widget
		{
			friend class Vajra::UI::UIManager;
		public:
			virtual ~Text(void);

			static std::string Type(void) { return "Text"; }

			virtual std::string GetType(void) const { return Type(); }

			virtual void AddWidget(const std::string& name) { };

			virtual UIState GetCurrentState(void) const { return m_state; }

			virtual void SetIdleState(void) { m_state = Vajra::UI::UI_Idle; }
			virtual void SetEnabledState(void) { m_state = Vajra::UI::UI_Enabled; }
			virtual void SetActiveState(void) { m_state = Vajra::UI::UI_Active; }
			virtual void SetInactiveState(void) { m_state = Vajra::UI::UI_Inactive; }
			virtual void SetDisabledState(void) { m_state = Vajra::UI::UI_Disabled; }

			virtual void Update(float delta);
			virtual void Render(float delta);

			virtual bool HandleInput(void) { }

		protected:
			Text(const std::string& name);

			virtual void SetProperty(const std::string& propertyName, const std::string& propertyValue);

		private:
			std::string text;
		};
	}
}

#endif //_VAJRA_VERSION_2_TEXT_HPP_
