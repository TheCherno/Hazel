#pragma once
#include "Hazel/Core/Process.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
#include <glm/glm.hpp>

namespace Hazel {
    class AudioProcess : implements Process
    {
    public:
        AudioProcess(ALuint buffer, int volume = 100, bool looping = false);
        virtual ~AudioProcess() { alDeleteSources(1, &m_Source); }
        void InitializeVolume();
    protected:
        virtual void OnInit(void) override;
        virtual void OnUpdate(unsigned long deltaMs) override;
        virtual void OnAbort(void) override;
    public:
        void Play(const int volume, const bool looping);
        bool IsPlaying();

        void Stop() { alSourceStop(m_Source); }
        void PauseSound() { alSourcePause(m_Source); }

        void SetLooping(bool loop) { m_Looping = loop; alSourcei(m_Source, AL_LOOPING, m_Looping); }
        bool GetLooping() { return m_Looping; }
        void SetVolume(int vol) { m_Volume = vol; alSourcef(m_Source, AL_GAIN, m_Volume / 100.0f); }
        int GetVolume() { return m_Volume; }
        float GetProgress() { alGetSourcef(m_Source, AL_SEC_OFFSET, &m_Progress); return m_Progress; }

        void SetPosition(const glm::vec3& pos);
        void SetPosition(float x, float y, float z);
        const glm::vec3& GetPosition() { return m_Position; }
        void SetVelocity(const glm::vec3& vel);
        void SetVelocity(float x, float y, float z);
        const glm::vec3& GetVelocity() { return m_Velocity; }
    private:
        ALuint m_Buffer;
        ALuint m_Source;
        ALenum m_State;
        ALfloat m_Progress;
        int m_Volume;
        bool m_Looping;
        // TODO : set audio position, to make a 3D sound
        glm::vec3 m_Position;
        glm::vec3 m_Velocity;
    };

    class FadeProcess : public Process
    {
    protected:
        Ref<AudioProcess> m_Sound;
        
        int m_TotalFadeTime;
        int m_ElapsedTime;
        int m_StartVolume;
        int m_EndVolume;

    public:
        FadeProcess(Ref<AudioProcess> sound, int fadeTime, int endVolume);
        virtual void OnUpdate(unsigned long deltaMs);
    };
}
