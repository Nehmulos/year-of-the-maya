#pragma once

#include "Constants.h"
#include "AnimatedSprite.h"
#include "List.h"
#include "Camera.h"
#include "Combo.h"

#define COLLISION_GROUP_DEFAULT 1
#define COLLISION_GROUP_PLAYER 1 << 2

#define PHYSICS_SCALE 6

typedef struct Scene Scene;
CLASS(EntityPhysics) {
	Scene* scene;
	int dx, dy;
	SDL_Rect bounds;
	int weight;

	int groups;
	int groupMask;
};

CLASS(Entity) {
	AnimatedSprite* animatedSprite;
	bool destroyed;
	EntityPhysics physics;

	void (*destroy)(void* context);
	void (*update)(void* context, RawTime dt);
	void (*draw)(void* context, SDL_Renderer*, Camera* camera);
	Scene* scene;
	void* context;
	List* hitboxes;

	Vector* combos;
	Combo* currentCombo;
	RawTime timeSinceLastComboAction;
	const char* currentComboName;
};

Entity* Entity_create(void* context, Scene* scene, AnimatedSprite* sprite);
void Entity_destroy(Entity* this);

void Entity_update(Entity* this, RawTime dt);
bool Entity_collides(Entity* this, Entity* other);
bool Entity_wouldCollide(Entity* this, SDL_Rect *rect);
void Entity_performComboAction(Entity* this, ActionId action);
void Entity_resetComboProgress(Entity* this);

void EntityPhysics_init(EntityPhysics* this, Sprite* sprite);
void Entity_emptyDraw(void* context, SDL_Renderer* screen, Camera* camera);
