#ifndef GAME_HPP
#define GAME_HPP

#include <memory>
#include <SFML/Graphics.hpp>

class Game
{
private:
//	std::shared_ptr<sf::RenderTarget> mRenderTarget;
	sf::RenderTarget* mRenderTarget;
	bool mIsRunning;

public:
	Game(sf::RenderTarget& window);

	void init();
	bool isRunning() const;

	~Game();
};

#endif
