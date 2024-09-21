#include"pd_api.h"
#include"app.h"
#include"src/Core/Ecs/ecsComponent.h"
#include"src/Core/Ecs/ecsEntity.h"
#include"src/Core/Scene/scene.h"
#include"src/Components/Draw/draw.h"
#include"src/Components/PlayerController/playerController.h"
#include"src/Components/AiController/aiController.h"
#include"src/Components/Collision/boxCollider.h"
#include"src/Components/BallMover/ballMover.h"

Entity* CreatePlayerPaddle(Application *application, int vertical_position)
{
	Entity *entity = EntityCreate(application->playdateApi->system->realloc);
	Component* position = PositionCreate(application->playdateApi->system->realloc,vertical_position,40);
	Component* draw = DrawCreate(application->playdateApi->system->realloc,position->data,10,40,application->playdateApi);
	Component* boxCollider = BoxColliderCreate(application->playdateApi->system->realloc,10,40,position->data);
	Component* playerController = PlayerControllerCreate(application->playdateApi->system->realloc,position->data,application->playdateApi);
	EntityAddComponent(entity, playerController);
	EntityAddComponent(entity, position);
	EntityAddComponent(entity, draw);
	EntityAddComponent(entity, boxCollider);
	return entity;
}


Entity* CreateOpponentPaddle(Application *application, int vertical_position)
{
	Entity *entity = EntityCreate(application->playdateApi->system->realloc);
	Component* position = PositionCreate(application->playdateApi->system->realloc,vertical_position,40);
	Component* draw = DrawCreate(application->playdateApi->system->realloc,position->data,10,40,application->playdateApi);
	Component* boxCollider = BoxColliderCreate(application->playdateApi->system->realloc,10,40,position->data);
	EntityAddComponent(entity, position);
	EntityAddComponent(entity, draw);
	EntityAddComponent(entity, boxCollider);
	return entity;
}

Entity* CreateBall(Application *application, int vertical_position,BoxCollider* playerPaddle, BoxCollider* opponentPaddle)
{
	Entity *entity = EntityCreate(application->playdateApi->system->realloc);
	Component* position = PositionCreate(application->playdateApi->system->realloc,vertical_position,40);
	Component* draw = DrawCreate(application->playdateApi->system->realloc,position->data,10,10,application->playdateApi);
	Component* ballMover = BallMoverCreate(application->playdateApi->system->realloc,position->data,application->playdateApi,playerPaddle, opponentPaddle);
	EntityAddComponent(entity ,position);
	EntityAddComponent(entity, draw);
	EntityAddComponent(entity, ballMover);
	return entity;
}

Application* CreateApplication(PlaydateAPI *pd){
	void* (*realloc)(void *, size_t) = pd->system->realloc;
	Application *application = realloc(0,sizeof(Application));
	application->playdateApi = pd;
	return application;
}

void SetupApplication(Application *application){
	application->playdateApi->system->logToConsole("Application Setup\0");
	srand(application->playdateApi->system->getCurrentTimeMilliseconds());
	Scene* mainScene = SceneCreate(application->playdateApi->system->realloc);

	int HEIGHT = application->playdateApi->display->getHeight();
	int WIDTH = application->playdateApi->display->getWidth();
	
	Entity* playerPaddle = CreatePlayerPaddle(application,10);

	Entity* opponentPaddle = CreateOpponentPaddle(application,WIDTH-20);

	Entity* ball = CreateBall(application,WIDTH/2-5,EntityGetComponent(playerPaddle,"BoxCollider")->data,EntityGetComponent(opponentPaddle,"BoxCollider")->data);
	
	Component* aiController = AiControllerCreate(application->playdateApi->system->realloc,EntityGetComponent(opponentPaddle,"Position")->data,EntityGetComponent(ball,"Position")->data,application->playdateApi);
	EntityAddComponent(opponentPaddle, aiController);

	SceneAddEntity(mainScene,playerPaddle);
	SceneAddEntity(mainScene,opponentPaddle);
	SceneAddEntity(mainScene,ball);
	application->currentScene = mainScene;
	SceneInitialize(application->currentScene);
}


int UpdateApplication(Application *application){
	application->playdateApi->graphics->clear(kColorWhite);
	application->playdateApi->system->drawFPS(0,0);

	float deltaTime = application->playdateApi->system->getElapsedTime(); 


	SceneUpdate(application->currentScene,deltaTime);

	application->playdateApi->system->resetElapsedTime();
	return 1;
}

void DestroyApplication(Application *application){
	void* (*realloc)(void *, size_t) = application->playdateApi->system->realloc;
	SceneDestroy(application->currentScene);
	realloc(application,0);
}