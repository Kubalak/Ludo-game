#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "Game.h"
#include "../BaseEngine/Engine.hpp"
#include "SfmlTile.hpp"
#include<cmath>
#define M_PI 3.14159265359f

/// <summary>
/// Konstruktor klasy Game
/// </summary>
/// <param name="engine">Referencja do silnika gry (pozwala korzystaæ z mo¿liwoœci silnika)</param>
Game::Game() :
	engine(nullptr),
	online(nullptr) {
	mWindow.create(sf::VideoMode(1060, 750), "Chinczyk");
	sf::Image img;
	img.loadFromFile("textures/icon.png");
	mWindow.setIcon(img.getSize().x, img.getSize().y, img.getPixelsPtr());
	mWindow.setFramerateLimit(60);
	mWindow.display();
	mCurrentState = GameState::MainMenu;
	selectedItemIndexMenu = 0;
	selectedItemIndexOptions = 0;
	Background.setSize(sf::Vector2f(1060, 750));
	Texture.loadFromFile("textures/BackgroundMenu.jpg");
	counterTexture.loadFromFile("textures/counter.png");
	Background.setTexture(&Texture);
	BoardBackground.setSize(sf::Vector2f(750, 750));
	BoardTexture.loadFromFile("textures/BOARD.jpg");
	BoardBackground.setTexture(&BoardTexture);
	BoardBackground.setOrigin(375, 375);
	BoardBackground.setPosition(520, 375);
	ButtonAdd.setFillColor(sf::Color(211, 211, 211));
	ButtonAdd.setSize(sf::Vector2f(100, 50));
	ButtonAdd.setOrigin(sf::Vector2f(50, 25));
	ButtonAdd.setPosition(sf::Vector2f((mWindow.getSize().x / 2.f), 500));
	ButtonStart.setFillColor(sf::Color(211, 211, 211));
	ButtonStart.setSize(sf::Vector2f(100, 50));
	ButtonStart.setOrigin(sf::Vector2f(50, 25));
	ButtonStart.setPosition(sf::Vector2f((mWindow.getSize().x / 2.f), 600));
	ButtonMinus.setFillColor(sf::Color(211, 211, 211));
	ButtonMinus.setSize(sf::Vector2f(30, 30));
	ButtonMinus.setOrigin(sf::Vector2f(15, 15));
	ButtonMinus.setPosition(sf::Vector2f((mWindow.getSize().x / 2.f) + 130, 420));
	ButtonPlus.setFillColor(sf::Color(211, 211, 211));
	ButtonPlus.setSize(sf::Vector2f(30, 30));
	ButtonPlus.setOrigin(sf::Vector2f(15, 15));
	ButtonPlus.setPosition(sf::Vector2f((mWindow.getSize().x / 2.f) + 230, 420));
	diceRoll = 0;
	music.openFromFile("sounds/music.flac");
	music.setVolume(50.0);
	music.setLoop(true);
	music.play();

	playerId = 0;


	MainMenuText[0].setFont(font);
	MainMenuText[0].setFillColor(sf::Color::Red);
	MainMenuText[0].setString("Play Offline");
	MainMenuText[0].setPosition(sf::Vector2f(mWindow.getSize().x / 2.f, mWindow.getSize().y / (MAIN_NUMBER_OF_ITEMS + 1) * 1.f));

	MainMenuText[1].setFont(font);
	MainMenuText[1].setFillColor(sf::Color::Yellow);
	MainMenuText[1].setString("Play Online");
	MainMenuText[1].setPosition(sf::Vector2f(mWindow.getSize().x / 2.f, mWindow.getSize().y / (MAIN_NUMBER_OF_ITEMS + 1) * 2.f));

	MainMenuText[2].setFont(font);
	MainMenuText[2].setFillColor(sf::Color::Yellow);
	MainMenuText[2].setString("Options");
	MainMenuText[2].setPosition(sf::Vector2f(mWindow.getSize().x / 2.f, mWindow.getSize().y / (MAIN_NUMBER_OF_ITEMS + 1) * 3.f));

	MainMenuText[3].setFont(font);
	MainMenuText[3].setFillColor(sf::Color::Yellow);
	MainMenuText[3].setString("Exit");
	MainMenuText[3].setPosition(sf::Vector2f(mWindow.getSize().x / 2.f, mWindow.getSize().y / (MAIN_NUMBER_OF_ITEMS + 1) * 4.f));

	OptionsText[0].setFont(font);
	OptionsText[0].setFillColor(sf::Color::Red);
	OptionsText[0].setString("Sound: ON");
	OptionsText[0].setPosition(sf::Vector2f(mWindow.getSize().x / 2.f, mWindow.getSize().y / (OPTIONS_NUMBER_OF_ITEMS + 1) * 1.f));

	OptionsText[1].setFont(font);
	OptionsText[1].setFillColor(sf::Color::Yellow);
	OptionsText[1].setString("1280x720");
	OptionsText[1].setPosition(sf::Vector2f(mWindow.getSize().x / 2.f, mWindow.getSize().y / (OPTIONS_NUMBER_OF_ITEMS + 1) * 2.f));

	OptionsText[2].setFont(font);
	OptionsText[2].setFillColor(sf::Color::Yellow);
	OptionsText[2].setString("Back");
	OptionsText[2].setPosition(sf::Vector2f(mWindow.getSize().x / 2.f, mWindow.getSize().y / (OPTIONS_NUMBER_OF_ITEMS + 1) * 3.f));

	OfflineText[0].setFont(font);
	OfflineText[0].setFillColor(sf::Color::White);
	OfflineText[0].setString("Players List");
	OfflineText[0].setPosition(sf::Vector2f((mWindow.getSize().x / 2.f) - 45, 45));

	quarterText = OfflineText[0];
	quarterText.setString("QUARTER");
	quarterText.setCharacterSize(18);
	quarterText.setPosition(sf::Vector2f((mWindow.getSize().x / 2.f) + 145, 460));

	OfflineText[1].setFont(font);
	OfflineText[1].setFillColor(sf::Color::White);
	OfflineText[1].setString("NICK\tID\tQUATER");
	OfflineText[1].setPosition(sf::Vector2f((mWindow.getSize().x / 2.f) - 70, 75));

	Players[0].setFont(font);
	Players[0].setCharacterSize(20);
	Players[0].setFillColor(sf::Color::Green);
	Players[0].setPosition(sf::Vector2f((mWindow.getSize().x / 2.f) - 70, 125));

	Players[1] = Players[2] = Players[3] = Players[0];
	Players[1].setPosition(sf::Vector2f((mWindow.getSize().x / 2.f) - 70, 150));
	Players[2].setPosition(sf::Vector2f((mWindow.getSize().x / 2.f) - 70, 175));
	Players[3].setPosition(sf::Vector2f((mWindow.getSize().x / 2.f) - 70, 200));


	OfflineText[2].setFont(font);
	OfflineText[2].setFillColor(sf::Color::White);
	OfflineText[2].setString("Input Player: ");
	OfflineText[2].setPosition(sf::Vector2f((mWindow.getSize().x / 2.f) - 300, 400));

	CurrentPlayerText.setFont(font);
	CurrentPlayerText.setCharacterSize(18);
	CurrentPlayerText.setPosition(sf::Vector2f(925, 50));
	CurrentPlayerText.setString("CURRENT PLAYER");
	CurrentPlayerText.setFillColor(sf::Color::White);
	
	currentPlayerHelp = yourTurnText = CurrentPlayerText;
	currentPlayerHelp.move(sf::Vector2f(-20, -20));
	yourTurnText.move(sf::Vector2f(20, 20));
	yourTurnText.setFillColor(sf::Color::Green);
	yourTurnText.setString("YOUR TURN");

	diceShape.setSize(sf::Vector2f(90, 90));
	diceShape.setPosition(sf::Vector2f(740, 55)); //dice.setPosition(sf::Vector2f(860, 55));
	diceShape.setFillColor(sf::Color::White);

	text.setString("Testowe");
	text.setFont(font);
	text.setFillColor(sf::Color::Red);
	text.setPosition(sf::Vector2f((mWindow.getSize().x / 2.f) - 90, 400));

	ButtonText[0].setString("Add");
	ButtonText[0].setFont(font);
	ButtonText[0].setFillColor(sf::Color::Black);
	ButtonText[0].setPosition(sf::Vector2f((mWindow.getSize().x / 2.f) - 18, 485));
	ButtonText[0].setCharacterSize(25);

	ButtonText[1].setString("Start");
	ButtonText[1].setFont(font);
	ButtonText[1].setFillColor(sf::Color::Black);
	ButtonText[1].setPosition(sf::Vector2f((mWindow.getSize().x / 2.f) - 28, 585));
	ButtonText[1].setCharacterSize(25);

	PlusMinusNumber[0].setString("-");
	PlusMinusNumber[0].setFont(font);
	PlusMinusNumber[0].setFillColor(sf::Color::Red);
	PlusMinusNumber[0].setPosition(sf::Vector2f((mWindow.getSize().x / 2.f) + 125, 400));

	PlusMinusNumber[1].setString("+");
	PlusMinusNumber[1].setFont(font);
	PlusMinusNumber[1].setFillColor(sf::Color::Red);
	PlusMinusNumber[1].setPosition(sf::Vector2f((mWindow.getSize().x / 2.f) + 225, 400));

	PlusMinusNumber[2].setString("1");
	PlusMinusNumber[2].setFont(font);
	PlusMinusNumber[2].setFillColor(sf::Color::Red);
	PlusMinusNumber[2].setPosition(sf::Vector2f((mWindow.getSize().x / 2.f) + 175, 400));

	address.setString("");
	address.setFont(font);
	address.setFillColor(sf::Color::Red);
	address.setPosition(sf::Vector2f((mWindow.getSize().x / 2.f) - 50, 400));
	
	connect = address;
	connect.setString("CONNECT");
	connect.setPosition(sf::Vector2f((mWindow.getSize().x / 2.f) + 220, 400));

	connectBg.setFillColor(sf::Color::White);
	connectBg.setSize(sf::Vector2f(150, 30));
	connectBg.setPosition(sf::Vector2f((mWindow.getSize().x / 2.f) + 205, 405));
	
	addressHelp = address;
	addressHelp.setString("ENTER SERVER ADDRESS:");
	addressHelp.setFillColor(sf::Color::White);
	addressHelp.setPosition(sf::Vector2f((mWindow.getSize().x / 2.f) - 430, 400));

	localP.setFont(font);
	localP.setFillColor(sf::Color::White);
	localP.setCharacterSize(15);
	localP.setFillColor(sf::Color(200, 200, 200));
	localP.setString("");
	localP.setPosition(sf::Vector2f((mWindow.getSize().x / 2.f) - 265, 475));

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
}

void Game::prepareEngine() {
	if (engine == nullptr) return;
	for (auto& player : engine->getQuarters()) {
		std::cout << "p.first " << player.first << " p.second " << player.second << '\n';
		switch (player.first) {
		case 1: playerColors[player.second] = sf::Color::Yellow; break;
		case 2: playerColors[player.second] = sf::Color::Blue; break;
		case 3: playerColors[player.second] = sf::Color::Red; break;
		case 4: playerColors[player.second] = sf::Color::Green; break;
		}
	}

	unsigned int index = 0;
	for (auto& tile : engine->getTiles())
		tiles[index++] = new SfmlTile(tile, index, counterTexture, playerColors);
	for (int i = 0; i < 4; ++i) {
		float deg = 90.0f * i * M_PI / 180.0f;
		for (int j = 0; j < 5; j++) {
			index = 13 * i + j;
			(*tiles[index]).move(sf::Vector2f(0, j * 43.f));
			(*tiles[index]).setPosition(rotate((*tiles[index]).getPosition(), BoardBackground.getPosition(), deg));
		}
		for (int j = 5; j < 11; ++j) {
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

/// <summary>
/// Destruktor obiektu Game
/// </summary>
Game::~Game() {
	for (auto* tile : tiles)
		delete tile;
	for (auto& p : playerHolders)
		delete p.second;
	for (auto& c : playerLast)
		delete c.second;
	if (online != nullptr)
		delete online;
	else if (engine != nullptr)
		delete engine;	
}

/// <summary>
/// Funkcja z g³ówna pêtla gry ( w œrodku obs³uga eventów, aktualizacja stanu gry, aktualizacja pozycji myszki, rysowanie )
/// </summary>
/// <returns></returns>
int Game::run() {
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

/// <summary>
/// Funkcja odpowiedzialna za obs³ugê wszystkich typów zdarzeñ
/// </summary>
/// <returns></returns>
int Game::handleEvents() {
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

			case sf::Keyboard::BackSpace:
				if (!input_text.empty())
					input_text.pop_back();
				break;

			case sf::Keyboard::Return:
				switch (Game::GetPressedItem())
				{
				case GameState::MainMenu:
					currentText = MainMenuText[selectedItemIndexMenu].getString();
					std::cout << currentText << " Was pressed\n";
					if (currentText == "Play Offline") {
						engine = new Engine();
						prepareEngine();
						mCurrentState = GameState::Offline;
					}

					if (currentText == "Play Online") {
						engine = online = new OnlineEngine();
						prepareEngine();
						mCurrentState = GameState::Online;
					}


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

					if (currentText == "Sound: ON") {

						OptionsText[0].setString("Sound: OFF");
						mWindow.display();
						music.stop();
					}
					else if (currentText == "Sound: OFF") {
						OptionsText[0].setString("Sound: ON");
						mWindow.display();
						music.play();
					}
					else if (currentText == "1280x720") {
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


		case sf::Event::MouseButtonPressed:
			switch (mCurrentState)
			{
			case GameState::MainGame:
				if (diceShape.getGlobalBounds().contains(mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow))) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)) && engine != nullptr)
					diceRoll = engine->rollDice();
				for (auto* tile : tiles)
				{
					if (tile->shape().contains(mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow))) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)) && engine != nullptr)
						engine->move(tile->id);
				}

				for (auto& playHold : playerHolders)
				{
					if (playHold.second->shape().contains(mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow))) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)) && engine != nullptr)
						engine->move(-1);
				}
				for (auto& last : playerLast)
					for (auto& lTile : last.second->getTiles())
						if (lTile->shape().contains(mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow))) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)) && engine != nullptr)
							engine->move(last.second->num * 100 + lTile->id);
				break;
			case GameState::Offline:
				if (ButtonAdd.getGlobalBounds().contains(mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow))) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)) && engine != nullptr)
					if (!input_text.empty()) {
						Player* p = new Player(input_text);
						if (!engine->addPlayer(p, playerId + 1))
							delete p;
						else input_text.clear();
					}
				//ButtonText[0].setFillColor(sf::Color::Red);
				//ButtonText[0].setFillColor(sf::Color::Black);
				if (ButtonPlus.getGlobalBounds().contains(mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow))) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
					if (playerId < 3)
						playerId++;
				if (ButtonMinus.getGlobalBounds().contains(mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow))) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
					if (playerId > 0)
						playerId--;
				if (ButtonStart.getGlobalBounds().contains(mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow))) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)) && engine != nullptr)
					engine->start();
				if (engine != nullptr && engine->getCurrentState() != EngineStates::CREATED)
					mCurrentState = GameState::MainGame;
				break;

			case GameState::Online:
				if (connectBg.getGlobalBounds().contains(mWindow.mapPixelToCoords(sf::Mouse::getPosition(mWindow))) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)) && online != nullptr)
					if (!input_text.empty() && online->connect(input_text)) {
						input_text.clear();
						addressHelp.setCharacterSize(15);
						addressHelp.setFillColor(sf::Color(200, 200, 200));
						addressHelp.setString("YOUR LOCAL PLAYER ID");
						addressHelp.setPosition(sf::Vector2f((mWindow.getSize().x / 2.f) - 285, 450));
						mCurrentState = GameState::Offline;
					}
				break;
			}
			break;

		case sf::Event::TextEntered:
			if (std::isprint(Event.text.unicode))
				if (mCurrentState == GameState::Offline && input_text.size() < 9)
					input_text += Event.text.unicode;
				else if (mCurrentState == GameState::Online && input_text.size() < 16)
					input_text += Event.text.unicode;
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


int Game::updateGame() {
	if (engine == nullptr)return 1;

	if (online != nullptr && online->getLocalPlayer() != nullptr) {
		std::stringstream ss;
		ss << online->getLocalPlayer()->getId();
		localP.setString(ss.str());
	}
	if (online != nullptr && mCurrentState == GameState::Offline && engine->getCurrentState() != EngineStates::CREATED)
		mCurrentState = GameState::MainGame;

	auto quarters = engine->getQuarters();
	for (auto& q : quarters) {
		switch (q.first) {
		case 1: playerColors[q.second] = sf::Color::Yellow; break;
		case 2: playerColors[q.second] = sf::Color::Blue; break;
		case 3: playerColors[q.second] = sf::Color::Red; break;
		case 4: playerColors[q.second] = sf::Color::Green; break;
		}
		if (playerHolders.find(q.first) == playerHolders.end()) {
			playerHolders[q.first] = new Holder(q.second, counterTexture, playerColors);
			float deg = 90.0f * (q.first - 1) * M_PI / 180.0f;
			playerHolders[q.first]->setPosition(rotate(playerHolders[q.first]->getPosition(), BoardBackground.getPosition(), deg));
		} //konstruktor dla holdera z id jako q.second //
		playerHolders[q.first]->counters = engine->getHolderCount(q.first);
		if (playerLast.find(q.first) == playerLast.end()) {
			playerLast[q.first] = new Last(q.first, engine->getPlayerContainer(q.first), counterTexture, playerColors[q.second]);
			playerLast[q.first]->rotate(BoardBackground.getPosition(), q.first - 1);
		}
	}
	diceRoll = engine->getDice();
	return 0;
}


int Game::drawMenuContent()
{

	mWindow.draw(Background);
	for (int i = 0; i < MAIN_NUMBER_OF_ITEMS; i++)
	{
		mWindow.draw(MainMenuText[i]);
	}
	return 0;
}


int Game::drawGameContent()
{

	mWindow.draw(BoardBackground);
	if (engine == nullptr)return 1;
	Player* p = engine->getCurrentPlayer();

	if (p != nullptr) {
		PlayerText = p->getNick();

		CurrentPlayerText.setString(PlayerText);
		CurrentPlayerText.setFillColor(playerColors[p->getId()]);
		mWindow.draw(CurrentPlayerText);
	}
	if (online != nullptr && p->getId() == online->getLocalPlayer()->getId())
		mWindow.draw(yourTurnText);
	mWindow.draw(currentPlayerHelp);
	mWindow.draw(diceShape);

	for (auto* tile : tiles)
		mWindow.draw((*tile));

	for (auto& c : playerHolders)
		mWindow.draw(*c.second);

	for (auto& pl : playerLast)
		mWindow.draw(*pl.second);



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

	return 0;
}


int Game::drawOptionsContent()
{
	mWindow.draw(Background);
	for (int i = 0; i < OPTIONS_NUMBER_OF_ITEMS; i++)
	{
		mWindow.draw(OptionsText[i]);
	}

	return 0;
}
void Game::drawOnlineContent() {
	address.setString(input_text);
	mWindow.draw(addressHelp);
	mWindow.draw(address);
	mWindow.draw(connectBg);
	mWindow.draw(connect);
}

int Game::drawOfflineContent()
{
	if (engine == nullptr)return 1;
	if (online != nullptr) {
		mWindow.draw(addressHelp);
		mWindow.draw(localP);
	}
	
	auto q = engine->getQuarters();
	unsigned int index = 0;
	for (auto& p : q) {
		std::stringstream ss;
		auto& pc = engine->getPlayerContainer(p.first);
		auto& player = pc.getPlayer();
		ss << player.getNick() << '\t' << player.getId() << '\t' << p.first;
		Players[index].setString(ss.str());//Ustawiæ text na bazie q.first(æwiarta) player.getId() player.getNick()
		mWindow.draw(Players[index++]);
	}
	PlusMinusNumber[2].setString(std::to_string(playerId + 1));
	text.setString(input_text);
	mWindow.draw(text);
	mWindow.draw(ButtonAdd);
	mWindow.draw(ButtonStart);
	mWindow.draw(ButtonText[0]);
	mWindow.draw(ButtonText[1]);
	mWindow.draw(ButtonPlus);
	mWindow.draw(ButtonMinus);
	mWindow.draw(quarterText);
	for (int i = 0; i < 3; i++)
	{
		mWindow.draw(OfflineText[i]);
		mWindow.draw(PlusMinusNumber[i]);
	}
	return 0;
}

/// <summary>
/// Funkcja wywo³uj¹ca odpowiednie metody rysuj¹ce w zale¿noœci od stanu (Menu g³ówne, Gra, Opcje, Koniec gry)
/// </summary>
int Game::draw() {
	switch (mCurrentState) {
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

	case GameState::Offline:
		mWindow.clear();
		Game::drawOfflineContent();
		mWindow.display();
		break;

	case GameState::Options:
		mWindow.clear();
		Game::drawOptionsContent();
		mWindow.display();
		break;

	case GameState::Online:
		mWindow.clear();
		drawOnlineContent();
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
			MainMenuText[selectedItemIndexMenu].setFillColor(sf::Color::Yellow);
			selectedItemIndexMenu--;
			MainMenuText[selectedItemIndexMenu].setFillColor(sf::Color::Red);
		};
		break;

	case GameState::Options:
		if (selectedItemIndexOptions - 1 >= 0)
		{
			OptionsText[selectedItemIndexOptions].setFillColor(sf::Color::Yellow);
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
		if (selectedItemIndexMenu + 1 < MAIN_NUMBER_OF_ITEMS)
		{
			MainMenuText[selectedItemIndexMenu].setFillColor(sf::Color::Yellow);
			selectedItemIndexMenu++;
			MainMenuText[selectedItemIndexMenu].setFillColor(sf::Color::Red);
		}
		break;

	case GameState::Options:
		if (selectedItemIndexOptions + 1 < OPTIONS_NUMBER_OF_ITEMS)
		{
			OptionsText[selectedItemIndexOptions].setFillColor(sf::Color::Yellow);
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