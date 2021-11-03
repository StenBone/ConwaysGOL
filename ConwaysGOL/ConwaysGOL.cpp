#include <Map>
#include <Vector>
#include <SFML/Graphics.hpp>

//namespace cgol { // Conways Game of Life

const std::string  APP_NAME				{ "Conway's Game of Life" };
const sf::Vector2u APP_BOUNDS			{ 800, 600 };
const sf::Vector2i BOARD_BOUNDS			{ 32, 24 };
const float		   BORDER_SIZE			{ 2.f };
const float		   BOX_SIZE				{ CELL_SIZE + TOTAL_BORDER_SIZE };
const sf::Color	   CELL_ALIVE_COLOR		{ sf::Color::Green };
const sf::Color	   CELL_DEAD_COLOR		{ sf::Color::Black };
const float		   CELL_SIZE			{ 21.f }; // should be a single value, always going to be square
const float		   CELLS_HORIZONTAL		{ APP_BOUNDS.x / BOX_SIZE }; // cell_index(border_left + cell_width + border_right) = cell_x
const float		   CELLS_VERTICAL		{ APP_BOUNDS.y / BOX_SIZE }; // cell_index(border_left + cell_height + border_right) = cell_y
const sf::Time	   SIMULATION_UPDATE_INTERVAL{ sf::seconds(3.f) };
const float		   TOTAL_BORDER_SIZE	{ 2 * BORDER_SIZE };

// 800 / 25 = 32 cells @ 25 pixels across
// 600 / 25 = 24 cells

struct Cell {
	bool isalive = false;
	sf::RectangleShape shape{};
};

//}

int main()
{
	bool cell_simulation_running{ false };
	sf::Clock clock{};
	sf::Time delta_time{};
	sf::Time time_since_last_cell_simulation_update{};
	sf::RenderWindow window{ sf::VideoMode{APP_BOUNDS.x, APP_BOUNDS.y}, APP_NAME };
	std::map<std::pair<int, int>, Cell> board{};


	// INIT BOARD, INIT CELLS
	for (int row = 0; row < CELLS_HORIZONTAL; row++) {
		for (int col = 0; col < CELLS_VERTICAL; col++) {
			Cell cell;
			cell.shape.setFillColor(CELL_DEAD_COLOR);

			int cell_x = (row * (CELL_SIZE + TOTAL_BORDER_SIZE)) + BORDER_SIZE;
			int cell_y = (col * (CELL_SIZE + TOTAL_BORDER_SIZE)) + BORDER_SIZE;

			cell.shape.setPosition(cell_x, cell_y);
			cell.shape.setSize(sf::Vector2f{ CELL_SIZE, CELL_SIZE });
			board[{ row, col }] = cell;
		}
	}

	while (window.isOpen()) {
		// TIME MANAGEMENT
		delta_time = clock.restart();

		// EVENTS AND INPUT
		sf::Event event {};
		while (window.pollEvent(event)) {

			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;

			// KEY RELEASED
			case sf::Event::KeyReleased: {
				switch (event.key.code) {
				case sf::Keyboard::Space:
					//if at the start of the gameand some cells are picked, start game
					break;

				default:
					break;
				}
			} 
			break;

			// MOUSE BUTTON RELEASED
			case sf::Event::MouseButtonReleased:
				switch (event.mouseButton.button)
				{
				case sf::Mouse::Button::Left:
					sf::Vector2i local_position = sf::Mouse::getPosition(window); // position relative to window
					int row = int(std::floor((local_position.x - BORDER_SIZE) / (CELL_SIZE + TOTAL_BORDER_SIZE)));
					int col = int(std::floor((local_position.y - BORDER_SIZE) / (CELL_SIZE + TOTAL_BORDER_SIZE)));
					
					if (board.count({ row, col })) {
						auto cell = board.at(std::pair<int, int>{row, col});
						if (cell.isalive) {
							cell.isalive = false;
							cell.shape.setFillColor(CELL_DEAD_COLOR);
						}
						else {
							cell.isalive = true;
							cell.shape.setFillColor(CELL_ALIVE_COLOR);
						}
					}
					break;
				default:
					break;
				} // switch (event.mouseButton.button)

			default:
				break;
			} // switch (event.type)
		} // while (window.pollEvent(event))

		// UPDATE BOARD
		if (cell_simulation_running) {
			time_since_last_cell_simulation_update += delta_time;

			if (time_since_last_cell_simulation_update >= SIMULATION_UPDATE_INTERVAL) {
				//update board -> run board rules, for all cell in Cells{ run rules against its neighbors, check if empty neighbors should live, if cell should die }
			}
		}

		// RENDER
		window.clear(sf::Color::Black);
		loop through map of all cells and draw them. 
		for (Cell cell : board) {
			window.draw(cell.shape);
		}
		window.display();
	}
	return EXIT_SUCCESS;
} // BE KIND