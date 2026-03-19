#include "RotatorComponent.h"
#include "GameObject.h"
#include "Timer.h"

dae::RotatorComponent::RotatorComponent(float speed, float startAngle, float radius, GameObject* pOwner) : BaseComponent(pOwner),
m_angle(startAngle),
m_speed(speed),
m_radius(radius)
{
}

void dae::RotatorComponent::Update()
{
    float deltaTime = dae::Timer::GetInstance().GetDeltaTime();
    m_angle += m_speed * deltaTime;

    float radians = glm::radians(m_angle);

    float cosAngle = cos(radians);
    float sinAngle = sin(radians);

    float newX = GetOwner()->GetPosition().x + m_radius * cosAngle;
    float newY = GetOwner()->GetPosition().y + m_radius * sinAngle;

    GetOwner()->SetLocalPosition(newX, newY);
}
