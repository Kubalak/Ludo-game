#pragma once
#include "../BaseEngine/Tile.hpp"
#include "SFML/Graphics.hpp"

class SfmlTile{
private:
	Tile& tile;
	sf::RectangleShape PawnRect;
	

public:
	SfmlTile(Tile& tile);
	~SfmlTile();
	sf::RectangleShape& operator()();

};
