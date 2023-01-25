all: OnlineServer EventMsg Engine Tile PlayerContainer Player Counter Dice
	mkdir -p ./LudoGameServer_0.9-1/bin
	g++ -I ../JSON/include -I ../ZeroMQ/include -L ../ZeroMQ/lib -D ZMQ_STATIC -D __UNIX__ -D SERVER main.cpp OnlineServer.o Engine.o PlayerContainer.o Player.o Tile.o Counter.o Dice.o EventMsg.o -o ./LudoGameServer_0.9-1/bin/LudoGameServer -lzmq -std=c++17

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
	rm -f *.deb
	rm -r -f ./LudoGameServer_0.9-1
deb: all
	mkdir -p ./LudoGameServer_0.9-1/usr/share/applications
	mkdir -p ./LudoGameServer_0.9-1/usr/share/icons/hicolor/*/apps/
	mkdir -p ./LudoGameServer_0.9-1/DEBIAN/
	cp LudoGameServer.desktop ./LudoGameServer_0.9-1/usr/share/applications/
	cp icon.png ./LudoGameServer_0.9-1/usr/share/icons/hicolor/*/apps/LudoGameServerIcon.png
	touch ./LudoGameServer_0.9-1/DEBIAN/control
	echo "Package: LudoGameServer" > ./LudoGameServer_0.9-1/DEBIAN/control
	echo "Version: 0.9" >> ./LudoGameServer_0.9-1/DEBIAN/control
	echo "Architecture: all" >> ./LudoGameServer_0.9-1/DEBIAN/control
	echo "Maintainer: Jakub Jach" >> ./LudoGameServer_0.9-1/DEBIAN/control
	echo "Installed-Size: 1148" >> ./LudoGameServer_0.9-1/DEBIAN/control
	echo "Description: Ludo Game server for online play" >> ./LudoGameServer_0.9-1/DEBIAN/control
	echo " This allows you to run Ludo Game Server on your machine." >> ./LudoGameServer_0.9-1/DEBIAN/control
	dpkg-deb --build --root-owner-group LudoGameServer_0.9-1
