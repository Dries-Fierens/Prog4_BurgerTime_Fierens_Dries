#pragma once
#include "Audio.h"
#include <mutex>
#include <queue>
#include <condition_variable>
#include <iostream>

class ConsoleAudio final : public Audio
{
public:
    ConsoleAudio();
    ~ConsoleAudio() override;

    void PlaySound(const std::string& file, int volume, int loops) override;
    void PlayMusic(const std::string& file, int volume, int loops) override;
    void PauseMusic(bool isPaused) override;
    void MuteSound(bool isMuted) override;

private:
    class ConsoleAudioImpl;
    std::unique_ptr<ConsoleAudioImpl> m_pImpl{};
};