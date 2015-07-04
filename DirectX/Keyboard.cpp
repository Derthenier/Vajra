#include "pch.hpp"
#include "Keyboard.hpp"
using Vajra::Input::Devices::Keyboard;

#include "Win32/Win32InputSystem.hpp"
using Vajra::Input::Win32::Win32InputSystem;

#include "Win32/Win32Application.hpp"
using Vajra::Core::ApplicationManager;
using Vajra::Core::Win32::Win32Application;

Keyboard::~Keyboard(void)
{
}

void Keyboard::Initialize()
{
	std::memset((void*)&m_previousState, 0, sizeof(m_previousState));
	std::memset((void*)&m_currentState, 0, sizeof(m_currentState));

	Win32Application& app = static_cast< Win32Application& >( Vajra::Core::ApplicationManager::GetApplication() );
	Win32InputSystem& is = static_cast< Win32InputSystem& >( Vajra::Input::InputManager::GetInput() );
	IDirectInput8* input = const_cast< IDirectInput8* >( is.GetInput() );

	if(input != NULL)
	{
		HRESULT result = input->CreateDevice(GUID_SysKeyboard, &m_device, NULL);
		if(FAILED(result))
		{
			DEFINE_ERROR("Failed to create input device keyboard")
			return;
		}

		result = m_device->SetDataFormat(&c_dfDIKeyboard);
		if(FAILED(result))
		{
			DEFINE_ERROR("Failed to set data format keyboard")
			return;
		}

		result = m_device->SetCooperativeLevel(app.GetAppWindow(), DISCL_FOREGROUND | DISCL_EXCLUSIVE);
		if(FAILED(result))
		{
			DEFINE_ERROR("Failed to set cooperative level keyboard")
			return;
		}

		result = m_device->Acquire();
		if(FAILED(result))
		{
			return;
		}
	}
}

void Keyboard::Update( float delta )
{
	std::memset((void*)&m_previousState, 0, sizeof(m_previousState));
	std::memcpy(&m_previousState, &m_currentState, sizeof(m_currentState));

	HRESULT result = m_device->GetDeviceState(sizeof(m_currentState), (void **)&m_currentState);
	if(FAILED(result))
	{
		if((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			result = m_device->Acquire();
			if (FAILED(result))
			{
				Vajra::Core::Logger::GetInstance().Write(Vajra::Core::LogInformation, "Unable to acquire keyboard.");
			}
		}
	}
}

void Keyboard::Poll(void)
{

}

std::vector<int> Keyboard::GetPressedKeys(void)
{
	std::vector<int> keyState;
	for (int i = 0; i < 256; i++)
	{
		if (IsKeyDown(i))
		{
			keyState.push_back(i);
		}
	}
	return keyState;
}

bool Keyboard::IsKeyDown( unsigned int key )
{
	unsigned char prevResult = m_previousState[key] & 0x80;
	unsigned char curResult = m_currentState[key] & 0x80;
	return curResult && !prevResult;
}

bool Keyboard::IsKeyUp( unsigned int key )
{
	unsigned char prevResult = m_previousState[key] & 0x80;
	unsigned char curResult = m_currentState[key] & 0x80;
	return !curResult && prevResult;
}

bool Keyboard::IsKeyHeld( unsigned int key )
{
	unsigned char prevResult = m_previousState[key] & 0x80;
	unsigned char curResult = m_currentState[key] & 0x80;
	return curResult && prevResult;
}
