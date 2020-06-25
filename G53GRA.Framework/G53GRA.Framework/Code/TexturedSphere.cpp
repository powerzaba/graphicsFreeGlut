#include "TexturedSphere.h"
#include "VectorMath.h"

TexturedSphere::TexturedSphere()
    : _resolution(4), _texID(NULL), mRadius(1)
{
    static float vertices[] =
    {
        1.0f, 0.0f, 0.0f,   
        0.0f, 0.0f, -1.0f,  
        -1.0f, 0.0f, 0.0f,  
        0.0f, 0.0f, 1.0f,   
        0.0f, 1.0f, 0.0f,   
        0.0f, -1.0f, 0.0f   
    };
    _initV = vertices;
}

TexturedSphere::TexturedSphere(const std::string& filename, Material mat) : TexturedSphere()
{
    SetTexture(filename);
    SetMaterial(mat);
}

void TexturedSphere::SetTexture(const std::string& filename)
{
    _texID = Scene::GetTexture(filename);
}

void TexturedSphere::Display()
{
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

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _texID);
    glEnable(GL_COLOR_MATERIAL);

    DrawSphere();

    glBindTexture(GL_TEXTURE_2D, NULL);
    glDisable(GL_TEXTURE_2D);
    glPopAttrib();
    glPopMatrix();
}

void TexturedSphere::DrawSphere()
{
    SubDivide(_resolution, &_initV[_VERTEX3], &_initV[_VERTEX0], &_initV[_VERTEX4]);
    SubDivide(_resolution, &_initV[_VERTEX0], &_initV[_VERTEX1], &_initV[_VERTEX4]);
    SubDivide(_resolution, &_initV[_VERTEX1], &_initV[_VERTEX2], &_initV[_VERTEX4]);
    SubDivide(_resolution, &_initV[_VERTEX2], &_initV[_VERTEX3], &_initV[_VERTEX4]);
	
    SubDivide(_resolution, &_initV[_VERTEX0], &_initV[_VERTEX3], &_initV[_VERTEX5]);
    SubDivide(_resolution, &_initV[_VERTEX1], &_initV[_VERTEX0], &_initV[_VERTEX5]);
    SubDivide(_resolution, &_initV[_VERTEX2], &_initV[_VERTEX1], &_initV[_VERTEX5]);
    SubDivide(_resolution, &_initV[_VERTEX3], &_initV[_VERTEX2], &_initV[_VERTEX5]);
}

void TexturedSphere::SubDivide(int recurse_idx, float* a, float* b, float* c)
{
    if (recurse_idx > 0)
    {
        float ab[3] = { a[0] + b[0], a[1] + b[1], a[2] + b[2] };
        float bc[3] = { b[0] + c[0], b[1] + c[1], b[2] + c[2] };
        float ca[3] = { c[0] + a[0], c[1] + a[1], c[2] + a[2] };

        norm(ab);
        norm(bc);
        norm(ca);

        SubDivide(recurse_idx - 1, a, ab, ca);
        SubDivide(recurse_idx - 1, ab, b, bc);
        SubDivide(recurse_idx - 1, ca, bc, c);
        SubDivide(recurse_idx - 1, ca, ab, bc);
    } else {
        DrawFace(a, b, c);
    }
}

void TexturedSphere::DrawFace(float* a, float* b, float* c)
{
    float sa = 0.5f + atan2f(a[0], a[2]) / (2.0f * M_PI);
    float ta = 0.5f + asinf(a[1]) / M_PI;

    float sb = 0.5f + atan2f(b[0], b[2]) / (2.0f * M_PI);
    float tb = 0.5f + asinf(b[1]) / M_PI;
	
    float sc = 0.5f + atan2f(c[0], c[2]) / (2.0f * M_PI);
    float tc = 0.5f + asinf(c[1]) / M_PI;

    FixSeam(sa, sb, sc);
    glBegin(GL_TRIANGLES);
    glTexCoord2f(sa, ta);
    glNormal3fv(a); glVertex3fv(a);
    glTexCoord2f(sb, tb);
    glNormal3fv(b); glVertex3fv(b);
    glTexCoord2f(sc, tc);
    glNormal3fv(c); glVertex3fv(c);
    glEnd();
}

void TexturedSphere::FixSeam(float& a, float& b, float& c)
{
    if (b < 0.75f && a > 0.75f)
        b += 1.0f;
    else if (b > 0.75f && a < 0.75f)
        b -= 1.0f;

    if (c < 0.75f && a > 0.75f)
        c += 1.0f;
    else if (c > 0.75f && a < 0.75f)
        c -= 1.0f;
}


