#pragma once

#ifndef _VAJRA_VERSION_2_UIMANAGER_HPP_
#define _VAJRA_VERSION_2_UIMANAGER_HPP_

#include "Singleton.hpp"
#include <string>
#include <map>
#include <vector>

#include "Widget.hpp"

namespace Vajra
{
    namespace UI
    {
        enum WidgetType
        {
            WT_Panel = 0,
			WT_Button = 1,
			WT_Text = 2,

			WT_MAX_WIDGET_TYPES
        };

        class UIManager : public Vajra::Core::Singleton< UIManager >
        {
            friend class Vajra::Core::Singleton< UIManager >;

        public:
            virtual ~UIManager(void);

            void Initialize(void);
            void Shutdown(void);

			void Load( const std::string& loadFile );

            Vajra::UI::Widget* GetWidgetByName( const std::string& name );
            std::vector< Vajra::UI::Widget* >& GetWidgetsByType( std::vector< Vajra::UI::Widget* >& widgets, Vajra::UI::WidgetType type );

        private:
            UIManager(void);
            UIManager( const UIManager& ui ) { }
            UIManager& operator = ( const UIManager& ui ) { }

            Vajra::UI::Widget* Create( const std::string& name, WidgetType type );

        private:
            std::map< std::string, Vajra::UI::Widget* > m_widgets;
			bool m_ready;

			static const std::string VERSION;
        };
    }
}

#endif //_VAJRA_VERSION_2_UIMANAGER_HPP_
