#include "Game.h"

int main() {
	
	//init srand
	srand(static_cast<unsigned>(time(0)));

	//init gameobject
	Game game;

	//game loop
	while (game.Running()) {
		game.Update();
		game.Render();
	}

	return 0;
}