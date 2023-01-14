all: OnlineServer EventMsg Engine Tile PlayerContainer Player Counter Dice
	g++ -I ../JSON/include -I ../ZeroMQ/include -L ../ZeroMQ/lib -D ZMQ_STATIC -D __UNIX__ -D SERVER main.cpp OnlineServer.o Engine.o PlayerContainer.o Player.o Tile.o Counter.o Dice.o EventMsg.o -o LudoGameServer -lzmq -std=c++17

Dice:
	g++ -c Dice.cpp -std=c++17

Counter:
	g++ -c Counter.cpp -std=c++17

Player: Counter
	g++ -c -I ../JSON/include Player.cpp -std=c++17

Tile: Counter
	g++ -c -I ../JSON/include Tile.cpp -std=c++17

EventMsg:
	g++ -c -D __UNIX__ EventMsg.cpp -std=c++17

PlayerContainer: Player Counter
	g++ -c -I ../JSON/include PlayerContainer.cpp -std=c++17

Engine: PlayerContainer Dice Tile
	g++ -c -I ../JSON/include Engine.cpp -std=c++17

OnlineServer: Engine
	g++ -c -I ../JSON/include -I ../ZeroMQ/include -L ../ZeroMQ/lib -D ZMQ_STATIC OnlineServer.cpp -lzmq -std=c++17

clean:
	rm -f *.o
