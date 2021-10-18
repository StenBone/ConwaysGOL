#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Conway's Game of Life");
	sf::RectangleShape box(sf::Vector2f(20.f, 20.f));

	while (window.isOpen()) {
		
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