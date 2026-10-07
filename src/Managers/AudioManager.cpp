#include "precomp.h"
#define MINIAUDIO_IMPLEMENTATION
#include "AudioManager.h"

#include <SoundID.h>
#include <ResourceManager.h>


AudioManager::AudioManager() : 
    soundsToPlay{SoundID::SID_NULL},
    soundCount(0)
{
    ma_engine_init(NULL, &engine);
}

void AudioManager::clearSounds(){
    for(int i = 0; i < MAXSOUNDS; i++){
        soundsToPlay[i] = SoundID::SID_NULL;
    }
    soundCount = 0;
}

bool AudioManager::addAudioToPlay(SoundID sid) {
    if(sid == SID_NULL) return false;
    if(soundCount >= MAXSOUNDS) throw runtime_error("MAX SOUNDS REACHED");
    this->soundsToPlay[soundCount++] = sid;

    return true;
}


void AudioManager::playSounds(const ResourceManager& rm){
    for(int i = 0; i < MAXSOUNDS; i++){
        if(soundsToPlay[i] == SoundID::SID_NULL) continue;
        ma_engine_play_sound(&engine, rm.getSoundPath(soundsToPlay[i]),NULL); 

    }
}


AudioManager::~AudioManager(){
    ma_engine_uninit(&engine); 
}
