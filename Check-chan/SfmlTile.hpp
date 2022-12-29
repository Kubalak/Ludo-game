#pragma once
#include "../BaseEngine/Tile.hpp"
#include "SFML/Graphics.hpp"

class SfmlTile : public sf::Drawable{
private:
	Tile& tile;
	sf::Texture& counterText;
	/** Kszta³t zajmuj¹cy ca³¹ powierzchniê pola */
	sf::RectangleShape PawnRect;
	std::map<unsigned int, sf::Color>& playerColors;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	SfmlTile(Tile& tile, sf::Texture& counterText, std::map<unsigned int, sf::Color>&);
	~SfmlTile();
	/** Pozwala ustawiæ obiekt w odpowiednim miejscu */
	void setPosition(sf::Vector2f pos);
	void move(sf::Vector2f offset);
	sf::Vector2f getPosition();
	//sf::RectangleShape& operator()();

};
