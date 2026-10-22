#include "precomp.h"
#define MINIAUDIO_IMPLEMENTATION
#include "AudioManager.h"

#include <SoundID.h>
#include <ResourceManager.h>
#include <iostream>


AudioManager::AudioManager() : 
    soundsToPlay{SoundID::SID_NULL},
    soundCount(0),
    currentMusic(SoundID::SID_NULL)
{
    ma_engine_init(NULL, &engine);
}

void AudioManager::clearSounds(){
    for(int i = 0; i < soundCount; i++){
        soundsToPlay[i] = SoundID::SID_NULL;
    }
    soundCount = 0;
}

bool AudioManager::addAudioToPlay(SoundID sid) {
    if(sid == SID_NULL) return false;
    if(soundCount >= MAXSOUNDS) {
            printf("MAX SOUNDS REACHED, AUDIOMANAGER");
            return;
    }
    this->soundsToPlay[soundCount++] = sid;

    return true;
}


void AudioManager::playSounds(const ResourceManager& rm) {
    for (int i = 0; i < soundCount; ++i) {
        SoundID id = soundsToPlay[i];

        for (ActiveSound& slot : activeSounds) {
            if (slot.initialized)
                continue;

            ma_result result = ma_sound_init_from_file(
                &engine,
                rm.getSoundPath(id),
                0,
                nullptr,
                nullptr,
                &slot.sound
            );

            if (result != MA_SUCCESS)
                break;

            slot.initialized = true;

            float volume = rm.getSoundVolume(id);
            ma_sound_set_volume(&slot.sound, volume);


            result = ma_sound_start(&slot.sound);

            if (result != MA_SUCCESS) { //if it doesnt run for n reasons
                ma_sound_uninit(&slot.sound);
                slot.initialized = false;
            }

            break;
        }
    }

    soundCount = 0;
}


AudioManager::~AudioManager() {
    clearSounds();

    for (ActiveSound& slot : activeSounds) {
        if (slot.initialized) {
            ma_sound_stop(&slot.sound);
            ma_sound_uninit(&slot.sound);
            slot.initialized = false;
        }
    }

    ma_sound_stop(&music.sound);
    ma_sound_uninit(&music.sound);
    music.initialized = false;

    ma_engine_uninit(&engine);
}


void AudioManager::updateSounds() {
    for (ActiveSound& slot : activeSounds) {
        if (!slot.initialized)
            continue;

        if (!ma_sound_is_playing(&slot.sound)) {
            ma_sound_uninit(&slot.sound);
            slot.initialized = false;
        }
    }
}

void AudioManager::setMusic(SoundID id, const ResourceManager& rm) {
    if (music.initialized && currentMusic == id) return;   // this track is already loaded
    stopMusic();                                           // unload the previous one

    // STREAM = read from disk while playing, instead of decoding the whole file into memory
    ma_result result = ma_sound_init_from_file(&engine, rm.getSoundPath(id),
                                               MA_SOUND_FLAG_STREAM, nullptr, nullptr, &music.sound);
    if (result != MA_SUCCESS) return;

    ma_sound_set_looping(&music.sound, MA_TRUE);
    ma_sound_set_volume(&music.sound, rm.getSoundVolume(id));

    music.initialized = true;
    currentMusic = id;
}

bool AudioManager::playMusic() {
    if (!music.initialized) return false;                
    if (ma_sound_is_playing(&music.sound)) return true;    // already playing

    return ma_sound_start(&music.sound) == MA_SUCCESS;
}

void AudioManager::stopMusic() {
    if (!music.initialized) return;
    ma_sound_stop(&music.sound);
    ma_sound_uninit(&music.sound);
    music.initialized = false;
    currentMusic = SoundID::SID_NULL;
}