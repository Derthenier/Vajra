#pragma once

#ifndef _VAJRA_VERSION_2_INPUTDEVICE_KEYBOARD_HPP_
#define _VAJRA_VERSION_2_INPUTDEVICE_KEYBOARD_HPP_

#include "../InputSystem.hpp"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

namespace Vajra
{
	namespace Input
	{
		namespace Devices
		{
			class Keyboard : public Vajra::Core::Singleton< Keyboard >, public Vajra::Input::InputDevice
			{
				friend class Vajra::Core::Singleton< Keyboard >;
	
			public:
				virtual ~Keyboard(void);

				virtual void Initialize();
				virtual void Update( float delta );
				virtual std::vector<int> GetPressedKeys(void);
	
				virtual bool IsKeyDown( unsigned int key );
				virtual bool IsKeyUp( unsigned int key );
				virtual bool IsKeyHeld( unsigned int key );
	
			private:
				Keyboard(void) { }
				Keyboard( const Keyboard& keyboard ) { }
				Keyboard& operator = ( const Keyboard& keyboard ) { return *this; }
	
				virtual void Poll(void);

			private:
				IDirectInputDevice8* m_device;
				unsigned char m_previousState[256];
				unsigned char m_currentState[256];
			};
		}
	}
}


#endif // _VAJRA_VERSION_2_INPUTDEVICE_KEYBOARD_HPP_
