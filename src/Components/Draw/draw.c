#include "draw.h"
#include <stdlib.h>

static void Initialize(void* draw){
    return;
}

static void Update(void* draw, float deltaTime){
    Draw* _draw = (Draw*)draw;
    _draw->playdateAPI->graphics->drawRect(_draw->position->x,_draw->position->y,_draw->width,_draw->height,kColorBlack);
}

static void Destroy(void* draw){
    Draw* _draw = (Draw*)draw;
    _draw->position = NULL;
    _draw->realloc(draw,0);
}

Component *DrawCreate(void* (*realloc)(void*,size_t),Position* position,int width,int height, PlaydateAPI* pdAPI)
{
    Draw* _draw = realloc(0,sizeof(Draw));
    _draw->width=width;
    _draw->height=height;
    _draw->realloc = realloc;
    _draw->playdateAPI=pdAPI;
    _draw->position=position;
    char* name = realloc(0,sizeof("Draw"));
    strcpy(name,"Draw");
    Component *drawComponent = ComponentCreate(realloc,name,Initialize,Update,Destroy,_draw);
    return drawComponent;
}