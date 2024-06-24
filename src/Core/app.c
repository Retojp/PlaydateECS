#include"pd_api.h"
#include"app.h"
#include"src/Core/Ecs/ecsComponent.h"
#include"src/Core/Ecs/ecsEntity.h"
#include"src/Components/Draw/draw.h"

Application* CreateApplication(PlaydateAPI *pd){
	void* (*realloc)(void *, size_t) = pd->system->realloc;
	Application *application = realloc(0,sizeof(Application));
	application->playdateApi = pd;
	return application;
}


Entity* entity; // TODO: move entities to scene system and make installer for it
void SetupApplication(Application *application){
	application->playdateApi->system->logToConsole("Application Setup\0");


	Component* position = PositionCreate(application->playdateApi->system->realloc,50,50);
	Component* draw = DrawCreate(application->playdateApi->system->realloc,position->data,application->playdateApi);
	entity=EntityCreate(application->playdateApi->system->realloc);
	EntityAddComponent(entity ,position);
	EntityAddComponent(entity, draw);
}

int UpdateApplication(Application *application){
	EntityUpdate(entity,1);
	return 1;
}

void DestroyApplication(Application *application){
	void* (*realloc)(void *, size_t) = application->playdateApi->system->realloc;
	EntityDestroy(entity);
	realloc(application,0);
}