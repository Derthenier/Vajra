#pragma once

#ifndef _VAJRA_VERSION_2_SOUNDSYSTEM_HPP_
#define _VAJRA_VERSION_2_SOUNDSYSTEM_HPP_

#include "Resource.hpp"
#include <string>

namespace Vajra
{
    namespace Audio
    {
        class Sound : public Vajra::Core::Resource
        {
        public:
            Sound( const std::string& name );
            virtual ~Sound(void);

            virtual void Load(void) = 0;
            static Sound* Create( const std::string& name );

            virtual void Play( bool loopSound = false ) = 0;
            virtual void Pause(void) = 0;
            virtual void Resume(void) = 0;
            virtual void Stop(void) = 0;

            virtual void SetVolume( const float& volume ) = 0;
            virtual float GetVolume(void) const = 0;
        };

        class SoundSystem
        {
        public:
            virtual void Initialize(void) = 0;
            virtual void Shutdown(void) = 0;

            virtual Sound& GetSound( const std::string& name ) = 0;

            virtual void PauseAll(void) = 0;
            virtual void ResumeAll(void) = 0;

            virtual void SetVolume( const float& volume ) = 0;
            virtual float GetVolume(void) const = 0;

            virtual void Play( const std::string& name, bool loopSound = false );
            virtual void Pause( const std::string& name );
            virtual void Resume( const std::string& name );
            virtual void Stop( const std::string& name );

        protected:
            SoundSystem(void);
            virtual ~SoundSystem(void);
        };

        class SoundManager
        {
        public:
            static SoundSystem& GetSoundSystem(void);

        private:
            SoundManager(void);
            ~SoundManager(void);
            SoundManager( const SoundManager& ss ) { }
            SoundManager& operator = ( const SoundManager& ss ) { }
        };
    }
}

#endif //_VAJRA_VERSION_2_SOUNDSYSTEM_HPP_
