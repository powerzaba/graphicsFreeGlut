#pragma once
#include "DisplayableObject.h"
#include "Animation.h"
#include "Input.h"
#include "VectorMath.h"


class SunAndMoon :
	public DisplayableObject,
	public Animation,
	public Input
{
public:
	SunAndMoon(float radius);
	~SunAndMoon() {};

	void Display() override;
	void Update(const double& deltaTime) override;
	void HandleKey(unsigned char key, int state, int x, int y) override;
	
private:
	//These variables contain the values used for the lights
	GLfloat* positionSun, * ambientSun, * diffuseSun, * specularSun;
	GLfloat* positionMoon, * ambientMoon, * diffuseMoon, * specularMoon;
	GLfloat* positionGlobal, * ambientGlobal, * diffuseGlobal, * specularGlobal;

	//These variables are used for animating the sun and the moon
	float mRadius;
	float mAngle;
	float mSpeed;

	float targetSun = 90;
	float targetMoon;
	bool done = true;
	bool sunIsDown = false;
	bool showSpheres = false;
};

