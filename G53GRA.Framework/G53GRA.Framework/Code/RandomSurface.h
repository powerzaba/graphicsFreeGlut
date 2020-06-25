#pragma once
#include "DisplayableObject.h"
#include <string>

#define TERRAIN_ROWS 160
#define TERRAIN_COLUMNS 160

class RandomSurface :
	public DisplayableObject
{
public:
	RandomSurface(float sideLength, const std::string& filename);
	~RandomSurface() {};

	void Display() override;

	void DrawSurface();

private:
	int rows = TERRAIN_ROWS;
	int columns = TERRAIN_COLUMNS;
	float sideLength;
	float heightMap[TERRAIN_ROWS][TERRAIN_COLUMNS];
	float vertexMap[TERRAIN_ROWS][TERRAIN_COLUMNS][3];

	int texID;
};

