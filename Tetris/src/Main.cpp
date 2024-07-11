#include "../include/Header.h"
#include "../include/ItIsGame.h"


int main()
{
	ItIsGame& game = ItIsGame::GetGame();
	game.run();

	return 0;
}