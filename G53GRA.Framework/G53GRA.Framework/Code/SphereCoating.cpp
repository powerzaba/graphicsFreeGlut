#include "SphereCoating.h"

#include <iostream>

#define BIND(method) std::bind(&SphereCoating::method, this)

SphereCoating::SphereCoating(float widthAngle, float heightAngle, float radius,
    float thickness, Material mat) : mWidthAngle(widthAngle),
                                     mHeightAngle(heightAngle),
                                     mRadius(radius),
                                     mThickness(thickness) {
	
	widthStep = (mWidthAngle * 2) / WIDTH_RESOLUTION;
	heightStep = (mHeightAngle * 2) / HEIGHT_RESOLUTION;

    //Default color
    mColor[0] = 0.f;
    mColor[1] = 0.f;
    mColor[2] = 1.f;

    SetMaterial(mat);
}

void SphereCoating::Display() {
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glTranslatef(pos[0], pos[1], pos[2]);
    glRotatef(rotation[1], 0.0f, 1.0f, 0.0f);
    glRotatef(rotation[2], 0.0f, 0.0f, 1.0f);
    glRotatef(rotation[0], 1.0f, 0.0f, 0.0f);
    glScalef(scale[0], scale[1], scale[2]);
	
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMateriali(GL_FRONT, GL_SHININESS, matShininess);

    glColor3f(mColor[0], mColor[1], mColor[2]);
    DrawCoating();

    glPopAttrib();
    glPopMatrix();
}

//This sets a color for the object
void SphereCoating::SetColor(GLfloat newColor[3]) {
    mColor[0] = newColor[0];
    mColor[1] = newColor[1];
    mColor[2] = newColor[2];
}

//This calls the various functions to draw the different faces
void SphereCoating::DrawCoating() {
    drawSubPart(BIND(DrawFront));
    drawSubPart(BIND(DrawBack));
    drawSubPart(BIND(DrawLeftSide));	
    drawSubPart(BIND(DrawRightSide));
    drawSubPart(BIND(DrawTop));
    drawSubPart(BIND(DrawBottom));
}

void SphereCoating::DrawFront() {
    DrawSurface(true);
}

void SphereCoating::DrawBack() {
    DrawSurface(false);
}

void SphereCoating::DrawLeftSide() {
    DrawSide(true);
}

void SphereCoating::DrawRightSide() {
    DrawSide(false);
}

void SphereCoating::DrawTop() {
    DrawClosing(true);
}

void SphereCoating::DrawBottom() {
    DrawClosing(false);
}

//This draws either the front or the back faces
void SphereCoating::DrawSurface(bool isFront) {	
    const float radius = (isFront) ? mRadius + mThickness : mRadius;

    for (float y = 90 - mHeightAngle; y < 90 + mHeightAngle; y += heightStep) {
        glBegin(GL_QUAD_STRIP);
        for (float x = -mWidthAngle; x <= mWidthAngle; x += widthStep) {
            float rad_y = y * (M_PI / 180);
            float rad_x = x * (M_PI / 180);
            float rad_step = heightStep * (M_PI / 180);

            float v1_x = radius * sin(rad_y) * sin(rad_x);
            float v1_y = radius * cos(rad_y);
            float v1_z = radius * sin(rad_y) * cos(rad_x);

            float v2_x = radius * sin(rad_y + rad_step) * sin(rad_x);
            float v2_y = radius * cos(rad_y + rad_step);
            float v2_z = radius * sin(rad_y + rad_step) * cos(rad_x);

        	if (isFront) {
                glNormal3f(v1_x, v1_y, v1_z);
                glVertex3f(v1_x, v1_y, v1_z);
                glNormal3f(v2_x, v2_y, v2_z);
                glVertex3f(v2_x, v2_y, v2_z);
        	} else {
	            glNormal3f(-v2_x, -v2_y, -v2_z);
	            glVertex3f(v2_x, v2_y, v2_z);
	            glNormal3f(-v1_x, -v1_y, -v1_z);
	            glVertex3f(v1_x, v1_y, v1_z);
            }            
        }
        glEnd();
    }
}

//This draw either the left or the right face
void SphereCoating::DrawSide(bool isLeft) {
    float bigRadius = mRadius + mThickness;

    glBegin(GL_QUAD_STRIP);
    for (float y = 90 - mHeightAngle; y <= 90 + mHeightAngle; y += heightStep) {
        float rad_y = y * (M_PI / 180);
        float widthAngle = (isLeft) ? mWidthAngle : -mWidthAngle;
        float rad_x = widthAngle * (M_PI / 180);
        float rad_x1 = 0.f;
    	
    	if (isLeft) {
            rad_x1 = (widthAngle - widthStep) * (M_PI / 180);
    	} else {
            rad_x1 = (widthAngle + widthStep) * (M_PI / 180);
    	}
        
        float v1_x = bigRadius * sin(rad_y) * sin(rad_x);
        float v1_y = bigRadius * cos(rad_y);
        float v1_z = bigRadius * sin(rad_y) * cos(rad_x);
    	
        float v2_x = mRadius * sin(rad_y) * sin(rad_x);
        float v2_y = mRadius * cos(rad_y);
        float v2_z = mRadius * sin(rad_y) * cos(rad_x);

    	//normal calculation 
        float v3_x = mRadius * sin(rad_y) * sin(rad_x1);
        float v3_y = mRadius * cos(rad_y);
        float v3_z = mRadius * sin(rad_y) * cos(rad_x1);
        float normal[] = { v2_x, v2_y, v2_z };
        float vec3[] = { v3_x, v3_y, v3_z };
        sub(normal, vec3);

    	if (isLeft) {
            glNormal3f(normal[0], normal[1], normal[2]);
            glVertex3f(v2_x, v2_y, v2_z);
            glNormal3f(normal[0], normal[1], normal[2]);
            glVertex3f(v1_x, v1_y, v1_z);
    	} else {
	        glNormal3f(normal[0], normal[1], normal[2]);
	        glVertex3f(v1_x, v1_y, v1_z);
	        glNormal3f(normal[0], normal[1], normal[2]);
	        glVertex3f(v2_x, v2_y, v2_z);
        }        
    }
    glEnd();
}

//This draws either the top or the bottom face
void SphereCoating::DrawClosing(bool isTop) {
    float bigRadius = mRadius + mThickness;

    glBegin(GL_QUAD_STRIP);
    for (float x = -mWidthAngle; x <= mWidthAngle; x += widthStep) {
        float rad_y = 0.f;
    	
    	if (isTop) {
            rad_y = (90 - mHeightAngle) * (M_PI / 180);
    	} else {
            rad_y = (90 + mHeightAngle) * (M_PI / 180);
    	}
        
        float rad_x = x * (M_PI / 180);

        float v1_x = bigRadius * sin(rad_y) * sin(rad_x);
        float v1_y = bigRadius * cos(rad_y);
        float v1_z = bigRadius * sin(rad_y) * cos(rad_x);

        float v2_x = mRadius * sin(rad_y) * sin(rad_x);
        float v2_y = mRadius * cos(rad_y);
        float v2_z = mRadius * sin(rad_y) * cos(rad_x);

    	if (isTop) {
            glNormal3f(0, 1, 0);
            glVertex3f(v2_x, v2_y, v2_z);
            glNormal3f(0, 1, 0);
            glVertex3f(v1_x, v1_y, v1_z);
    	} else {
	        glNormal3f(0, -1, 0);
	        glVertex3f(v1_x, v1_y, v1_z);
	        glNormal3f(0, -1, 0);
	        glVertex3f(v2_x, v2_y, v2_z);
        }        
    }
    glEnd();
}