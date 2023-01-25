#pragma once
#include <SFML/Graphics.hpp>
#include "PlayerContainer.hpp"
#include "LastTile.hpp"

class Last : public sf::Drawable
{
	sf::Texture& counterText;
	/** Kszta³t zajmuj¹cy ca³¹ powierzchniê pola */
	sf::RectangleShape lastShape;
	const PlayerContainer& container;
	std::array<std::unique_ptr<LastTile>, 6> last;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	const unsigned int num;
	Last(unsigned int, const PlayerContainer&, sf::Texture&, sf::Color&);
	const std::array<std::unique_ptr<LastTile>, 6>& getTiles()const { return last; }
	void rotate(sf::Vector2f around, unsigned int q);
};

