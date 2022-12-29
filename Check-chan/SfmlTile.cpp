#include "SfmlTile.hpp"

SfmlTile::SfmlTile(Tile& tile, sf::Texture& counterText, std::map<unsigned int, sf::Color>& colors) :
	tile(tile), 
	counterText(counterText),
	playerColors(colors) {
	PawnRect.setSize(sf::Vector2f(36, 36));
	PawnRect.setFillColor(sf::Color::Transparent);
	//PawnRect.setTexture(&counterText);
	PawnRect.setOrigin(PawnRect.getSize().x / 2.f, PawnRect.getSize().y / 2.f);
	PawnRect.setPosition(sf::Vector2f(560, 120));
}

SfmlTile::~SfmlTile() {}

void SfmlTile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	//target.draw(PawnRect);
	auto counts = tile.getPlayersCount();
	auto total = tile.getCounters().size();
	if (total) {
		auto c = sf::RectangleShape(sf::Vector2f(18, 18));
		c.setOrigin(9, 9);
		unsigned int index = 0;
		for (auto& count : counts) {
			c.setFillColor(playerColors[count.first]);
			c.setTexture(&counterText);
			if (total < 2) {
				c.setPosition(PawnRect.getPosition());
				target.draw(c);
			}
			else if (total == 2) {
				auto pos = PawnRect.getPosition();
				for (unsigned int j = 0; j < count.second; ++j) {
					c.setPosition(pos.x - 9 + (index + j) * 18, pos.y);
					target.draw(c);
				}
			}
			else if (total <= 4) {
				auto pos = PawnRect.getPosition();
				for (unsigned int j = 0; j < count.second; ++j) {
					c.setPosition(pos.x - 9 + static_cast<int>((index + j) % 2) * 18, pos.y - 9 + static_cast<int>((index + j) / 2) * 18);
					target.draw(c);
				}
			}
			else {
				auto pos = PawnRect.getPosition();
				c.setPosition(pos.x - 9 + static_cast<int>(index % 2) * 18, pos.y - 9 + static_cast<int>(index  / 2) * 18);
				target.draw(c);
			}
			++index;
		}
	}

}

void SfmlTile::setPosition(sf::Vector2f pos) {
	PawnRect.setPosition(pos);
}

void SfmlTile::move(sf::Vector2f offset) {
	PawnRect.move(offset);
}

sf::Vector2f SfmlTile::getPosition() {
	return PawnRect.getPosition();
}

//sf::RectangleShape& SfmlTile::operator()() {
//	return PawnRect;
//}
