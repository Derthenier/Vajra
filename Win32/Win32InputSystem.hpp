#pragma once

#ifndef _VAJRA_VERSION_2_WIN32INPUTSYSTEM_HPP_
#define _VAJRA_VERSION_2_WIN32INPUTSYSTEM_HPP_

#include "../Singleton.hpp"
#include "../InputSystem.hpp"
#include <map>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

namespace Vajra
{
    namespace Input
    {
        namespace Win32
        {
            class Win32InputSystem : public Vajra::Core::Singleton< Win32InputSystem >, public InputSystem
            {
                friend class Vajra::Core::Singleton< Win32InputSystem >;

            public:
                typedef std::map< unsigned int, Callback > InputCallbackMap;

                virtual ~Win32InputSystem(void);

				const IDirectInput8* GetInput(void) const;

				virtual void Initialize(void);
				virtual void Update( float delta );

                virtual void RegisterKeyDownCallback( unsigned int key, Callback  keyDownCallback );
                virtual void RegisterKeyUpCallback( unsigned int key, Callback keyUpCallback );
                virtual void RegisterKeyHeldCallback( unsigned int key, Callback keyHeldCallback );

                virtual void RegisterButtonDownCallback( unsigned int button, Callback buttonDownCallback );
                virtual void RegisterButtonUpCallback( unsigned int button, Callback buttonUpCallback );
                virtual void RegisterButtonHeldCallback( unsigned int button, Callback buttonHeldCallback );

                virtual Callback KeyDownCallback( unsigned int key );
                virtual Callback KeyUpCallback( unsigned int key );
                virtual Callback ButtonDownCallback( unsigned int button );
                virtual Callback ButtonUpCallback( unsigned int button );

            private:
                Win32InputSystem(void);
                Win32InputSystem( const Win32InputSystem& win32IS ) { }
                Win32InputSystem& operator = ( const Win32InputSystem& win32IS ) { }

            private:
                InputCallbackMap m_keyDownCallbacks;
                InputCallbackMap m_keyUpCallbacks;
                InputCallbackMap m_keyHeldCallbacks;
                InputCallbackMap m_buttonDownCallbacks;
                InputCallbackMap m_buttonUpCallbacks;
                InputCallbackMap m_buttonHeldCallbacks;

				IDirectInput8* m_input;
            };
        }
    }
}

#endif //_VAJRA_VERSION_2_WIN32INPUTSYSTEM_HPP_
