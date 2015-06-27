#include "pch.hpp"
#include "Panel.hpp"
using Vajra::UI::Panel;
using Vajra::UI::Widget;

Panel::Panel( const std::string& name )
: Widget( name )
{
}

Panel::~Panel(void)
{
}

void Panel::AddWidget( const std::string& name )
{
	m_widgets.insert(std::make_pair< std::string, Widget* >(std::string(name.c_str()), Vajra::UI::UIManager::GetInstance().GetWidgetByName(name)));
}

///
/// Nothing to update except children
///
void Panel::Update( float delta )
{
    std::map< std::string, Widget* >::iterator itr = m_widgets.begin();
    while( itr != m_widgets.end() )
    {
        Widget* widget = itr->second;
        widget->Update( delta );

        ++itr;
    }
}

///
/// Panels do not render... they only render child items if there are any
///
void Panel::Render( float delta )
{
    std::map< std::string, Widget* >::iterator itr = m_widgets.begin();
    while( itr != m_widgets.end() )
    {
        Widget* widget = itr->second;
        widget->Render( delta );

        ++itr;
    }
}

///
/// Panels never handle input
///
bool Panel::HandleInput(void)
{
    return false;
}

void Panel::SetProperty( const std::string& propertyName, const std::string& propertyValue )
{
}
