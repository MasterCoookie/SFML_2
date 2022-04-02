#include "SwagBall.h"

SwagBall::SwagBall(const sf::RenderWindow& window, int _type) : type(_type) {
	this->initShape(window);
}

SwagBall::~SwagBall()
{
}

const sf::CircleShape SwagBall::getShape() const
{
	return this->shape;
}

const int& SwagBall::getType() const {
	return this->type;
}

void SwagBall::initShape(const sf::RenderWindow& window){
	this->shape.setRadius(static_cast<float>(rand()%10+10));
	sf::Color color;
	if (this->type == SwagBallTypes::DEFAULT) {
		color = sf::Color::White;
	} else if (this->type == SwagBallTypes::DAMAGING) {
		color = sf::Color::Red;
	} if (this->type == SwagBallTypes::HEALING) {
		color = sf::Color::Green;
	}
	this->shape.setFillColor(color);
	this->shape.setPosition(sf::Vector2f(
		static_cast<float>(rand()%window.getSize().x - this->shape.getGlobalBounds().width),
		static_cast<float>(rand()%window.getSize().y - this->shape.getGlobalBounds().height))
	);
}

void SwagBall::render(sf::RenderTarget& target) {
	target.draw(this->shape);
}
