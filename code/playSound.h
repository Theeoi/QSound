#ifndef FMOD_PLAYSOUND
#define FMOD_PLAYSOUND

FMOD_RESULT System::createSound(
    const char *name_or_data,
    FMOD_MODE mode,
    FMOD_CREATESOUNDEXINFO *exinfo,
    FMOD::Sound **sound
);

FMOD_RESULT System::playSound(
    FMOD::Sound *sound,
    FMOD::ChannelGroup *channelgroup,
    bool paused,
    FMOD::Channel **channel
);




#endif
