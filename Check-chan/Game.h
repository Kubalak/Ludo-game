#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "../BaseEngine/Engine.hpp"
#include "SfmlTile.hpp"

#define MAX_NUMBER_OF_ITEMS 3
#define MAX_NUMBER_OF_ITEMS 3

class Game {
private:
    sf::RenderWindow mWindow;
    int selectedItemIndexMenu;
    int selectedItemIndexOptions;
    int diceRoll;
    std::string currentText;
    sf::Font font;
    sf::Text MainMenuText[MAX_NUMBER_OF_ITEMS];
    sf::Text OptionsText[MAX_NUMBER_OF_ITEMS];
    sf::RectangleShape Background;
    sf::RectangleShape BoardBackground;
    sf::RectangleShape dice;
    sf::CircleShape r_1;
    sf::CircleShape r_2_1;
    sf::CircleShape r_2_2;
    sf::CircleShape r_3_1;
    sf::CircleShape r_3_2;
    sf::CircleShape r_3_3;
    sf::CircleShape r_4_1;
    sf::CircleShape r_4_2;
    sf::CircleShape r_4_3;
    sf::CircleShape r_4_4;
    sf::CircleShape r_5_1;
    sf::CircleShape r_5_2;
    sf::CircleShape r_5_3;
    sf::CircleShape r_5_4;
    sf::CircleShape r_5_5;
    sf::CircleShape r_6_1;
    sf::CircleShape r_6_2;
    sf::CircleShape r_6_3;
    sf::CircleShape r_6_4;
    sf::CircleShape r_6_5;
    sf::CircleShape r_6_6;
    sf::Texture Texture, BoardTexture;
    sf::Sprite boardImg;
    sf::Music music;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    Engine& engine;

    std::array<SfmlTile*, 52> tiles;

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
    Game::GameState GetPressedItem();
};

