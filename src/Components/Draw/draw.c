#include "draw.h"


//TODO: its proof of concept and should be more focudes on sprites to be viable as draw component
static void Initialize(void* draw){
    return;
}

static void Update(void* draw, float deltaTime){
    Draw* _draw = (Draw*)draw;
    _draw->playdateAPI->graphics->drawRect(_draw->position->x,_draw->position->y,10,10,kColorBlack);
}

static void Destroy(void* draw){
    Draw* _draw = (Draw*)draw;
    _draw->position = NULL;
    _draw->realloc(draw,0);
}

Component *DrawCreate(void* (*realloc)(void*,size_t),Position* position, PlaydateAPI* pdAPI)
{
    Draw* _draw = realloc(0,sizeof(Draw));
    _draw->realloc = realloc;
    _draw->playdateAPI=pdAPI;
    _draw->position=position;
    Component *drawComponent = ComponentCreate(realloc,Initialize,Update,Destroy,_draw);
    return drawComponent;
}