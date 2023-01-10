# Projekt gra chi�czyk.

# CHANGELOG <i>(zmiany widoczne poni�ej)</i>

# v0.5.3
- Wersja beta silnika online i serwera online
- Modyfikacja cz�ci klas aby mo�liwe by�o przesy�anie danych przez sie�.
- Poprawki b��d�w<br/>
## <strong>Znany b��d:</strong><br/>
Kiedy klient nie jest pod��czony do serwera a metoda connect zosta�a wywo�ana, w�wczas pr�ba usuni�cia silnika blokuje w�tek.

# v0.3.1
- Dodanie obs�ugi eksportu obiekt�w do <a href='https://github.com/nlohmann/json'>`JSON`</a>
- Obs�uga tworzenia silnika z obiektu <a href='https://github.com/nlohmann/json'>`JSON`</a>
- Graficzna prezentacja stanu silnika

# v0.0.1.0
- Dodano bibliotek� <a href="https://zeromq.org/" target="blank">ZeroMQ.</a>
- Uproszczono relacje projekt�w.
- Generowanie UUID z u�yciem <a href="https://github.com/crashoz/uuid_v4" target="blank">uuid_v4</a>
- Rozpocz�to prace nad silnikiem w wersji online.

# v0.0.0.4
- Fixed known Engine issues (index out of bounds and nullptr exception).
- Code refactorization.
- Prepared for GUI version.

# v0.0.0.3
- Added more logic to `CounterContainer`, `Dice`, `Player`, `Tile`, `Engine`, etc.
- Methods have been shortened to provide better standards.
# v0.0.0.2
 - Created basic classess for Player, Dice, Counter and CounterContainer.
 - Started creating game logic.
# v0.0.0.1
- Created the project
- Added <a href='https://github.com/nlohmann/json'>`JSON`</a> library