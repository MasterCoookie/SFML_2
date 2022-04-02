#include "Game.h"

void Game::initWindow() {
	this->videoMode = sf::VideoMode(800, 600);
	this->window = new sf::RenderWindow(videoMode, "Gejm 2", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(60);
}

void Game::initVariables() {
	this->endGame = false;
	this->spawnTimerMax = 10.f;
	this->spawnTimer = this->spawnTimerMax;
	this->maxSwagBalls = 10;
	this->points = 0;
}

void Game::initFonts() {
	if (!this->font.loadFromFile("./fonts/IndieFlower-Regular.ttf")) {
		std::cout << " ! ERR: GAME::INITFONT:: Failed to load font" << std::endl;
	};
}

void Game::initText() {
	this->guiText.setFont(this->font);
	this->guiText.setFillColor(sf::Color::White);
	this->guiText.setCharacterSize(32);
	this->guiText.setString("Loading");

	this->endgameText.setFont(this->font);
	this->endgameText.setFillColor(sf::Color::Red);
	this->endgameText.setCharacterSize(60);
	this->endgameText.setPosition(sf::Vector2f(20, 240));
}

void Game::renderGui(sf::RenderTarget* target) {
	target->draw(this->guiText);
}

Game::Game() {
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
}

Game::~Game() {
	delete this->window;
}

const bool Game::Running() const
{
	return this->window->isOpen();
}

const bool& Game::getEndGame() const {
	return this->endGame;
}

void Game::PollEvents() {
	while (this->window->pollEvent(this->sfmlEvent)) {
		if (this->sfmlEvent.type == sf::Event::Closed) {
			this->window->close();
		} else if(this->sfmlEvent.key.code == sf::Keyboard::Escape) {
			this->window->close();
		}
	}
}

void Game::Update() {
	this->PollEvents();

	if (this->endGame == false) {
		this->SpawnSwagBalls();
		this->UpdateCollision();
		this->UpdateGui();
		this->UpdatePlayer();
	}

	
}

void Game::UpdateCollision() {
	//check the collision
	for (size_t i = 0; i < this->swagBalls.size(); ++i) {
		if (this->player.getShape().getGlobalBounds().intersects(this->swagBalls[i].getShape().getGlobalBounds())) {
			if (this->swagBalls[i].getType() == SwagBallTypes::DEFAULT) {
				//Add points
				this->points++;
			} else if (this->swagBalls[i].getType() == SwagBallTypes::DAMAGING) {
				this->player.takeDmg(10);
			} else if (this->swagBalls[i].getType() == SwagBallTypes::HEALING) {
				this->player.heal(1);
			}
			
			//remove ball
			this->swagBalls.erase(this->swagBalls.begin() + i);
		}
	}
	
}

void Game::UpdateGui() {
	std::stringstream ss;
	ss << "Points: " << this->points << std::endl;
	ss << "HP: " << this->player.getHp() << "/" << this->player.getHpMax() << std::endl;

	this->guiText.setString(ss.str());
}

void Game::UpdatePlayer() {
	this->player.Update(this->window);

	if (this->player.getHp() <= 0) {
		this->endGame = true;
	}
}

void Game::Render() {
	this->window->clear();

	// rendering stuff

	//player
	this->player.Render(this->window);

	//balls
	for (auto &i : this->swagBalls) {
		i.render(*this->window);
	}

	//gui
	this->renderGui(this->window);
	if (this->endGame) {
		std::stringstream ss;
		ss << "YOU ARE DEAD! SCORE: " << this->points;
		endgameText.setString(ss.str());
		this->window->draw(this->endgameText);
	}

	this->window->display();
}

const int Game::randomizeType() {
	int type = SwagBallTypes::DEFAULT;
	int randVal = rand() % 100 + 1;
	if (randVal > 55 && randVal <= 80) {
		type = SwagBallTypes::DAMAGING;
	} else if(randVal > 80 && randVal <= 100) {
		type = SwagBallTypes::HEALING;
	}
	return type;
}

void Game::SpawnSwagBalls() {
	if (this->spawnTimer < this->spawnTimerMax) {
		this->spawnTimer += 1.f;
	} else {
		if (this->swagBalls.size() < this->maxSwagBalls) {
			this->swagBalls.push_back(SwagBall(*this->window, this->randomizeType()));
			this->spawnTimer = 0.f;
		}
		
	}
}
