#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleMenuScene.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneIntro.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"

#include <fstream>
#include <iostream>

using namespace std;

ModuleMenuScene::ModuleMenuScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	menuBg.x = 20;
	menuBg.y = 7;
	menuBg.w = 256;
	menuBg.h = 160;

	subMenu.x = 284;
	subMenu.y = 132;
	subMenu.w = 96;
	subMenu.h = 83;

	scoreMenu.x = 99;
	scoreMenu.y = 1403;
	scoreMenu .w = 208;
	scoreMenu.h = 80;

	scorePrint.x = 388;
	scorePrint.y = 618;
	scorePrint.w = 35;
	scorePrint.h = 10;

	mapSelector.x = 20;
	mapSelector.y = 266;
	mapSelector.w = 256;
	mapSelector.h = 168;

	mapSelection.PushBack({ 18, 457, 72, 112 });
	mapSelection.PushBack({ 0, 0, 0, 0 });
	mapSelection.speed = 0.04f;

	pressStart.PushBack({319, 19, 84, 8});
	pressStart.PushBack({319, 29, 84, 8});
	pressStart.speed = 0.04f;

	flipper.PushBack({ 406, 24, 13, 8 });
	flipper.PushBack({ 406, 24, 13, 8 });
	flipper.PushBack({ 406, 24, 13, 8 });
	flipper.PushBack({ 406, 24, 13, 8 });
	flipper.PushBack({ 421, 24, 13, 8 });
	flipper.PushBack({ 436, 24, 13, 8 });
	flipper.PushBack({ 436, 24, 13, 8 });
	flipper.PushBack({ 436, 24, 13, 8 });
	flipper.PushBack({ 436, 24, 13, 8 });
	flipper.PushBack({ 421, 24, 13, 8 });
	flipper.speed = 0.2f;
}

ModuleMenuScene::~ModuleMenuScene()
{}

// Load assets
bool ModuleMenuScene::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	menu = App->textures->Load("Assets/Sprites/Menu&more.png");
	App->audio->PlayMusic("Assets/Audio/Music/MenuTheme.ogg");

	to_scene_intro = false;

	menuEnum = menu_;
	return ret;
}

// Load assets
bool ModuleMenuScene::CleanUp()
{
	LOG("Unloading Intro scene");
	App->menu_scene->menuEnum = null_;

	App->textures->Unload(menu);

	return true;
}

// Update: draw background
update_status ModuleMenuScene::Update()
{	

	switch (menuEnum)
	{
	case menu_:
		App->renderer->Blit(menu, 0, 0, &menuBg);

		current_animation = &pressStart;
		r = &current_animation->GetCurrentFrame();
		App->renderer->Blit(menu, 256 / 2 - 84 / 2, 145, r);

		current_animation = &flipper;
		r = &current_animation->GetCurrentFrame();
		App->renderer->Blit(menu, (256 / 2 - 84 / 2) - 20, 145, r);
		App->renderer->Blit(menu, (256 / 2 - 84 / 2) + 84 + 13 - 7, 145, r, 1, 0, INT_MAX, INT_MAX, SDL_FLIP_HORIZONTAL);
		if (App->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN) {
			menuEnum = subMenu_;
			break;
		}
		break;

	case subMenu_:
		App->renderer->Blit(menu, 0, 0, &menuBg);

		App->renderer->Blit(menu, 256 / 2 - 96 / 2, 160 / 2 - 83 / 2, &subMenu);
		
		current_animation = &flipper;
		r = &current_animation->GetCurrentFrame();
		App->renderer->Blit(menu, (256 / 2 - 84 / 2) - 20 + 22, 54, r);
		App->renderer->Blit(menu, (256 / 2 - 84 / 2) + 84 + 13 - 25, 54, r, 1, 0, INT_MAX, INT_MAX, SDL_FLIP_HORIZONTAL);
		
		if (App->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN) {
			menuEnum = mapSelector_;
			break;
		}
		else if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN) {
			menuEnum = menu_;
			break;
		}
		break;

	case mapSelector_:
		App->renderer->Blit(menu, 0, 0, &mapSelector);
		current_animation = &mapSelection;
		r = &current_animation->GetCurrentFrame();
		App->renderer->Blit(menu, 40, 36, r);

		if (App->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN) {
			App->audio->PlayMusic("Assets/Audio/Music/MainTheme.ogg");

			App->fade->FadeToBlack(this, App->scene_intro, 4.0f);

			break;
		}
		else if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN) {
			menuEnum = subMenu_;
			break;
		}
		break;

	case score_:

		App->renderer->Blit(App->scene_intro->general, 256/2 - 104, 280, &scoreMenu);
		App->renderer->Blit(App->scene_intro->general, 256 / 2 - 60, 320, &scorePrint);
		sprintf_s(App->scene_intro->str1, "%i", App->scene_intro->points);
		App->fonts->BlitText(256/2, 330, App->scene_intro->font_score, App->scene_intro->str1);
		sprintf_s(App->scene_intro->str1, "%i", App->scene_intro->highscore);
		App->fonts->BlitText(256/2, 310, App->scene_intro->font_score, App->scene_intro->str1);
		App->player->cameraAtPlayer = false;

		if (App->scene_intro->points > App->scene_intro->highscore) 
			App->scene_intro->highscore = App->scene_intro->points;

		if (App->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN) {
			// Restart variables
			App->scene_intro->points = 0;

			App->player->SetGeneralParameters();
			App->player->CreatePokemonCave();

			App->audio->PlayMusic("Assets/Audio/Music/MenuTheme.ogg");

			menuEnum = menu_;
		}
		break;

	case null_:
		if (App->input->GetKey(SDL_SCANCODE_Z) == KEY_DOWN) {
			menuEnum = mapSelector_;
			App->player->cameraAtPlayer = false;
			// Restart variables
			App->scene_intro->points = 0;
			App->player->SetGeneralParameters();
			App->player->CreatePokemonCave();
			break;
		}
		break;

	}

	return UPDATE_CONTINUE;
}