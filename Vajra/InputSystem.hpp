#pragma once

#ifndef _VAJRA_VERSION_2_INPUTSYSTEM_HPP_
#define _VAJRA_VERSION_2_INPUTSYSTEM_HPP_

#include "Vector.hpp"
using Vajra::Math::Vector;

#include <vector>

namespace Vajra
{
    namespace Input
    {
        enum InputKeys
        {
            IK_A = 0x1E,        IK_0 = 0x0B,	IK_NUMPAD_0,		IK_TAB,         IK_LBRACKET,
            IK_B = 0x42,        IK_1 = 0x02,	IK_NUMPAD_1,		IK_LSHIFT,      IK_RBRACKET,
            IK_C = 0x43,        IK_2 = 0x03,	IK_NUMPAD_2,		IK_LCTRL,       IK_FWDSLASH,
            IK_D = 0x44,        IK_3 = 0x04,	IK_NUMPAD_3,		IK_LALT,        IK_COLON,
            IK_E = 0x45,        IK_4 = 0x05,	IK_NUMPAD_4,		IK_SPACE,       IK_QUOTES,
            IK_F = 0x46,        IK_5 = 0x06,	IK_NUMPAD_5,		IK_RALT,        IK_BACKSLASH,
            IK_G = 0x47,        IK_6 = 0x07,	IK_NUMPAD_6,		IK_RSHIFT,      IK_PERIOD,
            IK_H = 0x48,        IK_7 = 0x08,	IK_NUMPAD_7,		IK_RCTRL,       IK_COMMA,
            IK_I = 0x49,        IK_8 = 0x09,	IK_NUMPAD_8,		IK_ENTER,
            IK_J = 0x4A,        IK_9 = 0x0A,	IK_NUMPAD_9,		IK_BACKSPACE,
            IK_K = 0x4B,        IK_F1 = 0x3B,	IK_NUMPAD_ENTER,	IK_TILDE,
            IK_L = 0x4C,        IK_F2 = 0x3C,	IK_NUMPAD_DIVIDE,	IK_ESCAPE = 0x01,
            IK_M = 0x4D,        IK_F3 = 0x3D,	IK_NUMPAD_MULTIPLY,	IK_INSERT,
            IK_N = 0x4E,        IK_F4 = 0x3E,	IK_NUMPAD_SUBTRACT,	IK_DELETE,
            IK_O = 0x4F,        IK_F5 = 0x3F,	IK_NUMPAD_ADD,		IK_HOME,
            IK_P = 0x50,        IK_F6 = 0x40,						IK_END,
            IK_Q = 0x51,        IK_F7 = 0x41,						IK_PAGEUP,
            IK_R = 0x52,        IK_F8 = 0x42,						IK_PAGEDOWN,
            IK_S = 0x53,        IK_F9 = 0x43,						IK_PRNTSCRN,
            IK_T = 0x54,        IK_F10 = 0x44,						IK_PAUSEBRK,
            IK_U = 0x55,        IK_F11 = 0x57,						IK_CAPSLOCK,
            IK_V = 0x56,        IK_F12 = 0x58,						IK_SCRLLOCK,
            IK_W = 0x57,											IK_NUMLOCK,
            IK_X = 0x58,											IK_UP,
            IK_Y = 0x59,											IK_DOWN,
            IK_Z = 0x5A,											IK_LEFT,
																	IK_RIGHT,
        };

		class InputDevice
		{
		public:
			typedef enum _inputdev_type
			{
				ID_KEYBOARD,
				ID_MOUSE,
				ID_JOYSTICK
			} InputDevType;

			static std::vector<int> EMPTY;

			InputDevice(void) { }
			virtual ~InputDevice(void) { }

			static InputDevice& GetDevice(InputDevType device);

			virtual void Initialize() = 0;

			virtual std::vector<int> GetPressedKeys(void) { return EMPTY; }
			virtual void Update( float delta ) = 0;

			virtual bool IsKeyDown( unsigned int key ) { return false; }
			virtual bool IsKeyUp( unsigned int key ) { return false; }
			virtual bool IsKeyHeld( unsigned int key ) { return false; }
			virtual bool IsButtonDown( unsigned int button ) { return false; }
			virtual bool IsButtonUp( unsigned int button ) { return false; }
			virtual bool IsButtonHeld( unsigned int button ) { return false; }
		};

        class InputSystem
        {
        public:
            typedef void (*Callback)(void);

            InputSystem(void);
            virtual ~InputSystem(void);

			virtual void Initialize(void) = 0;
			virtual void Update( float delta ) = 0;

            virtual void RegisterKeyDownCallback( unsigned int key, Callback keyDownCallback ) = 0;
            virtual void RegisterKeyUpCallback( unsigned int key, Callback keyUpCallback ) = 0;
            virtual void RegisterKeyHeldCallback( unsigned int key, Callback keyHeldCallback ) = 0;

            virtual void RegisterButtonDownCallback( unsigned int button, Callback buttonDownCallback ) = 0;
            virtual void RegisterButtonUpCallback( unsigned int button, Callback buttonUpCallback ) = 0;
            virtual void RegisterButtonHeldCallback( unsigned int button, Callback buttonHeldCallback ) = 0;

            virtual Callback KeyDownCallback( unsigned int key ) = 0;
            virtual Callback KeyUpCallback( unsigned int key ) = 0;
            virtual Callback ButtonDownCallback( unsigned int button ) = 0;
            virtual Callback ButtonUpCallback( unsigned int button ) = 0;
        };

        class InputManager
        {
        public:
            static InputSystem& GetInput(void);
			static InputDevice& GetInputDevice(InputDevice::InputDevType device);

        private:
            InputManager(void) { }
            InputManager( const InputManager& im ) { }
            virtual ~InputManager(void) { }
            InputManager& operator = ( const InputManager& im ) { }
        };
    }
}

#endif //_VAJRA_VERSION_2_INPUTSYSTEM_HPP_
