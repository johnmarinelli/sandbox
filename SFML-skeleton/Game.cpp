#include "Game.hpp"

Game::Game(sf::RenderTarget& window) : mRenderTarget(&window)
{
//	mRenderTarget = std::make_shared<sf::RenderWindow>(window);
}

void Game::init()
{
	mIsRunning = true;
}

bool Game::isRunning() const
{
	return mIsRunning;
}

Game::~Game()
{
}
