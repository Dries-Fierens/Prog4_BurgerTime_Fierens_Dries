#pragma once  
#include "Audio.h"  

class NullAudio final : public Audio
{
public:
	void PlaySound(const std::string& /*file*/, int /*volume*/, int /*loops*/) override {};
	void PlayMusic(const std::string& /*file*/, int /*volume*/, int /*loops*/) override {};
	void PauseMusic(bool /*isPaused*/) override {}
	void MuteSound(bool /*isMuted*/) override {}
};