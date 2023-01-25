#pragma once
#include "../BaseEngine/Tile.hpp"
#include "SFML/Graphics.hpp"
/// <summary>
///  Klasa SfmlTile jest odpowiedzialna za mapowanie poszczeg�lnych p�l do poruszania pionkami. Ma mo�liwo�� rysowania ustalania pozycji oraz rysowania pionk�w
/// </summary>
class SfmlTile : public sf::Drawable{
private:
	Tile& tile;
	sf::Texture& counterText;
	/** Kszta�t zajmuj�cy ca�� powierzchni� pola */
	sf::RectangleShape PawnRect;
	std::map<unsigned int, sf::Color>& playerColors;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:	
	const unsigned int id;
	SfmlTile(Tile& tile, unsigned int, sf::Texture& counterText, std::map<unsigned int, sf::Color>&);
	~SfmlTile();
	/** Pozwala ustawi� obiekt w odpowiednim miejscu */
	void setPosition(sf::Vector2f pos);
	/// <summary>
	/// Pozwala przesun�c obiekt na dane miejsce
	/// </summary>
	/// <param name="offset">Warto�� offsetu</param>
	void move(sf::Vector2f offset);
	/// <summary>
	/// Pobieranie pozycji obiektu
	/// </summary>
	/// <returns></returns>
	sf::Vector2f getPosition();
	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	sf::FloatRect shape() { return PawnRect.getGlobalBounds(); }
	//sf::RectangleShape& operator()();

};
