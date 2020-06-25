#pragma once

#include "DisplayableObject.h"
#include "Animation.h"
#include "VectorMath.h"
#include <string>

#define HEIGHT_RESOLUTION 10
#define WIDTH_RESOLUTION 50

class SphereCoating :
	public DisplayableObject
{

public:
	SphereCoating(float widthAngle, float heightAngle, float radius,
		float thickness, Material mat);
	
	~SphereCoating() {};

	void Display() override;
	void SetColor(GLfloat newColor[3]);

private:
	void DrawCoating();
	void DrawFront();
	void DrawSurface(bool isFront);
	void DrawSide(bool isLeft);
	void DrawClosing(bool isTop);
	void DrawLeftSide();
	void DrawRightSide();
	void DrawTop();
	void DrawBottom();
	void DrawBack();	

	//These variables are used to determine the shape of the coating
	GLfloat mWidthAngle, mHeightAngle, mRadius, mThickness;
	GLfloat widthStep;
	GLfloat heightStep;
	GLfloat mColor[3];
};
