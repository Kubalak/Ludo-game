#pragma once
#include <SFML/Graphics.hpp>
#include "PlayerContainer.hpp"
#include "LastTile.hpp"
/// <summary>
/// Klasa do mapowania pól koñcowych graczy
/// </summary>
class Last : public sf::Drawable
{
	/** Teksturka pionka*/
	sf::Texture& counterText;
	/** Kszta³t zajmuj¹cy ca³¹ powierzchniê pola */
	sf::RectangleShape lastShape;
	/** Kontener gracza*/
	const PlayerContainer& container;
	/** Tablica z ostatnimy(6) polami gracza*/
	std::array<std::unique_ptr<LastTile>, 6> last;
	/// <summary>
	/// Funkcja rysujac¹ 
	/// </summary>
	/// <param name="target"> Cel rysowania</param>
	/// <param name="states"> State rysowania</param>
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	const unsigned int num;
	/// <summary>
	/// Konstuktor klasy Last
	/// </summary>
	/// <param name="">Id gracza</param>
	/// <param name="">Referencja na ostatnie pola</param>
	/// <param name="">Tekstura</param>
	/// <param name="">Kolor</param>
	Last(unsigned int, const PlayerContainer&, sf::Texture&, sf::Color&);
	/// <summary>
	/// Array z ostatnimi polami (6 pól) zwraca last
	/// </summary>
	/// <returns></returns>
	const std::array<std::unique_ptr<LastTile>, 6>& getTiles()const { return last; }
	/// <summary>
	/// Funkcja do obrotu wzglêdem œrodka
	/// </summary>
	/// <param name="around">Wspó³rzêdne</param>
	/// <param name="q">Który quater</param>
	void rotate(sf::Vector2f around, unsigned int q);
};

