#include <cmath>
#include "TexturedCylinder.h"

TexturedCylinder::TexturedCylinder(float radius, float height, const std::string& filename, Material mat) : mRadius(radius), mHeight(height) {
    texID = Scene::GetTexture(filename);
    SetMaterial(mat);
    isMat = true;
}

TexturedCylinder::TexturedCylinder(float radius, float height) {
    texID = NULL;
    mRadius = radius;
    mHeight = height;
}

void TexturedCylinder::Display() {
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glTranslatef(pos[0], pos[1], pos[2]);
    glScalef(scale[0], scale[1], scale[2]);
    glRotatef(rotation[0], 1.f, 0.f, 0.f);
    glRotatef(rotation[1], 0.f, 1.f, 0.f);
    glRotatef(rotation[2], 0.f, 0.f, 1.f);

	if (isMat) {
        glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
		glMateriali(GL_FRONT, GL_SHININESS, matShininess);
	}
    
    DrawCylinder();

    glPopAttrib();
    glPopMatrix();
}

void TexturedCylinder::DrawCylinder() {
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);
    glBindTexture(GL_TEXTURE_2D, texID);

    float resolution = 0.1f * M_PI;
    float x = mRadius;
    float z = 0.f;
    float t = 0.f;

    float numberOfFaces = (2 * M_PI) / resolution;
    float width = 1 / numberOfFaces;

    for (int i = 0; i < numberOfFaces; i++) {
        glBegin(GL_QUADS);

        glNormal3f(x, 0.f, z);   
        glTexCoord2f(i * width, 0.f); 
        glVertex3f(x, 0.f, z);  

        glTexCoord2f(i * width, 1.f); 
        glVertex3f(x, mHeight, z);          

        t += resolution;                       
        x = mRadius * cos(t);                  
        z = mRadius * sin(t);        

        glNormal3f(x, 0.f, z);         
        glTexCoord2f(i * width + width, 1.f);  
        glVertex3f(x, mHeight, z);          

        glTexCoord2f(i * width + width, 0.f);
        glVertex3f(x, 0.f, z);   

        glEnd();
    }

    glDisable(GL_COLOR_MATERIAL);
    glBindTexture(GL_TEXTURE_2D, NULL);
    glDisable(GL_TEXTURE_2D);
}

float TexturedCylinder::getRadius() const {
    return mRadius;
}

float TexturedCylinder::getHeight() const {
    return mHeight;
}