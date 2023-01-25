#pragma once
#include "SFML/Graphics.hpp"
/// <summary>
/// Klasa Holder jest odpowiedzialna za domki pocz�tkowe dla pionk�w poszczeg�lnych graczy.
/// </summary>
class Holder : public sf::Drawable {
private:
	/** Tektura pionka */
	sf::Texture& counterText;
	/** Kszta�t zajmuj�cy ca�� powierzchni� pola */
	sf::RectangleShape HolderShape;
	/** Kszta�t pionka nr 1 */
	sf::RectangleShape Holder1;
	/** Kszta�t pionka nr 2 */
	sf::RectangleShape Holder2;
	/** Kszta�t pionka nr 3 */
	sf::RectangleShape Holder3;
	/** Kszta�t pionka nr 4 */
	sf::RectangleShape Holder4;
	/** Mapa kolorami graczy <id_gracza, kolor> */
	std::map<unsigned int, sf::Color>& playerColors;
	/// <summary>
	/// Funkcja do rysowania Shape domk�w i pionk�w 
	/// </summary>
	/// <param name="target"> Render target</param>
	/// <param name="states"> Render state</param>
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	/** id gracza*/
	const unsigned int id;
	/** licznik liczby pionk�w graczy*/
	unsigned int counters;
	/// <summary>
	/// Konstruktor klasy Holder
	/// </summary>
	/// <param name="">Id gracza</param>
	/// <param name="counterText">Tekstura</param>
	/// <param name="">mapa <id, kolor></param>
	Holder(unsigned int, sf::Texture& counterText, std::map<unsigned int, sf::Color>&);
	~Holder();
	/// <summary>
	/// Funkcja ustawia obiekt w pozycji
	/// </summary>
	/// <param name="pos"></param>
	void setPosition(sf::Vector2f pos);
	/// <summary>
	/// Pozwala przestwaic obiekt w odpowiednie miejsce
	/// </summary>
	/// <param name="offset"></param>
	void move(sf::Vector2f offset);
	/** Pozwala pobra� pozycje obiektu*/
	sf::Vector2f getPosition();
	sf::FloatRect shape() { return HolderShape.getGlobalBounds(); }

};

