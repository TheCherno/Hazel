#pragma once

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
#include <sndfile.h>

namespace Hazel {
    struct AudioInfo
    {
        ALuint buffer;
        ALuint source;
    };

    class AudioManager
    {
    public:
        AudioManager() {}
        virtual ~AudioManager() {}

        virtual int Initialize();
        virtual void Finalize();

        virtual int Tick(Timestep ts);
        
        void LoadAudio(const std::string& filename);
        void PlayAudio(const std::string& name);
    private:
        ALuint Load(const std::string& filename);
        void Play(AudioInfo& info);
    private:
        std::unordered_map<std::string, AudioInfo> m_AudioStore;
    };

    extern AudioManager* g_AudioManager;
}
