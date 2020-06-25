#include "Monument.h"

#include <iostream>

#define BIND(method) std::bind(&Monument::method, this)

Monument::Monument(const std::string& filename) : firstRing(180, 5, RADIUS_FIRST_RING, RING_THICKNESS, ringMaterial),
												  secondRing(180, 5, RADIUS_SECOND_RING, RING_THICKNESS, ringMaterial),
												  thirdRing(150, 5, RADIUS_THIRD_RING, RING_THICKNESS, ringMaterial),
												  mainBody(filename, innerMaterial)
{
	
}

void Monument::Display() {
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glTranslatef(pos[0], pos[1], pos[2]);
    glRotatef(rotation[1], 0.0f, 1.0f, 0.0f);
    glRotatef(rotation[2], 0.0f, 0.0f, 1.0f);
    glRotatef(rotation[0], 1.0f, 0.0f, 0.0f);
    glScalef(scale[0], scale[1], scale[2]);

    DrawMonument();

    glPopAttrib();
    glPopMatrix();
}

//The three rings rotate at different speeds around the monument, and they all rotate
//according to their local y axis
void Monument::Update(const double& deltaTime) {
    GLfloat firstStep = FIRST_ROT_SPEED * SPEED * deltaTime;
    GLfloat secondStep = SECOND_ROT_SPEED * SPEED * deltaTime;
    GLfloat thirdStep = THIRD_ROT_SPEED * SPEED * deltaTime;
    GLfloat bodyStep = BODY_ROT_SPEED * SPEED * deltaTime;

	if (rotateFirst)
		firstRotationAngle -= firstStep;

	if (rotateSecond)
		secondRotationAngle -= secondStep;

	if (rotateThird)
		thirdRotationAngle += thirdStep;
	
    bodyRotationAngle += bodyStep;
}

//When the camera is repositioned in the monument the user can stop the animations of the rings
void Monument::HandleKey(unsigned char key, int state, int x, int y) {
    Camera* camera = Scene::GetCamera();
    bool val = camera->IsInNewPosition();
	
    if (key == 'c' && state && val) {
        rotateFirst = !rotateFirst;
        std::cout << rotateFirst;
    }

    if (key == 'v' && state && val) {
        rotateSecond = !rotateSecond;
    }

    if (key == 'b' && state && val) {
        rotateThird = !rotateThird;
    }
}

//This function draw the monument 
void Monument::DrawMonument() {
    drawSubPart(BIND(DrawBody));
    drawSubPart(BIND(DrawFirstRing));
    drawSubPart(BIND(DrawSecondRing));
    drawSubPart(BIND(DrawThirdRing));
}

//This draw the central sphere
void Monument::DrawBody() {
    glRotatef(bodyRotationAngle, 0, 1, 0);
    mainBody.size(MAIN_SIZE);
    mainBody.Display();
}

//This draws the first ring
void Monument::DrawFirstRing() {
    GLfloat color[] = { 0.2,0.2,0.2 };
    glRotatef(firstRotationAngle, 1, 0, 0);
    firstRing.SetColor(color);
    firstRing.Display();
}

//This draws the second ring
void Monument::DrawSecondRing() {
    GLfloat color[] = { 0.5,0.5,0.5 };
    glRotatef(90, 0, 0, 1);
    glRotatef(secondRotationAngle, 1, 0, 0);
    secondRing.SetColor(color);
    secondRing.Display();
}

//This draws the third ring
void Monument::DrawThirdRing() {
    GLfloat color[] = { 0.1,0.1,0.1 };
    glRotatef(45, 0, 0, 1);
    glRotatef(thirdRotationAngle, 0, 1, 0);
    thirdRing.SetColor(color);
    thirdRing.Display();
}



