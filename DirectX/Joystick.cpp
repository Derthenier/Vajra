#include "pch.hpp"
#include "Joystick.hpp"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

using Vajra::Input::Devices::Joystick;


Joystick::~Joystick(void)
{
}

void Joystick::Initialize()
{

}

void Joystick::Update( float delta )
{

}

void Joystick::Poll(void)
{

}

int* Joystick::GetPressedButtons(void)
{
	return 0;
}

bool Joystick::IsButtonDown( unsigned int button )
{
	return false;
}

bool Joystick::IsButtonUp( unsigned int button )
{
	return false;
}

bool Joystick::IsButtonHeld( unsigned int button )
{
	return false;
}

