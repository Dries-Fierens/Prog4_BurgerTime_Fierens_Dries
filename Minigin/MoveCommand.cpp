#include "MoveCommand.h"  
#include "Timer.h"

void MoveCommand::Execute()
{
    if (m_pGameObject)
    {
        if (m_MoveHorizontally) 
        {
            glm::vec3 position = m_pGameObject->GetPosition();
            position.x += m_Speed * dae::Timer::GetInstance().GetDeltaTime();
            m_pGameObject->SetLocalPosition(position);
        }
        else 
        {
            glm::vec3 position = m_pGameObject->GetPosition();
            position.y += m_Speed * dae::Timer::GetInstance().GetDeltaTime();
            m_pGameObject->SetLocalPosition(position);
        }
    }
}