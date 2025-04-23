#include "pch.hpp"
#include "Widget.hpp"
using Vajra::UI::Widget;

Widget::Widget( const std::string& name )
: m_name( name )
, m_state( Vajra::UI::UI_Idle )
{
}

Widget::~Widget(void)
{
}

void Widget::SetState( const Vajra::UI::UIState& state )
{
    switch( state )
    {
    case UI_Idle:
        SetIdleState();
        break;

    case UI_Enabled:
        SetEnabledState();
        break;

    case UI_Active:
        SetActiveState();
        break;

    case UI_Inactive:
        SetInactiveState();
        break;

    case UI_Disabled:
        SetDisabledState();
        break;

    default:
        break;
    }
}

void Widget::SetPosition( const Vajra::Math::Vector& position )
{
    m_position = position;
}

const Vajra::Math::Vector& Widget::GetPosition(void) const
{
    return m_position;
}

void Widget::SetSize( const Vajra::Math::Vector& size )
{
    m_size = size;
}

const Vajra::Math::Vector& Widget::GetSize(void) const
{
    return m_size;
}

void Widget::SetScale( const Vajra::Math::Vector& scale )
{
    m_scale = scale;
}

const Vajra::Math::Vector& Widget::GetScale(void) const
{
    return m_scale;
}
