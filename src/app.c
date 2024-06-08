#include"pd_api.h"
#include"app.h"

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
	free(application);
}
