#include "MainMenuCommand.h"
#include "GameManager.h"
#include "MainMenu.h"


void MainMenuCommand::Execute()
{
	GameManager::GetInstance().SetGameState(GameManager::GameState::Menu);
	MainMenu::Create();
}