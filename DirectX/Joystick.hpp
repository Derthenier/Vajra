#pragma once

#ifndef _VAJRA_VERSION_2_INPUTDEVICE_JOYSTICK_HPP_
#define _VAJRA_VERSION_2_INPUTDEVICE_JOYSTICK_HPP_

#include "../InputSystem.hpp"

struct IDirectInput8;
struct IDirectInputDevice8;

namespace Vajra
{
	namespace Input
	{
		namespace Devices
		{
			class Joystick : public Vajra::Core::Singleton< Joystick >, public Vajra::Input::InputDevice
			{
				friend class Vajra::Core::Singleton< Joystick >;
			public:
				virtual ~Joystick(void);

				virtual void Initialize();
				virtual void Update( float delta );

				virtual int* GetPressedButtons(void);

				virtual bool IsButtonDown( unsigned int button );
				virtual bool IsButtonUp( unsigned int button );
				virtual bool IsButtonHeld( unsigned int button );

			private:
				IDirectInputDevice8* m_device;

			private:
				Joystick(void) { }
				Joystick( const Joystick& jk ) { }
				Joystick& operator = ( const Joystick& jk ) { return *this; }

				virtual void Poll(void);
			};
		}
	}
}

#endif // _VAJRA_VERSION_2_INPUTDEVICE_JOYSTICK_HPP_
