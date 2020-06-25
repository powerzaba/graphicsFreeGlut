#include "SunAndMoon.h"

#define Y_OFFSET 150
#define Z_OFFSET 200
#define SUN_MOON_SPEED 5


SunAndMoon::SunAndMoon(float radius) : mRadius(radius), mAngle(90), mSpeed(SUN_MOON_SPEED) {
	
	static GLfloat posSun[] = {0.f, mRadius - Y_OFFSET, Z_OFFSET, 1.f};
	static GLfloat ambSun[] = { 0.7f, 0.7f, 0.2f, 1.f };
	static GLfloat diffSun[] = { 1.f, 0.f, 0.f, 1.f };
	static GLfloat specSun[] = { 1.f, 0.f, 0.f, 1.f };
	positionSun = posSun;
	ambientSun = ambSun;
	diffuseSun = diffSun;
	specularSun = specSun;

	static GLfloat posMoon[] = { 0.f, -mRadius - Y_OFFSET, Z_OFFSET, 1.f };
	static GLfloat ambMoon[] = { 0.f, 0.f, 0.2f, 1.f };
	static GLfloat diffMoon[] = { 0.f, 0.f, 1.f, 1.f };
	static GLfloat specMoon[] = { 0.f, 0.f, 1.f, 1.f };
	positionMoon = posMoon;
	ambientMoon = ambMoon;
	diffuseMoon = diffMoon;
	specularMoon = specMoon;

	static GLfloat posGlobal[] = { 1.f, 1.f, 1.f, 0.f };
	static GLfloat ambGlobal[] = { 0.2f, 0.2f, 0.2f, 0.2f };
	static GLfloat diffGlobal[] = { 0.2f, 0.2f, 0.2f, 1.f };
	static GLfloat specGlobal[] = { 1.f, 1.f, 1.f, 1.f };
	positionGlobal = posGlobal;
	ambientGlobal = ambGlobal;
	diffuseGlobal = diffGlobal;
	specularGlobal = specGlobal;
		
}

void SunAndMoon::Display() {
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDisable(GL_LIGHTING);

	//This allows the user to see the position of the sun or the moon
	if (showSpheres) {
		glPushMatrix();
		glColor4fv(&diffuseSun[0]);
		glTranslatef(positionSun[0], positionSun[1], positionSun[2]);
		glutSolidSphere(10.0, 10, 10);
		glPopMatrix();

		glPushMatrix();
		glColor4fv(&diffuseMoon[0]);
		glTranslatef(positionMoon[0], positionMoon[1], positionMoon[2]);
		glutSolidSphere(10.0, 10, 10);
		glPopMatrix();
	}	

	glEnable(GL_LIGHTING);
	glPopAttrib();
	glPopMatrix();
}

//This function allows the sun and the moon to rotate if the user presses a key
void SunAndMoon::Update(const double& deltaTime) {
	if (mAngle <= -270) {
		mAngle = 90;
		targetSun = 90;
	}
	
	if (mAngle <= targetSun) {
		mAngle = targetSun;
		done = true;				
	} else {
		done = false;
		mAngle -= mSpeed;
		float rad = mAngle * (M_PI / 180);
		positionSun[0] = mRadius * cos(rad);
		positionSun[1] = mRadius * sin(rad) - Y_OFFSET;

		positionMoon[0] = -mRadius * cos(rad);
		positionMoon[1] = -mRadius * sin(rad) - Y_OFFSET;
	}

	
	float a = mAngle;
	if (a < 0) {
		a += 180;
		a = -a;
	}
	float t = a / 90.f;
	ambientSun[0] = Lerp(1.f, 0.7f, t);
	ambientSun[1] = Lerp(0.25f, 0.7f, t);
	ambientSun[2] = Lerp(0.f, 0.5f, t);

	glEnable(GL_LIGHTING);
	
	glLightfv(GL_LIGHT0, GL_POSITION, positionGlobal);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientGlobal);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseGlobal);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularGlobal);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_POSITION, positionSun);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambientSun);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuseSun);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specularSun);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0025f);
	if (-180 <= mAngle && mAngle <= 0) {
		glDisable(GL_LIGHT1);
		sunIsDown = true;
	} else {
		glEnable(GL_LIGHT1);
		sunIsDown = false;
	}
	

	glLightfv(GL_LIGHT2, GL_POSITION, positionMoon);
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambientMoon);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuseMoon);
	glLightfv(GL_LIGHT2, GL_SPECULAR, specularMoon);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.00025f);
	if (sunIsDown) {
		glEnable(GL_LIGHT2);
	} else {
		glDisable(GL_LIGHT2);
	}
}

//This function changes the target for the sun when the user presses 1
//Changing the target activates the update function
//The user needs to wait for the animation to be completed before being able to press 1 again
void SunAndMoon::HandleKey(unsigned char key, int state, int x, int y) {
	if (key == '1' && state) {
		if (done) {
			if (targetSun == -90.f) {
				targetSun = -270.f;
			} else if (targetSun == -270.f) {
				targetSun = -90.f;
			} else if (targetSun == 90.f) {
				targetSun = -90.f;
			}
		}		
	}

	if (key == '2' && state) {
		showSpheres = !showSpheres;
	}
}




