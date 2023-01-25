#pragma once
#include <SFML/Graphics.hpp>
#include "Counter.hpp"

/// <summary>
/// Klasa Last Tile odpowiedzialne za mapowanie pól koñcowych
/// </summary>
class LastTile : public sf::Drawable
{
	/**Wektor pionków*/
	const std::vector<Counter*>& counters;
	/**Tektura pionka*/
	sf::Texture& counterText;
	/**Kolor pionka*/
	sf::Color counterColor;
	/**Shape kafelka pola koñcowego*/
	sf::RectangleShape tileShape;
	/**Poszczególne pionki*/
	sf::RectangleShape counter, c_h1, c_h2, c_q1, c_q2, c_q3, c_q4;
	/// <summary>
	/// Metoda do rysowania
	/// </summary>
	/// <param name="">Target renderowania</param>
	/// <param name="">State renderowania</param>
	virtual void draw(sf::RenderTarget&, sf::RenderStates)const;
	
public:
	/**Id gracza*/
	const unsigned int id;
	/// <summary>
	/// Konstruktor klasy LastTile
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <param name=""></param>
	LastTile(unsigned int, const std::vector<Counter*>&, sf::Texture&, sf::Color);
	/// <summary>
	/// Funkcja zwracaj¹ca globalne granice
	/// </summary>
	/// <returns></returns>
	sf::FloatRect shape() { return tileShape.getGlobalBounds(); }
	/// <summary>
	/// Funkcja do ustawiania pozycji na ekranie (ostatnich tiles)
	/// </summary>
	/// <param name=""></param>
	void setPosition(sf::Vector2f);
	/// <summary>
	/// Funkcja do pobierania pozycji ostatnich pionków
	/// </summary>
	/// <returns></returns>
	sf::Vector2f getPosition(){ return  counter.getPosition(); }
};

