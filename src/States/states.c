#include "states.h"

int StateManagerUpdate(StateManager *StateManager, float deltaTime){
    if(StateManager->current->update != NULL) 
        return StateManager->current->update(deltaTime);
    return -1;
}

int StateManagerDraw(StateManager *StateManager, float deltaTime){
    if(StateManager->current->draw != NULL) 
        return StateManager->current->draw(deltaTime);
    return -1;
}

int StateManagerChangeTo(StateManager *StateManager, State *newState){
    if(StateManager->current != NULL) 
        StateManager->current->exit();
    StateManager->current = newState;
    return StateManager->current->enter();
}