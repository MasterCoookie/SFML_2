#include "Player.h"

Player::Player(float x, float y) {

	this->shape.setPosition(x, y);

	this->initVariables();
	this->initShapes();
}

Player::~Player() {

}

void Player::takeDmg(const int dmg) {
	if (this->hp > 0) {
		this->hp -= dmg;
	} else {
		this->hp = 0;
	}
}

void Player::heal(const int amount) {
	if (this->hp < this->hpMax) {
		this->hp += amount;
	}
	if (this->hp > this->hpMax) {
		this->hp = this->hpMax;
	}
}

void Player::UpdateInput() {
	// keyboard input
	//left - right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->shape.move(-this->movementSpeed, 0.f);
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->shape.move(this->movementSpeed, 0.f);
	}
	
	// up - down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->shape.move(0.f, -this->movementSpeed);
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->shape.move(0.f, this->movementSpeed);
	}
}

void Player::UpdateWindowBoundsCollision(const sf::RenderTarget* target) {

	//sf::Vector2f playerPos = this->shape.getPosition();
	sf::FloatRect playerBounds = this->shape.getGlobalBounds();

	//left
	if (playerBounds.left <= 0.f) {
		this->shape.setPosition(0.f, playerBounds.top);
	//right
	} else if (playerBounds.left + playerBounds.width >= target->getSize().x) {
		this->shape.setPosition(target->getSize().x - playerBounds.width, playerBounds.top);
	}

	//redefine 
	sf::FloatRect playerBoundsNew = this->shape.getGlobalBounds();

	//top
	if (playerBoundsNew.top <= 0.f) {
		this->shape.setPosition(playerBoundsNew.left, 0.f);
	//bottom
	} else if (playerBoundsNew.top + playerBoundsNew.height >= target->getSize().y) {
		this->shape.setPosition(playerBoundsNew.left, target->getSize().y - playerBoundsNew.height);
	}
}

void Player::Update(const sf::RenderTarget* target) {

	//keyboard
	this->UpdateInput();

	//window bounds collision
	this->UpdateWindowBoundsCollision(target);
}

void Player::Render(sf::RenderTarget* target) {
	target->draw(this->shape);
}

const sf::RectangleShape& Player::getShape() const
{
	return this->shape;
}

const int& Player::getHp() const
{
	return this->hp;
}

const int& Player::getHpMax() const
{
	return this->hpMax;
}



void Player::initVariables() {
	this->movementSpeed = 5.f;
	this->hpMax = 10;
	this->hp = this->hpMax;
	
}

void Player::initShapes() {
	this->shape.setFillColor(sf::Color::Green);;
	this->shape.setSize(sf::Vector2f(50.f, 50.f));
}
