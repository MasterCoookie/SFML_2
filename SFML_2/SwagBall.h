#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

enum SwagBallTypes { DEFAULT = 0, DAMAGING, HEALING, NROFTYPES };

class SwagBall
{
public:
	SwagBall(const sf::RenderWindow& window, int _type);
	~SwagBall();

	const sf::CircleShape getShape() const;
	const int& getType() const;

	void render(sf::RenderTarget& target);

private:
	sf::CircleShape shape;
	int type;

	void initShape(const sf::RenderWindow& window);
	
};

