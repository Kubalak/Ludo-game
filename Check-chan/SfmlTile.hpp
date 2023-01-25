#pragma once
#include "../BaseEngine/Tile.hpp"
#include "SFML/Graphics.hpp"
/// <summary>
///  Klasa SfmlTile jest odpowiedzialna za mapowanie poszczególnych pól do poruszania pionkami. Ma mo¿liwoœæ rysowania ustalania pozycji oraz rysowania pionków
/// </summary>
class SfmlTile : public sf::Drawable{
private:
	/**Referencja na obiekt Tile*/
	Tile& tile;
	/**Tekstura pionka*/
	sf::Texture& counterText;
	/** Kszta³t zajmuj¹cy ca³¹ powierzchniê pola */
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
	/** Pozwala ustawiæ obiekt w odpowiednim miejscu */
	void setPosition(sf::Vector2f pos);
	/// <summary>
	/// Pozwala przesun¹c obiekt na dane miejsce
	/// </summary>
	/// <param name="offset">Wartoœæ offsetu</param>
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
