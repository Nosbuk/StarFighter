# Dokumentacja Techniczna: Projekt „StarFighter”

## Opis projektu

„StarFighter” to dwuwymariowa gra komputerowa rozwijana w języku C++ i opublikowana na platformie GitHub. Niniejsza dokumentacja ma na celu zaprezentowanie struktury kodu źródłowego, jego kluczowych komponentów oraz głównych założeń projektu.

## Struktura projektu

1. **Kod źródłowy**: Główny kod źródłowy projektu znajduje się w katalogu `src/`. Jest on podzielony na klasy odpowiadjące za wszystkie obiekty pojawiające się na ekranie

2. **Biblioteki zewnętrzne**: Projekt korzysta z następujących komponentów bibioteki SFML: -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network. Niektóre z nich nie są potrzebne do działania programu ale są uwzględnione do przyszłego developmentu.

3. **Zasoby**: Wszystkie zasoby gry, takie jak tekstury i fonty, są przechowywane w katalogu `assets/`.

## Główne komponenty

1. **Game**: Główny obiekt odpowiadający za wykonanie metody `run()`, w której wykonuje się główny loop odpowiadający za renderowanie kolejnych klatek.

2. **Entity**: Obiekt w którym zawarta jest logika geometrii i przemieszczania. Wszystkie inne obiekty oprócz `Game` dziedziczą wszystkie metody i własności po tej klasie.

3. **Alive**: Obiekt w którym zawarta jest logika punktów wytrzymałość `HP` i metody do manipulacji tą wartością. Dziedziczą z niej klasy Enemy i Player

4. **Player**: Obiekt w którym zawarta jest logika i własności pionka gracza jak i wektor przechowujący wszystkie pociski wystrzelone przez gracza.

5. **Enemy**: Obiekt w którym zawarta jest logika i własności pionków przeciwników.

6. **Bullet**: Obiekt w którym zawarta jest logika i własności pocisków wystrzeliwanych przez gracza.

## Instrukcje kompilacji i uruchomienia

1. Pobierz HomeBrew: [https://brew.sh/](https://brew.sh/)

2. W terminalu wpisz: `brew install sfml` (lub `apt get sfml` dla systemu Linux).

3. Aby skompilować i uruchomić grę (wymaga g++, który jest dostępny w zestawie narzędzi Xcode SDK), użyj poniższej komendy:

```bash
g++ ./src/main.cpp -I/usr/local/Cellar/sfml/2.5.1_2/include -o StarFighter -L/usr/local/Cellar/sfml/2.5.1_2/lib/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network && ./StarFighter
```
