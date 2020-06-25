#include "SkyBox.h"

SkyBox::SkyBox() {
	mCamera = nullptr;
    followCamera = false;
    SetTexture();
}

SkyBox::SkyBox(Camera* camera1) {
    mCamera = camera1;
    followCamera = true;

    SetTexture();
}


void SkyBox::Display() {
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	//SkyBox is always centered from the camera
	if (followCamera) {
        mCamera->GetEyePosition(pos[0], pos[1], pos[2]);
        pos[1] -= 2000;
	}

	glTranslatef(pos[0], pos[1], pos[2]);               
	glScalef(scale[0], scale[1], scale[2]);             
	glRotatef(rotation[1], 0.f, 1.f, 0.f);              
	glRotatef(rotation[2], 0.f, 0.f, 1.f);              
	glRotatef(rotation[0], 1.f, 0.f, 0.f);              

	DrawStage();

	glPopAttrib();
	glPopMatrix();
}

//This draws the skybox
void SkyBox::DrawStage() {
    glDisable(GL_LIGHTING);                
    glEnable(GL_TEXTURE_2D);  
    glColor4f(1.f, 1.f, 1.f, 1.f);        

    glBindTexture(GL_TEXTURE_2D, texID[0]);
    glBegin(GL_QUADS);
    // LEFT SIDE
    glTexCoord2f(1.f, 1.f); 
    glVertex3f(-1.f, 1.f, -1.f);
    glTexCoord2f(0.f, 1.f);  
    glVertex3f(-1.f, 1.f, 1.f);
    glTexCoord2f(0.f, 0.f); 
    glVertex3f(-1.f, 0.f, 1.f);
    glTexCoord2f(1.f, 0.f);  
    glVertex3f(-1.f, 0.f, -1.f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texID[1]);
    glBegin(GL_QUADS);
    // RIGHT SIDE
    glTexCoord2f(1.f, 1.f); 
    glVertex3f(1.f, 1.f, 1.f);
    glTexCoord2f(0.f, 1.f);  
    glVertex3f(1.f, 1.f, -1.f);
    glTexCoord2f(0.f, 0.f);  
    glVertex3f(1.f, 0.f, -1.f);
    glTexCoord2f(1.f, 0.f); 
    glVertex3f(1.f, 0.f, 1.f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texID[2]);
    glBegin(GL_QUADS);
    //  FAR SIDE
    glTexCoord2f(1.f, 1.f);  
    glVertex3f(1.f, 1.f, -1.f);
    glTexCoord2f(0.f, 1.f);  
    glVertex3f(-1.f, 1.f, -1.f);
    glTexCoord2f(0.f, 0.f); 
    glVertex3f(-1.f, 0.f, -1.f);
    glTexCoord2f(1.f, 0.f);  
    glVertex3f(1.f, 0.f, -1.f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texID[3]); 
    glBegin(GL_QUADS);
    // NEAR SIDE
    glTexCoord2f(1.f, 1.f);  
    glVertex3f(-1.f, 1.f, 1.f);
    glTexCoord2f(0.f, 1.f);  
    glVertex3f(1.f, 1.f, 1.f);
    glTexCoord2f(0.f, 0.f);  
    glVertex3f(1.f, 0.f, 1.f);
    glTexCoord2f(1.f, 0.f); 
    glVertex3f(-1.f, 0.f, 1.f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texID[4]); 
    glBegin(GL_QUADS);
    // BOTTOM SIDE
    glTexCoord2f(0.f, 0.f);  
    glVertex3f(-1.f, 0.f, 1.f);
    glTexCoord2f(1.f, 0.f);  
    glVertex3f(1.f, 0.f, 1.f);
    glTexCoord2f(1.f, 1.f);  
    glVertex3f(1.f, 0.f, -1.f);
    glTexCoord2f(0.f, 1.f);  
    glVertex3f(-1.f, 0.f, -1.f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texID[5]); 
    glBegin(GL_QUADS);
    // TOP SIDE
    glTexCoord2f(1.f, 1.f);  
    glVertex3f(1.f, 1.f, 1.f);
    glTexCoord2f(0.f, 1.f);  
    glVertex3f(-1.f, 1.f, 1.f);
    glTexCoord2f(0.f, 0.f);  
    glVertex3f(-1.f, 1.f, -1.f);
    glTexCoord2f(1.f, 0.f);  
    glVertex3f(1.f, 1.f, -1.f);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, NULL);
    glDisable(GL_TEXTURE_2D);   
    glEnable(GL_LIGHTING);                     
}

//This function sets the textures for the skybox
void SkyBox::SetTexture() {
    texID[0] = Scene::GetTexture("./Textures/left.bmp");
    texID[1] = Scene::GetTexture("./Textures/right.bmp");
    texID[2] = Scene::GetTexture("./Textures/front.bmp");
    texID[3] = Scene::GetTexture("./Textures/back.bmp");
    texID[4] = Scene::GetTexture("./Textures/bottom.bmp");
    texID[5] = Scene::GetTexture("./Textures/top.bmp");
}
