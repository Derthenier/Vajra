#include "pch.hpp"
#include "FmodSound.hpp"
using Vajra::Audio::Fmod::FmodSound;

#include "FmodSoundSystem.hpp"
using Vajra::Audio::Fmod::FmodSoundSystem;

#include "../Logger.hpp"
using Vajra::Core::Logger;

#include "fmod_errors.h"

FmodSound::FmodSound( const std::string& name )
: Vajra::Audio::Sound( name )
, m_sound( NULL )
{
}

FmodSound::~FmodSound(void)
{
}

void FmodSound::Load(void)
{
    FMOD::System* system = ( static_cast< FmodSoundSystem& >( Vajra::Audio::SoundManager::GetSoundSystem() ) ).GetSystem();
    FMOD_RESULT result = system->createSound( m_name.c_str(), FMOD_DEFAULT, NULL, &m_sound );
    if( result != FMOD_OK )
    {
        m_sound->release();
        m_sound = NULL;
        Logger::GetInstance().Write( Vajra::Core::LogError, "FMOD Error! %s%d", FMOD_ErrorString( result ), result );
        return;
    }
}
