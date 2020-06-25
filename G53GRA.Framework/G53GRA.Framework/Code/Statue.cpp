#include "Statue.h"
#include <functional>
#include <iostream>

#define BIND(method) std::bind(&Statue::method, this)
#define BIND_1(method) std::bind(&Statue::method, this, std::placeholders::_1)

// Constructor with Texture filename
Statue::Statue(const std::string& filename) : mUpperChest(filename, marble),
											  mLowerChest(filename, marble),
											  mFeet(filename, marble),
										      mNeck(NECK_RADIUS, NECK_LENGTH, filename, marble),
											  mArm(ARM_JOINT_RADIUS, SHORT_LIMB, filename, marble),
											  mLeg(LEG_RADIUS, LONG_LIMB, filename, marble),
											  mHead(filename, marble),
											  mHip(filename, marble),
											  mJoint(filename, marble)
{    

}

void Statue::Display() {
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	
	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);
	glRotatef(rotation[0], 1.f, 0.f, 0.f);
	glRotatef(rotation[1], 0.f, 1.f, 0.f);
	glRotatef(rotation[2], 0.f, 0.f, 1.f);
	
	DrawStatue();

	glPopAttrib();
	glPopMatrix();	
}

//This allows the statue to perform the skipping animation
void Statue::Update(const double& deltaTime) {
	if (!animate) {
		return;
	}
	
	animationTime += static_cast<float>(deltaTime);
	float t = 0;
	
	if (animationTime >= 4.f) {
		ResetAnimation();
	}

	if (animationTime < 1.f) {
		if (currentKeyFrame != 0) {
			animationTime = 0;
			currentKeyFrame = 0;
		}

		t = animationTime - oldDuration / keyframeDuration1;
		interpA = -10.f;
		interpB = -30.f;
		rightShoulderAngle = Lerp(interpA, interpB, EaseIn(t, 5));
		interpA = 90.f;
		interpB = 120.f;
		rightForeArmAngle = Lerp(interpA, interpB, EaseIn(t, 5));
		interpA = 0.f;
		interpB = 90.f;
		leftQuadAngle = Lerp(interpA, interpB, EaseIn(t, 5));
		interpA = 20.f;
		interpB = 90.f;
		leftCalvAngle = Lerp(interpA, interpB, EaseIn(t, 5));
		
	} else if (animationTime < 2.f) {
		if (currentKeyFrame != 1) {			
			currentKeyFrame = 1;
			oldDuration += keyframeDuration1;
		}

		t = (animationTime - oldDuration) / keyframeDuration2;
		interpA = -30.f;
		interpB = -10.f;
		rightShoulderAngle = Lerp(interpA, interpB, EaseOut(t, 5));
		interpA = 120.f;
		interpB = 90.f;
		rightForeArmAngle = Lerp(interpA, interpB, EaseOut(t, 5));
		interpA = 90.f;
		interpB = 0.f;
		leftQuadAngle = Lerp(interpA, interpB, EaseOut(t, 5));
		interpA = 90.f;
		interpB = 20.f;
		leftCalvAngle = Lerp(interpA, interpB, EaseOut(t, 5));
		
	} else if (animationTime < 3.f) {
		if (currentKeyFrame != 2) {
			currentKeyFrame = 2;
			oldDuration += keyframeDuration2;
		}

		t = (animationTime - oldDuration) / keyframeDuration3;
		interpA = 10.f;
		interpB = 30.f;
		leftShoulderAngle = Lerp(interpA, interpB, EaseIn(t, 5));
		interpA = 90.f;
		interpB = 120.f;
		leftForeArmAngle = Lerp(interpA, interpB, EaseIn(t, 5));
		interpA = 0.f;
		interpB = -90.f;
		rightQuadAngle = Lerp(interpA, interpB, EaseIn(t, 5));
		interpA = 20.f;
		interpB = 90.f;
		rightCalvAngle = Lerp(interpA, interpB, EaseIn(t, 5));
		
	} else {
		if (currentKeyFrame != 3) {
			currentKeyFrame = 3;
			oldDuration += keyframeDuration3;
		}
	
		t = (animationTime - oldDuration) / keyframeDuration4;
		interpA = 30.f;
		interpB = 10.f;
		leftShoulderAngle = Lerp(interpA, interpB, EaseOut(t, 5));
		interpA = 120.f;
		interpB = 90.f;
		leftForeArmAngle = Lerp(interpA, interpB, EaseOut(t, 5));
		interpA = -90.f;
		interpB = 0.f;
		rightQuadAngle = Lerp(interpA, interpB, EaseOut(t, 5));
		interpA = 90.f;
		interpB = 20.f;
		rightCalvAngle = Lerp(interpA, interpB, EaseOut(t, 5));
	}		
}

//The user can start/stop the animation, or reset it
void Statue::HandleKey(unsigned char key, int state, int x, int y) {
	if (key == 'z' && state) {
		animate = !animate;
	}

	if (key == 'x' && state) {
		ResetAnimation();
	}
}

//This function draws the statue
void Statue::DrawStatue() {
	drawSubPart(BIND(DrawHead));
}

//This function draws the head
void Statue::DrawHead() {
	mHead.size(HEAD_RADIUS);
	mHead.Display();
	glTranslatef(0, -mNeck.getHeight(), -5);
	glRotatef(5, 1, 0, 0);
	drawSubPart(BIND(DrawNeck));
}

//This function draws the neck
void Statue::DrawNeck() {
	mNeck.Display();
	glTranslatef(0, -mUpperChest.size()[1] / 2, 0);
	glRotatef(-6.5, 1, 0, 0); 
	drawSubPart(BIND(DrawUpperBody));	
}

//This function draws the upper body
void Statue::DrawUpperBody() {	
	mUpperChest.size(23.2f, 22.6f, 14.f);
	mUpperChest.Display();	
	
	drawSubPart(BIND(DrawArms));
	
	//Draw lower part of the upper body
	float a = -mUpperChest.size()[1] / 2;
	float b = -mLowerChest.size()[1] / 2;

	glTranslatef(0, a + b, 0);
	glRotatef(-2.5, 1, 0, 0);
	
	mLowerChest.size(18.2f, 17.8f, 14.f);
	mLowerChest.Display();
	
	drawSubPart(BIND(DrawHip));
}

//This function draws the arms
void Statue::DrawArms() {
	//Draw Left Arm
	glTranslatef(mUpperChest.size()[0] / 2, mUpperChest.size()[1] / 2 - 2, 0);
	drawSubPart(BIND(DrawLeftArm));

	//Draw Right Arm
	glTranslatef(-mUpperChest.size()[0], 0, 0);
	drawSubPart(BIND(DrawRightArm));
}

//This function draw the left arm
void Statue::DrawLeftArm() {
	float shoulderAngle[3] = { -leftShoulderAngle, 0, -160 };
	float foreArmAngle[3] = { leftForeArmAngle, 0, -30 };
	
	glRotatef(shoulderAngle[0], 1, 0, 0);
	glRotatef(shoulderAngle[1], 0, 1, 0);
	glRotatef(shoulderAngle[2], 0, 0, 1);
	DrawJoint(ARM_JOINT_RADIUS);
	mArm.Display();

	glTranslatef(0, SHORT_LIMB, 0);
	DrawJoint(ARM_JOINT_RADIUS);
	glRotatef(foreArmAngle[0], 1, 0, 0);
	glRotatef(foreArmAngle[1], 0, 1, 0);
	glRotatef(foreArmAngle[2], 0, 0, 1);
	mArm.Display();

	glTranslatef(0, SHORT_LIMB, 0);
	DrawJoint(ARM_JOINT_RADIUS);
}

//This function draws the right arm
void Statue::DrawRightArm() {
	float shoulderAngle[3] = { rightShoulderAngle, 0, 160 };
	float foreArmAngle[3] = { rightForeArmAngle, 0, 30 }; //90

	glRotatef(shoulderAngle[0], 1, 0, 0);
	glRotatef(shoulderAngle[1], 0, 1, 0);
	glRotatef(shoulderAngle[2], 0, 0, 1);
	DrawJoint(ARM_JOINT_RADIUS);
	mArm.Display();

	glTranslatef(0, SHORT_LIMB, 0);
	DrawJoint(ARM_JOINT_RADIUS);
	glRotatef(foreArmAngle[0], 1, 0, 0);
	glRotatef(foreArmAngle[1], 0, 1, 0);
	glRotatef(foreArmAngle[2], 0, 0, 1);
	mArm.Display();

	glTranslatef(0, SHORT_LIMB, 0);
	DrawJoint(ARM_JOINT_RADIUS);
}

//This function draws the joints
void Statue::DrawJoint(float size) {
	mJoint.size(size);
	mJoint.Display();
}

//This function draws the hip
void Statue::DrawHip() {
	float a = mLowerChest.size()[1] / 2;
	float b = HIP_RADIUS / 2;		
	glTranslatef(0, -(a + b), 0);
	mHip.size(HIP_RADIUS);
	mHip.Display();

	drawSubPart(BIND(DrawLegs));	
}

//This function draws the leg
void Statue::DrawLegs() {		
	//Draw left leg
	glTranslatef(mHip.size()[0], 0, 0);
	drawSubPart(BIND_1(DrawLeftLeg), false);

	//Draw right leg
	glTranslatef(-mHip.size()[0] * 2, 0, 0);
	drawSubPart(BIND_1(DrawRightLeg), true);
}

//This function draws the left leg
void Statue::DrawLeftLeg(bool isRight) {		
	float quadsAngle[3] = { -leftQuadAngle, 0, 190 };
	float calvAngle[3] = { -leftCalvAngle, 0, 0 };
	
	mJoint.size(LEG_JOING_RADIUS);
	mJoint.Display();
	glRotatef(quadsAngle[0], 1, 0, 0);
	glRotatef(quadsAngle[1], 0, 1, 0);
	glRotatef(quadsAngle[2], 0, 0, 1);
	mLeg.Display();

	
	glTranslatef(0, mLeg.getHeight(), 0);
	mJoint.Display();
	glRotatef(calvAngle[0], 1, 0, 0);
	glRotatef(calvAngle[1], 0, 1, 0);
	glRotatef(calvAngle[2], 0, 0, 1);
	mLeg.Display();

	glTranslatef(0, mLeg.getHeight(), 0);
	mJoint.Display();
	
	glTranslatef( 0, mJoint.size()[0], 0 );
	drawSubPart(BIND_1(DrawFoot), isRight);
}

//This function draws the right leg
void Statue::DrawRightLeg(bool isRight) {
	float quadsAngle[3] = { rightQuadAngle, 0, -190 };
	float calvAngle[3] = { -rightCalvAngle, 0, 0 };

	mJoint.size(LEG_JOING_RADIUS);
	mJoint.Display();
	glRotatef(quadsAngle[0], 1, 0, 0);
	glRotatef(quadsAngle[1], 0, 1, 0);
	glRotatef(quadsAngle[2], 0, 0, 1);
	mLeg.Display();


	glTranslatef(0, mLeg.getHeight(), 0);
	mJoint.Display();
	glRotatef(calvAngle[0], 1, 0, 0);
	glRotatef(calvAngle[1], 0, 1, 0);
	glRotatef(calvAngle[2], 0, 0, 1);
	mLeg.Display();

	glTranslatef(0, mLeg.getHeight(), 0);
	mJoint.Display();

	glTranslatef(0, mJoint.size()[0], 0);
	drawSubPart(BIND_1(DrawFoot), isRight);
}

//This function draws either the left or the right foot
void Statue::DrawFoot(bool isRight) {
	float footRotation[3] = { 15, 0, -10 };

	if (isRight) {
		footRotation[2] = -footRotation[2];
	}	
	
	glRotatef(footRotation[0], 1, 0, 0);
	glRotatef(footRotation[1], 0, 1, 0);
	glRotatef(footRotation[2], 0, 0, 1);
		
	mFeet.size(10, 6, 15);
	mFeet.Display();
	glTranslatef(0, 0, mFeet.size()[2] + 2);	
	mFeet.Display();
}

//This function resets the animation for the statue
void Statue::ResetAnimation() {
	animationTime = 0.f;
	oldDuration = 0.f;
	currentKeyFrame = -1;
	rightShoulderAngle = -10.f;
	rightForeArmAngle = 90.f;
	leftQuadAngle = 0.f;
	leftCalvAngle = 20.f;
	leftShoulderAngle = 10.f;
	leftForeArmAngle = 90.f;
	rightQuadAngle = 0.f;
	rightCalvAngle = 20.f;
}

