#include "LastTile.hpp"

LastTile::LastTile(unsigned int id, const std::vector<Counter*>& counters, sf::Texture& counterText, sf::Color color):
	id(id),
	counters(counters),
	counterText(counterText),
	counterColor(color) {

	tileShape.setFillColor(sf::Color::Red);
	tileShape.setSize(sf::Vector2f(36, 36));
	tileShape.setOrigin(sf::Vector2f(18, 18));

	counter.setTexture(&counterText);
	counter.setFillColor(color);
	counter.setSize(sf::Vector2f(18, 18));
	counter.setOrigin(sf::Vector2f(9, 9));

	c_h1 = c_h2 = c_q1 = c_q2 = c_q3 = c_q4 = counter;
}

void LastTile::setPosition(sf::Vector2f position) {
	tileShape.setPosition(position);
	counter.setPosition(position);
	auto x = position.x;
	auto y = position.y;
	c_h1.setPosition(sf::Vector2f(x - 9, y));
	c_h2.setPosition(sf::Vector2f(x + 9, y));
	c_q1.setPosition(sf::Vector2f(x - 9, y - 9));
	c_q2.setPosition(sf::Vector2f(x + 9, y - 9));
	c_q3.setPosition(sf::Vector2f(x - 9, y + 9));
	c_q4.setPosition(sf::Vector2f(x + 9, y + 9));
}

void LastTile::draw(sf::RenderTarget& rt, sf::RenderStates rs)const {
	
	sf::RectangleShape tmp = counter;
	unsigned int size = counters.size();
	if (size == 1) {
		rt.draw(counter);
	}
	else if (size == 2) {
		rt.draw(c_h1);
		rt.draw(c_h2);
	}
	else if (size == 3) {
		rt.draw(c_q1);
		rt.draw(c_q2);
		rt.draw(c_q3);
	}
	else if (size == 4) {
		rt.draw(c_q1);
		rt.draw(c_q2);
		rt.draw(c_q3);
		rt.draw(c_q4);
	}
}