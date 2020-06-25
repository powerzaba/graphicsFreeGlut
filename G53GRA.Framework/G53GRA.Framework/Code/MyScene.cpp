#include "MyScene.h"
#include "TexturedCube.h"
#include "TexturedCylinder.h"
#include "TexturedSphere.h"
#include "Statue.h"
#include "RandomSurface.h"
#include "SkyBox.h"
#include "GiantSword.h"
#include "SunAndMoon.h"
#include "SphereCoating.h"
#include "Monument.h"

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{

}

void MyScene::Initialise()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

#ifdef __APPLE__
	TexturedCube* tc = new TexturedCube("./batmanlogo.bmp");
#else
	Statue* statue = new Statue("./Textures/marble.bmp");
	statue->position(0, -100, 100);
#endif
	float sideLegth = 5;
	RandomSurface* randomSur = new RandomSurface(sideLegth, "./Textures/desert.bmp");
	randomSur->orientation(-90, 0, 0);	
	randomSur->position(-(TERRAIN_ROWS * sideLegth) / 2, -280, -300);

	SkyBox* skyBox = new SkyBox(Scene::GetCamera());
	skyBox->size(4000);

	GiantSword* sword = new GiantSword();
	sword->position(0, -50, 150);

	float radius = 400;
	SunAndMoon* sunAndMoon = new SunAndMoon(radius);

	Monument* monument = new Monument("./Textures/map.bmp");
	monument->position(0, 0, -150);

	Camera* camera;
	camera = Scene::GetCamera();
	camera->SetPosition(monument->position());
		
	AddObjectToScene(randomSur);
	AddObjectToScene(statue);
	AddObjectToScene(skyBox);
	AddObjectToScene(sword);
	AddObjectToScene(sunAndMoon);
	AddObjectToScene(monument);
}


void MyScene::Projection()
{
	GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
	gluPerspective(60.0, aspect, 1.0, 10000.0);
}
