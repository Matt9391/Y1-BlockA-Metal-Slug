#pragma once
#include "miniaudio.h"

enum SoundID : int;
class ResourceManager;

class AudioManager{
public:
    AudioManager();
    ~AudioManager();

    void clearSounds();

    bool addAudioToPlay(SoundID sid);

    void playSounds(const ResourceManager& rm);

    

private:
    ma_engine engine;
    static const int MAXSOUNDS = 300;
    SoundID soundsToPlay[MAXSOUNDS];
    int soundCount;
};
