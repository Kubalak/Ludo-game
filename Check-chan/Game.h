#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "Engine.hpp"
#include "OnlineEngine.hpp"
#include "SfmlTile.hpp"
#include "Holder.hpp"
#include "Last.hpp"
#include "locale"

#define MAIN_NUMBER_OF_ITEMS 4
#define OPTIONS_NUMBER_OF_ITEMS 3
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
    /**
    Quater pobrane z tekstu do usigned int
    */
    unsigned int playerId;
    std::string currentText;
    /**
    String przechowujacy quater gracza.
    */
    std::string playerIdString;
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
    Tekst CURRENT PLAYER
    */
    sf::Text currentPlayerHelp;
    /**
    Tekst YOUR TURN
    */
    sf::Text yourTurnText;
    /**
    Text buttona dodawania gracza.
    */
    sf::Text ButtonText[2];
    /**
    Text SFML z iloœcia mo¿liwoœci w g³ównym menu gry.
    */
    sf::Text MainMenuText[MAIN_NUMBER_OF_ITEMS];
    /**
    Text SFML z iloœcia mo¿liwoœci w opcjach menu gry.
    */
    sf::Text OptionsText[OPTIONS_NUMBER_OF_ITEMS];
    /**
    Text do offline menu gry.
    */
    sf::Text OfflineText[3];
    /**
    Znak plusa i minusa liczby w quater.
    */
    sf::Text PlusMinusNumber[3];
    /**
    Text przechowuj¹cy graczy.
    */
    sf::Text Players[4];
    /**
    Text SFML obrazuj¹cy znaki wpisane przez gracza.
    */
    sf::Text text;
    /**
    Adres serwera gry u¿ywany w OnlineEngine.
    */
    sf::Text address;
    /**
    Napis przy przycisku connect.
    */
    sf::Text connect;
    /**
    Napis dla pomocy przy æwiartce.
    */
    sf::Text quarterText;
    /**
    T³o dla przycisku connect.
    */
    sf::RectangleShape connectBg;
    /**
    Pomocniczy tekst dla adresu serwera.
    */
    sf::Text addressHelp;
    /**
    Lokalny gracz (u¿ywane w wersji online).
    */
    sf::Text localP;
    /**
    SFML Rectangle t³a.
    */
    sf::RectangleShape Background;
    /**
    SFML Button dodawania graczy.
    */
    sf::RectangleShape ButtonAdd;
    /**
    SFML Button zwiêkszania numeru quater na planszy.
    */
    sf::RectangleShape ButtonPlus;
    /**
    SFML Button zmniejszania numeru quater na planszy.
    */
    sf::RectangleShape ButtonMinus;
    /**
    SFML Button startu gry.
    */
    sf::RectangleShape ButtonStart;
    /**
    SFML Button dodawania graczy.
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
    WskaŸnik na obiekt silnika gry (zarówno zwyk³y jak i OnlineEngine)
    */
    Engine* engine;
    /**
    WskaŸnik na obiekt OnlineEngine potrzebny przy konfiguracji silnika.
    */
    OnlineEngine* online;

    /**
    array z kafelkami pól do poruszania na planszy (pocz¹tkowe 52).
    */
    std::array<SfmlTile*, 52> tiles;
    /**
    Mapa <id_gracza, jego domek z pionkami>.
    */
    std::map<unsigned int, Holder*> playerHolders;
    std::map<unsigned int, Last*> playerLast;

    /**
    klasa Enum stanu gry (G³ówne menu, opcje, Gra, Koniec gry).
    */
    enum class GameState {
        MainMenu,
        Offline,
        Online,
        Options,
        MainGame,
        GameOver
    };
    
    /**
    obiekt Enum aktualnego stanu gry.
    */
    GameState mCurrentState;
   
public:
    Game();
    ~Game();
    /// <summary>
    /// Funkcja z g³ówna pêtla gry ( w œrodku obs³uga eventów, aktualizacja stanu gry, aktualizacja pozycji myszki, rysowanie )
    /// </summary>
    /// <returns></returns>
    int run();
    /// <summary>
    /// Funkcja odpowiedzialna za obs³ugê wszystkich typów zdarzeñ
    /// </summary>
    /// <returns></returns>
    int handleEvents();
    /// <summary>
    /// Funkcja do aktualizacji liczby pionków w domkach graczy
    /// </summary>
    /// <returns></returns>
    int updateGame();
    /// <summary>
    /// Funkcja wywo³uj¹ca odpowiednie metody rysuj¹ce w zale¿noœci od stanu (Menu g³ówne, Gra, Opcje, Koniec gry)
    /// </summary>
    int draw();
    /// <summary>
    /// Do rysowania zawartoœci Menu g³ównego
    /// </summary>
    int drawMenuContent();
    int drawOfflineContent();
    /// <summary>
    /// Funkcja do rysowania zawartoœci opcji gry
    /// </summary>
    /// <returns></returns>
    int drawOptionsContent();
    /// <summary>
    /// Funkcja do rysowania zawartoœci g³ównej gry
    /// </summary>
    /// <returns></returns>
    int drawGameContent();
    void MoveUp();
    /// <summary>
    /// Funkcja dekrementuj¹ca(poruszanie w góre menu) numer indexu oraz kolor tekstu aktualnego wyboru w g³ównym menu, opcjach itd.
    /// </summary>
    void MoveDown();
    /// <summary>
    /// Funkcja aktualizuj¹ca pozycje myszki na ekranie
    /// </summary>
    void UpdateMousePos();
    /// <summary>
    /// Rotacja wzglêdem œrodka
    /// </summary>
    /// <param name="position"> Wzglêdem jakiej pozycji</param>
    /// <param name="around"> </param>
    /// <param name="rad"> Radiany</param>
    /// <returns></returns>
    sf::Vector2f rotate(sf::Vector2f position, sf::Vector2f around, float rad);
    /// <summary>
    /// 
    /// </summary>
    /// <param name="x"> Wspó³rzêdne x</param>
    /// <param name="y"> Wspó³rzêdne y</param>
    /// <param name="ox"></param>
    /// <param name="oy"></param>
    /// <param name="rad">Radiany</param>
    /// <returns></returns>
    sf::Vector2f rotate(float x, float y, float ox, float oy, float rad);
    /// <summary>
    /// Funkcja aktualizuj¹ca aktualny stan  (Pobiera stan: Menu, Opcje, Gra)
    /// </summary>
    /// <returns></returns>
    Game::GameState GetPressedItem();
    /// <summary>
    /// Funkcja przygotowuj¹ca silnik (³¹czy go z obiektem Engine)
    /// </summary>
    void prepareEngine();
    /// <summary>
    /// Funkcja rysuj¹ca elementy przy wybraniu opcji gry online.
    /// </summary>
    void drawOnlineContent();
};

