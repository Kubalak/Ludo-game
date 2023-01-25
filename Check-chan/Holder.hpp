#pragma once
#include "SFML/Graphics.hpp"
/// <summary>
/// Klasa Holder jest odpowiedzialna za domki pocz¹tkowe dla pionków poszczególnych graczy.
/// </summary>
class Holder : public sf::Drawable {
private:
	/** Tektura pionka */
	sf::Texture& counterText;
	/** Kszta³t zajmuj¹cy ca³¹ powierzchniê pola */
	sf::RectangleShape HolderShape;
	/** Kszta³t pionka nr 1 */
	sf::RectangleShape Holder1;
	/** Kszta³t pionka nr 2 */
	sf::RectangleShape Holder2;
	/** Kszta³t pionka nr 3 */
	sf::RectangleShape Holder3;
	/** Kszta³t pionka nr 4 */
	sf::RectangleShape Holder4;
	/** Mapa kolorami graczy <id_gracza, kolor> */
	std::map<unsigned int, sf::Color>& playerColors;
	/// <summary>
	/// Funkcja do rysowania Shape domków i pionków 
	/// </summary>
	/// <param name="target"> Render target</param>
	/// <param name="states"> Render state</param>
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	/** id gracza*/
	const unsigned int id;
	/** licznik liczby pionków graczy*/
	unsigned int counters;
	Holder(unsigned int, sf::Texture& counterText, std::map<unsigned int, sf::Color>&);
	~Holder();
	/** Pozwala ustawiæ obiekt w odpowiednim miejscu */
	void setPosition(sf::Vector2f pos);
	/** Pozwala przestawiæ obiekt na odpowiednie miejsce */
	void move(sf::Vector2f offset);
	/** Pozwala pobraæ pozycje obiektu*/
	sf::Vector2f getPosition();
	sf::FloatRect shape() { return HolderShape.getGlobalBounds(); }
	//sf::HolderShape& operator()();

};

