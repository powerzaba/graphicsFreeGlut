#pragma once
#include "DisplayableObject.h"
#include "Camera.h"

class SkyBox : public DisplayableObject {
public:
    SkyBox();
    SkyBox(Camera* camera);
    ~SkyBox() {};

    void Display() override;

private:
    void DrawStage();
    void SetTexture();
	
    GLint texID[6];
	//The camera is needed to determine its position so that the skybox can always be centered
	//based on it
    Camera* mCamera;

    bool followCamera;
};
