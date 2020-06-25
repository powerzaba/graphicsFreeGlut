#pragma once
#include "DisplayableObject.h"
#include "Animation.h"
#include "TexturedCube.h"
#include "TexturedSphere.h"
#include "TexturedCylinder.h"
#include "GiantSword.h"

//Internal scaling value
#define ARM_JOINT_RADIUS 4
#define LEG_JOING_RADIUS 5
#define HIP_RADIUS 10
#define SHORT_LIMB 30
#define LONG_LIMB 45
#define LEG_RADIUS 5
#define HEAD_RADIUS 14
#define NECK_LENGTH 20
#define NECK_RADIUS 5

class Statue :
	public DisplayableObject,
	public Animation,
	public Input
{
public:	
	//Texture to use for the statue
	Statue(const std::string& filename);
	~Statue() {};

	void Display() override;
	void Update(const double& deltaTime) override;
	void HandleKey(unsigned char key, int state, int x, int y) override;
	
private:
	void DrawStatue();
	void DrawHead();
	void DrawNeck();
	void DrawUpperBody();
	void DrawJoint(float size);
	void DrawArms();
	void DrawLeftArm();
	void DrawRightArm();
	void DrawHip();
	void DrawLegs();
	void DrawLeftLeg(bool isRight);
	void DrawRightLeg(bool isRight);
	void DrawFoot(bool isRight);
	void ResetAnimation();
	
	TexturedCube mUpperChest;
	TexturedCube mLowerChest;
	TexturedCube mFeet;
	TexturedCylinder mNeck;
	TexturedCylinder mArm;
	TexturedCylinder mLeg;
	TexturedSphere mHead;
	TexturedSphere mHip;
	TexturedSphere mJoint;

	Marble marble;
	GiantSword sword;	

	//These variables are used to animate the statue
	int currentKeyFrame;
	float oldDuration;
	float keyframeDuration1 = 1.f;
	float keyframeDuration2 = 1.f;
	float keyframeDuration3 = 1.f;
	float keyframeDuration4 = 1.f;
	float animationTime;
	float rightShoulderAngle = -10.f;
	float rightForeArmAngle = 90.f;
	float leftQuadAngle = 0.f;
	float leftCalvAngle = 20.f;
	float leftShoulderAngle = 10.f;
	float leftForeArmAngle = 90.f;
	float rightQuadAngle = 0.f;
	float rightCalvAngle = 20.f;
	float interpA;
	float interpB;
	bool animate = false;
};


