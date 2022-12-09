#include "SfmlTile.hpp"

SfmlTile::SfmlTile(Tile& tile) : tile(tile)
{
	PawnRect.setSize(sf::Vector2f(36, 36));
	PawnRect.setFillColor(sf::Color::Red);
	PawnRect.setOrigin(PawnRect.getSize().x / 2.f, PawnRect.getSize().y / 2.f);
	PawnRect.setPosition(sf::Vector2f(560, 120));
}

SfmlTile::~SfmlTile() {}

sf::RectangleShape& SfmlTile::operator()() {
	return PawnRect;
}
