#include "../headers/Country.h"

using namespace std;

Country::Country(string countryName){
  armies = 0;
  owner = NULL;
  name = countryName;
  numberOfNeighbours = 0;
}

Country::Country(){
  armies = 0;
  owner = NULL;
  name = "";
  numberOfNeighbours = 0;
}

bool Country::hasEnnemies(){
  for(int n = 0; n < numberOfNeighbours; n++){
    if(neighbours[n]->owner != NULL && owner != NULL && neighbours[n]->owner != owner){
      return true;
    }
  }
  return false;
}

void Country::listEnnemies(){
  for(int n = 0; n < numberOfNeighbours; n++){
    if(neighbours[n]->owner != NULL && owner != NULL && neighbours[n]->owner != owner){
      cout << neighbours[n]->name << ", ";
    }
  }
  cout << endl;
}
string Country::getWeakestEnemy(){
  int armiesInweakestCountry = 1000;
  string weakestCountry = "";
  for(int n = 0; n < numberOfNeighbours; n++){
    if(neighbours[n]->owner != NULL && 
        owner != NULL && neighbours[n]->owner != owner && 
        neighbours[n]->armies < armiesInweakestCountry){
      cout << neighbours[n]->name << ", with "<< neighbours[n]->armies << endl;
      armiesInweakestCountry = neighbours[n]->armies;
      weakestCountry = neighbours[n]->name;
    }
  }
  return weakestCountry;
}
string Country::getRandonEnemy(){
  Country* coun = neighbours[rand()% numberOfNeighbours];
  while(coun->owner == NULL ||
        owner == NULL ||
        coun->owner == owner){
          //condition to be an enemy is not met, then randomly choose another one
          coun = neighbours[rand()% numberOfNeighbours];
        }
  return coun->name;
}

bool Country::isNeighbour(Country* c){
  for(int i = 0; i < numberOfNeighbours; i++){
    if(neighbours[i]->name == c->name){
      return true;
    }
  }
  return false;
}

void Country::addNeighbour(Country* newNeighbour){

  bool alreadyNeighbours = false;

  // Create a new array of size current + 1
  Country **newNeighbours = new Country*[++numberOfNeighbours];
  // and populate it with the old neighbours
  for(int i = 0; i < numberOfNeighbours - 1; i++){
    newNeighbours[i] = neighbours[i];
    if(neighbours[i]->name == newNeighbour->name){
      alreadyNeighbours = true;
      break;
    }
  }

  // add the new neighbour to the list if not already neighbours
  if(!alreadyNeighbours){
    newNeighbours[numberOfNeighbours - 1] = newNeighbour;
    // and make sure that the new neighbour knows its a neighbour
    neighbours = newNeighbours;
    newNeighbour->addNeighbour(this);
  }else{
    numberOfNeighbours--;
  }

}
