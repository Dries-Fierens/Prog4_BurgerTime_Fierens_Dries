#pragma once
#include "Command.h"

class MuteCommand final : public dae::Command
{
public:
	MuteCommand() = default;
	void Execute() override;
private:
	bool m_IsMuted{ false };
};

