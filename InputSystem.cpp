#include "pch.hpp"
#include "InputSystem.hpp"
using Vajra::Input::InputSystem;
using Vajra::Input::InputManager;
using Vajra::Input::InputDevice;

std::vector<int> InputDevice::EMPTY;

InputSystem::InputSystem(void)
{
}

InputSystem::~InputSystem(void)
{
}

#if defined( _WIN32 )

#include "Win32/Win32InputSystem.hpp"
#include "DirectX/Keyboard.hpp"
#include "DirectX/Mouse.hpp"
#include "DirectX/Joystick.hpp"
using Vajra::Input::Win32::Win32InputSystem;
using Vajra::Input::Devices::Keyboard;
using Vajra::Input::Devices::Mouse;
using Vajra::Input::Devices::Joystick;

InputSystem& InputManager::GetInput(void)
{
    return ( Win32InputSystem::GetInstance() );
}

Vajra::Input::InputDevice& InputManager::GetInputDevice(InputDevice::InputDevType device)
{
	return ( InputDevice::GetDevice(device) );
}

InputDevice& InputDevice::GetDevice(InputDevice::InputDevType device)
{
	switch(device)
	{
	case ID_KEYBOARD:
		return Keyboard::GetInstance();
		break;
	case ID_MOUSE:
		return Mouse::GetInstance();
		break;
	case ID_JOYSTICK:
		return Joystick::GetInstance();
		break;
	}

	return Keyboard::GetInstance();
}

#elif defined( _MACOS )

#include "Mac/MacInputSystem.hpp"
using Vajra::Input::Mac::MacInputSystem;

InputSystem& InputManager::GetInput(void)
{
    return ( MacInputSystem::GetInstance() );
}

#elif defined( _LINUX )

#include "Linux/LinuxInputSystem.hpp"
using Vajra::Input::Linux::LinuxInputSystem;

InputSystem& InputManager::GetInput(void)
{
    return ( LinuxInputSystem::GetInstance() );
}

#endif // _WIN32, _MACOS, _LINUX
