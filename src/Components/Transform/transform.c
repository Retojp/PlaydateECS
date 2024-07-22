#include "transform.h"

Component *DrawCreate(void *(*realloc)(void *, size_t), Position *position)
{
    Transform* newTransform = realloc(0,sizeof(Transform));
    newTransform->position = position;
    char* name = realloc(0,sizeof("Transform"));
    name = "Transform";
    Component* newComponent = ComponentCreate(realloc,name,Initialize, Update, Destroy, newTransform);
    return newComponent;
}

void Initialize(void* data){
    return;
}

void Update(void* data, float deltaTime){
    return;
}

void Destroy(void* data){
    Transform* _transform = (Transform*)data;
    _transform->position = NULL;
    _transform->realloc(data,0);
}

void Translate(Transform *transform, int deltaX, int deltaY)
{
    transform->position->x+=deltaX;
    transform->position->y+=deltaY;
}