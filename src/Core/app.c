#include"pd_api.h"
#include"app.h"
#include"src/Core/Ecs/ecsComponent.h"
#include"src/Core/Ecs/ecsEntity.h"

Application* CreateApplication(PlaydateAPI *pd){
	void* (*realloc)(void *, size_t) = pd->system->realloc;
	Application *application = realloc(0,sizeof(Application));
	application->playdateApi = pd;
	return application;
}

void SetupApplication(Application *application){
	application->playdateApi->system->logToConsole("Application Setup\0");
}

int UpdateApplication(Application *application){
	return 1;
}

void DestroyApplication(Application *application){
	void* (*realloc)(void *, size_t) = application->playdateApi->system->realloc;
	realloc(application,0);
}