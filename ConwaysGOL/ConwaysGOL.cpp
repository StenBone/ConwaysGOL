#include <Vector>
#include <SFML/Graphics.hpp>

//namespace cgol { // Conways Game of Life

const std::string  APP_NAME{ "Conway's Game of Life" };
const sf::Vector2u APP_BOUNDS{ 800, 600 };
const sf::Vector2i BOARD_BOUNDS{ 40, 30 };
const sf::Vector2f CELL_SIZE{ 20.f, 20.f };

enum class GAME_STATES {
	STAGING, // Waiting for user to setup cells and press 'space' to start the game
	PLAYING, // Simulation is activiely being processed
	GAME_OVER // Exit out of app and perform resource clean up
};

struct Cell {
	sf::RectangleShape shape{};
};


//}

int main()
{
	GAME_STATES game_state = GAME_STATES::STAGING;

	sf::RenderWindow window{ sf::VideoMode{APP_BOUNDS.x, APP_BOUNDS.y}, APP_NAME };

	// INIT BOARD, INIT CELLS
	std::vector<Cell> board{};

	while (window.isOpen()) {

		int border = 9;
		for (int row = 0; row < 4; row++) {
			Cell cell;
			cell.shape.setPosition(row * CELL_SIZE.x + 9, 0);
			cell.shape.setSize(CELL_SIZE);
			board.push_back(cell);
		}


		// STAGING


		// PLAYING


		// GAME_OVER

		sf::Event event = {};
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		// RENDER
		window.clear(sf::Color::Black);
		for (Cell cell : board) {
			window.draw(cell.shape);
		}
		window.display();
	}
	return EXIT_SUCCESS;
} // BE KIND