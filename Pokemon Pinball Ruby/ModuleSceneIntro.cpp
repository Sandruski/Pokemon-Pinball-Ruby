#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"
#include "ModuleMenuScene.h"
#include "ModuleFonts.h"

#include <fstream>
#include <iostream>

using namespace std;

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	general = NULL;
	ray_on = false;

	background.x = 533;
	background.y = 3;
	background.w = 257;
	background.h = 425;

	rChargePikachu.x = 63;
	rChargePikachu.y = 703;
	rChargePikachu.w = 18;
	rChargePikachu.h = 17;

	trianglesOnCollision.x = 273;
	trianglesOnCollision.y = 329;
	trianglesOnCollision.w = 23;
	trianglesOnCollision.h = 34;

	rCircle1.x = 412;
	rCircle1.y = 253;
	rCircle1.w = 10;
	rCircle1.h = 10;

	rCircle2.x = 460;
	rCircle2.y = 254;
	rCircle2.w = 8;
	rCircle2.h = 8;

	rBall.x = 470;
	rBall.y = 252;
	rBall.w = 12;
	rBall.h = 12;

	rEvo.x = 268;
	rEvo.y = 247;
	rEvo.w = 14;
	rEvo.h = 19;

	rEVo.x = 284;
	rEVo.y = 247;
	rEVo.w = 14;
	rEVo.h = 19;

	rEVO.x = 300;
	rEVO.y = 247;
	rEVO.w = 14;
	rEVO.h = 19;

	rLs10.x = 316;
	rLs10.y = 247;
	rLs10.w = 14;
	rLs10.h = 19;

	rLS10.x = 332;
	rLS10.y = 247;
	rLS10.w = 14;
	rLS10.h = 19;

	rLS10T.x = 348;
	rLS10T.y = 247;
	rLS10T.w = 14;
	rLS10T.h = 19;

	rGet.x = 365;
	rGet.y = 248;
	rGet.w = 14;
	rGet.h = 19;

	rGEt.x = 380;
	rGEt.y = 247;
	rGEt.w = 14;
	rGEt.h = 19;

	rGET.x = 396;
	rGET.y = 248;
	rGET.w = 14;
	rGET.h = 19;

	hatch.PushBack({ 273, 283, 30, 33 });
	hatch.PushBack({ 0, 0, 0, 0 });
	hatch.speed = 0.075f;

	bumper.PushBack({ 0, 0, 0, 0 });
	bumper.PushBack({ 305, 283, 31, 33 });
	bumper.speed = 0.075f;

	catchvar.PushBack({ 0, 0, 0, 0 });
	catchvar.PushBack({ 391, 284, 30, 33 });
	catchvar.speed = 0.075f;

	hart.PushBack({ 338, 284, 24, 32 });
	hart.PushBack({ 0, 0, 0, 0 });
	hart.speed = 0.075f;

	latiosSave.PushBack({ 484, 245, 43, 25 });
	latiosSave.PushBack({ 0, 0, 0, 0 });
	latiosSave.speed = 0.075f;

	pikachu.PushBack({ 51, 1199, 38, 91 });
	pikachu.PushBack({ 91, 1199, 38, 91 });
	pikachu.speed = 0.05f;

	impactTrueno.PushBack({ 209, 1199, 38, 91 });
	impactTrueno.PushBack({ 249, 1199, 38, 91 });
	impactTrueno.PushBack({ 289, 1199, 38, 91 });
	impactTrueno.PushBack({ 11, 920, 38, 91 });
	impactTrueno.PushBack({ 51, 920, 38, 91 });
	impactTrueno.PushBack({ 51, 1013, 38, 91 });
	impactTrueno.speed = 0.1f;
	impactTrueno.loop = false;

	impactTrueno2.PushBack({ 11, 1106, 38, 91 });
	impactTrueno2.PushBack({ 11, 1199, 38, 91 });
	impactTrueno2.PushBack({ 51, 1106, 38, 91 });
	impactTrueno2.PushBack({ 11, 1013, 38, 91 });
	impactTrueno2.PushBack({ 369, 1199, 38, 91 });
	impactTrueno2.PushBack({ 329, 1199, 38, 91 });
	impactTrueno2.speed = 0.1f;
	impactTrueno2.loop = false;

	chargePikachu.PushBack({ 83, 703, 18, 17 });
	chargePikachu.PushBack({ 103, 703, 18, 17 });
	chargePikachu.PushBack({ 123, 703, 18, 17 });
	chargePikachu.PushBack({ 143, 703, 18, 17 });
	chargePikachu.PushBack({ 163, 703, 18, 17 });
	chargePikachu.PushBack({ 183, 703, 18, 17 });
	chargePikachu.PushBack({ 203, 703, 18, 17 });
	chargePikachu.PushBack({ 223, 703, 18, 17 });
	chargePikachu.PushBack({ 243, 703, 18, 17 });
	chargePikachu.PushBack({ 263, 703, 18, 17 });
	chargePikachu.PushBack({ 283, 703, 18, 17 });
	chargePikachu.PushBack({ 303, 703, 18, 17 });
	chargePikachu.PushBack({ 323, 703, 18, 17 });
	chargePikachu.PushBack({ 343, 703, 18, 17 });
	chargePikachu.speed = 0.5f;

	mPokemon.PushBack({ 345, 990, 28, 34 });
	mPokemon.PushBack({ 375, 990, 30, 34 });
	mPokemon.speed = 0.05f;

	slime.PushBack({ 162, 1002, 23, 22 });
	slime.PushBack({ 162, 1002, 23, 22 });
	slime.PushBack({ 162, 1002, 23, 22 });
	slime.PushBack({ 186, 1002, 23, 22 });
	slime.PushBack({ 186, 1002, 23, 22 });
	slime.PushBack({ 186, 1002, 23, 22 });
	slime.PushBack({ 211, 1002, 31, 22 });
	slime.PushBack({ 244, 1002, 31, 22 });
	slime.PushBack({ 278, 1002, 31, 22 });
	slime.PushBack({ 312, 1002, 31, 22 });
	slime.PushBack({ 162, 1002, 23, 22 });
	slime.PushBack({ 162, 1002, 23, 22 });
	slime.PushBack({ 162, 1002, 23, 22 });
	slime.PushBack({ 186, 1002, 23, 22 });
	slime.PushBack({ 186, 1002, 23, 22 });
	slime.PushBack({ 186, 1002, 23, 22 });
	slime.PushBack({ 162, 1002, 23, 22 });
	slime.PushBack({ 162, 1002, 23, 22 });
	slime.PushBack({ 162, 1002, 23, 22 });
	slime.PushBack({ 186, 1002, 23, 22 });
	slime.PushBack({ 186, 1002, 23, 22 });
	slime.PushBack({ 186, 1002, 23, 22 });
	slime.speed = 0.25f;

	chikorita.PushBack({ 224, 1035, 19, 43 });
	chikorita.PushBack({ 245, 1035, 19, 43 });
	chikorita.speed = 0.075f;

	topo.PushBack({ 120, 1003, 19, 24 });
	topo.PushBack({ 141, 1003, 19, 24 });
	topo.speed = 0.10f;

}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{

	LOG("Loading Intro assets");
	bool ret = true;

	general = App->textures->Load("Assets/Sprites/GeneralSpritesheet.png");

	font_score = App->fonts->Load("Assets/Sprites/Font.png", "0123456789", 1);

	LoadScore();

	App->renderer->camera.x = App->renderer->camera.y = 0;

	CreateChains();

	SetSensors();

	indexPikachu = 0;
	pika = false;

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(general);

	App->fonts->UnLoad(font_score);

	SaveScore();

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	// F2: fullscreen
	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {
		if (App->window->fullscreen) {
			App->window->fullscreen = false;
			SDL_SetWindowFullscreen(App->window->window, SDL_WINDOW_SHOWN);
		}
		else {
			App->window->fullscreen = true;
			SDL_SetWindowFullscreen(App->window->window, SDL_WINDOW_FULLSCREEN_DESKTOP); //if not working properly, try SDL_WINDOW_FULLSCREEN_DESKTOP
		}
	}

	App->renderer->Blit(general, 0, 0, &background);

	if (indexPikachu == 0 && sensorPikachu->body->GetPosition().x != 33) {
		App->physics->world->DestroyBody(sensorPikachu->body);
		sensorPikachu = App->physics->CreateRectangleSensor(33, 360, 10, 10);
		sensorPikachu->listener = this;
		sensorPikachu->body->GetFixtureList()->SetFilterData(f);
	}

	if (indexPikachu == 1 && sensorPikachu->body->GetPosition().x != 210) {
		App->physics->world->DestroyBody(sensorPikachu->body);
		sensorPikachu = App->physics->CreateRectangleSensor(210, 360, 10, 10);
		sensorPikachu->listener = this;
		sensorPikachu->body->GetFixtureList()->SetFilterData(f);
	}

	if (trianglesBlit1) {
		timeTriangle1++;
		App->renderer->Blit(general, 65, 331, &trianglesOnCollision);
		if (timeTriangle1 > 30) {
			timeTriangle1 = 0;
			trianglesBlit1 = false;
		}
	}
	if (trianglesBlit2) {
		timeTriangle2++;
		App->renderer->Blit(general, 152, 331, &trianglesOnCollision, 1.0f, (0.0), INT_MAX, INT_MAX, SDL_FLIP_HORIZONTAL);
		if (timeTriangle2 > 30) {
			timeTriangle2 = 0;
			trianglesBlit2 = false;
		}
	}

	current_anim = &hatch;
	r = &current_anim->GetCurrentFrame();
	App->renderer->Blit(general, 87, 198, r);


	current_anim = &catchvar;
	r = &current_anim->GetCurrentFrame();
	App->renderer->Blit(general, 154, 249, r);


	current_anim = &hart;
	r = &current_anim->GetCurrentFrame();
	App->renderer->Blit(general, 144, 222, r);


	current_anim = &bumper;
	r = &current_anim->GetCurrentFrame();
	App->renderer->Blit(general, 120, 194, r);

	SensorsForBLit();

	BlitStaticPokemonsAndLife();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	// Hey! Destroy the ball
	if (bodyB->body == App->player->ball->body && bodyA->body == sensor->body)
	{
		destroy_ball = true;
		App->player->life--;
		if (App->player->life == 0)
			App->menu_scene->menuEnum = score_;
	}

	// Check sensors
	if (bodyB->body == App->player->ball->body && bodyA->body == sensorPikachu->body || bodyA->body == App->player->ball->body && bodyB->body == sensorPikachu->body)
	{
		pika = true;
		impactCheck = 1;
		points += 2;
	}

	if (bodyB->body == App->player->ball->body && bodyA->body == sensorPikachuCharge->body || bodyA->body == App->player->ball->body && bodyB->body == sensorPikachuCharge->body)
	{
		pikachuChargeCheck = true;
		points += 5;
	}

	if (bodyB->body == App->player->ball->body && bodyA->body == sensorEvo->body || bodyA->body == App->player->ball->body && bodyB->body == sensorEvo->body)
	{
		App->audio->PlayFx(7);
		Evo = true;
		points += 2;
	}

	if (bodyB->body == App->player->ball->body && bodyA->body == sensorEVo->body || bodyA->body == App->player->ball->body && bodyB->body == sensorEVo->body)
	{
		EVo = true;
		points += 2;
	}

	if (bodyB->body == App->player->ball->body && bodyA->body == sensorEVO->body || bodyA->body == App->player->ball->body && bodyB->body == sensorEVO->body)
	{
		EVO = true;
		points += 2;
	}

	if (bodyB->body == App->player->ball->body && bodyA->body == sensorLs10->body || bodyA->body == App->player->ball->body && bodyB->body == sensorLs10->body)
	{
		App->audio->PlayFx(7);
		Ls10 = true;
		points += 2;
	}

	if (bodyB->body == App->player->ball->body && bodyA->body == sensorLS10->body || bodyA->body == App->player->ball->body && bodyB->body == sensorLS10->body)
	{
		LS10 = true;
		points += 2;
	}

	if (bodyB->body == App->player->ball->body && bodyA->body == sensorLS10T->body || bodyA->body == App->player->ball->body && bodyB->body == sensorLS10T->body)
	{
		LS10T = true;
		points += 2;
	}
	if (bodyB->body == App->player->ball->body && bodyA->body == sensorGet->body || bodyA->body == App->player->ball->body && bodyB->body == sensorGet->body)
	{
		App->audio->PlayFx(7);
		Get = true;
		points += 2;
	}

	if (bodyB->body == App->player->ball->body && bodyA->body == sensorGEt->body || bodyA->body == App->player->ball->body && bodyB->body == sensorGEt->body)
	{
		GEt = true;
		points += 2;
	}

	if (bodyB->body == App->player->ball->body && bodyA->body == sensorGET->body || bodyA->body == App->player->ball->body && bodyB->body == sensorGET->body)
	{
		GET = true;
		points += 2;
	}


	if (bodyB->body == App->player->ball->body && bodyA->body == trianglebody1->body || bodyA->body == App->player->ball->body && bodyB->body == trianglebody1->body)
	{
		App->audio->PlayFx(4);
		trianglesBlit1 = true;	
		points += 5;
	}

	if (bodyB->body == App->player->ball->body && bodyA->body == trianglebody2->body || bodyA->body == App->player->ball->body && bodyB->body == trianglebody2->body)
	{
		App->audio->PlayFx(4);
		trianglesBlit2 = true;
		points += 5;
	}

	if (bodyB->body == App->player->ball->body && bodyA->body == sensorCircle1->body || bodyA->body == App->player->ball->body && bodyB->body == sensorCircle1->body)
	{
		circle1 = true;
		points += 2;
	}

	if (bodyB->body == App->player->ball->body && bodyA->body == sensorCircle2->body || bodyA->body == App->player->ball->body && bodyB->body == sensorCircle2->body)
	{
		circle2 = true;
		points += 2;
	}

	if (bodyB->body == App->player->ball->body && bodyA->body == sensorCircle3->body || bodyA->body == App->player->ball->body && bodyB->body == sensorCircle3->body)
	{
		circle3 = true;
		points += 2;
	}

	if (bodyB->body == App->player->ball->body && bodyA->body == sensorCircle4->body || bodyA->body == App->player->ball->body && bodyB->body == sensorCircle4->body)
	{
		circle4 = true;
		points += 2;

	}

	if (bodyB->body == App->player->ball->body && bodyA->body == sensorCircle5->body || bodyA->body == App->player->ball->body && bodyB->body == sensorCircle5->body)
	{
		circle5 = true;
		points += 2;
	}

	if (bodyB->body == App->player->ball->body && bodyA->body == sensorCircle6->body || bodyA->body == App->player->ball->body && bodyB->body == sensorCircle6->body)
	{
		circle6 = true;
		points += 2;
	}

	if (bodyB->body == App->player->ball->body && bodyA->body == sensorCircle7->body || bodyA->body == App->player->ball->body && bodyB->body == sensorCircle7->body)
	{
		circle7 = true;
		points += 2;
	}
}

void ModuleSceneIntro::SensorsForBLit() {
	if (Evo && timeEvo < 45) {
		App->renderer->Blit(general, 33, 249, &rEvo);
		timeEvo++;
		if (timeEvo >= 45) {
			timeEvo = 0;
			Evo = false;
		}
	}

	if (EVo && timeEVo < 45) {
		App->renderer->Blit(general, 43, 265, &rEVo);
		timeEVo++;
		if (timeEVo >= 45) {
			timeEVo = 0;
			EVo = false;
		}
	}

	if (EVO && timeEVO < 45) {
		App->renderer->Blit(general, 53, 281, &rEVO);
		timeEVO++;
		if (timeEVO >= 45) {
			timeEVO = 0;
			EVO = false;
		}
	}


	if (Ls10 && timeEvo < 45) {
		App->renderer->Blit(general, 61, 192, &rLs10);
		timeEvo++;
		if (timeEvo >= 45) {
			timeEvo = 0;
			Ls10 = false;
		}
	}

	if (LS10 && timeEVo < 45) {
		App->renderer->Blit(general, 66, 210, &rLS10);
		timeEVo++;
		if (timeEVo >= 45) {
			timeEVo = 0;
			LS10 = false;
		}
	}

	if (LS10T && timeEVO < 45) {
		App->renderer->Blit(general, 74, 227, &rLS10T);
		timeEVO++;
		if (timeEVO >= 45) {
			timeEVO = 0;
			LS10T = false;
		}
	}

	if (Get && timeEvo < 45) {
		App->renderer->Blit(general, 194, 249, &rGet);
		timeEvo++;
		if (timeEvo >= 45) {
			timeEvo = 0;
			Get = false;
		}
	}

	if (GEt && timeEVo < 45) {
		App->renderer->Blit(general, 183, 264, &rGEt);
		timeEVo++;
		if (timeEVo >= 45) {
			timeEVo = 0;
			GEt = false;
		}
	}

	if (GET && timeEVO < 45) {
		App->renderer->Blit(general, 173, 281, &rGET);
		timeEVO++;
		if (timeEVO >= 45) {
			timeEVO = 0;
			GET = false;
		}
	}

	if (circle1 && timeCircle1 < 45) {
		App->renderer->Blit(general, 155, 97, &rCircle2);
		timeCircle1++;
		if (timeCircle1 >= 45) {
			timeCircle1 = 0;
			circle1 = false;
		}
	}

	if (circle2 && timeCircle2 < 45) {
		App->renderer->Blit(general, 134, 97, &rCircle2);
		timeCircle2++;
		if (timeCircle2 >= 45) {
			timeCircle2 = 0;
			circle2 = false;
		}
	}

	if (circle3 && timeCircle3 < 45) {
		App->renderer->Blit(general, 113, 97, &rCircle2);
		timeCircle3++;
		if (timeCircle3 >= 45) {
			timeCircle3 = 0;
			circle3 = false;
		}
	}

	if (circle4 && timeCircle4 < 45) {
		App->renderer->Blit(general, 28, 335, &rCircle1);
		timeCircle4++;
		if (timeCircle4 >= 45) {
			timeCircle4 = 0;
			circle4 = false;
		}
	}

	if (circle5 && timeCircle5 < 45) {
		App->renderer->Blit(general, 52, 335, &rCircle1);
		timeCircle5++;
		if (timeCircle5 >= 45) {
			timeCircle5 = 0;
			circle5 = false;
		}
	}

	if (circle6 && timeCircle6 < 45) {
		App->renderer->Blit(general, 178, 335, &rCircle1);
		timeCircle6++;
		if (timeCircle6 >= 45) {
			timeCircle6 = 0;
			circle6 = false;
		}
	}

	if (circle7 && timeCircle7 < 45) {
		App->renderer->Blit(general, 202, 335, &rCircle1);
		timeCircle7++;
		if (timeCircle7 >= 45) {
			timeCircle7 = 0;
			circle7 = false;
		}
	}

}

void ModuleSceneIntro::SetSensors() {

	b2Filter f;
	f.categoryBits = WALL;
	f.maskBits = BALL;

	//sensor to destroy the ball
	sensor = App->physics->CreateRectangleSensor(115 , 440, 135, 15);
	sensorPikachu = App->physics->CreateRectangleSensor(33, 360, 10, 10);
	sensorPikachuCharge = App->physics->CreateRectangleSensor(218, 180, 5, 5);
	sensorEvo = App->physics->CreateRectangleSensor(40, 260, 4, 4);
	sensorEVo = App->physics->CreateRectangleSensor(50, 277, 4, 4);
	sensorEVO = App->physics->CreateRectangleSensor(60, 290, 4, 4);
	sensorLs10 = App->physics->CreateRectangleSensor(68, 203, 4, 4);
	sensorLS10 = App->physics->CreateRectangleSensor(73, 220, 4, 4);
	sensorLS10T = App->physics->CreateRectangleSensor(80, 240, 4, 4);
	sensorGet = App->physics->CreateRectangleSensor(200, 260, 4, 4);
	sensorGEt = App->physics->CreateRectangleSensor(190, 275, 4, 4);
	sensorGET = App->physics->CreateRectangleSensor(181, 291, 4, 4);
	sensorCircle1 = App->physics->CreateRectangleSensor(159, 101, 3, 3);
	sensorCircle2 = App->physics->CreateRectangleSensor(138, 101, 4, 4);
	sensorCircle3 = App->physics->CreateRectangleSensor(117, 101, 4, 4);
	sensorCircle4 = App->physics->CreateRectangleSensor(33, 340, 4, 4);
	sensorCircle5 = App->physics->CreateRectangleSensor(57, 340, 4, 4);
	sensorCircle6 = App->physics->CreateRectangleSensor(183, 340, 4, 4);
	sensorCircle7 = App->physics->CreateRectangleSensor(207, 340, 4, 4);

	sensor->listener = this;
	sensorPikachu->listener = this;
	sensorPikachuCharge->listener = this;
	sensorEvo->listener = this;
	sensorEVo->listener = this;
	sensorEVO->listener = this;
	sensorLs10->listener = this;
	sensorLS10->listener = this;
	sensorLS10T->listener = this;
	sensorGet->listener = this;
	sensorGEt->listener = this;
	sensorGET->listener = this;
	sensorCircle1->listener = this;
	sensorCircle2->listener = this;
	sensorCircle3->listener = this;
	sensorCircle4->listener = this;
	sensorCircle5->listener = this;
	sensorCircle6->listener = this;
	sensorCircle7->listener = this;

	sensor->body->GetFixtureList()->SetFilterData(f);
	sensorPikachu->body->GetFixtureList()->SetFilterData(f);
	sensorPikachuCharge->body->GetFixtureList()->SetFilterData(f);
	sensorEvo->body->GetFixtureList()->SetFilterData(f);
	sensorEVo->body->GetFixtureList()->SetFilterData(f);
	sensorEVO->body->GetFixtureList()->SetFilterData(f);
	sensorLs10->body->GetFixtureList()->SetFilterData(f);
	sensorLS10->body->GetFixtureList()->SetFilterData(f);
	sensorLS10T->body->GetFixtureList()->SetFilterData(f);
	sensorGet->body->GetFixtureList()->SetFilterData(f);
	sensorGEt->body->GetFixtureList()->SetFilterData(f);
	sensorGET->body->GetFixtureList()->SetFilterData(f);
	sensorCircle1->body->GetFixtureList()->SetFilterData(f);
	sensorCircle2->body->GetFixtureList()->SetFilterData(f);
	sensorCircle3->body->GetFixtureList()->SetFilterData(f);
	sensorCircle4->body->GetFixtureList()->SetFilterData(f);
	sensorCircle5->body->GetFixtureList()->SetFilterData(f);
	sensorCircle6->body->GetFixtureList()->SetFilterData(f);
	sensorCircle7->body->GetFixtureList()->SetFilterData(f);
}

void ModuleSceneIntro::CreateChains() {

	int triangle[6] = {
		620 - 533, 362,
		604 - 533, 339,
		601 - 533, 336
	};

	int triangle2[6] = {
		686 - 533, 362,
		702 - 533, 337,
		705 - 533, 336
	};

	int triangleFloor1[10] = {
		599 - 533, 337,
		599 - 533, 356,
		616 - 533, 367,
		619 - 533, 366,
		620 - 533, 362,
	};

	int triangleFloor2[10] = {
		705 - 533, 338,
		705 - 533, 355,
		691 - 533, 364,
		687 - 533, 366,
		686 - 533, 362,
	};


	int GeneralSpritesheet0[14] = {
		679 - 533, 94,
		682 - 533, 93,
		684 - 533, 95,
		684 - 533, 110,
		681 - 533, 111,
		679 - 533, 109,
		678 - 533, 97
	};

	int GeneralSpritesheet1[110] = {
		632 - 533, 427,
		632 - 533, 426,
		573 - 533, 391,
		573 - 533, 399,
		556 - 533, 399,
		556 - 533, 327,
		557 - 533, 322,
		560 - 533, 319,
		564 - 533, 317,
		569 - 533, 316,
		574 - 533, 315,
		578 - 533, 313,
		580 - 533, 310,
		580 - 533, 289,
		567 - 533, 273,
		551 - 533, 241,
		544 - 533, 213,
		545 - 533, 162,
		562 - 533, 112,
		588 - 533, 86,
		626 - 533, 70,
		654 - 533, 66,
		678 - 533, 69,
		713 - 533, 82,
		737 - 533, 98,
		760 - 533, 118,
		774 - 533, 139,
		783 - 533, 168,
		783 - 533, 191,
		783 - 533, 411,
		767 - 533, 411,
		767 - 533, 191,
		756 - 533, 144,
		753 - 533, 141,
		752 - 533, 147,
		764 - 533, 192,
		760 - 533, 226,
		750 - 533, 257,
		736 - 533, 279,
		727 - 533, 287,
		727 - 533, 312,
		733 - 533, 317,
		744 - 533, 320,
		750 - 533, 327,
		749 - 533, 400,
		733 - 533, 400,
		732 - 533, 389,
		675 - 533, 427,
		675 - 533, 426,
		737 - 533, 449,
		742 - 533, 544,
		645 - 533, 558,
		569 - 533, 531,
		574 - 533, 457,
		620 - 533, 430
	};

	int GeneralSpritesheet2[14] = {
		658 - 533, 92,
		661 - 533, 90,
		663 - 533, 92,
		663 - 533, 109,
		659 - 533, 109,
		658 - 533, 107,
		658 - 533, 95
	};

	int GeneralSpritesheet3[38] = {
		620 - 533, 396,
		624 - 533, 393,
		618 - 533, 388,
		605 - 533, 380,
		590 - 533, 371,
		582 - 533, 364,
		582 - 533, 352,
		582 - 533, 343,
		582 - 533, 338,
		580 - 533, 334,
		577 - 533, 335,
		577 - 533, 343,
		577 - 533, 353,
		577 - 533, 361,
		577 - 533, 371,
		582 - 533, 375,
		592 - 533, 380,
		604 - 533, 387,
		614 - 533, 394
	};

	int GeneralSpritesheet4[58] = {
		608 - 533, 189,
		603 - 533, 160,
		603 - 533, 145,
		603 - 533, 133,
		610 - 533, 116,
		620 - 533, 104,
		630 - 533, 94,
		642 - 533, 90,
		642 - 533, 107,
		640 - 533, 111,
		640 - 533, 138,
		642 - 533, 149,
		645 - 533, 162,
		648 - 533, 169,
		653 - 533, 179,
		639 - 533, 180,
		635 - 533, 177,
		636 - 533, 162,
		637 - 533, 146,
		635 - 533, 136,
		627 - 533, 131,
		614 - 533, 131,
		609 - 533, 137,
		608 - 533, 146,
		608 - 533, 159,
		612 - 533, 176,
		614 - 533, 187,
		613 - 533, 190,
		610 - 533, 190
	};

	int GeneralSpritesheet5[58] = {
		608 - 533, 189,
		603 - 533, 160,
		603 - 533, 145,
		603 - 533, 133,
		610 - 533, 116,
		620 - 533, 104,
		630 - 533, 94,
		642 - 533, 90,
		642 - 533, 107,
		640 - 533, 111,
		640 - 533, 138,
		642 - 533, 149,
		645 - 533, 162,
		648 - 533, 169,
		653 - 533, 179,
		639 - 533, 180,
		635 - 533, 177,
		636 - 533, 162,
		637 - 533, 146,
		635 - 533, 136,
		627 - 533, 131,
		614 - 533, 131,
		609 - 533, 137,
		608 - 533, 146,
		608 - 533, 159,
		612 - 533, 176,
		614 - 533, 187,
		613 - 533, 190,
		610 - 533, 190
	};

	int GeneralSpritesheet6[28] = {
		729 - 533, 336,
		727 - 533, 333,
		723 - 533, 336,
		723 - 533, 347,
		723 - 533, 363,
		719 - 533, 369,
		708 - 533, 375,
		689 - 533, 387,
		682 - 533, 392,
		682 - 533, 397,
		688 - 533, 396,
		720 - 533, 375,
		729 - 533, 367,
		729 - 533, 340
	};

	int GeneralSpritesheet7[58] = {
		715 - 533, 111,
		701 - 533, 101,
		701 - 533, 111,
		712 - 533, 118,
		720 - 533, 126,
		721 - 533, 139,
		714 - 533, 158,
		704 - 533, 179,
		688 - 533, 208,
		694 - 533, 211,
		717 - 533, 165,
		725 - 533, 182,
		721 - 533, 200,
		707 - 533, 228,
		707 - 533, 231,
		712 - 533, 223,
		722 - 533, 204,
		728 - 533, 200,
		735 - 533, 202,
		736 - 533, 208,
		731 - 533, 228,
		725 - 533, 249,
		725 - 533, 251,
		730 - 533, 242,
		741 - 533, 214,
		744 - 533, 199,
		738 - 533, 161,
		730 - 533, 137,
		718 - 533, 114
	};

	int GeneralSpritesheet8[22] = {
		590 - 533, 112,
		590 - 533, 120,
		583 - 533, 141,
		582 - 533, 169,
		586 - 533, 194,
		578 - 533, 187,
		569 - 533, 174,
		566 - 533, 162,
		569 - 533, 146,
		577 - 533, 126,
		586 - 533, 113
	};

	int GeneralSpritesheet9[22] = {
		565 - 533, 209,
		573 - 533, 240,
		588 - 533, 266,
		601 - 533, 281,
		611 - 533, 274,
		612 - 533, 262,
		601 - 533, 244,
		594 - 533, 228,
		581 - 533, 220,
		571 - 533, 210,
		566 - 533, 206
	};

	int GeneralSpritesheet10[8] = {
		565 - 533, 206,
		564 - 533, 191,
		564 - 533, 180,
		566 - 533, 165
	};

	int GeneralSpritesheet11[14] = {
		680 - 533, 103,
		680 - 533, 116,
		684 - 533, 116,
		684 - 533, 106,
		684 - 533, 97,
		682 - 533, 93,
		680 - 533, 98
	};

	int GeneralSpritesheet12[16] = {
		554 - 533, 368,
		558 - 533, 377,
		565 - 533, 383,
		573 - 533, 388,
		561 - 533, 389,
		552 - 533, 386,
		548 - 533, 370,
		550 - 533, 365
	};

	int GeneralSpritesheet13[16] = {
		729 - 533, 390,
		740 - 533, 383,
		747 - 533, 378,
		751 - 533, 372,
		752 - 533, 389,
		739 - 533, 393,
		732 - 533, 399,
		726 - 533, 394
	};

	f.categoryBits = WALL;
	f.maskBits = BALL;

	//App->physics->CreateChain(0, 0, GeneralSpritesheet0, 14, b2_staticBody);
	map_chain1 = App->physics->CreateChain(0, 0, GeneralSpritesheet1, 110, b2_staticBody);
	map_chain1->body->GetFixtureList()->SetFilterData(f);
	map_chain2 = App->physics->CreateChain(0, 0, GeneralSpritesheet2, 14, b2_staticBody);
	map_chain2->body->GetFixtureList()->SetFilterData(f);
	map_chain3 = App->physics->CreateChain(0, 0, GeneralSpritesheet3, 38, b2_staticBody);
	map_chain3->body->GetFixtureList()->SetFilterData(f);
	map_chain4 = App->physics->CreateChain(0, 0, GeneralSpritesheet4, 58, b2_staticBody);
	map_chain4->body->GetFixtureList()->SetFilterData(f);
	map_chain5 = App->physics->CreateChain(0, 0, GeneralSpritesheet5, 58, b2_staticBody);
	map_chain5->body->GetFixtureList()->SetFilterData(f);
	map_chain6 = App->physics->CreateChain(0, 0, GeneralSpritesheet6, 28, b2_staticBody);
	map_chain6->body->GetFixtureList()->SetFilterData(f);
	map_chain7 = App->physics->CreateChain(0, 0, GeneralSpritesheet7, 58, b2_staticBody);
	map_chain7->body->GetFixtureList()->SetFilterData(f);
	map_chain8 = App->physics->CreateChain(0, 0, GeneralSpritesheet8, 22, b2_staticBody);
	map_chain8->body->GetFixtureList()->SetFilterData(f);
	map_chain9 = App->physics->CreateChain(0, 0, GeneralSpritesheet9, 22, b2_staticBody);
	map_chain9->body->GetFixtureList()->SetFilterData(f);
	map_chain10 = App->physics->CreateChain(0, 0, GeneralSpritesheet10, 8, b2_staticBody);
	map_chain10->body->GetFixtureList()->SetFilterData(f);
	map_chain11 = App->physics->CreateChain(0, 0, GeneralSpritesheet11, 14, b2_staticBody);
	map_chain11->body->GetFixtureList()->SetFilterData(f);
	map_chain12 = App->physics->CreateChain(0, 0, GeneralSpritesheet12, 16, b2_staticBody);
	map_chain12->body->GetFixtureList()->SetFilterData(f);
	map_chain13 = App->physics->CreateChain(0, 0, GeneralSpritesheet13, 16, b2_staticBody);
	map_chain13->body->GetFixtureList()->SetFilterData(f);

	//Setting... triangles(?)
	trianglebody1 = App->physics->CreateChain(0, 0, triangle, 6, b2_staticBody);
	trianglebody2 = App->physics->CreateChain(0, 0, triangle2, 6, b2_staticBody);
	trianglebody3 = App->physics->CreateChain(0, 0, triangleFloor1, 10, b2_staticBody);
	trianglebody4 = App->physics->CreateChain(0, 0, triangleFloor2, 10, b2_staticBody);
	trianglebody1->body->GetFixtureList()->SetRestitution(2.0f);
	trianglebody2->body->GetFixtureList()->SetRestitution(2.0f);
	trianglebody1->listener = this;
	trianglebody2->listener = this;
	trianglebody1->body->GetFixtureList()->SetFilterData(f);
	trianglebody2->body->GetFixtureList()->SetFilterData(f);
	trianglebody3->body->GetFixtureList()->SetFilterData(f);
	trianglebody4->body->GetFixtureList()->SetFilterData(f);
}

void ModuleSceneIntro::BlitStaticPokemonsAndLife() {

	if (App->player->life == 3) {
		current_anim = &latiosSave;
		r = &current_anim->GetCurrentFrame();
		App->renderer->Blit(general, 101, 353, r);
		App->renderer->Blit(general, 98, 330, &rBall);
		App->renderer->Blit(general, 114, 330, &rBall);
		App->renderer->Blit(general, 130, 330, &rBall);
	}
	else if (App->player->life == 2) {
		current_anim = &latiosSave;
		r = &current_anim->GetCurrentFrame();
		App->renderer->Blit(general, 101, 353, r);
		App->renderer->Blit(general, 98, 330, &rBall);
		App->renderer->Blit(general, 114, 330, &rBall);
	}
	else if (App->player->life == 1) {
		current_anim = &latiosSave;
		r = &current_anim->GetCurrentFrame();
		App->renderer->Blit(general, 101, 353, r);
		App->renderer->Blit(general, 98, 330, &rBall);
	}

	//mPokemon
	current_anim = &mPokemon;
	r = &current_anim->GetCurrentFrame();
	App->renderer->Blit(general, 195, 275, r);

	//slime
	current_anim = &slime;
	r = &current_anim->GetCurrentFrame();
	App->renderer->Blit(general, 20, 280, r);

	//topo
	current_anim = &topo;
	r = &current_anim->GetCurrentFrame();
	App->renderer->Blit(general, 173, 290, r, 1, 0, INT_MAX, INT_MAX, SDL_FLIP_HORIZONTAL);

	//Chikorita
	current_anim = &chikorita;
	r = &current_anim->GetCurrentFrame();
	App->renderer->Blit(general, 55, 220, r);

}

bool ModuleSceneIntro::LoadScore() {

	bool ret = true;

	ifstream scorefile;
	scorefile.open("score.txt");
	scorefile >> highscore;
	scorefile.close();

	return ret;
}

bool ModuleSceneIntro::SaveScore() const {

	bool ret = true;

	ofstream scorefile2;
	scorefile2.open("score.txt", std::ofstream::out | std::ofstream::trunc);
	scorefile2 << highscore;
	scorefile2.close();

	return ret;
}

void ModuleSceneIntro::Pikachu() {

	//Pikachu
	if (impactCheck == 1 && !impactTrueno.Finished()) {
		App->player->ball->body->SetLinearVelocity({ 0,0 });
		App->player->ball->body->SetGravityScale(0);

		if (pika) {
			App->audio->PlayFx(2);
			pika = false;
		}
	}

	else if (impactCheck == 1 && impactTrueno.Finished()) {
		App->player->ball->body->SetGravityScale(1);
		App->player->ball->body->ApplyForceToCenter({ 0, -50 }, true);		
		impactCheck = 2;
	}

	else if (impactTrueno2.Finished() && impactCheck == 2) {
		impactCheck = 0;
		impactTrueno.Reset();
		impactTrueno2.Reset();
	}

	if (impactCheck == 0)
		current_anim = &pikachu;
	else if (impactCheck == 1)
		current_anim = &impactTrueno;
	else
		current_anim = &impactTrueno2;
	r = &current_anim->GetCurrentFrame();
	int x, y;
	sensorPikachu->GetPosition(x, y);
	App->renderer->Blit(general, x - 10, y - 45, r);

	/// pikaCharge
	if (!pikachuChargeCheck)
		App->renderer->Blit(general, 209, 170, &rChargePikachu);

	if (pikachuChargeCheck && !chargePikachu.Finished()) {
		current_anim = &chargePikachu;
		r = &current_anim->GetCurrentFrame();
		App->renderer->Blit(general, 209, 170, r);
	}
	else {
		pikachuChargeCheck = false;
		chargePikachu.Reset();
	}
	//


}