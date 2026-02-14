#pragma once
#include "BaseComponent.h"
#include <memory>
#include <SDL3_ttf/SDL_ttf.h>
#include "Transform.h"
#include "TextComponent.h"

namespace dae
{
    class Font;
    class Texture2D;
    class FPSCounter final : public BaseComponent
    {
    public:
        FPSCounter(std::shared_ptr<Font> font, GameObject* pOwner);
        virtual ~FPSCounter() = default;
        FPSCounter(const FPSCounter& other) = delete;
        FPSCounter(FPSCounter&& other) = delete;
        FPSCounter& operator=(const FPSCounter& other) = delete;
        FPSCounter& operator=(FPSCounter&& other) = delete;

        void Update() override;
        void Render() const override;
        void SetPosition(float x, float y);

    private:
        Transform m_position{};
        float m_FPS;
        float m_Timer;
        std::unique_ptr<TextComponent> m_textComponent;
    };
}
