#include "pch.hpp"
#include "Definitions.hpp"
#include "UIManager.hpp"
using Vajra::UI::UIManager;

#include "Panel.hpp"
#include "Button.hpp"
#include "pugixml\pugixml.hpp"

namespace Vajra
{
	namespace UI
	{
		const std::string BUTTON("button");
		const std::string PANEL("panel");
	}
}

const std::string UIManager::VERSION("1.0");

UIManager::UIManager(void)
	: m_ready( false )
{
}

UIManager::~UIManager(void)
{
}

void UIManager::Initialize(void)
{
}

void UIManager::Shutdown(void)
{
}

void UIManager::Load( const std::string& loadFile )
{
	pugi::xml_document document;
	pugi::xml_parse_result result = document.load_file(loadFile.c_str());
	if( !result )
	{
		Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, "Cannot load UI Widgets from file '%s'.\n\tError: %s.", loadFile.c_str(), result.description() );
		return;
	}

	pugi::xml_node root = document.child("Widgets");
	pugi::xml_attribute ver = root.attribute("version");
	if( !ver.empty() && std::strcmp(VERSION.c_str(), ver.as_string()) != 0 )
	{
		Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, "Wrong version of '%s'. Expected '%s' and found '%s'.", loadFile.c_str(), VERSION.c_str(), ver.as_string() );
		return;
	}

	struct __Property
	{
		std::string type;
		std::string value;
	};

	std::string name;
	std::string text;
	WidgetType typeOfWidget;
	for( pugi::xml_node widget = root.child( "Widget" ); widget; widget = widget.next_sibling( "Widget" ) )
	{
		pugi::xml_attribute attr = widget.attribute( "type" );
		if( std::strcmp( attr.as_string(), BUTTON.c_str() ) == 0 )
		{
			typeOfWidget = WT_Button;
		}
		else if( std::strcmp( attr.as_string(), PANEL.c_str() ) == 0 )
		{
			typeOfWidget = WT_Panel;
		}
		else
		{
			Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, "Wrong widget type." );
			continue;
		}

		name = widget.attribute( "name" ).as_string();
		text = widget.attribute( "text" ).as_string();

		Vajra::UI::Widget* w = Create( name, typeOfWidget );

		for( pugi::xml_node property = widget.child( "Property" ); property; property = property.next_sibling( "Property" ) )
		{
			std::string type = property.attribute( "type" ).as_string();
			std::string value = property.attribute( "value" ).as_string();

			if( type.empty() )
			{
				continue;
			}

			w->SetProperty( type, value );
		}

		m_widgets.insert( std::make_pair( name, w ) );
	}

	m_ready = true;
}

Vajra::UI::Widget* UIManager::Create( const std::string& name, Vajra::UI::WidgetType type )
{
    switch( type )
    {
    case Vajra::UI::WT_Panel:
        return new Vajra::UI::Panel( name );
        break;

	case Vajra::UI::WT_Button:
		return new Vajra::UI::Button(name);

    default:
        break;
    }

	return NULL;
}

Vajra::UI::Widget* UIManager::GetWidgetByName( const std::string& name )
{
    std::map< std::string, Vajra::UI::Widget* >::iterator itr = m_widgets.find( name );
    if( itr == m_widgets.end() )
        return NULL;

    return m_widgets[ name ];
}

std::vector< Vajra::UI::Widget* >& UIManager::GetWidgetsByType( std::vector< Vajra::UI::Widget* >& widgets, Vajra::UI::WidgetType type )
{
    std::string widgetType;
    switch( type )
    {
    case Vajra::UI::WT_Panel:
        widgetType = Vajra::UI::Panel::Type();
        break;

	case Vajra::UI::WT_Button:
		widgetType = Vajra::UI::Button::Type();
		break;
    }

    std::map< std::string, Vajra::UI::Widget* >::iterator itr = m_widgets.begin();
    while( itr != m_widgets.end() )
    {
        Vajra::UI::Widget* widget = itr->second;

        if( widget != NULL && strcmp( widget->GetType().c_str(), widgetType.c_str() ) == 0 )
                widgets.push_back( widget );

        ++itr;
    }

    return widgets;
}
