#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>

#define MAX_NUMBER_OF_ITEMS 3
#define MAX_NUMBER_OF_ITEMS 3

class Game {
private:
    sf::RenderWindow mWindow;
    int selectedItemIndexMenu;
    int selectedItemIndexOptions;
    std::string currentText;
    sf::Font font;
    sf::Text MainMenuText[MAX_NUMBER_OF_ITEMS];
    sf::Text OptionsText[MAX_NUMBER_OF_ITEMS];
    sf::RectangleShape Background;
    sf::RectangleShape BoardBackground;
    sf::Texture Texture, BoardTexture;
    sf::Sprite boardImg;
    sf::Music music;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;


    enum class GameState {
        MainMenu,
        Options,
        MainGame,
        GameOver
    };

    enum class Button_State {
        BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE, BTN_PRESSED
    };

    Button_State mButtonState;
    GameState mCurrentState;
   
public:
    Game();
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
    void MovePiece(int player_no, int& curx, int& cur);
    Game::GameState GetPressedItem();
};

