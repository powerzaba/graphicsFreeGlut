#include "TexturedCube.h"

TexturedCube::TexturedCube(const std::string& filename, Material mat)
{
	texID = Scene::GetTexture(filename);
	SetMaterial(mat);
	texture = true;
}

TexturedCube::TexturedCube(Material mat) {
	texID = 0;
	SetMaterial(mat);
	texture = false;
}

void TexturedCube::Display()
{
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);
	glRotatef(rotation[1], 0.f, 1.f, 0.f);
	glRotatef(rotation[2], 0.f, 0.f, 1.f);
	glRotatef(rotation[0], 1.f, 0.f, 0.f);

	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
	glMateriali(GL_FRONT, GL_SHININESS, matShininess);

	DrawCube();

	glPopAttrib();
	glPopMatrix();
}

void TexturedCube::DrawCube() {
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	glBindTexture(GL_TEXTURE_2D, texID);
	
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	if (texture) glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	if (texture) glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	if (texture) glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	if (texture) glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);

	glNormal3f(0.0f, 0.0f, -1.0f);
	if (texture) glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	if (texture) glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	if (texture) glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	if (texture) glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	if (texture) glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	if (texture) glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	if (texture) glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	if (texture) glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	glNormal3f(1.0f, 0.0f, 0.0f);
	if (texture) glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	if (texture) glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	if (texture) glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	if (texture) glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);

	glNormal3f(0.0f, 1.0f, 0.0f);
	if (texture) glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	if (texture) glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	if (texture) glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	if (texture) glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, -0.5f);

	glNormal3f(0.0f, -1.0f, 0.0f);
	if (texture) glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	if (texture) glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	if (texture) glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	if (texture) glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glEnd();

	glDisable(GL_COLOR_MATERIAL);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);
}



