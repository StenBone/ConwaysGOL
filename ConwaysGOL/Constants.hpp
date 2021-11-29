#include <string>
#include <SFML/Graphics.hpp>

namespace CGOL {
	/* app constants */
	const std::string  APP_NAME{ "Conway's Game of Life" };
	const sf::Vector2u APP_BOUNDS{ 800, 600 };
	/* board constants */
	const sf::Vector2i BOARD_BOUNDS{ 32, 24 };
	const float		   BORDER_SIZE{ 2.f };
	const sf::Color	   LINE_COLOR{ sf::Color::Color(235, 235, 235) };
	const float		   CELLS_HORIZONTAL{ APP_BOUNDS.x / BOX_SIZE }; // cell_index(border_left + cell_width + border_right) = cell_x
	const float		   CELLS_VERTICAL{ APP_BOUNDS.y / BOX_SIZE }; // cell_index(border_left + cell_height + border_right) = cell_y
	/* cell constants*/
	const float		   CELL_SIZE{ 21.f };
	const float		   TOTAL_BORDER_SIZE{ 2 * BORDER_SIZE };
	const float		   BOX_SIZE{ CELL_SIZE + TOTAL_BORDER_SIZE };
	const sf::Color	   CELL_ALIVE_COLOR{ sf::Color::Black };
	const sf::Color	   CELL_DEAD_COLOR{ sf::Color::White };
	/* simulation constants */
	const sf::Time	   SIMULATION_UPDATE_INTERVAL{ sf::seconds(1.5f) };
}