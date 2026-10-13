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

    

private:
    ma_engine engine;
    static const int MAXSOUNDS = 300;
    SoundID soundsToPlay[MAXSOUNDS];
    int soundCount;
};
