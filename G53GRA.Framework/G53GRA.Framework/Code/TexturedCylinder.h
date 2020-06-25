#pragma once
#include "DisplayableObject.h"
#include "VectorMath.h"
#include "Materials.h"

class TexturedCylinder : 
	public DisplayableObject 
{
public:
	TexturedCylinder(float radius, float height, const std::string& filename, Material mat);
	TexturedCylinder(float radius, float height);

	void Display() override;
	void DrawCylinder();
	float getRadius() const;
	float getHeight() const;

private:
	float mRadius;
	float mHeight;

	bool isMat = false;;
	GLint texID;
};

