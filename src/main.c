#include "app.h"
#include "pd_api.h"

#define TEXT_HEIGHT 16
#define TEXT_HEIGHT 16
#define TEXT_WIDTH 86

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
	pd->system->setUpdateCallback(Update, pd);
}