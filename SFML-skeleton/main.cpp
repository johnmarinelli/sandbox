#include <SFML/Graphics.hpp>
#include "Run.hpp"

const unsigned int WINDOW_WIDTH = 640;
const unsigned int WINDOW_HEIGHT = 480;

const char* const TITLE = "John's game";

int main(int argc, char* args[])
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), TITLE);
	Game game(window);
	game.init();
	
	return Run(game, window);
}
