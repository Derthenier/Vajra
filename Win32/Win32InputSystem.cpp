#include "pch.hpp"
#include "../Definitions.hpp"
#include "Win32InputSystem.hpp"
using Vajra::Input::Win32::Win32InputSystem;

#include "Win32/Win32Application.hpp"
using Vajra::Core::ApplicationManager;
using Vajra::Core::Win32::Win32Application;

Win32InputSystem::Win32InputSystem(void)
	: m_input( NULL )
{
}

Win32InputSystem::~Win32InputSystem(void)
{
}

const IDirectInput8* Win32InputSystem::GetInput(void) const
{
	return m_input;
}

void Win32InputSystem::Initialize(void)
{
	Win32Application& app = static_cast< Win32Application& >( Vajra::Core::ApplicationManager::GetApplication() );
	HRESULT result = DirectInput8Create(app.GetAppInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_input, NULL);
	if(FAILED(result))
	{
		return;
	}

	InputManager::GetInputDevice(InputDevice::ID_KEYBOARD).Initialize();
	InputManager::GetInputDevice(InputDevice::ID_MOUSE).Initialize();
	InputManager::GetInputDevice(InputDevice::ID_JOYSTICK).Initialize();
}

void Win32InputSystem::Update( float delta )
{
	InputManager::GetInputDevice(InputDevice::ID_KEYBOARD).Update( delta );
	InputManager::GetInputDevice(InputDevice::ID_MOUSE).Update( delta );
	InputManager::GetInputDevice(InputDevice::ID_JOYSTICK).Update( delta );

	std::vector<int> keysPressed = InputManager::GetInputDevice(InputDevice::ID_KEYBOARD).GetPressedKeys();
	for (int i = 0; i < keysPressed.size(); i++)
	{
		Vajra::Input::InputSystem::Callback callback = KeyDownCallback(keysPressed[i]);
		if (callback != NULL)
		{
			callback();
		}
	}

	std::vector<int> buttonsPressed = InputManager::GetInputDevice(InputDevice::ID_MOUSE).GetPressedKeys();
	for (int i = 0; i < buttonsPressed.size(); i++)
	{
		Vajra::Input::InputSystem::Callback callback = ButtonDownCallback(buttonsPressed[i]);
		if (callback != NULL)
		{
			callback();
		}
	}
}

void Win32InputSystem::RegisterKeyDownCallback( unsigned int key, Callback KeyDownCallback )
{
	if( m_keyDownCallbacks.find( key ) == m_keyDownCallbacks.end() && KeyDownCallback != NULL )
		m_keyDownCallbacks.insert( std::make_pair( key, KeyDownCallback ) );
}

void Win32InputSystem::RegisterKeyUpCallback( unsigned int key, Callback KeyUpCallback )
{
	if( m_keyUpCallbacks.find( key ) == m_keyUpCallbacks.end() && KeyUpCallback != NULL )
		m_keyUpCallbacks.insert( std::make_pair( key, KeyUpCallback ) );
}

void Win32InputSystem::RegisterKeyHeldCallback( unsigned int key, Callback KeyHeldCallback )
{
	if( m_keyHeldCallbacks.find( key ) == m_keyHeldCallbacks.end() && KeyHeldCallback != NULL )
		m_keyHeldCallbacks.insert( std::make_pair( key, KeyHeldCallback ) );
}

void Win32InputSystem::RegisterButtonDownCallback( unsigned int button, Callback ButtonDownCallback )
{
	if( m_buttonDownCallbacks.find( button ) == m_buttonDownCallbacks.end() && ButtonDownCallback != NULL )
		m_buttonDownCallbacks.insert( std::make_pair( button, ButtonDownCallback ) );
}

void Win32InputSystem::RegisterButtonUpCallback( unsigned int button, Callback ButtonUpCallback )
{
	if( m_buttonUpCallbacks.find( button ) == m_buttonUpCallbacks.end() && ButtonUpCallback != NULL )
		m_buttonUpCallbacks.insert( std::make_pair( button, ButtonUpCallback ) );
}

void Win32InputSystem::RegisterButtonHeldCallback( unsigned int button, Callback ButtonHeldCallback )
{
	if( m_buttonHeldCallbacks.find( button ) == m_buttonHeldCallbacks.end() && ButtonHeldCallback != NULL )
		m_buttonHeldCallbacks.insert( std::make_pair( button, ButtonHeldCallback ) );
}

Vajra::Input::InputSystem::Callback Win32InputSystem::KeyDownCallback( unsigned int key )
{
	if( m_keyDownCallbacks.find( key ) != m_keyDownCallbacks.end() )
		return m_keyDownCallbacks[ key ];
	return NULL;
}
	
Vajra::Input::InputSystem::Callback Win32InputSystem::KeyUpCallback( unsigned int key )
{
	if( m_keyUpCallbacks.find( key ) != m_keyUpCallbacks.end() )
		return m_keyUpCallbacks[ key ];
	return NULL;
}

Vajra::Input::InputSystem::Callback Win32InputSystem::ButtonDownCallback( unsigned int button )
{
	if( m_buttonDownCallbacks.find( button ) != m_buttonDownCallbacks.end() )
		return m_buttonDownCallbacks[ button ];
	return NULL;
}

Vajra::Input::InputSystem::Callback Win32InputSystem::ButtonUpCallback( unsigned int button )
{
	if( m_buttonUpCallbacks.find( button ) != m_buttonUpCallbacks.end() )
		return m_buttonUpCallbacks[ button ];
	return NULL;
}

