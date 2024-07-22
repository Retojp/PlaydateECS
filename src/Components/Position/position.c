#include "position.h"

static void Update(void* position, float deltaTime){
    return;
}

static void Initialize(void* position){
    return;
}

static void Destroy(void* position)
{
    Position* _position = (Position*)position;
    _position->realloc(position,0);
}

Component *PositionCreate(void *(*realloc)(void *, size_t),int x,int y)
{
    Position* _position = realloc(0,sizeof(Position));
    _position->realloc = realloc;
    _position->x = x;
    _position->y = y;
    char* name = realloc(0,sizeof("Position"));
    strcpy(name,"Position");
    Component* positionComponent = ComponentCreate(realloc,name,Initialize,Update,Destroy,_position);
    return positionComponent;
}