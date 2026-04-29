#pragma once
#include "Audio.h"
#include "NullAudio.h"
#include "ConsoleAudio.h"
#include <memory>

class Locator
{
public:
    Locator() = default;
    ~Locator() = default;
    Locator(const Locator&) = delete;
    Locator(Locator&&) = delete;
    Locator& operator=(const Locator&) = delete;
    Locator& operator=(Locator&&) = delete;

    static void Initialize() { service_ = std::make_unique<ConsoleAudio>(); }
	static void Shutdown() { service_ = std::make_unique<NullAudio>(); }

	static Audio* GetAudio() { return service_ ? service_.get() : &nullService_; }

    static void SetAudio(Audio* service)
    {
        if (service == nullptr) service_ = std::make_unique<NullAudio>();
        else service_ = std::unique_ptr<Audio>(service);
    }

private:
    static std::unique_ptr<Audio> service_;
    static NullAudio nullService_;
};