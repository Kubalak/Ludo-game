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
/// Klasa Game odpowiedzialna jest za wszystkie elementy graficzne oraz poszczególne stany projektu
/// </summary>
class Game {
private:
    /**
    Okno do renderowania elementów gry.
    */
    sf::RenderWindow mWindow;
    /**
    Zmienna okreœlaj¹ca aktualny index pola w g³ównym menu gry.
    */
    int selectedItemIndexMenu;
    /**
    Zmienna okreœlaj¹ca aktualny index pola w opcjach gry.
    */
    int selectedItemIndexOptions;
    /**
    Zmienna okreœlaj¹ca wartoœc aktualnego rzutu kostk¹.
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
    Text SFML okreœlaj¹cy nazwe aktualnego gracza.
    */
    sf::Text CurrentPlayerText;
    /**
    Text SFML z iloœcia mo¿liwoœci w g³ównym menu gry.
    */
    sf::Text MainMenuText[MAX_NUMBER_OF_ITEMS];
    /**
    Text SFML z iloœcia mo¿liwoœci w opcjach menu gry.
    */
    sf::Text OptionsText[MAX_NUMBER_OF_ITEMS];
    /**
    Text SFML obrazuj¹cy znaki wpisane przez gracza.
    */
    sf::Text text;
    /**
    SFML Rectangle t³a.
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
    SFML Circle shape pierwszy dla dwóch oczek kostki.
    */
    sf::CircleShape r_2_1;
    /**
    SFML Circle shape drugi dla dwóch oczek kostki.
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
    SFML Circle shape pierwszy dla piêciu oczek kostki.
    */
    sf::CircleShape r_5_1;
    /**
    SFML Circle shape drugi dla piêciu oczek kostki.
    */
    sf::CircleShape r_5_2;
    /**
    SFML Circle shape trzeci dla piêciu oczek kostki.
    */
    sf::CircleShape r_5_3;
    /**
    SFML Circle shape czwarty dla piêciu oczek kostki.
    */
    sf::CircleShape r_5_4;
    /**
    SFML Circle shape pi¹ty dla piêciu oczek kostki.
    */
    sf::CircleShape r_5_5;
    /**
    SFML Circle shape pierwszy dla szeœciu oczek kostki.
    */
    sf::CircleShape r_6_1;
    /**
    SFML Circle shape drugi dla szeœciu oczek kostki.
    */
    sf::CircleShape r_6_2;
    /**
    SFML Circle shape trzeci dla szeœciu oczek kostki.
    */
    sf::CircleShape r_6_3;
    /**
    SFML Circle shape czwarty dla szeœciu oczek kostki.
    */
    sf::CircleShape r_6_4;
    /**
    SFML Circle shape pi¹ty dla szeœciu oczek kostki.
    */
    sf::CircleShape r_6_5;
    /**
    SFML Circle shape szósty dla szeœciu oczek kostki.
    */
    sf::CircleShape r_6_6;
    /**
    SFML Tekstury t³a, planszy, pionka.
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
    Pozycja myszki wzglêdem ekranu.
    */
    sf::Vector2i mousePosScreen;
    /**
    Pozycja myszki wzglêdem okna.
    */
    sf::Vector2i mousePosWindow;
    /**
    Pozycja myszki wzglêdem widoku.
    */
    sf::Vector2f mousePosView;
    /**
    Referencja na obiekt silnika gry.
    */
    Engine& engine;

    /**
    array z kafelkami pól do poruszania na planszy (pocz¹tkowe 52).
    */
    std::array<SfmlTile*, 52> tiles;
    /**
    Mapa <id_gracza, jego domek z pionkami>.
    */
    std::map<unsigned int, Holder*> playerHolders;

    /**
    klasa Enum stanu gry (G³ówne menu, opcje, Gra, Koniec gry).
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

