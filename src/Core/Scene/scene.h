#ifndef scene_h
#define scene_h

#include <stdlib.h>
#include "src/Core/Utils/functionTypes.h"
#include "src/Core/Ecs/ecsEntity.h"

typedef struct Scene Scene;

Scene* SceneCreate(void* (*realloc)(void*, size_t));
void SceneInitialize(Scene* scene);
void SceneUpdate(Scene* scene,float deltaTime);
void SceneAddEntity(Scene* scene, Entity* entity);
void SceneDestroy(Scene* scene);

#endif