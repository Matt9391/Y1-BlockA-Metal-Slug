#pragma once
#include "miniaudio.h"

enum SoundID : int;
class ResourceManager;

class AudioManager{
public:
    AudioManager();
    ~AudioManager();
    void clearSounds();
    
    //DONE: delete copy constructor and assingment constructor
    AudioManager(const AudioManager& other) = delete;
    AudioManager& operator=(const AudioManager& other) = delete;

    bool addAudioToPlay(SoundID sid);

    void playSounds(const ResourceManager& rm);

    void updateSounds();

    void setMusic(SoundID id, const ResourceManager& rm);
    bool playMusic();
    void stopMusic();
private:
    ma_engine engine;
    static const int MAXSOUNDS = 300;
    SoundID soundsToPlay[MAXSOUNDS];
    int soundCount;

    static const int MAX_ACTIVE_SOUNDS = 300;

    struct ActiveSound {
        ma_sound sound{};
        bool initialized = false;
    };

    ActiveSound activeSounds[MAX_ACTIVE_SOUNDS];

    ActiveSound music;
    SoundID currentMusic;
};

