#pragma once

#ifndef _VAJRA_VERSION_2_INPUTDEVICE_MOUSE_HPP_
#define _VAJRA_VERSION_2_INPUTDEVICE_MOUSE_HPP_

#include "../InputSystem.hpp"

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

namespace Vajra
{
	namespace Input
	{
		namespace Devices
		{
			class Mouse : public Vajra::Core::Singleton< Mouse >, public Vajra::Input::InputDevice
			{
				friend class Vajra::Core::Singleton< Mouse >;
			public:
				virtual ~Mouse(void);

				virtual void Initialize();
				virtual void Update( float delta );

				virtual int* GetPressedButtons(void);

				virtual bool IsButtonDown( unsigned int button );
				virtual bool IsButtonUp( unsigned int button );
				virtual bool IsButtonHeld( unsigned int button );

			private:
				Mouse(void) { }
				Mouse( const Mouse& mouse ) { }
				Mouse& operator = ( const Mouse& mouse ) { return *this; }

				virtual void Poll(void);

			private:
				IDirectInputDevice8* m_device;
				DIMOUSESTATE2 m_previousState;
				DIMOUSESTATE2 m_currentState;
			};
		}
	}
}

#endif // _VAJRA_VERSION_2_INPUTDEVICE_MOUSE_HPP_
