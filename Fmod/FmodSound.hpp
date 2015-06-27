#pragma once

#ifndef _VAJRA_VERSION_2_FMODSOUND_HPP_
#define _VAJRA_VERSION_2_FMODSOUND_HPP_

#include "FmodSoundSystem.hpp"

namespace Vajra
{
    namespace Audio
    {
        namespace Fmod
        {
            class FmodSound : public Vajra::Audio::Sound
            {
                friend class Vajra::Audio::Fmod::FmodSoundSystem;
            public:
                FmodSound( const std::string& name );
                virtual ~FmodSound(void);

                virtual void Load(void);

                virtual void Play( bool loopSound = false ) { }
                virtual void Pause(void) { }
                virtual void Resume(void) { }
                virtual void Stop(void) { }

                virtual void SetVolume( const float& volume ) { }
                virtual float GetVolume(void) const { return 0.0f; }

            private:
                FMOD::Sound* m_sound;
            };
        }
    }
}

#endif //_VAJRA_VERSION_2_FMODSOUND_HPP_
