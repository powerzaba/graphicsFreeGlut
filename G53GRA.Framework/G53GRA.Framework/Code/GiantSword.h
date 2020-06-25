#pragma once
#include "DisplayableObject.h"
#include "TexturedCube.h"
#include "TexturedSphere.h"
#include "TexturedCylinder.h"
#include "Animation.h"

#define SMALL_SPHERE 3
#define GEM_RADIUS 5
#define GUARD_RADIUS 5
#define GUARD_LENGTH 15
#define HANDLE_LENGTH 18
#define GUARD_RADIUS 1.5
#define HANDLE_RADIUS 2
#define ROTATION_SWORD 20
#define UP_DOWN_SPEED 0.5

class GiantSword :
	public DisplayableObject,
	public Animation
{
	
public:
	GiantSword();
	~GiantSword() {};

	void Display() override;
	void Update(const double& deltaTime) override;

private:
	void DrawHandle();
	void DrawGem();
	void DrawGuards();
	void DrawBlade();

	Metal metal;
	Gold gold;
	Gem gem;
	Marble marble;
	TexturedCube mSwordStart;
	TexturedCube mBlade;
	TexturedCube mBladeEnd;
	TexturedCylinder mHandle;
	TexturedCylinder mGuards;
	TexturedSphere mSmallSphere;
	TexturedSphere mGem;
	TexturedSphere mGuardsSpheres;

	GLfloat mRotation = 0;
};

