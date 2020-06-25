#pragma once

#include "DisplayableObject.h"
#include "Animation.h"
#include "Input.h"
#include "TexturedSphere.h"
#include "SphereCoating.h"

#define RADIUS_FIRST_RING 150
#define RADIUS_SECOND_RING 170
#define RADIUS_THIRD_RING 190
#define RING_THICKNESS 10
#define MAIN_SIZE 120
#define FIRST_ROT_SPEED 60
#define SECOND_ROT_SPEED 40
#define THIRD_ROT_SPEED 20
#define BODY_ROT_SPEED 10
#define SPEED 3

class Monument :
	public DisplayableObject,
	public Animation,
	public Input {

public:
	Monument(const std::string& filename);
	~Monument() {};

	void Display() override;
	void Update(const double& deltaTime) override;
	void HandleKey(unsigned char key, int state, int x, int y) override;
	
private:
	void DrawMonument();
	void DrawBody();
	void DrawFirstRing();
	void DrawSecondRing();
	void DrawThirdRing();

	Metal ringMaterial;
	Marble innerMaterial;
	TexturedSphere mainBody;
	SphereCoating firstRing;
	SphereCoating secondRing;
	SphereCoating thirdRing;

	//These variables are used to control the rotation angle of the rings
	GLfloat firstRotationAngle = 0;
	GLfloat secondRotationAngle = 0;
	GLfloat thirdRotationAngle = 0;
	GLfloat bodyRotationAngle = 0;

	//These variables are used to control the rotation of the rings
	bool rotateFirst = true;
	bool rotateSecond = true;
	bool rotateThird = true;
};


