#ifndef app_h
#define app_h
#include "States/states.h"
#include "pd_api.h"

extern StateManager *AppStateManager;
extern PlaydateAPI *usr;

int Update(void* userdata);

#endif /*app_h*/