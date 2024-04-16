#include"pd_api.h"
#include"app.h"

int Update(void* userdata)
{
	PlaydateAPI* pd = userdata;

	int x = LCD_COLUMNS/2;
	int y = LCD_ROWS/2;
	char HWString[] = "Hello World";

	pd->graphics->clear(kColorWhite);
	pd->graphics->drawText(HWString, strlen(HWString), kASCIIEncoding, x, y);

	pd->system->drawFPS(0,0);

	return 1;
}