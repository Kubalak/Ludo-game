#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "../BaseEngine/Engine.hpp"
#include "SfmlTile.hpp"
#include "locale"

#define MAX_NUMBER_OF_ITEMS 3
#define MAX_NUMBER_OF_ITEMS 3

class Game {
private:
    sf::Clock clock;
    sf::RenderWindow mWindow;
    int selectedItemIndexMenu;
    int selectedItemIndexOptions;
    int diceRoll;
    std::string currentText;
    std::string PlayerText;
    std::string input_text;
    sf::Font font;
    sf::Text CurrentPlayerText;
    sf::Text MainMenuText[MAX_NUMBER_OF_ITEMS];
    sf::Text OptionsText[MAX_NUMBER_OF_ITEMS];
    sf::Text text;
    sf::RectangleShape Background;
    sf::RectangleShape BoardBackground;
    sf::RectangleShape diceShape;
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
    sf::Texture Texture, BoardTexture, counterTexture;
    sf::Sprite boardImg;
    sf::Music music;
    std::map<unsigned int, sf::Color> playerColors;
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
    sf::Vector2f rotate(sf::Vector2f position, sf::Vector2f around, float rad);
    sf::Vector2f rotate(float x, float y, float ox, float oy, float rad);
    Game::GameState GetPressedItem();
};

