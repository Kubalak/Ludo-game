#include "SfmlTile.hpp"

SfmlTile::SfmlTile(Tile& tile) : tile(tile)
{
	PawnRect.setSize(sf::Vector2f(51, 37));
	PawnRect.setFillColor(sf::Color::Red);
	PawnRect.setPosition(sf::Vector2f(560, 98));
}

SfmlTile::~SfmlTile() {}

sf::RectangleShape& SfmlTile::operator()() {
	return PawnRect;
}
