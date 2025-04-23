#include "pch.hpp"
#include "Button.hpp"
using Vajra::UI::Button;
using Vajra::UI::UIState;

#include "Renderer.hpp"
using Vajra::Graphics::RenderManager;

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <map>

namespace Vajra
{
	namespace UI
	{
		std::map< std::string, std::string > GetMappedValues( const std::vector< std::string >& values )
		{
			std::map< std::string, std::string > mapValues;
			for( std::vector< std::string >::const_iterator citr = values.begin(); citr != values.end(); citr++ )
			{
				std::string str = *citr;
				std::string::size_type pos = str.find( '=' );
				std::string key = str.substr( 0, pos );
				std::string val = str.substr( pos + 1 );
				mapValues.insert( std::make_pair( key, val) );
			}
			return mapValues;
		}

		template< class T >
		T GetMappedValue(const std::string& varName, const T& defaultValue) {
			try
			{
				return boost::lexical_cast< T, std::string >(varName);
			}
			catch (boost::bad_lexical_cast& ble)
			{
				Vajra::Core::Logger::GetInstance().Write(Vajra::Core::LogError, "%s for %s", ble.what(), varName);
			}
			return defaultValue;
		}

		Vajra::Math::Vector GetValue(const std::vector< std::string >& values)
		{
			float zero = 0.0;
			std::string float_zero = "0.0";
			std::map< std::string, std::string > mappedValues = GetMappedValues(values);

			if (mappedValues["x"].empty())
			{
				mappedValues["x"] = float_zero;
			}

			if (mappedValues["y"].empty())
			{
				mappedValues["y"] = float_zero;
			}

			if (mappedValues["z"].empty())
			{
				mappedValues["z"] = float_zero;
			}

			float x = GetMappedValue<float>(mappedValues["x"], zero);
			float y = GetMappedValue<float>(mappedValues["y"], zero);
			float z = GetMappedValue<float>(mappedValues["z"], zero);

			return Vajra::Math::Vector(x, y, z);
		}
	}
}

Button::Button( const std::string& name )
: Widget( name )
, m_idleTexture( NULL )
, m_enabledTexture( NULL )
, m_activeTexture( NULL )
, m_inactiveTexture( NULL )
, m_disabledTexture( NULL )
, m_rotation( 0.f )
{
}

Button::~Button(void)
{
}

void Button::Update( float delta )
{
    switch( m_state )
    {
    case UI_Idle:
        break;

    case UI_Enabled:
        break;

    case UI_Active:
        break;

    case UI_Inactive:
        break;

    case UI_Disabled:
        break;

    default:
        break;
    }
}

void Button::Render( float delta )
{
    Vajra::Graphics::Texture* texture = NULL;
    switch( m_state )
    {
    case UI_Idle:
        texture = m_idleTexture;
        break;

    case UI_Enabled:
        texture = m_enabledTexture;
        break;

    case UI_Active:
        texture = m_activeTexture;
        break;

    case UI_Inactive:
        texture = m_inactiveTexture;
        break;

    case UI_Disabled:
        texture = m_disabledTexture;
        break;
    }

    Vajra::Graphics::RenderManager::GetRenderer().DrawTexturedRectangle( texture, m_position, m_position + m_size, m_scale, m_rotation );
}

bool Button::HandleInput(void)
{
    return false;
}

void Button::SetIdleTexture( Vajra::Graphics::Texture* texture )
{
    m_idleTexture = texture;
}

void Button::SetActiveTexture( Vajra::Graphics::Texture* texture )
{
    m_enabledTexture = texture;
    m_activeTexture = texture;
}

void Button::SetInactiveTexture( Vajra::Graphics::Texture* texture )
{
    m_inactiveTexture = texture;
    m_disabledTexture = texture;
}

void Button::SetProperty( const std::string& propertyName, const std::string& propertyValue )
{
	if( propertyName.empty() )
	{
		Vajra::Core::Logger::GetInstance().Write(Vajra::Core::LogInformation, "Property name is empty and property value is '%s'.", propertyValue.c_str());
		return;
	}

	float zero = 0.0f;
	std::string float_zero = std::string("0.0");

	std::vector< std::string > strings;
	strings = boost::split( strings, propertyValue, boost::is_any_of( ";") );

	if( propertyName.compare( "position" ) == 0 )
	{
		if( strings.size() != 2 )
		{
			Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogInformation, "Position for button '%s' is invalid. Need to provide x, y, and z values as value=\"x=a;y=b;z=c\". Setting unsupplied values to 0.", m_name.c_str() );
		}

		Vajra::Math::Vector pos = GetValue(strings);
		SetPosition( pos );
		Vajra::Core::Logger::GetInstance().Write(Vajra::Core::LogInformation, "Setting button %s's position to (%.2f, %.2f, %.2f)", m_name.c_str(), pos.X(), pos.Y(), pos.Z());
	}
	else if( propertyName.compare( "state" ) == 0 )
	{
		if( strings.size() != 1 )
		{
			Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogInformation, "State for button '%s' is invalid. Need to provide value as value=\"<state>\". Setting state to idle.", m_name.c_str() );
			if( strings.empty() )
			{
				strings.push_back( "idle" );
			}
		}

		if( strings[0].compare( "idle" ) == 0 )
		{
			SetState( UI_Idle );
		}
		else if( strings[0].compare( "active" ) == 0 )
		{
			SetState( UI_Active );
		}
		else if( strings[0].compare( "inactive" ) == 0 )
		{
			SetState( UI_Inactive );
		}
		else if( strings[0].compare( "enabled" ) == 0 )
		{
			SetState( UI_Enabled );
		}
		else if( strings[0].compare( "disabled" ) == 0 )
		{
			SetState( UI_Disabled );
		}
		else
		{
			Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogInformation, "Invalid state '%s' provided for button '%s'.", strings[0].c_str(), m_name.c_str() );
		}
	}
	else if( propertyName.compare( "size" ) == 0 )
	{
		if( strings.size() != 2 )
		{
			Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogInformation, "Size for button '%s' is invalid. Need to provide x, y, and z values as value=\"x=a;y=b;z=c\". Setting unsupplied values to 0.", m_name.c_str() );
		}

		Vajra::Math::Vector size = GetValue(strings);
		SetSize( size );
		Vajra::Core::Logger::GetInstance().Write(Vajra::Core::LogInformation, "Setting button %s's size to (%.2f, %.2f, %.2f)", m_name.c_str(), size.X(), size.Y(), size.Z());
	}
	else if( propertyName.compare( "scale" ) == 0 )
	{
		if( strings.size() != 2 )
		{
			Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogInformation, "Scale for button '%s' is invalid. Need to provide x, y, and z values as value=\"x=a;y=b;z=c\". Setting unsupplied values to 0.", m_name.c_str() );
		}

		Vajra::Math::Vector scale = GetValue(strings);
		SetScale( scale );
		Vajra::Core::Logger::GetInstance().Write(Vajra::Core::LogInformation, "Setting button %s's scale to (%.2f, %.2f, %.2f)", m_name.c_str(), scale.X(), scale.Y(), scale.Z());
	}
	else if( propertyName.compare( "texture" ) == 0 )
	{
		if( strings.size() != 3 )
		{
			Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogInformation, "Textures for button '%s' are invalid. Need to provide value as value=\"idle=<texture>;active=<texture>;inactive=<texture>\". Setting textures to empty.", m_name.c_str() );
			return;
		}

		std::map< std::string, std::string > mappedValues = GetMappedValues( strings );

		if( !mappedValues["idle"].empty() )
		{
			Vajra::Graphics::Texture* idleTexture = Vajra::Core::ResourceManager::GetInstance().Load< Vajra::Graphics::Texture >( mappedValues["idle"] );
			SetIdleTexture( idleTexture );
		}
		else if( !mappedValues["active"].empty() )
		{
			Vajra::Graphics::Texture* activeTexture = Vajra::Core::ResourceManager::GetInstance().Load< Vajra::Graphics::Texture >( mappedValues["active"] );
			SetActiveTexture( activeTexture );
		}
		else if( !mappedValues["inactive"].empty() )
		{
			Vajra::Graphics::Texture* inactiveTexture = Vajra::Core::ResourceManager::GetInstance().Load< Vajra::Graphics::Texture >( mappedValues["inactive"] );
			SetInactiveTexture( inactiveTexture );
		}
	}
	else
	{
		Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, "Wrong property ('%s') for %s.", propertyName.c_str(), m_name.c_str() );
	}
}
