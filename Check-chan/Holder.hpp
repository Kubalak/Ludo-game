#pragma once
#include "SFML/Graphics.hpp"

class Holder : public sf::Drawable {
private:
	sf::Texture& counterText;
	/** Kszta³t zajmuj¹cy ca³¹ powierzchniê pola */
	sf::RectangleShape HolderShape;
	sf::RectangleShape Holder1;
	sf::RectangleShape Holder2;
	sf::RectangleShape Holder3;
	sf::RectangleShape Holder4;
	std::map<unsigned int, sf::Color>& playerColors;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	const unsigned int id;
	unsigned int counters;
	Holder(unsigned int, sf::Texture& counterText, std::map<unsigned int, sf::Color>&);
	~Holder();
	/** Pozwala ustawiæ obiekt w odpowiednim miejscu */
	void setPosition(sf::Vector2f pos);
	void move(sf::Vector2f offset);
	sf::Vector2f getPosition();
	sf::FloatRect shape() { return HolderShape.getGlobalBounds(); }
	//sf::HolderShape& operator()();

};

