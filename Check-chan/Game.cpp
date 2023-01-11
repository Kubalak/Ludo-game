#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "Game.h"
#include "../BaseEngine/Engine.hpp"
#include "SfmlTile.hpp"
#include<cmath>
#define M_PI 3.14159265359f


Game::Game(Engine& engine):
    engine(engine) {
    mWindow.create(sf::VideoMode(1060,750), "Chinczyk");
    sf::Image img;
    img.loadFromFile("textures/icon.png");
    mWindow.setIcon(img.getSize().x, img.getSize().y,img.getPixelsPtr());
    mWindow.setFramerateLimit(60);
    mWindow.display();
    mCurrentState = GameState::MainMenu;
    mButtonState = Button_State::BTN_IDLE;
    selectedItemIndexMenu = 0;
    selectedItemIndexOptions = 0;
    Background.setSize(sf::Vector2f(1060,750));
    Texture.loadFromFile("textures/BackgroundMenu.jpg");
    counterTexture.loadFromFile("textures/counter.png");
    Background.setTexture(&Texture);
    BoardBackground.setSize(sf::Vector2f(750, 750));
    BoardTexture.loadFromFile("textures/BOARD.jpg");
    BoardBackground.setTexture(&BoardTexture);
    BoardBackground.setOrigin(375, 375);
    BoardBackground.setPosition(520, 375);
    diceRoll = 0;
    music.openFromFile("sounds/damage(e).flac");
    music.play();
    
    MainMenuText[0].setFont(font);
    MainMenuText[0].setFillColor(sf::Color::Red);
    MainMenuText[0].setString("Play");
    MainMenuText[0].setPosition(sf::Vector2f(mWindow.getSize().x / 2.f, mWindow.getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 1.f));
    
    MainMenuText[1].setFont(font);
    MainMenuText[1].setFillColor(sf::Color::White);
    MainMenuText[1].setString("Options");
    MainMenuText[1].setPosition(sf::Vector2f(mWindow.getSize().x / 2.f, mWindow.getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 2.f));

    MainMenuText[2].setFont(font);
    MainMenuText[2].setFillColor(sf::Color::White);
    MainMenuText[2].setString("Exit");
    MainMenuText[2].setPosition(sf::Vector2f(mWindow.getSize().x / 2.f, mWindow.getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 3.f));

    OptionsText[0].setFont(font);
    OptionsText[0].setFillColor(sf::Color::Red);
    OptionsText[0].setString("Sound: ON");
    OptionsText[0].setPosition(sf::Vector2f(mWindow.getSize().x / 2.f, mWindow.getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 1.f));

    OptionsText[1].setFont(font);
    OptionsText[1].setFillColor(sf::Color::White);
    OptionsText[1].setString("1280x720");
    OptionsText[1].setPosition(sf::Vector2f(mWindow.getSize().x / 2.f, mWindow.getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 2.f));

    OptionsText[2].setFont(font);

    OptionsText[2].setFillColor(sf::Color::White);
    OptionsText[2].setString("Back");
    OptionsText[2].setPosition(sf::Vector2f(mWindow.getSize().x / 2.f, mWindow.getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 3.f));

    dice.setSize(sf::Vector2f(90, 90));
    dice.setPosition(sf::Vector2f(740, 55)); //dice.setPosition(sf::Vector2f(860, 55));
    dice.setFillColor(sf::Color::White);

    //1
    r_1.setRadius(10.f);
    r_1.setFillColor(sf::Color::Black);
    r_1.setPosition(773, 92);

    //2
    r_2_1.setRadius(10.f);
    r_2_2.setRadius(10.f);
    r_2_1.setFillColor(sf::Color::Black);
    r_2_1.setPosition(750, 67);
    r_2_2.setFillColor(sf::Color::Black);
    r_2_2.setPosition(800, 113);

    //3
    r_3_1.setRadius(10.f);
    r_3_2.setRadius(10.f);
    r_3_3.setRadius(10.f);
    r_3_1.setFillColor(sf::Color::Black);
    r_3_1.setPosition(750, 67);
    r_3_2.setFillColor(sf::Color::Black);
    r_3_2.setPosition(775, 88);
    r_3_3.setFillColor(sf::Color::Black);
    r_3_3.setPosition(800, 113);

    //4
    r_4_1.setRadius(10.f);
    r_4_2.setRadius(10.f);
    r_4_3.setRadius(10.f);
    r_4_4.setRadius(10.f);
    r_4_1.setFillColor(sf::Color::Black);
    r_4_1.setPosition(750, 112);
    r_4_2.setFillColor(sf::Color::Black);
    r_4_2.setPosition(800, 112);
    r_4_3.setFillColor(sf::Color::Black);
    r_4_3.setPosition(750, 72);
    r_4_4.setFillColor(sf::Color::Black);
    r_4_4.setPosition(800, 72);

    //5
    r_5_1.setRadius(10.f);
    r_5_2.setRadius(10.f);
    r_5_3.setRadius(10.f);
    r_5_4.setRadius(10.f);
    r_5_5.setRadius(10.f);
    r_5_1.setFillColor(sf::Color::Black);
    r_5_1.setPosition(755, 112);
    r_5_2.setFillColor(sf::Color::Black);
    r_5_2.setPosition(795, 112);
    r_5_3.setFillColor(sf::Color::Black);
    r_5_3.setPosition(755, 72);
    r_5_4.setFillColor(sf::Color::Black);
    r_5_4.setPosition(795, 72);
    r_5_5.setFillColor(sf::Color::Black);
    r_5_5.setPosition(775, 92);

    //6
    r_6_1.setRadius(10.f);
    r_6_2.setRadius(10.f);
    r_6_3.setRadius(10.f);
    r_6_4.setRadius(10.f);
    r_6_5.setRadius(10.f);
    r_6_6.setRadius(10.f);
    r_6_1.setFillColor(sf::Color::Black);
    r_6_1.setPosition(755, 120);
    r_6_2.setFillColor(sf::Color::Black);
    r_6_2.setPosition(795, 120);
    r_6_3.setFillColor(sf::Color::Black);
    r_6_3.setPosition(795, 60);
    r_6_4.setFillColor(sf::Color::Black);
    r_6_4.setPosition(755, 60);
    r_6_5.setFillColor(sf::Color::Black);
    r_6_5.setPosition(795, 88);
    r_6_6.setFillColor(sf::Color::Black);
    r_6_6.setPosition(755, 88);

    for (auto& player : engine.getQuarters()) {
        std::cout << "p.first " << player.first << " p.second " << player.second << '\n';
        switch (player.first) {
        case 0: playerColors[player.second] = sf::Color::Yellow; break;
        case 1: playerColors[player.second] = sf::Color::Blue; break;
        case 2: playerColors[player.second] = sf::Color::Red; break;
        case 3: playerColors[player.second] = sf::Color::Green; break;
        }
    }

    unsigned int index = 0;
    for (auto& tile : engine.getTiles())
        tiles[index++] = new SfmlTile(tile, index, counterTexture, playerColors);
    for (int i = 0; i < 4; ++i) {
       float deg = 90.0f * i * M_PI / 180.0f;
       for (int j = 0; j < 5; j++) {
           index = 13 * i + j;
           (*tiles[index]).move(sf::Vector2f(0, j * 43.f));
           (*tiles[index]).setPosition(rotate((*tiles[index]).getPosition(), BoardBackground.getPosition(), deg));
       }
       for(int j=5;j<11;++j) {
           index = 13 * i + j;
           (*tiles[index]).move(sf::Vector2f(-172.f + j * 43.f, 215.f));
           (*tiles[index]).setPosition(rotate((*tiles[index]).getPosition(), BoardBackground.getPosition(), deg));
       }
       index = 13 * i + 11;
       (*tiles[index]).move(sf::Vector2f(258.f, 256.f));
       (*tiles[index]).setPosition(rotate((*tiles[index]).getPosition(), BoardBackground.getPosition(), deg));
       index = 13 * i + 12;
       (*tiles[index]).move(sf::Vector2f(258.f, 296.f));
       (*tiles[index]).setPosition(rotate((*tiles[index]).getPosition(), BoardBackground.getPosition(), deg));
    }
    
        
}

Game::~Game() { for (auto* tile : tiles) delete tile; }

    //G³ówna pêtla która chodzi zawsze
int Game::run(){
    if (!font.loadFromFile("fonts/font.ttf"))
        return-1;
    

    while (mWindow.isOpen()) {
            handleEvents();
            updateGame();
            UpdateMousePos();
            draw();
        }
        return 0;
}

    //Pêtla odpowiedzialna za handle eventów    
int Game::handleEvents(){
        sf::Event Event;
        while (mWindow.pollEvent(Event)) {
            switch (Event.type) 
            {
            case sf::Event::KeyPressed:
                switch (Event.key.code)
                {
                case sf::Keyboard::Up:
                    std::cout << "KEY UP PRESSED\n";
                    Game::MoveUp();
                    break;

                case sf::Keyboard::Down:
                    std::cout << "KEY DOWN PRESSED\n";
                    Game::MoveDown();
                    break;

                case sf::Keyboard::F11:
                    break;

                case sf::Keyboard::Return:
                    switch (Game::GetPressedItem())
                    {
                        case GameState::MainMenu:
                            currentText = MainMenuText[selectedItemIndexMenu].getString();
                            std::cout << currentText << " Was pressed\n";
                            if (currentText == "Play")
                                mCurrentState = GameState::MainGame;

                            if (currentText == "Options")
                                mCurrentState = GameState::Options;

                            if (currentText == "Exit")
                                mWindow.close();
                            break;

                        case GameState::MainGame:
                            ;
                            break;

                        case GameState::Options:
                            
                            currentText = OptionsText[selectedItemIndexOptions].getString();;
                                
                            if(currentText == "Sound: ON") {

                                OptionsText[0].setString("Sound: OFF");
                                mWindow.display();
                                music.stop();
                            }
                            else if(currentText == "Sound: OFF") {
                                OptionsText[0].setString("Sound: ON");
                                mWindow.display();
                                music.play();
                            }
                            else if(currentText == "1280x720") {
                                mWindow.create(sf::VideoMode(1360, 768), "Chinczyk");
                                OptionsText[1].setString("Resolution: 1360x768");
                                mWindow.display();
                                music.play();
                            }

                           
                            if (currentText == "Back")
                                mCurrentState = GameState::MainMenu;
                            break;
                        }
                }
                break;
            
            case sf::Event::MouseMoved:
                break;


            case sf::Event::Resized:
                mWindow.setSize(sf::Vector2u(Event.size.width, Event.size.height));
                break;

                
            case sf::Event::Closed:
                mWindow.close();
                break;
            }
        }
        return 0;
 }

int Game::updateGame(){
        return 0;
 }

int Game::drawMenuContent()
{

    mWindow.draw(Background);
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
    {
        
        mWindow.draw(MainMenuText[i]);
    }

    return 0;
}

int Game::drawGameContent()
{
 
    mWindow.draw(BoardBackground);
    mWindow.draw(dice);
    // Przeniesc do konstruktora
    //Dice
    //sf::CircleShape s(2.0f);
    //s.setOrigin(1.f, 1.f);
    for (auto* tile : tiles) //{
        //s.setFillColor(sf::Color::Blue);
        //s.setPosition((*tile)().getPosition());
        mWindow.draw((*tile));
        //mWindow.draw(s);
    //}
    
    /*for (int i = 0; i < 360; ++i) {
        s.setFillColor(sf::Color::Cyan);
        s.setPosition(rotate(sf::Vector2f(560.f, 116.f), BoardBackground.getPosition(), i * M_PI / 180.f));
        mWindow.draw(s);
    }*/
    diceRoll = engine.getDice();
    
    if (diceRoll == 1)
    {
        mWindow.draw(r_1);
    }
    else if (diceRoll == 2)
    {
        mWindow.draw(r_2_1);
        mWindow.draw(r_2_2);
    }
    else if (diceRoll == 3)
    {
        mWindow.draw(r_3_1);
        mWindow.draw(r_3_2);
        mWindow.draw(r_3_3);
    }
    else if (diceRoll == 4)
    {
        mWindow.draw(r_4_1);
        mWindow.draw(r_4_2);
        mWindow.draw(r_4_3);
        mWindow.draw(r_4_4);
    }
    else if (diceRoll == 5)
    {
        mWindow.draw(r_5_1);
        mWindow.draw(r_5_2);
        mWindow.draw(r_5_3);
        mWindow.draw(r_5_4);
        mWindow.draw(r_5_5);
    }
    else if (diceRoll == 6)
    {
        mWindow.draw(r_6_1);
        mWindow.draw(r_6_2);
        mWindow.draw(r_6_3);
        mWindow.draw(r_6_4);
        mWindow.draw(r_6_5);
        mWindow.draw(r_6_6);
    }


    //auto& tiles = engine.getTiles();
    //unsigned int index = 0U;
    //sf::RectangleShape s;
    //s.setSize(sf::Vector2f(25, 25));
    //for (auto& t : tiles) {
    //    s.setPosition(50.0f + (index % 10) * 30, 50.0f + ((index / 10) * 30)); // ¯eby by³ sobie ³adny grid.
    //    int c = static_cast<int>(t.getCounters().size()); // Pobiera ile pionków jest na danym polu (w ogóle)
    //    
    //    /*
    //    * Dla konkretnego gracza wzi¹æ
    //    * auto mp = t.getPlayersCount();
    //    * mp.first -> Id gracza.
    //    * mp.second -> Liczba pionków gracza, która znajduje siê na tym polu.
    //    */
    //    s.setFillColor(sf::Color(c * 64, 0, 0, 127 + !t.allowManyPlayers() * 128));
    //    mWindow.draw(s);
    //    ++index;
    //}
    return 0;
}

int Game::drawOptionsContent()
{
    mWindow.draw(Background);
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
    {
        mWindow.draw(OptionsText[i]);
    }

    return 0;
}

int Game::draw(){
    switch (mCurrentState){
        case GameState::MainMenu:
            mWindow.clear();
            Game::drawMenuContent();
            mWindow.display();
            break;

        case GameState::MainGame:
           mWindow.clear();
           Game::drawGameContent();
           mWindow.display();
           break;

        case GameState::Options:
            mWindow.clear();
            Game::drawOptionsContent();
            mWindow.display();
            break;

        case GameState::GameOver:
                // Draw the game over screen here
               break;
            }
            return 0;
    }


void Game::MoveUp()
{
    switch (mCurrentState) {
    case GameState::MainMenu:
            if (selectedItemIndexMenu - 1 >= 0)
            {
                MainMenuText[selectedItemIndexMenu].setFillColor(sf::Color::White);
                selectedItemIndexMenu--;
                MainMenuText[selectedItemIndexMenu].setFillColor(sf::Color::Red);
            };
            break;

    case GameState::Options:
            if (selectedItemIndexOptions - 1 >= 0)
            {
                OptionsText[selectedItemIndexOptions].setFillColor(sf::Color::White);
                selectedItemIndexOptions--;
                OptionsText[selectedItemIndexOptions].setFillColor(sf::Color::Red);
            }
            break;
    break;
    }
}

void Game::MoveDown()
{
    switch (mCurrentState) {

    case GameState::MainMenu:
        if (selectedItemIndexMenu + 1 < MAX_NUMBER_OF_ITEMS)
        {
            MainMenuText[selectedItemIndexMenu].setFillColor(sf::Color::White);
            selectedItemIndexMenu++;
            MainMenuText[selectedItemIndexMenu].setFillColor(sf::Color::Red);
        }
        break;

    case GameState::Options:
        if (selectedItemIndexOptions + 1 < MAX_NUMBER_OF_ITEMS)
        {
            OptionsText[selectedItemIndexOptions].setFillColor(sf::Color::White);
            selectedItemIndexOptions++;
            OptionsText[selectedItemIndexOptions].setFillColor(sf::Color::Red);
        }
        break;

    }
    
}

void Game::UpdateMousePos()
{
    mousePosScreen = sf::Mouse::getPosition();
    mousePosWindow = sf::Mouse::getPosition(mWindow);
    mousePosView = mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow));
}

Game::GameState Game::GetPressedItem()
{
        return mCurrentState;
}

void Game::drawDice(int val) {

    
}

sf::Vector2f Game::rotate(sf::Vector2f position, sf::Vector2f around, float rad) {
    float s = sin(rad);
    float c = cos(rad);
    float px = position.x;
    float py = position.y;
    float ox = around.x;
    float oy = around.y;
    float x = (px - ox) * c - (py - oy) * s + ox;
    float y = (px - ox) * s + (py - oy) * c + oy;
    return sf::Vector2f(x, y);
}

sf::Vector2f Game::rotate(float x, float y, float ox, float oy, float rad) {
    float s = sin(rad);
    float c = cos(rad);
    float rx = (x - ox) * c - (y - oy) * s + ox;
    float ry = (x - ox) * s + (y - oy) * c + oy;
    return sf::Vector2f(rx, ry);
}