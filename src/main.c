#include "app.h"
#include "pd_api.h"
#include "States/states.h"

#define TEXT_HEIGHT 16
#define TEXT_HEIGHT 16
#define TEXT_WIDTH 86


PlaydateAPI *usr;
State *helloWorld;
State *helloWorld2;

void Initialize(PlaydateAPI* pd);

#ifdef _WINDLL
__declspec(dllexport)
#endif

int eventHandler(PlaydateAPI* pd, PDSystemEvent event, uint32_t arg)
{
	switch(event){
		case kEventInit:
			Initialize(pd);
			break;
		case kEventTerminate:
			Destroy(pd);
			break;
		default:
			break;
	}
	return 0;
}

int draw1(float deltatime)
{
	PlaydateAPI* pd = usr;

	int x = LCD_COLUMNS/2;
	int y = LCD_ROWS/2;
	char HWString[] = "Hello World 1\0";

	pd->graphics->clear(kColorWhite);
	pd->graphics->drawText(HWString, strlen(HWString), kASCIIEncoding, x, y);

	pd->system->drawFPS(0,0);

	PDButtons pushed;
	pd->system->getButtonState(NULL,&pushed,NULL);
	if(pushed & kButtonA)
		AppStateManager->current = helloWorld2;
	return 0;
}

int draw2(float deltatime)
{
	PlaydateAPI* pd = usr;

	int x = LCD_COLUMNS/2;
	int y = LCD_ROWS/2;
	char HWString[] = "Hello World 2\0";

	pd->graphics->clear(kColorWhite);
	pd->graphics->drawText(HWString, strlen(HWString), kASCIIEncoding, x, y);

	pd->system->drawFPS(0,0);

	PDButtons pushed;
	pd->system->getButtonState(NULL,&pushed,NULL);
	if(pushed & kButtonA)
		AppStateManager->current = helloWorld;
	return 0;
}

void Initialize(PlaydateAPI* pd)
{
	usr = pd;
	AppStateManager = pd->system->realloc(NULL,sizeof(StateManager));
	helloWorld = pd->system->realloc(NULL,sizeof(State));
	helloWorld->draw = draw1;
	helloWorld2 = pd->system->realloc(NULL,sizeof(State));
	helloWorld2->draw = draw2;
	AppStateManager->current = helloWorld;
	pd->system->setUpdateCallback(Update, pd);
}

void Destroy(PlaydateAPI* pd){

}