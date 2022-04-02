#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class Player {
public:
	Player(float x = 0.f, float y = 0.f);
	~Player();

	const sf::RectangleShape& getShape() const;
	const int& getHp() const;
	const int& getHpMax() const;

	void takeDmg(const int dmg);
	void heal(const int amount);

	void UpdateInput();
	void UpdateWindowBoundsCollision(const sf::RenderTarget* target);
	void Update(const sf::RenderTarget* target);
	void Render(sf::RenderTarget* target);
private:
	sf::RectangleShape shape;

	float movementSpeed;
	int hp;
	int hpMax;
	
	

	void initVariables();
	void initShapes();
};

