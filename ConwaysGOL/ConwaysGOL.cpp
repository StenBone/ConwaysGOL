#include <SFML/Graphics.hpp>

namespace ConwaysGOL {

	const std::string  APP_NAME{ "Conway's Game of Life" };
	const sf::Vector2i APP_BOUNDS{800, 600};
	const sf::Vector2i BOARD_BOUNDS{ 40, 30 };
	const float CELL_SIZE{20.f};

	enum class GAME_STATES {
		STAGING, // Waiting for user to setup cells and press 'space' to start the game
		PLAYING, // Simulation is activiely being processed
		GAME_OVER // Exit out of app and perform resource clean up
	};

	int main()
	{
		GAME_STATES game_state = GAME_STATES::STAGING;

		sf::RenderWindow window(sf::VideoMode(APP_BOUNDS.x, APP_BOUNDS.y), APP_NAME);
		sf::RectangleShape box(sf::Vector2f(CELL_SIZE, CELL_SIZE));

		while (window.isOpen()) {

			// STAGING


			// PLAYING


			// GAME_OVER

			sf::Event event;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}
			}

			window.clear(sf::Color::Black);
			//DRAW LINES, UNTIL IT SHOULD BE CACHED
			//UPDATE CELLS IF IT IS TIME TO
			window.draw(box);
			window.display();
		}
		return EXIT_SUCCESS;
	} // BE KIND
}