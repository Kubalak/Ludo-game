#include "Last.hpp"
#include <numbers>

Last::Last(unsigned int num, const PlayerContainer& pc, sf::Texture& counter, sf::Color& color):
	num(num),
	container(pc),
	counterText(counter) {

	lastShape.setFillColor(sf::Color::White);
	lastShape.setSize(sf::Vector2f(36, 216));
	lastShape.setOrigin(sf::Vector2f(18, 108));
	lastShape.setPosition(sf::Vector2f(518, 200));

	auto x = lastShape.getPosition().x;
	auto y = lastShape.getPosition().y;

	auto& lastTiles = container.getLast();
	for (unsigned int i{ 0 }; i < 6; ++i) {
		last[i] = std::make_unique<LastTile>(i + 1, lastTiles[i], counterText, color);
		last[i]->setPosition(sf::Vector2f(x, y + (static_cast<int>(i) - 2) * 43));
	}
	last[5]->setPosition(sf::Vector2f(x, y + 140));
}

void Last::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	//target.draw(lastShape);
	for (auto& l : last)
		target.draw(*l);
}

void Last::rotate(sf::Vector2f around, unsigned int q) {
	float rad = 90 * q  * 3.141592653589793238463 / 180.0f;
	float s = sin(rad);
	float c = cos(rad);
	for (auto& l : last) {
		float px = l->getPosition().x;
		float py = l->getPosition().y;
		float ox = around.x;
		float oy = around.y;
		float x = (px - ox) * c - (py - oy) * s + ox;
		float y = (px - ox) * s + (py - oy) * c + oy;
		l->setPosition(sf::Vector2f(x, y));
	}
}