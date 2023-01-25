#pragma once
#include <SFML/Graphics.hpp>
#include "Counter.hpp"

class LastTile : public sf::Drawable
{
	const std::vector<Counter*>& counters;
	sf::Texture& counterText;
	sf::Color counterColor;
	sf::RectangleShape tileShape;
	sf::RectangleShape counter, c_h1, c_h2, c_q1, c_q2, c_q3, c_q4;
	virtual void draw(sf::RenderTarget&, sf::RenderStates)const;
	
public:
	const unsigned int id;
	LastTile(unsigned int, const std::vector<Counter*>&, sf::Texture&, sf::Color);
	sf::FloatRect shape() { return tileShape.getGlobalBounds(); }
	void setPosition(sf::Vector2f);
	sf::Vector2f getPosition(){ return  counter.getPosition(); }
};

