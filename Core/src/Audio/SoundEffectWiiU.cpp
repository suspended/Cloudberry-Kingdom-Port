#include <Audio/SoundEffect.h>

#include <cmath>
#include <Content/File.h>
#include <Content/Filesystem.h>
#include <Utility/Log.h>

#include "AudioInternalWiiU.h"
#include "CKSounds.h"

#include <fmod.hpp>

extern FMOD::System *FMODSystem;

struct SoundEffectInternal
{
	FMOD::Sound *Sound;
	FMOD::Channel *Channel;
};

SoundEffect::SoundEffect() :
	internal_( new SoundEffectInternal )
{
	internal_->Sound = NULL;
	internal_->Channel = NULL;
}

SoundEffect::~SoundEffect()
{
	if( internal_->Sound )
		internal_->Sound->release();

	delete internal_;
}

void SoundEffect::Load( const std::string &path )
{
	FMOD_RESULT result;
	result = FMODSystem->createSound( ( "/vol/content/" + path ).c_str(), FMOD_DEFAULT, 0, &internal_->Sound );
	if( result != FMOD_OK )
	{
		LOG.Write( "Failed to load sound: %s\n", path.c_str() );
		internal_->Sound = NULL;
	}
}

void SoundEffect::Play( float volume, float pitch, float pan )
{
	if( !internal_->Sound )
		return;

	FMODSystem->playSound( FMOD_CHANNEL_FREE, internal_->Sound, true, &internal_->Channel );
	internal_->Channel->setVolume( volume );
	internal_->Channel->setPan( pan );
	internal_->Channel->setPaused( false );
}
