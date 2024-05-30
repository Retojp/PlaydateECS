#include"pd_api.h"
#include"app.h"
#include"States/states.h"

StateManager *AppStateManager;

int Update(void* userdata)
{
	usr = userdata;

	AppStateManager->current->draw(1);

	return 1;
}