#include"pd_api.h"
#include"app.h"
#include"src/Core/Utils/SparseSet/SparseSet.h"

Application* CreateApplication(PlaydateAPI *pd){
	void* (*realloc)(void *, size_t) = pd->system->realloc;
	Application *application = realloc(0,sizeof(Application));
	application->playdateApi = pd;
	application->ecs=EcsCreate(pd->system->realloc);
	return application;
}

void DestroyApplication(Application *application){
	EcsDestroy(application->ecs);
	void* (*realloc)(void *, size_t) = application->playdateApi->system->realloc;
	realloc(application,0);
	return;
}