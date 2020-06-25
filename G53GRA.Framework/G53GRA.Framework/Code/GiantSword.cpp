#include "GiantSword.h"

#define BIND(method) std::bind(&GiantSword::method, this)

GiantSword::GiantSword() : mSwordStart("./Textures/marble.bmp", marble),
						   mBlade("./Textures/fire.bmp", metal),
						   mBladeEnd("./Textures/fire.bmp", metal),
						   mHandle(HANDLE_RADIUS, HANDLE_LENGTH, "./Textures/marble.bmp", marble),
						   mGuards(GUARD_RADIUS, GUARD_LENGTH, "./Textures/marble.bmp", marble),
						   mSmallSphere("./Textures/gold.bmp", gold),
						   mGuardsSpheres("./Textures/gold.bmp", gold),
						   mGem("./Textures/gem.bmp", gem)
{

}

void GiantSword::Display() {
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glTranslatef(pos[0], pos[1], pos[2]);
    glRotatef(rotation[1], 0.0f, 1.0f, 0.0f);
    glRotatef(rotation[2], 0.0f, 0.0f, 1.0f);
    glRotatef(rotation[0], 1.0f, 0.0f, 0.0f);
    glScalef(scale[0], scale[1], scale[2]);

    DrawHandle();
	
    glPopAttrib();
    glPopMatrix();
}

//The sword rotates on its own y axis and wobbles up and down
void GiantSword::Update(const double& deltaTime) {
    mRotation += ROTATION_SWORD * deltaTime;
    GLfloat radVal = glutGet(GLUT_ELAPSED_TIME) * (M_PI / 180);
    pos[1] += sin(radVal * UP_DOWN_SPEED) * 10;
}

//This function draws the handle
void GiantSword::DrawHandle() {
    glRotatef(mRotation, 0, 1, 0);
    mSmallSphere.size(SMALL_SPHERE);
    mSmallSphere.Display();
    glTranslatef(0, -SMALL_SPHERE, 0);
    glTranslatef(0, -mHandle.getHeight(), 0);
    mHandle.Display();
    drawSubPart(BIND(DrawGem));
}

//This draws the gem
void GiantSword::DrawGem() {
    mGem.size(GEM_RADIUS);
    mGem.Display();

    drawSubPart(BIND(DrawGuards));
    drawSubPart(BIND(DrawBlade));
}

//This draws the guards
void GiantSword::DrawGuards() {
    glRotatef(90, 0, 1, 0);
    glRotatef(-90, 1, 0, 0);
    glTranslatef(0, -GUARD_LENGTH, 0);
    mGuards.Display();
    mGuardsSpheres.size(2);
    mGuardsSpheres.Display();
    glTranslatef(0, GUARD_LENGTH, 0);
    glRotatef(90, 1, 0, 0);
    glRotatef(-90, 0, 1, 0);

    glTranslatef(-GUARD_LENGTH, 0, 0);
    glRotatef(-90, 0, 1, 0);
    glRotatef(-90, 1, 0, 0);
    mGuards.Display();
    mGuardsSpheres.size(2);
    mGuardsSpheres.Display();
}

//This draws the blade 
void GiantSword::DrawBlade() {
    glTranslatef(0, -5, 0);
    mSwordStart.size(13, 5, 2);
    mSwordStart.Display();
    glTranslatef(0, -mSwordStart.size()[1] / 2, 0);
    mBlade.size(10, 65, 1.5);
    glTranslatef(0, -mBlade.size()[1] / 2, 0);
    mBlade.Display();
    glTranslatef(0, -mBlade.size()[1] / 2, 0);
    mBladeEnd.size(10, 10, 1.5);
    glRotatef(45, 0, 0, 1);
    mBladeEnd.Display();
}


