#include <Vector>
#include <SFML/Graphics.hpp>

//namespace cgol { // Conways Game of Life

const std::string  APP_NAME				{ "Conway's Game of Life" };
const sf::Vector2u APP_BOUNDS			{ 800, 600 };
const sf::Vector2i BOARD_BOUNDS			{ 32, 24 };
const float		   CELL_SIZE			{ 21.f }; // should be a single value, always going to be square
const float		   BORDER_SIZE			{ 2.f };
const float		   TOTAL_BORDER_SIZE	{ 2 * BORDER_SIZE };
const float		   BOX_SIZE				{ CELL_SIZE + TOTAL_BORDER_SIZE };
const float		   CELLS_HORIZONTAL		{ APP_BOUNDS.x / BOX_SIZE }; // cell_index(border_left + cell_width + border_right) = cell_x
const float		   CELLS_VERTICAL		{ APP_BOUNDS.y / BOX_SIZE }; // cell_index(border_left + cell_height + border_right) = cell_y

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
		for (int col = 0; col < CELLS_VERTICAL; col++) {
			Cell cell;
			cell.shape.setPosition(
									(row * (CELL_SIZE + TOTAL_BORDER_SIZE)) + BORDER_SIZE, 
									(col * (CELL_SIZE + TOTAL_BORDER_SIZE)) + BORDER_SIZE
								);
			cell.shape.setSize(sf::Vector2f{ CELL_SIZE, CELL_SIZE });
			board.push_back(cell);
		}
	}

	while (window.isOpen()) {

		// EVENTS
		sf::Event event {};
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