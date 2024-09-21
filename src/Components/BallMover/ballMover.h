#ifndef ball_mover_h
#define ball_mover_h
#include "src/Core/Ecs/ecsComponent.h"
#include "src/Core/Utils/functionTypes.h"
#include "src/Components/Position/position.h"
#include "src/Components/Collision/boxCollider.h"
#include "pd_api.h"

typedef struct {
    void* (*realloc)(void*, size_t);
    Position* position;
    float yVelocity;
    float xVelocity;
    BoxCollider* ballCollider;
    BoxCollider* paddles[2];
    PlaydateAPI* playdateAPI;
} BallMover;

Component* BallMoverCreate(void* (*realloc)(void*,size_t),Position* position, PlaydateAPI *pdAPI, BoxCollider* playerPaddle,BoxCollider* opponentPaddle);

#endif