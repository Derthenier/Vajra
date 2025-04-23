#include "pch.hpp"
#include "../Definitions.hpp"
#include "../Logger.hpp"
#include "FmodSoundSystem.hpp"
using Vajra::Audio::Fmod::FmodSoundSystem;

#include "FmodSound.hpp"

FmodSoundSystem::FmodSoundSystem(void)
: Vajra::Audio::SoundSystem()
, m_system( NULL )
, m_masterGroup( NULL )
, m_musicGroup( NULL )
, m_effectsGroup( NULL )
{
}

FmodSoundSystem::~FmodSoundSystem(void)
{
    Shutdown();
}

void FmodSoundSystem::Initialize(void)
{
    FMOD_RESULT result = FMOD::Memory_Initialize( std::malloc( 12 * 1024 * 1024 ), ( 12 * 1024 * 1024 ), NULL, NULL, NULL );
    if( result != FMOD_OK )
    {
        Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogCritical, "Failed to allocate memory for Fmod. (%s)", FMOD_ErrorString( result ) );
        return;
    }
        
    result = FMOD::System_Create( &m_system );
    if( result != FMOD_OK )
    {
        m_system = NULL;
        Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, "Failed to create Fmod System. (%s)", FMOD_ErrorString( result ) );
        return;
    }

    result = m_system->init( 100, FMOD_INIT_NORMAL, NULL );
    if( result != FMOD_OK )
    {
        Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, "Failed to initialize Fmod System. (%s)", FMOD_ErrorString( result ) );
        return;
    }

    result = m_system->createSoundGroup( "Master Group", &m_masterGroup );
    if( result != FMOD_OK )
    {
        m_masterGroup = NULL;
        Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, "Failed to create master sound group. (%s)", FMOD_ErrorString( result ) );
        return;
    }

    result = m_system->createSoundGroup( "Music Group", &m_musicGroup );
    if( result != FMOD_OK )
    {
        m_musicGroup = NULL;
        Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, "Failed to create music group. (%s)", FMOD_ErrorString( result ) );
        return;
    }

    result = m_system->createSoundGroup( "Sound Effects Group", &m_effectsGroup );
    if( result != FMOD_OK )
    {
        m_effectsGroup = NULL;
        Vajra::Core::Logger::GetInstance().Write( Vajra::Core::LogError, "Failed to create effects group. (%s)", FMOD_ErrorString( result ) );
        return;
    }
}

void FmodSoundSystem::Shutdown(void)
{
    if( NULL != m_musicGroup )
    {
        m_musicGroup->release();
        m_musicGroup = NULL;
    }

    if( NULL != m_effectsGroup )
    {
        m_effectsGroup->release();
        m_effectsGroup = NULL;
    }

    if( NULL != m_masterGroup )
    {
        m_masterGroup->release();
        m_masterGroup = NULL;
    }

    if( NULL != m_system )
    {
        m_system->close();
        m_system->release();
        m_system = NULL;
    }
}

void FmodSoundSystem::PauseAll(void)
{
}

void FmodSoundSystem::ResumeAll(void)
{
}

Vajra::Audio::Sound& FmodSoundSystem::GetSound( const std::string& name )
{
    Vajra::Audio::Fmod::FmodSound* sound = Vajra::Core::ResourceManager::GetInstance().GetResource< Vajra::Audio::Fmod::FmodSound >( name );
    if( sound == NULL )
        Vajra::Core::ResourceManager::GetInstance().Load< Vajra::Audio::Sound >( name );
    return *( Vajra::Core::ResourceManager::GetInstance().GetResource< Vajra::Audio::Fmod::FmodSound >( name ) );
}

void FmodSoundSystem::SetVolume( const float& volume )
{
    m_masterGroup->setVolume( volume );
}

float FmodSoundSystem::GetVolume(void) const
{
    float l_volume = 0.0f;
    m_masterGroup->getVolume( &l_volume );
    return l_volume;
}

void FmodSoundSystem::Play( const std::string& name, bool loopSound )
{
    Vajra::Audio::Fmod::FmodSound& sound = static_cast< Vajra::Audio::Fmod::FmodSound& >( GetSound( name ) );

    FMOD::Channel* channel = NULL;

    FMOD_RESULT result = m_system->playSound( FMOD_CHANNEL_FREE, sound.m_sound, true, &channel );
    if( result != FMOD_OK )
    {

    }

    if( channel != NULL )
    {
        if( loopSound )
            channel->setLoopCount( -1 );
        else
            channel->setLoopCount( 0 );

        FmodSoundSystem::Channel* c = new FmodSoundSystem::Channel();

        c->m_channel = channel;
        c->m_state = FmodSoundSystem::Playing;

        m_channels.insert( std::make_pair( name, c ) );

        channel->setPaused( false );
    }
}

void FmodSoundSystem::Pause( const std::string& name )
{
    if( m_channels.find( name ) == m_channels.end() )
        return;
    FmodSoundSystem::Channel* c = m_channels[ name ];
    if( c != NULL )
    {
        bool isPlaying = false;
        c->m_channel->isPlaying( &isPlaying );

        if( isPlaying )
        {
            c->m_channel->setPaused( true );
            c->m_state = FmodSoundSystem::Paused;
        }
    }
}

void FmodSoundSystem::Resume( const std::string& name )
{
    if( m_channels.find( name ) == m_channels.end() )
        return;

    FmodSoundSystem::Channel* c = m_channels[ name ];
    if( c != NULL )
    {
        bool isPaused = false;
        c->m_channel->getPaused( &isPaused );

        if( isPaused )
        {
            c->m_channel->setPaused( false );
            c->m_state = FmodSoundSystem::Playing;
        }
    }
}

void FmodSoundSystem::Stop( const std::string& name )
{
    std::map< std::string, FmodSoundSystem::Channel* >::iterator itr = m_channels.find( name );
    if( itr == m_channels.end() )
        return;

    FmodSoundSystem::Channel* c = itr->second;
    if( c != NULL )
    {
        c->m_channel->stop();
        c->m_state = FmodSoundSystem::Stopped;
    }

    m_channels.erase( itr );
}

FMOD::System* FmodSoundSystem::GetSystem(void) const
{
    return m_system;
}

