#include "RotatorComponent.h"
#include "GameObject.h"
#include "Timer.h"

dae::RotatorComponent::RotatorComponent(float speed, float startAngle, float radius, GameObject* pOwner) : BaseComponent(pOwner),
m_speed(speed),
m_angle(startAngle),
m_radius(radius),
m_position(pOwner->GetPosition())
{
}

void dae::RotatorComponent::Update()
{
    float deltaTime = dae::Timer::GetInstance().GetDeltaTime();
    m_angle += m_speed * deltaTime;

    float radians = glm::radians(m_angle);

    float cosAngle = cos(radians);
    float sinAngle = sin(radians);

    float newX = m_position.x + m_radius * cosAngle;
    float newY = m_position.y + m_radius * sinAngle;

    GetOwner()->SetLocalPosition(newX, newY);
}
