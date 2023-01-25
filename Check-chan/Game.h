#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "../BaseEngine/Engine.hpp"
#include "SfmlTile.hpp"
#include "Holder.hpp"
#include "locale"

#define MAX_NUMBER_OF_ITEMS 3
#define MAX_NUMBER_OF_ITEMS 3

/// <summary>
/// Klasa Game odpowiedzialna jest za wszystkie elementy graficzne oraz poszczeg�lne stany projektu
/// </summary>
class Game {
private:
    /**
    Okno do renderowania element�w gry.
    */
    sf::RenderWindow mWindow;
    /**
    Zmienna okre�laj�ca aktualny index pola w g��wnym menu gry.
    */
    int selectedItemIndexMenu;
    /**
    Zmienna okre�laj�ca aktualny index pola w opcjach gry.
    */
    int selectedItemIndexOptions;
    /**
    Zmienna okre�laj�ca warto�c aktualnego rzutu kostk�.
    */
    int diceRoll;
    /**
    String aktualnego tekstu w opcjach
    */
    std::string currentText;
    /**
    String do zmiany nazwy gracza w turze.
    */
    std::string PlayerText;
    /**
    String wprowadzonego tekstu.
    */
    std::string input_text;
    /**
    Czczionka gry (FONT SFML)
    */
    sf::Font font;
    /**
    Text SFML okre�laj�cy nazwe aktualnego gracza.
    */
    sf::Text CurrentPlayerText;
    /**
    Text SFML z ilo�cia mo�liwo�ci w g��wnym menu gry.
    */
    sf::Text MainMenuText[MAX_NUMBER_OF_ITEMS];
    /**
    Text SFML z ilo�cia mo�liwo�ci w opcjach menu gry.
    */
    sf::Text OptionsText[MAX_NUMBER_OF_ITEMS];
    /**
    Text SFML obrazuj�cy znaki wpisane przez gracza.
    */
    sf::Text text;
    /**
    SFML Rectangle t�a.
    */
    sf::RectangleShape Background;
    /**
    SFML Rectangle planszy gry.
    */
    sf::RectangleShape BoardBackground;
    /**
    SFML Rectangle kostki do gry.
    */
    sf::RectangleShape diceShape;
    /**
    SFML Circle shape jednego oczka kostki.
    */
    sf::CircleShape r_1;
    /**
    SFML Circle shape pierwszy dla dw�ch oczek kostki.
    */
    sf::CircleShape r_2_1;
    /**
    SFML Circle shape drugi dla dw�ch oczek kostki.
    */
    sf::CircleShape r_2_2;
    /**
    SFML Circle shape pierwszy dla trzech oczek kostki.
    */
    sf::CircleShape r_3_1;
    /**
    SFML Circle shape drugi dla trzech oczek kostki.
    */
    sf::CircleShape r_3_2;
    /**
    SFML Circle shape trzeci dla trzech oczek kostki.
    */
    sf::CircleShape r_3_3;
    /**
    SFML Circle shape pierwszy dla czterech oczek kostki.
    */
    sf::CircleShape r_4_1;
    /**
    SFML Circle shape drugi dla czterech oczek kostki.
    */
    sf::CircleShape r_4_2;
    /**
    SFML Circle shape trzeci dla czterech oczek kostki.
    */
    sf::CircleShape r_4_3;
    /**
    SFML Circle shape czwarty dla czterech oczek kostki.
    */
    sf::CircleShape r_4_4;
    /**
    SFML Circle shape pierwszy dla pi�ciu oczek kostki.
    */
    sf::CircleShape r_5_1;
    /**
    SFML Circle shape drugi dla pi�ciu oczek kostki.
    */
    sf::CircleShape r_5_2;
    /**
    SFML Circle shape trzeci dla pi�ciu oczek kostki.
    */
    sf::CircleShape r_5_3;
    /**
    SFML Circle shape czwarty dla pi�ciu oczek kostki.
    */
    sf::CircleShape r_5_4;
    /**
    SFML Circle shape pi�ty dla pi�ciu oczek kostki.
    */
    sf::CircleShape r_5_5;
    /**
    SFML Circle shape pierwszy dla sze�ciu oczek kostki.
    */
    sf::CircleShape r_6_1;
    /**
    SFML Circle shape drugi dla sze�ciu oczek kostki.
    */
    sf::CircleShape r_6_2;
    /**
    SFML Circle shape trzeci dla sze�ciu oczek kostki.
    */
    sf::CircleShape r_6_3;
    /**
    SFML Circle shape czwarty dla sze�ciu oczek kostki.
    */
    sf::CircleShape r_6_4;
    /**
    SFML Circle shape pi�ty dla sze�ciu oczek kostki.
    */
    sf::CircleShape r_6_5;
    /**
    SFML Circle shape sz�sty dla sze�ciu oczek kostki.
    */
    sf::CircleShape r_6_6;
    /**
    SFML Tekstury t�a, planszy, pionka.
    */
    sf::Texture Texture, BoardTexture, counterTexture;
    /**
    Sprite planszy do gry.
    */
    sf::Sprite boardImg;
    /**
    Muzyka gry w tle.
    */
    sf::Music music;
    /**
    Mapa <id_gracza, kolor pionka>.
    */
    std::map<unsigned int, sf::Color> playerColors;
    /**
    Pozycja myszki wzgl�dem ekranu.
    */
    sf::Vector2i mousePosScreen;
    /**
    Pozycja myszki wzgl�dem okna.
    */
    sf::Vector2i mousePosWindow;
    /**
    Pozycja myszki wzgl�dem widoku.
    */
    sf::Vector2f mousePosView;
    /**
    Referencja na obiekt silnika gry.
    */
    Engine& engine;

    /**
    array z kafelkami p�l do poruszania na planszy (pocz�tkowe 52).
    */
    std::array<SfmlTile*, 52> tiles;
    /**
    Mapa <id_gracza, jego domek z pionkami>.
    */
    std::map<unsigned int, Holder*> playerHolders;

    /**
    klasa Enum stanu gry (G��wne menu, opcje, Gra, Koniec gry).
    */
    enum class GameState {
        MainMenu,
        Options,
        MainGame,
        GameOver
    };
    
    /**
    obiekt Enum aktualnego stanu gry.
    */
    GameState mCurrentState;
   
public:
    Game(Engine& engine);
    ~Game();
    int run();
    int handleEvents();
    int updateGame();
    int draw();
    int drawMenuContent();
    int drawOptionsContent();
    int drawGameContent();
    void MoveUp();
    void MoveDown();
    void UpdateMousePos();
    void drawDice(int val);
    sf::Vector2f rotate(sf::Vector2f position, sf::Vector2f around, float rad);
    sf::Vector2f rotate(float x, float y, float ox, float oy, float rad);
    Game::GameState GetPressedItem();
};

