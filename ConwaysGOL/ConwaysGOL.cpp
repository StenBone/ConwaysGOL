#include <Vector>
#include <SFML/Graphics.hpp>

//namespace cgol { // Conways Game of Life

const std::string  APP_NAME		{ "Conway's Game of Life" };
const sf::Vector2u APP_BOUNDS	{ 800, 600 };
const sf::Vector2i BOARD_BOUNDS	{ 32, 24 };
const sf::Vector2f CELL_SIZE	{ 21.f, 21.f }; // should be a single value, always going to be square
const float		   BORDER_WIDTH	{ 2.f };
const int		   CELLS_HORIZONTAL = (BORDER_WIDTH + CELL_SIZE.x + BORDER_WIDTH) / APP_BOUNDS.x;

// 800 / 25 = 32 cells @ 25 pixels across
// 600 / 25 = 24 cells

struct Cell {
	sf::RectangleShape shape{};
};

//}

int main()
{
	sf::RenderWindow window{ sf::VideoMode{APP_BOUNDS.x, APP_BOUNDS.y}, APP_NAME };

	// INIT BOARD, INIT CELLS
	std::vector<Cell> board{};
	for (int row = 0; row < CELLS_HORIZONTAL; row++) {
		Cell cell;
		cell.shape.setPosition(BORDER_WIDTH + row * (CELL_SIZE.x + BORDER_WIDTH), 0); // Cell position = (index(cell_size + border_width))
		cell.shape.setSize(CELL_SIZE);
		board.push_back(cell);
	}

	while (window.isOpen()) {

		// EVENTS
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