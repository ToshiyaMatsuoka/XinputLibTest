#include "GameManager.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	GameManager* pGameManager = new GameManager(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	pGameManager->MessageLoop();
	delete pGameManager;
	pGameManager = NULL;
}
