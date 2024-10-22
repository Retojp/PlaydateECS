#include"pd_api.h"
#include"app.h"
#include"src/Core/Utils/SparseSet/SparseSet.h"

typedef struct testS{
	int id;
	char string[5];
}testS;

int getIndex(void* element){
	testS* _testS = (testS*)element;
	return _testS->id;
}

void iterate(void* element,void* userdata){
	testS* _testS = (testS*)element;
	PlaydateAPI* pdApi = (PlaydateAPI*)userdata;
	pdApi->system->logToConsole(_testS->string);
}

void setElement(Array* array, int id, void* element){
	testS* _testS = ArrayGetElementAt(array,id);
	memcpy(_testS,element,sizeof(testS));
}

Application* CreateApplication(PlaydateAPI *pd){
	void* (*realloc)(void *, size_t) = pd->system->realloc;
	Application *application = realloc(0,sizeof(Application));
	application->playdateApi = pd;
	application->ecs=EcsCreate(pd->system->realloc);
	return application;
}

void testSIIterate1(componentPtr component, userdataPtr userdata){
	PlaydateAPI* pdApi = (PlaydateAPI*)userdata;
	testS* _tests = (testS*)component;
	pdApi->system->logToConsole(_tests->string);
}

void SetupApplication(Application *application){
	testS test1 = {.id=2,.string="dupa\0"};
	testS test2 = {.id=4,.string="dup2\0"};
	testS test3 = {.id=1,.string="dup3\0"};
	testS test4 = {.id=4,.string="dup4\0"};

	int testSId = EcsRegisterComponent(application->ecs, sizeof(testS),getIndex,setElement);
	
	EcsAddComponentTo(application->ecs,testSId,&test1);
	EcsAddComponentTo(application->ecs,testSId,&test4);
	EcsAddComponentTo(application->ecs,testSId,&test2);
	EcsAddComponentTo(application->ecs,testSId,&test3);
	EcsRemoveComponentFrom(application->ecs,testSId,2);
	EcsRemoveComponentFrom(application->ecs,testSId,2);

	testS *retrieved = EcsGetComponent(application->ecs,2,testSId);
	retrieved = EcsGetComponent(application->ecs,4,testSId);

	application->playdateApi->system->logToConsole(retrieved->string);
	application->playdateApi->system->logToConsole("------");

	EcsIterateOver(application->ecs,testSId,testSIIterate1,application->playdateApi);
	// SparseSetIterate(ecs,iterate,application->playdateApi);
	return;
}

int UpdateApplication(Application *application){
	application->playdateApi->graphics->clear(kColorWhite);
	application->playdateApi->system->drawFPS(0,0);
	application->playdateApi->system->resetElapsedTime();
	return 1;
}

void DestroyApplication(Application *application){
	EcsDestroy(application->ecs);
	void* (*realloc)(void *, size_t) = application->playdateApi->system->realloc;
	realloc(application,0);
	return;
}