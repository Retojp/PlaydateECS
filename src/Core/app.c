#include"pd_api.h"
#include"app.h"
#include"src/Core/Ecs/ecsComponent.h"
#include"src/Core/Ecs/ecsEntity.h"
#include"src/Core/Scene/scene.h"
#include"src/Components/Draw/draw.h"


Application* CreateApplication(PlaydateAPI *pd){
	void* (*realloc)(void *, size_t) = pd->system->realloc;
	Application *application = realloc(0,sizeof(Application));
	application->playdateApi = pd;
	return application;
}

void SetupApplication(Application *application){
	application->playdateApi->system->logToConsole("Application Setup\0");

	Scene* mainScene = SceneCreate(application->playdateApi->system->realloc);

	Entity *entity;
	entity=EntityCreate(application->playdateApi->system->realloc);

	Component* position = PositionCreate(application->playdateApi->system->realloc,50,50);
	Component* draw = DrawCreate(application->playdateApi->system->realloc,position->data,application->playdateApi);
	EntityAddComponent(entity ,position);
	EntityAddComponent(entity, draw);

	SceneAddEntity(mainScene,entity);

	application->currentScene = mainScene;
	SceneInitialize(application->currentScene);
}

int UpdateApplication(Application *application){
	application->playdateApi->graphics->clear(kColorWhite);
	application->playdateApi->system->drawFPS(0,0);
	application->playdateApi->system->resetElapsedTime();

	float deltaTime = application->playdateApi->system->getElapsedTime(); 
	SceneUpdate(application->currentScene,deltaTime);

	return 1;
}

void DestroyApplication(Application *application){
	void* (*realloc)(void *, size_t) = application->playdateApi->system->realloc;
	SceneDestroy(application->currentScene);
	realloc(application,0);
}