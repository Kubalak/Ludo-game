#pragma once
#include "../BaseEngine/Tile.hpp"
#include "SFML/Graphics.hpp"
/// <summary>
///  Klasa SfmlTile jest odpowiedzialna za mapowanie poszczeg�lnych p�l do poruszania pionkami. Ma mo�liwo�� rysowania ustalania pozycji oraz rysowania pionk�w
/// </summary>
class SfmlTile : public sf::Drawable{
private:
	/**Referencja na obiekt Tile*/
	Tile& tile;
	/**Tekstura pionka*/
	sf::Texture& counterText;
	/** Kszta�t zajmuj�cy ca�� powierzchni� pola */
	sf::RectangleShape PawnRect;
	/**Mapa z kolorami graczy <id,color>*/
	std::map<unsigned int, sf::Color>& playerColors;
	/// <summary>
	/// Funkcja do rysowania tiles
	/// </summary>
	/// <param name="target">Target renderingu</param>
	/// <param name="states">State renderingu</param>
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:

	const unsigned int id;
	/// <summary>
	/// Konstruktor klasy SfmlTile
	/// </summary>
	/// <param name="tile">Referencja na Tile</param>
	/// <param name="">ID</param>
	/// <param name="counterText">Tekstura pionka</param>
	/// <param name="">Mapa(id,color)></param>
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
