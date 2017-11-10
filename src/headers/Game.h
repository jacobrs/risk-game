#ifndef GAME_H
#define GAME_H

#include "GameMap.h"
#include "Player.h"
#include "Deck.h"
#include "GameSubject.h"
#include "GameStateObserver.h"
#include "DiceRolling.h"
#include <vector>

using namespace std;

class Game{
private:
  //vector<Player*> players;
  GameMap* gameMap;
  GameSubject* stateChanges;
  GameStateObserver* stateObserver;

public:
  Game(GameMap* map, vector<Player*>);
  ~Game();
  void startGame();
  bool isWon();
  void observeGame();
  vector<Player*> players;

};

#endif
