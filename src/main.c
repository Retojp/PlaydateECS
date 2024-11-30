#include "src/Core/app.h"
#include "src/Core/Utils/SparseSet/SparseSet.h"

void SetupApplication(Application* app){
    SparseSet* ss;
    ss = SparseSetCreate(app->playdateApi->system->realloc,120,sizeof(int));
    for (int i = 0; i < 120; i++)
    {
        app->playdateApi->system->logToConsole("%d",i);
        SparseSetAdd(ss,i,&i);
    }
    
    return;
}

int UpdateApplication(Application* app){
    return 1;
}