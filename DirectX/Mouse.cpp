#include "pch.hpp"
#include "Mouse.hpp"
using Vajra::Input::Devices::Mouse;

#include "Win32/Win32InputSystem.hpp"
using Vajra::Input::Win32::Win32InputSystem;

#include "Win32/Win32Application.hpp"
using Vajra::Core::ApplicationManager;
using Vajra::Core::Win32::Win32Application;

Mouse::~Mouse(void)
{
}

void Mouse::Initialize()
{
	std::memset((void*)&m_previousState, 0, sizeof(DIMOUSESTATE2));
	std::memset((void*)&m_currentState, 0, sizeof(DIMOUSESTATE2));

	Win32Application& app = static_cast< Win32Application& >( Vajra::Core::ApplicationManager::GetApplication() );
	Win32InputSystem& is = static_cast< Win32InputSystem& >( Vajra::Input::InputManager::GetInput() );
	IDirectInput8* input = const_cast< IDirectInput8* >( is.GetInput() );

	if(input != NULL)
	{
		HRESULT result = input->CreateDevice(GUID_SysMouse, &m_device, NULL);
		if(FAILED(result))
		{
			return;
		}

		result = m_device->SetDataFormat(&c_dfDIMouse);
		if(FAILED(result))
		{
			return;
		}

		result = m_device->SetCooperativeLevel(app.GetAppWindow(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
		if(FAILED(result))
		{
			return;
		}

		result = m_device->Acquire();
		if(FAILED(result))
		{
			return;
		}
	}
}

void Mouse::Update( float delta )
{
	std::memset((void*)&m_previousState, 0, sizeof(m_previousState));
	std::memcpy(&m_previousState, &m_currentState, sizeof(m_currentState));

	HRESULT result = m_device->GetDeviceState(sizeof(m_currentState), (void **)&m_currentState);
	if(FAILED(result))
	{
		if((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_device->Acquire();
		}
	}
}

void Mouse::Poll(void)
{

}

int* Mouse::GetPressedButtons(void)
{
	return 0;
}

bool Mouse::IsButtonDown( unsigned int button )
{
	unsigned char prevResult = m_previousState.rgbButtons[button] & 0x80;
	unsigned char curResult = m_currentState.rgbButtons[button] & 0x80;
	return curResult && !prevResult;
}

bool Mouse::IsButtonUp( unsigned int button )
{
	unsigned char prevResult = m_previousState.rgbButtons[button] & 0x80;
	unsigned char curResult = m_currentState.rgbButtons[button] & 0x80;
	return !curResult && prevResult;
}

bool Mouse::IsButtonHeld( unsigned int button )
{
	unsigned char prevResult = m_previousState.rgbButtons[button] & 0x80;
	unsigned char curResult = m_currentState.rgbButtons[button] & 0x80;
	return curResult && prevResult;
}

