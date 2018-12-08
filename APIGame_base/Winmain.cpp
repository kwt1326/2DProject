#include "Gamemanager.h"

int APIENTRY WinMain(HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR Cmdline, int Cmdshow)
{
	return GAME_MGR->Run("PORTFOLIO_2D_MEGAMAN", 800, 600);
}