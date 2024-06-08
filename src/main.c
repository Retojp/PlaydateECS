#include "app.h"
#include "pd_api.h"

static Application *application = NULL;

void Initialize(PlaydateAPI* pd);
int RawUpdate(void* userdata);

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
			if(application)
				DestroyApplication(application);
			break;
		default:
			break;
	}
	return 0;
}

void Initialize(PlaydateAPI* pd)
{
	application = CreateApplication(pd);
	SetupApplication(application);
	pd->system->setUpdateCallback(RawUpdate, application);
}

int RawUpdate(void* userdata){
	application = (Application*)userdata;
	return UpdateApplication(application);
}