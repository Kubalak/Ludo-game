#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "Game.h"


Game::Game(){
    mWindow.create(sf::VideoMode(1280,768), "Chinczyk");
    mWindow.setFramerateLimit(60);
    mWindow.display();
    mCurrentState = GameState::MainMenu;
    mButtonState = Button_State::BTN_IDLE;
    selectedItemIndexMenu = 0;
    selectedItemIndexOptions = 0;
    Background.setSize(sf::Vector2f(1280,720));
    Texture.loadFromFile("Images/BackgroundMenu.jpg");
    Background.setTexture(&Texture);
    BoardBackground.setSize(sf::Vector2f(1280, 720));
    BoardTexture.loadFromFile("Images/BOARD.jpg");
    BoardBackground.setTexture(&BoardTexture);
    //music.openFromFile("C:/Users/Patryk/source/repos/SFML_MENU/SFML_MENU/SUICIDEBOYS-MATTE-BLACK.ogg");
    music.play();
    
    MainMenuText[0].setFont(font);
    MainMenuText[0].setFillColor(sf::Color::Red);
    MainMenuText[0].setString("Play");
    MainMenuText[0].setPosition(sf::Vector2f(mWindow.getSize().x / 2, mWindow.getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 1));
    
    MainMenuText[1].setFont(font);
    MainMenuText[1].setFillColor(sf::Color::White);
    MainMenuText[1].setString("Options");
    MainMenuText[1].setPosition(sf::Vector2f(mWindow.getSize().x / 2, mWindow.getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 2));

    MainMenuText[2].setFont(font);
    MainMenuText[2].setFillColor(sf::Color::White);
    MainMenuText[2].setString("Exit");
    MainMenuText[2].setPosition(sf::Vector2f(mWindow.getSize().x / 2, mWindow.getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 3));

    OptionsText[0].setFont(font);
    OptionsText[0].setFillColor(sf::Color::Red);
    OptionsText[0].setString("Sound: ON");
    OptionsText[0].setPosition(sf::Vector2f(mWindow.getSize().x / 2, mWindow.getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 1));

    OptionsText[1].setFont(font);
    OptionsText[1].setFillColor(sf::Color::White);
    OptionsText[1].setString("1280x720");
    OptionsText[1].setPosition(sf::Vector2f(mWindow.getSize().x / 2, mWindow.getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 2));

    OptionsText[2].setFont(font);

    OptionsText[2].setFillColor(sf::Color::White);
    OptionsText[2].setString("Back");
    OptionsText[2].setPosition(sf::Vector2f(mWindow.getSize().x / 2, mWindow.getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 3));
}

Game::~Game() {}

    //G³ówna pêtla która chodzi zawsze
int Game::run(){
    if (!font.loadFromFile("font.ttf"))
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

void Game::MovePiece(int player_no, int& curx, int& cury)
{
         
}