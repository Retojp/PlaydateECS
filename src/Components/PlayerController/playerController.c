#include "playerController.h"

static void Initialize(void* draw){
    return;
}

static void Update(void* controller, float deltaTime){
    PlayerController* _controller = (PlayerController*)controller;
    float deltaMove = _controller->playdateAPI->system->getCrankChange();
    if(deltaMove+_controller->position->y<0 || 
    deltaMove+_controller->position->y > _controller->playdateAPI->display->getHeight()-40)
        return;
    _controller->position->y = deltaMove+_controller->position->y;
}

static void Destroy(void* controller){
    PlayerController* _controller = (PlayerController*)controller;
    _controller->position = NULL;
    _controller->realloc(controller,0);
}

Component *PlayerControllerCreate(void *(*realloc)(void *, size_t), Position *position, PlaydateAPI *pdAPI)
{
    PlayerController* _controller = realloc(0,sizeof(PlayerController));
    _controller->playdateAPI=pdAPI;
    _controller->position=position;
    _controller->realloc=realloc;
    char* name = realloc(0,sizeof("PlayerController"));
    strcpy(name,"PlayerController");
    Component *controllerComponent = ComponentCreate(realloc,name,Initialize,Update,Destroy,_controller);
    return controllerComponent;
}