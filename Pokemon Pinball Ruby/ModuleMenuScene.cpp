#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleMenuScene.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleMenuScene::ModuleMenuScene(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = rick = NULL;
	general = NULL;
	ray_on = false;
	sensed = false;

	background.x = 533;
	background.y = 3;
	background.w = 257;
	background.h = 425;

}

ModuleMenuScene::~ModuleMenuScene()
{}

// Load assets
bool ModuleMenuScene::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	/*
	TODOS
	-Muchos edges.
	-Crear bonus (cuando pasa la bola, se tienen que activar.Tipo sensores : isSensor = true), bouncers(cuerpos est�ticos).
	-Que llame a una funci�n de AddBody de ModulePhysics.
	*/

	return ret;
}

// Load assets
bool ModuleMenuScene::CleanUp()
{
	LOG("Unloading Intro scene");
	

	return true;
}

// Update: draw background
update_status ModuleMenuScene::Update()
{	

	return UPDATE_CONTINUE;
}




/*
Module Physics
Class PhysBody:
- Con GetUserData y SetUserData podemos acceder a nuestro cuerpo con punteros.
- AddBody: con par�metros de densidad, restituci�n, masa, etc.Para que los objetos reboten m�s o menos.
�Bouncers : mucha restituci�n.
�Bola : mucha densidad, poca restituci�n.
- b2ContactListener
- b2Body*; = puntero al b2Body
- Module* listener; //qu� m�dulo est� interesado para detectar una colisi�n. Cada m�dulo debe tener un OnCollision()

-NO HACE FALTA CREAR CUERPOS CINEM�TICOS.

Detecci�n de colisiones y gesti�n de las mismas:
-Detectar cuando la bola cae m�s abajo del pinball. Detecci�n con un sensor muy grande.
-SetListener al world. BeginContact. Para los sensores no nos llama al BeginContact: soluci�n: a cada vuelta, iterar por todos los contactos del b2World y si alguno
de los contactos es una colisi�n, gestionar dicha colisi�n.
*/