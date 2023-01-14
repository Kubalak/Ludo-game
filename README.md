# Projekt gra chiñczyk.

# CHANGELOG

# v0.6.2
- Przeniesienie metody `Engine::step()` (wybranie nastêpnego gracza) do czêœci prywatnej (wywo³anie automatyczne po udanym ruchu).
- Usuniêcie metody `step()` z klas dziedzicz¹cych z `Engine` i sprawdzenie poprawnoœci dzia³ania silnika po zmianach.
- Silnik online automatycznie wysy³a komunikat o wykonaniu ruchu w przypadku braku mo¿liwoœci ruchu gracza tj. po rzucie kostk¹.
- Dodanie skryptu do przygotowania bibliotek (<a href='https://github.com/nlohmann/json'>`JSON`</a>, <a href="https://github.com/zeromq/cppzmq" target="blank">ZeroMQ</a>) dla systemu Linux.
- Dodanie pliku makefile umo¿liwiaj¹cego kompilacjê serwera dla systemu Linux.
- Poprawki w dokumentacji.
- Poprawki zgodnoœci i spójnoœci komunikatów klientów i serwera (<strong style="color:green;">OK</strong> / <strong style="color:red;">--</strong> ).

# v0.5.3
- Wersja beta silnika online i serwera online
- Modyfikacja czêœci klas aby mo¿liwe by³o przesy³anie danych przez sieæ.
- Poprawki b³êdów<br/>
## <strong>Znany b³¹d:</strong><br/>
Kiedy klient nie jest pod³¹czony do serwera a metoda connect zosta³a wywo³ana, wówczas próba usuniêcia silnika blokuje w¹tek.

# v0.3.1
- Dodanie obs³ugi eksportu obiektów do <a href='https://github.com/nlohmann/json'>`JSON`</a>
- Obs³uga tworzenia silnika z obiektu <a href='https://github.com/nlohmann/json'>`JSON`</a>
- Graficzna prezentacja stanu silnika

# v0.0.1.0
- Dodano bibliotekê <a href="https://zeromq.org/" target="blank">ZeroMQ.</a>
- Uproszczono relacje projektów.
- Generowanie UUID z u¿yciem <a href="https://github.com/crashoz/uuid_v4" target="blank">uuid_v4</a>
- Rozpoczêto prace nad silnikiem w wersji online.

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