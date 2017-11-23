#include "headers/Player.h"
#include "headers/Country.h"
#include "headers/Continent.h"
#include "headers/GameMap.h"
#include "headers/HumanPlayer.h"
#include "headers/AggressivePlayer.h"
#include "headers/BenevolentPlayer.h"
#include "headers/GameStart.h"
#include "headers/StartupPhase.h"
#include "headers/Game.h"
#include "headers/GameView.h"
#include "headers/CountryObserverDecorator.h"
#include "headers/HandObserverDecorator.h"

#include <iostream>
#include <string>

using namespace std;

int main(){

  srand (time(NULL)); 

  string selectedMap;
  int numOfPlayers = 0;
  bool promptPlayers = true;
  bool promptMap = true;

  bool dominationDecorator = false;
  bool handDecorator = false;
  bool continentDecorator = false;
     
  // Validates the number of players
  while (promptPlayers){
    cout << "Number of Players between 2-6: " << endl;
    cin >> numOfPlayers;

    if (numOfPlayers < 2 || numOfPlayers >6){ 
      cout << "Please enter correct number of players" << endl;
    } 
    else{
      promptPlayers =false;
    }
  }
  //validates the map chosen
  while (promptMap){
    cout << "Select Map File: Khoras or World" << endl;
    cin >> selectedMap;

    if (selectedMap.compare("Khoras") == 0 || selectedMap.compare("World") == 0){ 
      promptMap =false;
    } 
    else{
      cout << "Please enter the correct filename" << endl;
    }
  }

  GameStart* newGame = new GameStart(selectedMap, numOfPlayers);
  GameMap* map = newGame -> gameMap;

  string playerType = "";
  for(int i = 0; i < newGame->players.size(); i++){
    newGame->players.at(i)->setStrategy(new AggressivePlayer());
  }

  StartupPhase* startGame = new StartupPhase(newGame->gameMap, newGame->players);
  Game *game = new Game(newGame->gameMap, newGame->players);
  
  for(int j = 0; j < 10; j++){
    for(int i = 0; i<game->players.size(); i++){
      char input;
      
      if(!dominationDecorator){
        cout << "Enable domination decorator? [Yy]" << endl;
        cin >> input;
        if(toupper(input) == 'Y'){
          game->stateChanges->Attach(new CountryObserverDecorator(game->stateObserver));
          dominationDecorator = true;
        }
      }

      if(!handDecorator){
        cout << "Enable hand decorator? [Yy]" << endl;
        cin >> input;
        if(toupper(input) == 'Y'){
          game->stateChanges->Attach(new HandObserverDecorator(game->stateObserver));
          handDecorator = true;
        }
      }
      
      game->players.at(i)->reinforce(map);
      game->stateChanges->Notify(map, game->players);
      game -> players.at(i) -> attack(map);
      game -> players.at(i)->hand->addCard(newGame->playDeck->draw());
      game->stateChanges->Notify(map, game->players);

    }
  }
  return 0;
}

