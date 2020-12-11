#include "GEProcess/AudioProcess.h"

namespace Rocket {
    AudioProcess::AudioProcess(ALuint buffer, int volume, bool looping)
        : m_Buffer(buffer), m_Volume(volume), m_Looping(looping)
    {
        InitializeVolume();
    }

    void AudioProcess::InitializeVolume()
    {
        // TODO : use global volume setting
    }

    void AudioProcess::OnInit(void)
    {
        Process::OnInit();
        // audio should be loaded before this process
        alGenSources(1, &m_Source);
        alSourcei(m_Source, AL_BUFFER, (ALint)m_Buffer);

        alSourcef(m_Source, AL_GAIN, m_Volume / 100.0f);
        alSourcei(m_Source, AL_LOOPING, m_Looping);

        Play(m_Volume, m_Looping);
    }

    void AudioProcess::OnUpdate(unsigned long deltaMs)
    {
        if (!IsPlaying())
        {
            Succeed();
        }
    }

    void AudioProcess::OnAbort(void)
    {
        PauseSound();
    }

    bool AudioProcess::IsPlaying()
    {
        alGetSourcei(m_Source, AL_SOURCE_STATE, &m_State);
        return m_State == AL_PLAYING;
    }

    void AudioProcess::Play(const int volume, const bool looping)
    {
        alSourcef(m_Source, AL_GAIN, volume / 100.0f);
        alSourcePlay(m_Source);
    }

    void AudioProcess::SetPosition(const glm::vec3& pos)
    {
        m_Position = pos;
        alSource3f(m_Source, AL_POSITION, m_Position.x, m_Position.y, m_Position.z);
    }

    void AudioProcess::SetPosition(float x, float y, float z)
    {
        m_Position = {x, y, z};
        alSource3f(m_Source, AL_POSITION, m_Position.x, m_Position.y, m_Position.z);
    }

    void AudioProcess::SetVelocity(const glm::vec3& vel)
    {
        m_Velocity = vel;
        alSource3f(m_Source, AL_VELOCITY, m_Velocity.x, m_Velocity.y, m_Velocity.z);
    }

    void AudioProcess::SetVelocity(float x, float y, float z)
    {
        m_Velocity = {x, y, z};
        alSource3f(m_Source, AL_VELOCITY, m_Velocity.x, m_Velocity.y, m_Velocity.z);
    }

    /////////////////////////////////////////////////////////////////////////////
    // 
    // FadeProcess Implementation 
    //
    //////////////////////////////////////////////////////////////////////

    //
    // FadeProcess::FadeProcess						- Chapter 13, page 435
    //
    FadeProcess::FadeProcess(Ref<AudioProcess> sound, int fadeTime, int endVolume)
    {
        m_Sound = sound;
        m_TotalFadeTime = fadeTime;
        m_StartVolume = sound->GetVolume();
        m_EndVolume = endVolume;
        m_ElapsedTime = 0;

        OnUpdate(0);
    }

    //
    // FadeProcess::OnUpdate						- Chapter 13, page 435
    //
    void FadeProcess::OnUpdate(unsigned long deltaMs)
    {
        m_ElapsedTime += deltaMs;

        if (m_Sound->IsDead())
            Succeed();

        float cooef = (float)m_ElapsedTime / m_TotalFadeTime;
        if (cooef>1.0f)
            cooef = 1.0f;
        if (cooef<0.0f)
            cooef = 0.0f;

        int newVolume = m_StartVolume + (int)( float(m_EndVolume - m_StartVolume) * cooef);

        if (m_ElapsedTime >= m_TotalFadeTime)
        {
            newVolume = m_EndVolume;
            Succeed();
        }

        m_Sound->SetVolume(newVolume);
    }
}
