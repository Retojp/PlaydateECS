#include "aiController.h"

static void Initialize(void* draw){
    return;
}

static void Update(void* controller, float deltaTime){
    AiController* _controller = (AiController*)controller;
    int ballY = _controller->ballPosition->y + 5;
    int paddleY = _controller->position->y + 20;
    int direction = 0;
    if(ballY>paddleY)
        direction = 1;
    else if(ballY==paddleY)
        direction = 0;
    else
        direction = -1;
    float deltaMove = direction*_controller->speed;
    if(deltaMove+_controller->position->y<0 || 
    deltaMove+_controller->position->y > _controller->playdateAPI->display->getHeight()-40)
        return;
    _controller->position->y = deltaMove+_controller->position->y;
}

static void Destroy(void* controller){
    AiController* _controller = (AiController*)controller;
    _controller->position = NULL;
    _controller->realloc(controller,0);
}

Component *AiControllerCreate(void *(*realloc)(void *, size_t), Position *position, Position *ballPosition, PlaydateAPI *pdAPI)
{
    AiController* _controller = realloc(0,sizeof(AiController));
    _controller->playdateAPI=pdAPI;
    _controller->position=position;
    _controller->realloc=realloc;
    _controller->ballPosition=ballPosition;
    _controller->speed = 1;
    char* name = realloc(0,sizeof("AiController"));
    strcpy(name,"AiController");
    Component *controllerComponent = ComponentCreate(realloc,name,Initialize,Update,Destroy,_controller);
    return controllerComponent;
}