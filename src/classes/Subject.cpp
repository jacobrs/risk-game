#include "../headers/Subject.h"
#include "../headers/Observer.h"


Subject::Subject(){
    _observers = new list<Observer*>;
};

Subject::~Subject(){
    delete _observers;
};

//Add observers
void Subject::Attach(Observer* o){
    _observers -> push_back(o);
};

//Remove observers
void Subject::Detach(Observer* o){
    _observers -> remove(o);
};


void Subject::Notify(){
    list<Observer*>::iterator i = _observers->begin();
    for(; i != _observers->end(); ++i){
        (*i)->update();    
    }
};

// Notification methods when the attack phase is observed
void Subject::NotifyAttack(int a, string attackName, string defendName, int aa, int da, bool conquered){
    list<Observer*>::iterator i = _observers->begin();
    for(; i != _observers->end(); ++i){
        (*i)->updateAttack(a, attackName, defendName, aa, da, conquered);    
    }
};

// Notification methods when the reinforcement phase is observed
void Subject::NotifyReinforce(int r, int p, string where){
    list<Observer*>::iterator i = _observers->begin();
    for(; i != _observers->end(); ++i){
        (*i)->updateReinforce(r, p, where);    
    }
};

// Notification methods when the fortify phase is observed
void Subject::NotifyFortify(int f, string a, string b, int m){
    list<Observer*>::iterator i = _observers->begin();
    for(; i != _observers->end(); ++i){
        (*i)->updateFortify(f, a, b, m);    
    }
};
