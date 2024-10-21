#ifndef app_h
#define app_h
#include "pd_api.h"
#include "src/Core/Utils/Ecs/ecs.h"

typedef struct Application{
    PlaydateAPI *playdateApi;
    Ecs *ecs;
} Application;

Application* CreateApplication(PlaydateAPI *playdateApi);
void SetupApplication(Application *application);
int UpdateApplication(Application *application);
void DestroyApplication(Application *application);

#endif /*app_h*/