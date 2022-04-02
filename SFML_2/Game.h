#pragma once

#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "Player.h"
#include "SwagBall.h"

class Game
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	bool endGame;
	sf::Event sfmlEvent;

	Player player;

	int points;

	sf::Font font;
	sf::Text guiText;
	sf::Text endgameText;

	std::vector<SwagBall> swagBalls;
	float spawnTimerMax;
	float spawnTimer;
	int maxSwagBalls;

	void initWindow();
	void initVariables();
	void initFonts();
	void initText();
	void renderGui(sf::RenderTarget* target);
public:
	Game();
	~Game();

	//getters
	const bool Running() const;
	const bool& getEndGame() const;

	//modifiers
	void PollEvents();

	//functions
	void Update();
	void UpdateCollision();
	void UpdateGui();
	void UpdatePlayer();
	void Render();
	const int randomizeType();
	void SpawnSwagBalls();
};

