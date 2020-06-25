#pragma once
#include <cmath>

/**
* Class to be subclassed alongside DisplayableObject for all animated objects to be displayed in a Scene
* <p>
* Contains {@link #Update} method that must be overloaded. {@link #Update(float deltaTime)} is called from {@link Scene}.
*
* @author wil
*/
class Animation
{
public:
	Animation(void){}
	virtual ~Animation(void){}
	/**
	* Called each frame to update. Must be defined!
	* <p>
	* Use this to update animation sequence.
	* @param deltaTime change in time since previous call
	*/
	virtual void Update(const double& deltaTime) = 0;

	float Lerp(float startVal, float endVal, float t) {
		return (startVal + (endVal - startVal) * t);
	}

	float EaseIn(float t, int exp) {
		return pow(t, exp);
	}

	float Flip(float t) {
		return 1 - t;
	}

	float EaseOut(float t, int exp) {
		return Flip(EaseIn(Flip(t), exp));
	}

	float* LerpColor(float color[3], float color2[3], float t) {
		float lerpedColor[4];
		lerpedColor[0] = Lerp(color[0], color2[0], t);
		lerpedColor[1] = Lerp(color[1], color2[1], t);
		lerpedColor[2] = Lerp(color[2], color2[2], t);
		lerpedColor[3] = 0.f;

		return lerpedColor;
	}
};