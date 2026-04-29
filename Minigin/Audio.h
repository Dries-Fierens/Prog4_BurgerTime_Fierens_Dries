#pragma once
#include <string>

class Audio
{
public:
	Audio() = default;
	virtual ~Audio() {};

	Audio(const Audio&) = delete;
	Audio(Audio&&) noexcept = delete;
	Audio& operator=(const Audio&) = delete;
	Audio& operator=(Audio&&) noexcept = delete;

	virtual void PlaySound(const std::string& file, int volume, int loops) = 0;
	virtual void PlayMusic(const std::string& file, int volume, int loops) = 0;
	virtual void PauseMusic(bool isPaused) = 0;
	virtual void MuteSound(bool isMuted) = 0;
};
