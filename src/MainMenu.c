#include "MainMenu.h"

MainMenu* MainMenu_create(GameEngine* engine) {
	MainMenu* this = malloc(sizeof(MainMenu));
	this->engine = engine;
	this->module = GameModule_create(this);
	this->module->destroy = MainMenu_destroy;
	this->module->init = MainMenu_init;
	this->module->update = MainMenu_update;
	return this;
}

void MainMenu_init(void* context) {
	MainMenu* this = context;
	this->scene = Scene_create(this->engine, "scenes/mainMenu.lua");
	Scene_init(this->scene);
	this->ui = UiNode_create(NULL, NULL);
}

void MainMenu_destroy(void* context) {
	CANCEL_IF_FALSE(context);
	MainMenu* this = context;
	Scene_destroy(this->scene);
	UiNode_destroy(this->ui);
	free(this);
}

void MainMenu_update(void* context, RawTime dt) {
	MainMenu* this = context;
	Scene_update(this->scene, dt);
}

void MainMenu_draw(void* context, SDL_Surface* surface) {
	MainMenu* this = context;
	Scene_draw(this->scene, surface);
	UiNode_draw(this->ui, surface);
}