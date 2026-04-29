#include "ConsoleAudio.h"
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3/SDL.h>
#include <algorithm>
#include <filesystem>
#include <thread>
#include <unordered_map>

class ConsoleAudio::ConsoleAudioImpl final
{
public:
	ConsoleAudioImpl() : m_running(true)
	{
		Initialize();
	}

	~ConsoleAudioImpl()
	{
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_running = false;
		}
		m_conditionVariable.notify_all();

		if (m_thread.joinable())
		{
			m_thread.join();
		}

		if (m_pSoundTrack)
		{
			MIX_DestroyTrack(m_pSoundTrack);
			m_pSoundTrack = nullptr;
		}

		if (m_pMusicTrack)
		{
			MIX_DestroyTrack(m_pMusicTrack);
			m_pMusicTrack = nullptr;
		}

		for (auto& [_, pAudio] : m_loadedAudio)
		{
			MIX_DestroyAudio(pAudio);
		}
		m_loadedAudio.clear();

		if (m_pMixer)
		{
			MIX_DestroyMixer(m_pMixer);
			m_pMixer = nullptr;
		}

		MIX_Quit();

		if (m_initializedAudioSubsystem)
		{
			SDL_QuitSubSystem(SDL_INIT_AUDIO);
		}
	}

	ConsoleAudioImpl(const ConsoleAudioImpl& other) = delete;
	ConsoleAudioImpl& operator=(const ConsoleAudioImpl& rhs) = delete;
	ConsoleAudioImpl(ConsoleAudioImpl&& other) = delete;
	ConsoleAudioImpl& operator=(ConsoleAudioImpl&& rhs) = delete;

	void Initialize()
	{
		if ((SDL_WasInit(SDL_INIT_AUDIO) & SDL_INIT_AUDIO) == 0)
		{
			if (!SDL_InitSubSystem(SDL_INIT_AUDIO))
			{
				std::cout << "SDL audio subsystem could not initialize! Error: " << SDL_GetError() << std::endl;
				return;
			}

			m_initializedAudioSubsystem = true;
		}

		if (!MIX_Init())
		{
			std::cout << "SDL_mixer could not initialize! Error: " << SDL_GetError() << std::endl;
			return;
		}

		m_pMixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);
		if (!m_pMixer)
		{
			std::cout << "Could not create mixer device! Error: " << SDL_GetError() << std::endl;
			return;
		}

		m_pSoundTrack = MIX_CreateTrack(m_pMixer);
		m_pMusicTrack = MIX_CreateTrack(m_pMixer);

		if (!m_pSoundTrack || !m_pMusicTrack)
		{
			std::cout << "Could not create mixer tracks! Error: " << SDL_GetError() << std::endl;
			return;
		}

		m_thread = std::thread(&ConsoleAudioImpl::Update, this);
	}

	void Update()
	{
		for (;;)
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			m_conditionVariable.wait(lock, [this] { return !m_queue.empty() || !m_running; });

			if (!m_running)
			{
				break;
			}

			SoundEvent e = m_queue.front();
			m_queue.pop();
			lock.unlock();

			if (!e.pAudio)
			{
				continue;
			}

			auto* pTrack = e.isMusic ? m_pMusicTrack : m_pSoundTrack;
			if (!pTrack)
			{
				continue;
			}

			if (e.isMusic && (MIX_TrackPlaying(m_pMusicTrack) || MIX_TrackPaused(m_pMusicTrack)))
			{
				continue;
			}

			MIX_SetTrackAudio(pTrack, e.pAudio);
			MIX_SetTrackGain(pTrack, VolumeToGain(e.volume));

			SDL_PropertiesID playOptions{ 0 };
			if (e.loops != 0)
			{
				playOptions = SDL_CreateProperties();
				if (playOptions != 0)
				{
					SDL_SetNumberProperty(playOptions, MIX_PROP_PLAY_LOOPS_NUMBER, static_cast<Sint64>(e.loops));
				}
			}

			if (!MIX_PlayTrack(pTrack, playOptions))
			{
				std::cout << "Could not play audio! Error: " << SDL_GetError() << std::endl;
			}

			if (playOptions != 0)
			{
				SDL_DestroyProperties(playOptions); 
			}
		}
	}

	void PlaySound(const std::string& file, int volume, int loops)
	{
		QueueAudio(file, volume, false, loops);
	}

	void PlayMusic(const std::string& file, int volume, int loops)
	{
		QueueAudio(file, volume, true, loops);
	}

	void PauseMusic(bool isPaused)
	{
		if (!m_pMusicTrack)
		{
			return;
		}

		if (isPaused)
		{
			MIX_PauseTrack(m_pMusicTrack);
		}
		else
		{
			MIX_ResumeTrack(m_pMusicTrack);
		}
	}

	void MuteSound(bool isMuted)
	{
		if (!m_pMixer)
		{
			return;
		}

		MIX_SetMixerGain(m_pMixer, isMuted ? 0.0f : 1.0f);
	}

private:
	struct SoundEvent
	{
		MIX_Audio* pAudio;
		int volume;
		bool isMusic;
		int loops;
	};

	bool m_running;
	std::mutex m_mutex;
	std::condition_variable m_conditionVariable;
	std::queue<SoundEvent> m_queue;
	std::unordered_map<std::string, MIX_Audio*> m_loadedAudio;
	MIX_Mixer* m_pMixer{};
	MIX_Track* m_pSoundTrack{};
	MIX_Track* m_pMusicTrack{};
	std::thread m_thread;
	bool m_initializedAudioSubsystem{};

	static float VolumeToGain(int volume)
	{
		return static_cast<float>(std::clamp(volume, 0, 100)) / 100.0f;
	}

	static std::string ResolveAudioPath(const std::string& file)
	{
		namespace fs = std::filesystem;

		const fs::path requestedPath{ file };
		if (requestedPath.is_absolute() || fs::exists(requestedPath))
		{
			return requestedPath.string();
		}

		const auto filename = requestedPath.filename();
		if (filename.empty())
		{
			return file;
		}

		const fs::path candidatePaths[]
		{
			fs::path{ "Data" } / filename,
			fs::path{ ".." } / "Data" / filename
		};

		for (const auto& candidatePath : candidatePaths)
		{
			if (fs::exists(candidatePath))
			{
				return candidatePath.string();
			}
		}

		return file;
	}

	void QueueAudio(const std::string& file, int volume, bool isMusic, int loops)
	{
		std::lock_guard<std::mutex> lock(m_mutex);

		auto* pAudio = LoadAudio(file);
		if (!pAudio)
		{
			return;
		}

		m_queue.push(SoundEvent{ pAudio, volume, isMusic, loops });
		m_conditionVariable.notify_all();
	}

	MIX_Audio* LoadAudio(const std::string& file)
	{
		if (!m_pMixer)
		{
			return nullptr;
		}

		const auto resolvedFile = ResolveAudioPath(file);
		const auto found = m_loadedAudio.find(resolvedFile);
		if (found != m_loadedAudio.end())
		{
			return found->second;
		}

		auto* pAudio = MIX_LoadAudio(m_pMixer, resolvedFile.c_str(), false);
		if (!pAudio)
		{
			std::cout << "Could not load audio file '" << file << "'! Error: " << SDL_GetError() << std::endl;
			return nullptr;
		}

		m_loadedAudio.emplace(resolvedFile, pAudio);
		return pAudio;
	}
};

ConsoleAudio::ConsoleAudio() : m_pImpl{ std::make_unique<ConsoleAudioImpl>() } {}

ConsoleAudio::~ConsoleAudio() = default;

void ConsoleAudio::PlaySound(const std::string& file, int volume, int loops)
{
	m_pImpl->PlaySound(file, volume, loops);
}

void ConsoleAudio::PlayMusic(const std::string& file, int volume, int loops)
{
	m_pImpl->PlayMusic(file, volume, loops);
}

void ConsoleAudio::PauseMusic(bool isPaused)
{
	m_pImpl->PauseMusic(isPaused);
}

void ConsoleAudio::MuteSound(bool isMuted)
{
	m_pImpl->MuteSound(isMuted);
}