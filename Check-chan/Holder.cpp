#include "Holder.hpp"

Holder::Holder(unsigned int id, sf::Texture& counterText, std::map<unsigned int, sf::Color>& colors) :
	id(id),
	counterText(counterText),
	playerColors(colors) {
	HolderShape.setSize(sf::Vector2f(150, 150));
	HolderShape.setFillColor(sf::Color::Transparent);
	//PawnRect.setTexture(&counterText);
	HolderShape.setOrigin(HolderShape.getSize().x / 2.f, HolderShape.getSize().y / 2.f);
	//HolderShape.setPosition(sf::Vector2f(373, 237));
	HolderShape.setPosition(sf::Vector2f(665, 237));

	auto x = HolderShape.getPosition().x;
	auto y = HolderShape.getPosition().y;
	Holder1.setSize(sf::Vector2f(30, 30));
	Holder1.setFillColor(playerColors[id]);
	Holder1.setTexture(&counterText);
	Holder1.setOrigin(15, 15);
	Holder1.setPosition(sf::Vector2f(x-45, y-45));

	Holder2.setSize(sf::Vector2f(30, 30));
	Holder2.setFillColor(playerColors[id]);
	Holder2.setTexture(&counterText);
	Holder2.setOrigin(15, 15);
	Holder2.setPosition(sf::Vector2f(x + 45, y - 45));

	Holder3.setSize(sf::Vector2f(30, 30));
	Holder3.setFillColor(playerColors[id]);
	Holder3.setTexture(&counterText);
	Holder3.setOrigin(15, 15);
	Holder3.setPosition(sf::Vector2f(x - 45, y + 45));

	Holder4.setSize(sf::Vector2f(30, 30));
	Holder4.setFillColor(playerColors[id]);
	Holder4.setTexture(&counterText);
	Holder4.setOrigin(15, 15);
	Holder4.setPosition(sf::Vector2f(x + 45, y + 45));
}

Holder::~Holder() {}

void Holder::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	//auto c = sf::RectangleShape(sf::Vector2f(18, 18));
	if (counters == 1)
	{
		target.draw(Holder1);
	}
	if (counters == 2)
	{
		target.draw(Holder1);
		target.draw(Holder2);
	}
	if (counters == 3)
	{
		target.draw(Holder1);
		target.draw(Holder2);
		target.draw(Holder3);
	}
	if (counters == 4)
	{
		target.draw(Holder1);
		target.draw(Holder2);
		target.draw(Holder3);
		target.draw(Holder4);
	}
	
}

void Holder::setPosition(sf::Vector2f pos) {
	HolderShape.setPosition(pos);
	auto x = HolderShape.getPosition().x;
	auto y = HolderShape.getPosition().y;
	Holder1.setPosition(sf::Vector2f(x - 45, y - 45));
	Holder2.setPosition(sf::Vector2f(x + 45, y - 45));
	Holder3.setPosition(sf::Vector2f(x - 45, y + 45));
	Holder4.setPosition(sf::Vector2f(x + 45, y + 45));
}

void Holder::move(sf::Vector2f offset) {
	HolderShape.move(offset);
}

sf::Vector2f Holder::getPosition() {
	return HolderShape.getPosition();
}
