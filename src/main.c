#include <stdio.h>
#include <stdlib.h>

#include "pd_api.h"

#define TEXT_HEIGHT 16
#define TEXT_HEIGHT 16
#define TEXT_WIDTH 86

static int update(void* userdata);

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
		default:
		break;
	}
	return 0;
}

void Initialize(PlaydateAPI* pd)
{
	pd->system->setUpdateCallback(update, pd);
}


static int update(void* userdata)
{
	PlaydateAPI* pd = userdata;
	
	int x = LCD_COLUMNS/2;
	int y = LCD_ROWS/2;
	char HWString[] = "Hello World!";

	pd->graphics->clear(kColorWhite);
	pd->graphics->drawText(HWString, strlen(HWString), kASCIIEncoding, x, y);

	pd->system->drawFPS(0,0);

	return 1;
}