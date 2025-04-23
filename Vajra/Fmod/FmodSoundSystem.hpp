#pragma once

#ifndef _VAJRA_VERSION_2_FMODSOUNDSYSTEM_HPP_
#define _VAJRA_VERSION_2_FMODSOUNDSYSTEM_HPP_

#include "../Singleton.hpp"
#include "../SoundManager.hpp"
#include <map>
#include "fmod.hpp"
#include "fmod_errors.h"

namespace Vajra
{
    namespace Audio
    {
        namespace Fmod
        {
            class FmodSoundSystem : public Vajra::Audio::SoundSystem, public Vajra::Core::Singleton< FmodSoundSystem >
            {
                friend class Vajra::Core::Singleton< FmodSoundSystem >;

            public:
                virtual ~FmodSoundSystem(void);

                virtual void Initialize(void);
                virtual void Shutdown(void);

                virtual Vajra::Audio::Sound& GetSound( const std::string& name );

                virtual void PauseAll(void);
                virtual void ResumeAll(void);

                virtual void SetVolume( const float& volume );
                virtual float GetVolume(void) const;

                FMOD::System* GetSystem(void) const;

                virtual void Play( const std::string& name, bool loopSound = false );
                virtual void Pause( const std::string& name );
                virtual void Resume( const std::string& name );
                virtual void Stop( const std::string& name );

            private:
                FmodSoundSystem(void);
                FmodSoundSystem( const FmodSoundSystem& fss ) { }
                FmodSoundSystem& operator = ( const FmodSoundSystem& fss ) { }

                enum State
                {
                    Playing = 0,
                    Paused = 1,
                    Stopped = 2
                };

                struct Channel
                {
                    FMOD::Channel* m_channel;
                    FmodSoundSystem::State m_state;
                };

            private:
                FMOD::System* m_system;
                FMOD::SoundGroup* m_masterGroup;
                FMOD::SoundGroup* m_musicGroup;
                FMOD::SoundGroup* m_effectsGroup;

                std::map< std::string, FmodSoundSystem::Channel* > m_channels;
            };
        }
    }
}

#endif //_VAJRA_VERSION_2_FMODSOUNDSYSTEM_HPP_
