#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleMenuScene.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "p2Point.h"
#include "math.h"

#ifdef _DEBUG
#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" )
#else
#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" )
#endif

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	world = NULL;
	mouse_joint = NULL;
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));
	world->SetContactListener(this);

	// needed to create joints like mouse joint
	b2BodyDef bd;
	ground = world->CreateBody(&bd);

	return true;
}

//
update_status ModulePhysics::PreUpdate()
{
	world->Step(1.0f / 60.0f, 6, 2);

	for(b2Contact* c = world->GetContactList(); c; c = c->GetNext())
	{
		if(c->GetFixtureA()->IsSensor() && c->IsTouching())
		{
			PhysBody* pb1 = (PhysBody*)c->GetFixtureA()->GetBody()->GetUserData();
			PhysBody* pb2 = (PhysBody*)c->GetFixtureA()->GetBody()->GetUserData();
			if(pb1 && pb2 && pb1->listener)
				pb1->listener->OnCollision(pb1, pb2);
		}
	}

	return UPDATE_CONTINUE;
}

PhysBody* ModulePhysics::CreateCircle(int x, int y, int diameter, b2BodyType type)
{
	b2BodyDef body;
	body.type = type;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(diameter) * 0.5f;
	b2FixtureDef fixture;
	fixture.density = 1.0f;
	fixture.shape = &shape;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = diameter * 0.5f;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangle(int x, int y, int width, int height, b2BodyType type)
{
	b2BodyDef body;
	body.type = type;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);
	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width * 0.5f;
	pbody->height = height * 0.5f;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangleSensor(int x, int y, int width, int height)
{
	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2PolygonShape box;
	box.SetAsBox(PIXEL_TO_METERS(width) * 0.5f, PIXEL_TO_METERS(height) * 0.5f);

	b2FixtureDef fixture;
	fixture.shape = &box;
	fixture.density = 1.0f;
	fixture.isSensor = true;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = width;
	pbody->height = height;

	return pbody;
}

PhysBody* ModulePhysics::CreateChain(int x, int y, int* points, int size, b2BodyType value)
{
	b2BodyDef body;
	body.type = value;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2ChainShape shape;
	b2Vec2* p = new b2Vec2[size / 2];

	for(uint i = 0; i < size / 2; ++i)
	{
		p[i].x = PIXEL_TO_METERS(points[i * 2 + 0]);
		p[i].y = PIXEL_TO_METERS(points[i * 2 + 1]);
	}

	shape.CreateLoop(p, size / 2);

	b2FixtureDef fixture;
	fixture.density = 1.0f;
	fixture.shape = &shape;

	b->CreateFixture(&fixture);

	delete p;

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = 0;

	return pbody;
}

PhysBody* ModulePhysics::CreateFlipper(b2Vec2 flipper_vertices[], int size, float angle) {
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(0, 0);
	body.angle = angle * DEGTORAD;

	b2Body* b = App->physics->world->CreateBody(&body);
	b2PolygonShape flipper;
	flipper.Set(flipper_vertices, size);

	b2FixtureDef fixture;
	fixture.density = 1.0f;
	fixture.shape = &flipper;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	b->SetUserData(pbody);
	pbody->width = pbody->height = 0;

	return pbody;
}

b2RevoluteJoint* ModulePhysics::CreateFlipperRevoluteJoint(b2Body* bodyA, b2Body* bodyB, b2Vec2 setBodyA, float upperAngle, float lowerAngle) {

	b2RevoluteJointDef jointDef;
	jointDef.bodyA = bodyA;
	jointDef.bodyB = bodyB;
	jointDef.collideConnected = false;

	b2Vec2 setA = setBodyA;
	b2Vec2 setB = bodyB->GetLocalCenter();

	jointDef.localAnchorA.Set(setA.x, setA.y);
	jointDef.localAnchorB.Set(setB.x, setB.y);

	jointDef.enableLimit = true;
	jointDef.upperAngle = upperAngle * DEGTORAD;
	jointDef.lowerAngle = lowerAngle * DEGTORAD;

	/*
	//Motor
	jointDef.enableMotor = true;
	jointDef.maxMotorTorque = 10.0f;
	jointDef.motorSpeed = 0.0f;
	*/

	b2RevoluteJoint* revoluteJoint = (b2RevoluteJoint*)world->CreateJoint(&jointDef);

	return revoluteJoint;
}

b2RevoluteJoint* ModulePhysics::CreatePokemonRevoluteJoint(b2Body* bodyA, b2Body* bodyB, b2Vec2 setBodyB) {

	b2RevoluteJointDef jointDef;
	jointDef.bodyA = bodyA;
	jointDef.bodyB = bodyB;
	jointDef.collideConnected = false;

	b2Vec2 setA = bodyA->GetLocalCenter();
	b2Vec2 setB = setBodyB;

	jointDef.localAnchorA.Set(setA.x, setA.y);
	jointDef.localAnchorB.Set(setB.x, setB.y);

	//Motor
	jointDef.enableMotor = true;
	jointDef.maxMotorTorque = 10.0f;
	jointDef.motorSpeed = 0.0f;

	b2RevoluteJoint* revoluteJoint = (b2RevoluteJoint*)world->CreateJoint(&jointDef);

	return revoluteJoint;
}

b2DistanceJoint* ModulePhysics::CreateDistanceJoint(b2Body* bodyA, b2Body* bodyB) {

	b2DistanceJointDef jointDef;

	jointDef.Initialize(bodyA, bodyB, bodyA->GetWorldCenter(), bodyB->GetWorldCenter());
	jointDef.collideConnected = true;
	
	//Spring
	//jointDef.dampingRatio = 0.5f;
	//jointDef.frequencyHz = 4.0f;

	b2DistanceJoint* distanceJoint = (b2DistanceJoint*)world->CreateJoint(&jointDef);

	return distanceJoint;
}

b2PrismaticJoint* ModulePhysics::CreateSpringPrismaticJoint(b2Body* bodyA, b2Body* bodyB) {
	b2PrismaticJointDef jointDef;
	b2Vec2 worldAxis(0.0f, 1.0f);

	jointDef.Initialize(bodyA, bodyB, bodyA->GetWorldCenter(), worldAxis);
	jointDef.collideConnected = true;

	/*
	jointDef.lowerTranslation = -5.0f;
	jointDef.upperTranslation = 2.5f;
	jointDef.enableLimit = true;
	*/

	b2PrismaticJoint* prismaticJoint = (b2PrismaticJoint*)world->CreateJoint(&jointDef);

	return prismaticJoint;
}

// 
update_status ModulePhysics::PostUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN) //F1: show colliders
		debug = !debug;

	if (debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels

	b2Body* body_clicked = nullptr;
	b2Vec2 mouse_position = { PIXEL_TO_METERS(App->input->GetMouseX()), PIXEL_TO_METERS(App->input->GetMouseY()) };
	
	if (App->menu_scene->menuEnum == null_ && !debug) {

		for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
		{
			for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
			{
				switch (f->GetType())
				{
					// Draw circles ------------------------------------------------
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
				}
				break;

				// Draw polygons ------------------------------------------------
				case b2Shape::e_polygon:
				{
					b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
					int32 count = polygonShape->GetVertexCount();
					b2Vec2 prev, v;

					for (int32 i = 0; i < count; ++i)
					{
						v = b->GetWorldPoint(polygonShape->GetVertex(i));
						if (i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);

						prev = v;
					}

					v = b->GetWorldPoint(polygonShape->GetVertex(0));
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);
				}
				break;

				// Draw chains contour -------------------------------------------
				case b2Shape::e_chain:
				{
					b2ChainShape* shape = (b2ChainShape*)f->GetShape();
					b2Vec2 prev, v;

					for (int32 i = 0; i < shape->m_count; ++i)
					{
						v = b->GetWorldPoint(shape->m_vertices[i]);
						if (i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
						prev = v;
					}

					v = b->GetWorldPoint(shape->m_vertices[0]);
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
				}
				break;

				// Draw a single segment(edge) ----------------------------------
				case b2Shape::e_edge:
				{
					b2EdgeShape* shape = (b2EdgeShape*)f->GetShape();
					b2Vec2 v1, v2;

					v1 = b->GetWorldPoint(shape->m_vertex0);
					v1 = b->GetWorldPoint(shape->m_vertex1);
					App->renderer->DrawLine(METERS_TO_PIXELS(v1.x), METERS_TO_PIXELS(v1.y), METERS_TO_PIXELS(v2.x), METERS_TO_PIXELS(v2.y), 100, 100, 255);
				}
				break;
				}

				// TODO 1: If mouse button 1 is pressed ...
				// App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN
				// test if the current body contains mouse position
				/*
				if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN && b != big_ball) {

					if (f->TestPoint(mouse_position))
						body_clicked = b;
				}
				*/
			}
		}
	}

	// If a body was selected we will attach a mouse joint to it
	// so we can pull it around
	// TODO 2: If a body was selected, create a mouse joint
	// using mouse_joint class property

	
	if (body_clicked != nullptr) {

		// Mouse joint
		b2MouseJointDef mouse_def;

		mouse_def.bodyA = ground;
		mouse_def.bodyB = body_clicked;
		mouse_def.target = mouse_position;
		mouse_def.dampingRatio = 0.5f;
		mouse_def.frequencyHz = 2.0f;
		mouse_def.maxForce = 100.0f * body_clicked->GetMass();

		mouse_joint = (b2MouseJoint*)world->CreateJoint(&mouse_def);

		// Distance joint
		b2DistanceJointDef distance_def;

		distance_def.Initialize(big_ball, body_clicked, big_ball->GetWorldCenter(), body_clicked->GetWorldCenter());
		distance_def.dampingRatio = 0.5f;
		distance_def.frequencyHz = 2.0f;

		distance_joint = (b2DistanceJoint*)world->CreateJoint(&distance_def);

		// Motor joint
		b2MotorJointDef motor_def;
		motor_def.Initialize(big_ball, body_clicked);

		motor_def.maxForce = 50.0f;
		motor_def.maxTorque = 0.0f;
	}
	

	// TODO 3: If the player keeps pressing the mouse button, update
	// target position and draw a red line between both anchor points
	
	// Draw mouse joint
	
	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT && mouse_joint != nullptr) {

		b2Vec2 anchorA = mouse_joint->GetBodyB()->GetPosition();

		mouse_joint->SetTarget(mouse_position);
		b2Vec2 anchorB = mouse_joint->GetTarget();

		App->renderer->DrawLine(METERS_TO_PIXELS(anchorA.x), METERS_TO_PIXELS(anchorA.y), METERS_TO_PIXELS(anchorB.x), METERS_TO_PIXELS(anchorB.y), 255, 0, 0);
	}
	

	// Draw distance joint
	
	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT && distance_joint != nullptr) {

		b2Vec2 anchorA = distance_joint->GetBodyA()->GetPosition();
		b2Vec2 anchorB = distance_joint->GetBodyB()->GetPosition();

		App->renderer->DrawLine(METERS_TO_PIXELS(anchorA.x), METERS_TO_PIXELS(anchorA.y), METERS_TO_PIXELS(anchorB.x), METERS_TO_PIXELS(anchorB.y), 255, 0, 0);
	}
	

	// TODO 4: If the player releases the mouse button, destroy the joint
	
	if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_UP) {

		if (mouse_joint != nullptr) {
			world->DestroyJoint(mouse_joint);
			mouse_joint = nullptr;
		}

		// Uncomment if you want to maintain the distance joint
		
		if (distance_joint != nullptr) {
			world->DestroyJoint(distance_joint);
			distance_joint = nullptr;
		}
		

		// Uncomment if you want to maintain the motor joint
		
		if (distance_joint != nullptr) {
			world->DestroyJoint(distance_joint);
			distance_joint = nullptr;
		}
		
	}
	

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete world;

	return true;
}

void PhysBody::GetPosition(int& x, int &y) const
{
	b2Vec2 pos = body->GetPosition();
	x = METERS_TO_PIXELS(pos.x) - (width);
	y = METERS_TO_PIXELS(pos.y) - (height);
}

float PhysBody::GetRotation() const
{
	return RADTODEG * body->GetAngle();
}

bool PhysBody::Contains(int x, int y) const
{
	b2Vec2 p(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->TestPoint(body->GetTransform(), p) == true)
			return true;
		fixture = fixture->GetNext();
	}

	return false;
}

int PhysBody::RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const
{
	int ret = -1;

	b2RayCastInput input;
	b2RayCastOutput output;

	input.p1.Set(PIXEL_TO_METERS(x1), PIXEL_TO_METERS(y1));
	input.p2.Set(PIXEL_TO_METERS(x2), PIXEL_TO_METERS(y2));
	input.maxFraction = 1.0f;

	const b2Fixture* fixture = body->GetFixtureList();

	while(fixture != NULL)
	{
		if(fixture->GetShape()->RayCast(&output, input, body->GetTransform(), 0) == true)
		{
			// do we want the normal ?

			float fx = x2 - x1;
			float fy = y2 - y1;
			float dist = sqrtf((fx*fx) + (fy*fy));

			normal_x = output.normal.x;
			normal_y = output.normal.y;

			return output.fraction * dist;
		}
		fixture = fixture->GetNext();
	}

	return ret;
}

void ModulePhysics::BeginContact(b2Contact* contact)
{
	PhysBody* physA = (PhysBody*)contact->GetFixtureA()->GetBody()->GetUserData();
	PhysBody* physB = (PhysBody*)contact->GetFixtureB()->GetBody()->GetUserData();

	if(physA && physA->listener != NULL)
		physA->listener->OnCollision(physA, physB);

	if(physB && physB->listener != NULL)
		physB->listener->OnCollision(physB, physA);
}