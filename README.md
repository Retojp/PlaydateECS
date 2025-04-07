Playdate ECS Engine

How to use
1. First you need to download dependencies:
 - PlaydateSDK >= 2.5.0 (can be higher but it's created on 2.5.0)
 - GNU Make >= 4.3
 - gcc eabi for playdate sdk
 - visual studio code
2. Setup env varialbe 'PLAYDATE_SDK_PATH' to path to your PlaydateSDK.
3. Download project and open in visual studio code.
4. In main.c you can implement 2 engine functions.

Setup executes once at start of application
```
void SetupApplication(Application *application);
```
Update executes every frame
```
int UpdateApplication(Application *application);
```

Application struct is defined by:
```
struct Application{
    PlaydateAPI *playdateApi;
    Ecs *ecs;
};
```

PlaydateAPI is pointer of PlaydateSDK

Ecs pointer is used for operations on well... ECS.

Register Component to ECS of given size - return id of component type
```
int EcsRegisterComponent(Ecs *ecs, size_t componentSize);
```

Add to Ecs entity of registered component type identyfied by id, of given entityId, and given data referenced by pointer.
```
void EcsAddComponentTo(Ecs *ecs, int componentType, int entityId, componentPtr component);
```

Remove from ecs entity of given type id by entity id
```
void EcsRemoveComponentFrom(Ecs* ecs, int componentType, int entityId);
```

Iterate over entities of given type id executing "iterateFunc" passing userdata.
```
void EcsIterateOver(Ecs *ecs, int componentType, void (*iterateFunc)(componentPtr, int, userdataPtr),userdataPtr userdata);
```

1 argument is a pointer to entity component data,
2 argument is an id of entity,
3 argument is a pointer to passed userdata 
```
void (*iterateFunc)(componentPtr, int, userdataPtr)
```

Get given component data of entity of given entityId
```
void *EcsGetComponent(Ecs *ecs, int componentType, int entityId);
```