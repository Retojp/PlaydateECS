#include "scene.h"
#include "src/Core/Utils/Array/array.h"

typedef struct SceneImpl{
    void* (*realloc)(void*,size_t);
    Array* entities; 
} SceneImpl;

Scene *SceneCreate(void *(*realloc)(void *, size_t))
{
    SceneImpl* scene = realloc(0,sizeof(SceneImpl));
    scene->realloc = realloc;
    scene->entities = ArrayCreate(EntityGetSize(), realloc);
    return (Scene*)scene;
}

void SceneInitialize(Scene *scene)
{
    SceneImpl* _scene = (SceneImpl*)scene;
    int entitiesCount = ArrayGetSize(_scene->entities);
    int i=0;
    for(i=0;i<entitiesCount;i++){
        Entity* entity = ArrayGetElementAt(_scene->entities,i);
        EntityInitialize(entity);
    }
}

void SceneUpdate(Scene *scene, float deltaTime)
{
    SceneImpl* _scene = (SceneImpl*)scene;
    int entitiesCount = ArrayGetSize(_scene->entities);
    int i=0;
    for(i=0;i<entitiesCount;i++){
        Entity* entity = ArrayGetElementAt(_scene->entities,i);
        EntityUpdate(entity, deltaTime);
    }
}

void SceneAddEntity(Scene *scene, Entity *entity)
{
    SceneImpl* _scene = (SceneImpl*)scene;
    ArrayAddElement(_scene->entities,entity);
}

void SceneDestroy(Scene *scene)
{
    SceneImpl* _scene = (SceneImpl*)scene;
    int entitiesCount = ArrayGetSize(_scene->entities);
    int i=0;
    for(i=0;i<entitiesCount;i++){
        Entity* entity = ArrayGetElementAt(_scene->entities,i);
        EntityDestroy(entity);
    }
    _scene = _scene->realloc(_scene,0);
}
