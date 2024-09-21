#include "ballMover.h"

static void Initialize(void* ballMover)
{
    BallMover* _ballMover = (BallMover*)ballMover;
    _ballMover->xVelocity=-1;
    _ballMover->yVelocity=1;
    return;
}

static void Update(void* ballMover, float deltaTime){
    BallMover* _ballMover = (BallMover*)ballMover;
    const int HEIGHT = _ballMover->playdateAPI->display->getHeight();
    const int WIDTH = _ballMover->playdateAPI->display->getWidth();
    if(_ballMover->position->y+_ballMover->yVelocity > HEIGHT - 10 ||
        _ballMover->position->y+_ballMover->yVelocity < 0)
        _ballMover->yVelocity*=-1;
    
    int i=0;
    for(i=0;i<2;i++){
        if(BoxColliderCollisionCheck(_ballMover->ballCollider, _ballMover->paddles[i]))
        {
            _ballMover->xVelocity*=-1;
        }
    }

    if(_ballMover->position->x+_ballMover->xVelocity > WIDTH - 10 ||
        _ballMover->position->x+_ballMover->xVelocity < 0)
        _ballMover->xVelocity*=-1; // lose
    
    _ballMover->position->y+=_ballMover->yVelocity;
    _ballMover->position->x+=_ballMover->xVelocity;

}

static void Destroy(void* ballMover){
    BallMover* _ballMover = (BallMover*)ballMover;
    _ballMover->position = NULL;
    _ballMover->realloc(ballMover,0);
}

Component *BallMoverCreate(void* (*realloc)(void*,size_t),Position* position, PlaydateAPI *pdAPI, BoxCollider* playerPaddle, BoxCollider* opponentPaddle)
{
    BallMover* _ballMover = realloc(0,sizeof(BallMover));
    Component* _ballCollider = BoxColliderCreate(realloc,10,10,position);
    _ballMover->realloc = realloc;
    _ballMover->playdateAPI=pdAPI;
    _ballMover->position=position;
    _ballMover->ballCollider=_ballCollider->data;
    _ballMover->paddles[0]=playerPaddle;
    _ballMover->paddles[1]=opponentPaddle;
    char* name = realloc(0,sizeof("BallMover"));
    strcpy(name,"BallMover");
    Component *ballMoverComponent = ComponentCreate(realloc,name,Initialize,Update,Destroy,_ballMover);
    return ballMoverComponent;
}