#include "pch.hpp"
#include "SoundManager.hpp"
using Vajra::Audio::Sound;
using Vajra::Audio::SoundManager;
using Vajra::Audio::SoundSystem;

Sound::Sound( const std::string& name )
: Vajra::Core::Resource( name )
{
}

Sound::~Sound(void)
{
}

// #if using fmod

#include "Fmod/FmodSound.hpp"

Sound* Sound::Create( const std::string& name )
{
    return new Vajra::Audio::Fmod::FmodSound( name );
}

// #endif

SoundSystem::SoundSystem(void)
{
}

SoundSystem::~SoundSystem(void)
{
}

void SoundSystem::Play( const std::string& name, bool loopSound /* = false */ )
{
    GetSound( name ).Play( loopSound );
}

void SoundSystem::Pause( const std::string& name )
{
    GetSound( name ).Pause();
}

void SoundSystem::Resume( const std::string& name )
{
    GetSound( name ).Resume();
}

void SoundSystem::Stop( const std::string& name )
{
    GetSound( name ).Stop();
}

SoundManager::SoundManager(void)
{
}

SoundManager::~SoundManager(void)
{
}

#include "Fmod/FmodSoundSystem.hpp"
Vajra::Audio::SoundSystem& SoundManager::GetSoundSystem(void)
{
    return ( Vajra::Audio::Fmod::FmodSoundSystem::GetInstance() );
}
