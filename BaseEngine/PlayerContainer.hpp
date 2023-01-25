#pragma once
#include "Player.hpp"

/**
* Klasa przechowuj�ca gracza wraz z pionkami w domku.
* @author Jakub Jach &copy; 2023
*/

class PlayerContainer
{
	/** Wska�nik do gracza, kt�ry ma by� przechowany. */
	Player* player;
	/** Pozycja pocz�tkowa na planszy */
	unsigned int startPos;
	
	std::vector<Counter*> holder;
	/** Lista z pionkami na ko�cowych polach */
	std::array<std::vector<Counter*>, 6>last;
public:
	/**
	* @param p Wska�nik na gracza, dla kt�rego tworzony jest obiekt.
	* @param startPos Pozycja pocz�tkowa na planszy.
	*/
	PlayerContainer(Player* p, unsigned int startPos);
	/**
	* Umo�liwia stworzenie obiektu na podstawie obiektu JSON.
	* @param obj Obiekt, na kt�rego podstawie stworzy� obiekt.
	*/
	PlayerContainer(nlohmann::json);
	~PlayerContainer();
	/** Usuwa jeden pionek z zasobnika na pionki.
	* @return Wska�nik na pionek lub nullptr je�li pusty.
	*/
	Counter* holderPop();
	/** Pozwala na dodanie pionka do zasobnika na pionki.
	* @param c Wska�nik na pionek do dodania.
	* @return true je�li dodanie zako�czy si� powodzeniem lub false je�li pionek znajduje si� w zasobniku.
	*/
	bool addToHolder(Counter* c);
	/** Pozwala na dodanie pionka do 6 ostatnich p�l na planszy.
	* @param c Wska�nik na pionek do dodania.
	* @param offset Przesuni�cie wzgl�dem pocz�tku (domy�lnie 0).
	* @return true je�li dodanie si� powiedzie lub false je�li pionek znajduje si� ju� na wybranym polu.
	*/
	bool addToLast(Counter* c, unsigned int offset = 0);
	/** Przesuwa pionek na wybranym polu o wskazan� liczb� p�l.
	* @param fieldNo Nr pola, z kt�rego nale�y przenie�� pionek.
	* @param offset Liczba p�l, o kt�r� przenoszony jest pionek.
	*/
	bool moveOnLast(unsigned int fieldNo, unsigned int offset);
	/**
	* @return Liczba pionk�w w zasobniku.
	*/
	unsigned int holderCount() { return static_cast<unsigned int>(holder.size()); }
	/**
	* @param fieldNo Nr pola, z kt�rego ma pobra� ilo�� pionk�w.
	* @return Liczba pionk�w na polu podanym w parametrze.
	*/
	unsigned int lastCount(unsigned int fieldNo);
	/** Zwraca liczb� pionk�w na ka�dym z p�l
	* @return Tablica z liczb� pionk�w na ka�dym z p�l
	*/
	std::array<unsigned int, 6> getLastCount();
	/**
	* @return Referencja do gracza.
	*/
	Player& getPlayer() { return *player; }
	/**
	* @return Wska�nik do obiektu gracza.
	*/
	Player* getPlayerPtr() noexcept { return player; }
	/**
	* Zwraca referencj� do domku.
	* @return Referencja do domku.
	*/
	std::vector<Counter*>& getHolder() { return holder; }
	/**
	* Zwraca ostatnie pola.
	* @return Tablica z list� pionk�w na ko�cowych polach.
	*/
	const std::array<std::vector<Counter*>, 6>& getLast() const { return last; }
	/**
	* @return Pozycja startowa na planszy.
	*/
	unsigned int getStartPos() { return startPos; }
	/**
	* @return Informacja czy gracz zako�czy� rozgrywk�.
	*/
	bool allIn();
	/** Zwraca informacj� czy gracz mo�e si� porusza� po planszy.
	* @return Informacja czy pionek znajduje si� na planszy i nie na ko�cu.
	*/
	bool canMove() { return holder.size() + last[5].size() != 4; }

	/**
	* Umo�liwia przekierowanie do strumienia.
	* Wyj�cie w postaci takiej jak metoda json()
	* @param os Strumie� wyj�ciowy
	* @param e Obiekt PlayerContainer, kt�ry ma zosta� przekierowany do strumienia.
	* @return Strumie� os.
	*/
	friend std::ostream& operator<< (std::ostream& os, const PlayerContainer& e);
	/**
	* Zwraca reprezentacj� obiektu w bardziej czytelnej postaci.
	* @return Reprezentacja obiektu jako std::string.
	*/
	std::string str();
	/**
	* Zwraca obiekt w postaci tekstu JSON.
	* @return Reprezentacja w postaci JSON.
	*/
	std::string json();

};


