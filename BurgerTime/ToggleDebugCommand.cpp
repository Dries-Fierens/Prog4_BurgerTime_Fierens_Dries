#include "ToggleDebugCommand.h"
#include "BoardComponent.h"

void ToggleDebugCommand::Execute()
{
	BoardComponent::ToggleDebugRendering();
}