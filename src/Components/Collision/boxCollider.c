#include "boxCollider.h"

static void Initialize(void* draw){
    return;
}

static void Update(void* collider, float deltaTime){
    return;
}

static void Destroy(void* collider){
    BoxCollider* _collider = (BoxCollider*)collider;
    _collider->realloc(collider,0);
}

Component *BoxColliderCreate(void *(*realloc)(void *, size_t), int width, int height, Position* position)
{
    BoxCollider* _collider = realloc(0,sizeof(BoxCollider));
    _collider->realloc = realloc;
    _collider->height=height;
    _collider->width=width;
    _collider->position=position;
    char* name = realloc(0,sizeof(BOX_COLLIDER_COMPONENT_NAME));
    strcpy(name,BOX_COLLIDER_COMPONENT_NAME);
    Component *boxColliderComponent = ComponentCreate(realloc,name,Initialize,Update,Destroy,_collider);
    return boxColliderComponent;
}

int BoxColliderCollisionCheck(BoxCollider *box1, BoxCollider *box2)
{
    int x1 = box1->position->x;
    int y1 = box1->position->y;
    int w1 = box1->width;
    int h1 = box1->height;

    int x2 = box2->position->x;
    int y2 = box2->position->y;
    int w2 = box2->width;
    int h2 = box2->height;

    if(x1>(x2+w2) || x2>(x1+w1)) 
        return 1;
    if(y1>(y2+h2) || y2>(y1+h1))
        return 1;
    return 0;
}
