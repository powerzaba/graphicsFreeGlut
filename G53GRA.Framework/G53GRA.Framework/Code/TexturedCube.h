#pragma once

#include "DisplayableObject.h"
#include "Materials.h"
#include <string>

class TexturedCube :
	public DisplayableObject
{
public:
	TexturedCube(const std::string& filename, Material mat);
	TexturedCube(Material mat);
	~TexturedCube() {}

	void Display() override;

private:
	void DrawCube();
	
	bool texture;
	GLint texID;
};

