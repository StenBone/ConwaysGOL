#include <Map>
#include <iostream>
#include <Vector>
#include <SFML/Graphics.hpp>

//namespace cgol { // Conways Game of Life

const std::string  APP_NAME				{ "Conway's Game of Life" };
const sf::Vector2u APP_BOUNDS			{ 800, 600 };
const sf::Vector2i BOARD_BOUNDS			{ 32, 24 };
const float		   BORDER_SIZE			{ 2.f };
const float		   CELL_SIZE			{ 21.f };
const float		   TOTAL_BORDER_SIZE	{ 2 * BORDER_SIZE };
const float		   BOX_SIZE				{ CELL_SIZE + TOTAL_BORDER_SIZE };
const sf::Color	   CELL_ALIVE_COLOR		{ sf::Color::Black };
const sf::Color	   CELL_DEAD_COLOR		{ sf::Color::White };
const sf::Color	   LINE_COLOR			{ sf::Color::Color(235, 235, 235) };
const float		   CELLS_HORIZONTAL		{ APP_BOUNDS.x / BOX_SIZE }; // cell_index(border_left + cell_width + border_right) = cell_x
const float		   CELLS_VERTICAL		{ APP_BOUNDS.y / BOX_SIZE }; // cell_index(border_left + cell_height + border_right) = cell_y
const sf::Time	   SIMULATION_UPDATE_INTERVAL{ sf::seconds(1.5f) };

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
	sf::RenderWindow window{ sf::VideoMode{ APP_BOUNDS.x, APP_BOUNDS.y }, APP_NAME };
	std::map<std::pair<int, int>, Cell> board{};

	// INIT BOARD, INIT CELLS
	for (int row = 0; row < CELLS_HORIZONTAL; row++) {
		for (int col = 0; col < CELLS_VERTICAL; col++) {
			Cell cell{};
			cell.shape.setFillColor(CELL_DEAD_COLOR);

			int cell_x = (row * (CELL_SIZE + TOTAL_BORDER_SIZE)) + BORDER_SIZE;
			int cell_y = (col * (CELL_SIZE + TOTAL_BORDER_SIZE)) + BORDER_SIZE;

			cell.shape.setPosition(cell_x, cell_y);
			cell.shape.setSize(sf::Vector2f{ CELL_SIZE, CELL_SIZE });
			board[{ row, col }] = cell;
		}
	}

	// GAME LOOP
	while (window.isOpen()) {
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
				int alive_cell_count = 0; // todo de-uglify
				switch (event.key.code) {
				case sf::Keyboard::Space:
					// todo de-uglify
					for (auto& item : board) {
						if (item.second.isalive) {
							alive_cell_count++;
						}
					}

					if (!cell_simulation_running && alive_cell_count > 0) {
						cell_simulation_running = true;
					}
					else {
						cell_simulation_running = false;
						time_since_last_cell_simulation_update = sf::Time::Zero;

					}
					// todo tap space again to restart simulation

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
					if (!cell_simulation_running) {
						sf::Vector2i local_position = sf::Mouse::getPosition(window); // position relative to window
						int row = int(std::floor((local_position.x - BORDER_SIZE) / (CELL_SIZE + TOTAL_BORDER_SIZE)));
						int col = int(std::floor((local_position.y - BORDER_SIZE) / (CELL_SIZE + TOTAL_BORDER_SIZE)));

						if (board.count({ row, col })) {
							auto& cell = board.at(std::pair<int, int>{row, col});
							if (cell.isalive) {
								cell.isalive = false;
								cell.shape.setFillColor(CELL_DEAD_COLOR);
							}
							else {
								cell.isalive = true;
								cell.shape.setFillColor(CELL_ALIVE_COLOR);
							}
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
				time_since_last_cell_simulation_update = sf::Time::Zero;
				std::map<std::pair<int, int>, Cell> updated_board = board;

				for (const auto& item : board) {
					int neighbor_count = 0;
					const auto pair = item.first;
					auto cell = item.second;
					int cell_x = pair.first;
					int cell_y = pair.second;
					// cells have 8 neighbors: NW, N, NE, E, W, SW, S, SE
					for (int x = cell_x - 1; x <= cell_x + 1; x++) {
						for (int y = cell_y - 1; y <= cell_y + 1; y++) {
							if (x == cell_x && y == cell_y) { continue; } // don't count the value of the center as a neighbor

							if (board.count({ x,y })) {
								const auto& neighbor_cell = board.at(std::pair<int, int>{x, y});
								if (neighbor_cell.isalive) {
									neighbor_count++;
								}
							}
						}
					}
					// STAYS ALIVE RULE: cell stays alive if it has 2-3 neighbors
					// REINCARNATE RULE: cell springs to life if it has 3 live neighbors

					// DEATH RULES
					if (cell.isalive) {
						if (neighbor_count < 2) {
							auto& cell_to_kill{ updated_board[pair] };
							cell_to_kill.isalive = false;
							cell_to_kill.shape.setFillColor(CELL_DEAD_COLOR);
							std::cout << "Cell at x:" << cell_x << " y:" << cell_y << " dies of loneliness." << std::endl;
						}
						else if (neighbor_count > 3) {
							auto& cell_to_kill{ updated_board[pair] };
							cell_to_kill.isalive = false;
							cell_to_kill.shape.setFillColor(CELL_DEAD_COLOR);
							std::cout << "Cell at x:" << cell_x << " y:" << cell_y << " dies of over crowding." << std::endl;
						}
					}
					// RIENCARNATION RULES
					else {
						if (neighbor_count == 3) {
							auto& cell_to_reincarnate{ updated_board[pair] };
							cell_to_reincarnate.isalive = true;
							cell_to_reincarnate.shape.setFillColor(CELL_ALIVE_COLOR);
						}
					}
				}
				board = updated_board;
			}
		}

		// RENDER
		window.clear(LINE_COLOR);
		for (const auto& item : board) {
			window.draw(item.second.shape);
		}
		window.display();
	}
	return EXIT_SUCCESS;
} // BE KIND


// todo JT pass
// todo refactor into classes
// todo refactor into functions
// todo infinite board, cells don't die on the side of the screen
// todo scroll with arrow keys to move around
// todo resize window
// todo json config loader

