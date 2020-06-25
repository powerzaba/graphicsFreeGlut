#pragma once

#include "DisplayableObject.h"
#include "Input.h"
#include "Materials.h"

#include <string>
#define _ROTV 18.0f
#define _VERTEX0 0
#define _VERTEX1 3
#define _VERTEX2 6
#define _VERTEX3 9
#define _VERTEX4 12
#define _VERTEX5 15
#define _MAX_RES 7

class TexturedSphere :
	public DisplayableObject
{
public:
	TexturedSphere();
	TexturedSphere(const std::string& filename, Material mat);
	~TexturedSphere() {}

	void Display();

	void SetTexture(const std::string& filename);

	inline void SetResolution(int r) { _resolution = r >= 0 ? (r > _MAX_RES ? _MAX_RES : r) : 0; }

protected:
	void DrawSphere();
	void SubDivide(int p_recurse, float* a, float* b, float* c);
	void DrawFace(float* a, float* b, float* c);
	void FixSeam(float& a, float& b, float& c);

	int _texID;
	int _resolution;
	float* _initV;

	float mRadius;
};
