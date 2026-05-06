#include "MuteCommand.h"
#include "Locator.h"

void MuteCommand::Execute()
{
	m_IsMuted = !m_IsMuted;
	Locator::GetAudio()->MuteSound(m_IsMuted);
}
