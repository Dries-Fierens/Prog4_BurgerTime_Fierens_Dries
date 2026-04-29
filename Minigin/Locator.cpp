#include "Locator.h"

NullAudio Locator::nullService_{};
std::unique_ptr<Audio> Locator::service_{ std::make_unique<NullAudio>() };