#ifndef app_h
#define app_h
#include "pd_api.h"
#include "src/Core/Scene/scene.h"

typedef struct Application{
    PlaydateAPI *playdateApi;
    Scene* currentScene;
} Application;

Application* CreateApplication(PlaydateAPI *playdateApi);
void SetupApplication(Application *application);
int UpdateApplication(Application *application);
void DestroyApplication(Application *application);

#endif /*app_h*/