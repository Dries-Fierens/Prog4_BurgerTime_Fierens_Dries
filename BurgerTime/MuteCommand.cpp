#include "MuteCommand.h"
#include "Locator.h"

void MuteCommand::Execute()
{
	m_IsMuted = !m_IsMuted;
#ifndef __EMSCRIPTEN__
	Locator::GetAudio()->MuteSound(m_IsMuted);
#endif
}
