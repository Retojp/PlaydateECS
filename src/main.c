#include "src/Core/app.h"
#include "src/Core/Components/vector2.h"
int positionId;
int velocityId;

struct MoveUserdata{
    Application* app;
};

void Move(void* componentData, int entityId, void* userdata){
    vector2* position = (vector2*)componentData;
    struct MoveUserdata* _userdata = (struct MoveUserdata*)userdata;
    vector2* velocity = EcsGetComponent(_userdata->app->ecs,velocityId,entityId);
    if(velocity == NULL){
        return;
    }
    if(position->x+velocity->x > 300 || position->x+velocity->x<0) velocity->x *=-1;
    if(position->y+velocity->y > 200 || position->y+velocity->y<0) velocity->y *=-1;
    position->x+=velocity->x;
    position->y+=velocity->y;

    _userdata->app->playdateApi->graphics->drawEllipse(position->x,position->y,10,10,3,0,360,kColorBlack);
}

void SetupApplication(Application* app){
    positionId = EcsRegisterComponent(app->ecs,sizeof(vector2));
    velocityId = EcsRegisterComponent(app->ecs,sizeof(vector2));

    for (int i = 0; i < 1000; i++)
    {
        vector2 position = {.x=rand()%100+10,.y=rand()%100+10};
        vector2 velocity = {.x=rand()%5+1,.y=rand()%5+1};
        EcsAddComponentTo(app->ecs,positionId,i,&position);
        EcsAddComponentTo(app->ecs,velocityId,i,&velocity);
    }
    
    app->playdateApi->system->logToConsole("%d", EcsGetComponent(app->ecs,positionId,999));
    return;
}

int UpdateApplication(Application* app){
    app->playdateApi->graphics->clear(kColorWhite);
    app->playdateApi->system->drawFPS(10,220);
    struct MoveUserdata userdata = {.app=app};
    EcsIterateOver(app->ecs,positionId,Move,&userdata);
    return 1;
}