#include "RandomSurface.h"
#include "ImprovedNoise.h"

RandomSurface::RandomSurface(float length, const std::string& filename)
	: sideLength(length) {

	texID = Scene::GetTexture(filename);

	//This sets up the values used for the perlin noise
	double frequency = 6;	
	std::int32_t octaves = 16;	
	std::uint32_t seed = rand();
	const siv::PerlinNoise pok(seed);
	const double fx = 160 / frequency;
	const double fy = 160 / frequency;

	//Creation of the height and vertex map
	for (int x = 0; x < rows; x++) {
		for (int y = 0; y < columns; y++) {
			float ampl = 30;			
			heightMap[x][y] = pok.accumulatedOctaveNoise2D(x / fx, y / fy, octaves) * ampl;
			vertexMap[x][y][0] = y * sideLength;
			vertexMap[x][y][1] = - x * sideLength;
			vertexMap[x][y][2] = heightMap[x][y];
		}
	}		
}

void RandomSurface::Display() {
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);
	glRotatef(rotation[0], 1.f, 0.f, 0.f);
	glRotatef(rotation[1], 0.f, 1.f, 0.f);
	glRotatef(rotation[2], 0.f, 0.f, 1.f);

	glColor4f(1.0, 1.0, 1.0, 0.0);
	DrawSurface();

	glPopAttrib();
	glPopMatrix();
}

//This function draws the surface of the procedural terrain
void RandomSurface::DrawSurface() {
	glEnable(GL_TEXTURE_2D);	
	glBindTexture(GL_TEXTURE_2D, texID);
	glDisable(GL_BLEND);
	glDisable(GL_COLOR_MATERIAL);
	
	float step = 1.0 / (TERRAIN_ROWS - 1.0);
	
	for (int y = 0; y < rows - 1; y++) {
		glBegin(GL_QUAD_STRIP);
		for (int x = 0; x < columns; x++) {
			float* v1 = vertexMap[y][x];
			float* v2 = vertexMap[y + 1][x];

			float a = 1 - (step * y);
			float b = x * step;

			glTexCoord2f(b, a);			
			glVertex3f(v1[0], v1[1], heightMap[y][x]);

			glTexCoord2f(b, a - step);
			glVertex3f(v2[0], v2[1], heightMap[y + 1][x]);
		}		
		glEnd();
	}

	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);
}


