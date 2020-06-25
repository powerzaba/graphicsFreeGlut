#pragma once

//This is the base material class used in this project, subsequent materials can be seen below
class Material
{
public:
	Material() {
		matAmbient[0] = 0.f;
		matAmbient[1] = 0.f;
		matAmbient[2] = 0.f;
		matAmbient[3] = 0.f;
		
		matDiffuse[0] = 0.f;
		matDiffuse[1] = 0.f;
		matDiffuse[2] = 0.f;
		matDiffuse[3] = 0.f;

		matSpecular[0] = 0.f;
		matSpecular[1] = 0.f;
		matSpecular[2] = 0.f;
		matSpecular[3] = 0.f;

		matShininess = 0; 
	}	
	
	~Material() {}
	
	float* GetAmbient() {
		return matAmbient;
	}
	float* GetDiffuse() {
		return matDiffuse;
	}
	float* GetSpecular() {
		return matSpecular;
	}
	int GetShininess() {
		return matShininess;
	}
	
protected:	
	float matAmbient[4], matDiffuse[4], matSpecular[4];
	int matShininess;
};

//This is the marble material, used mainly for the statue and some parts of the sword
class Marble : public Material
{
public:
	Marble() {
		matAmbient[0] = 0.8f;
		matAmbient[1] = 0.8f;
		matAmbient[2] = 0.8f;
		matAmbient[3] = 1.f;
		
		matDiffuse[0] = 0.4f;
		matDiffuse[1] = 0.4f;
		matDiffuse[2] = 0.4f;
		matDiffuse[3] = 1.f;

		matSpecular[0] = 0.2f;
		matSpecular[1] = 0.2f;
		matSpecular[2] = 0.2f;
		matSpecular[3] = 1.f;

		matShininess = 50;
	}
};

//This is the sand material, used for the procedural terrain
class Sand : public Material {
public:
	Sand() {
		matAmbient[0] = 0.8f;
		matAmbient[1] = 0.7f;
		matAmbient[2] = 0.6f;
		matAmbient[3] = 1.f;

		matDiffuse[0] = 0.7f;
		matDiffuse[1] = 0.6f;
		matDiffuse[2] = 0.5f;
		matDiffuse[3] = 1.f;

		matSpecular[0] = 0.4f;
		matSpecular[1] = 0.4f;
		matSpecular[2] = 0.4f;
		matSpecular[3] = 1.f;

		matShininess = 70;
	}
};

//This a shiny material uses for the gem that is found in the sword
class Gem : public Material {
public:
	Gem() {
		matAmbient[0] = 0.05f;
		matAmbient[1] = 0.75f;
		matAmbient[2] = 0.90f;
		matAmbient[3] = 1.f;

		matDiffuse[0] = 0.05f;
		matDiffuse[1] = 0.60f;
		matDiffuse[2] = 0.80f;
		matDiffuse[3] = 1.f;

		matSpecular[0] = 0.9f;
		matSpecular[1] = 0.9f;
		matSpecular[2] = 0.9f;
		matSpecular[3] = 1.f;

		matShininess = 110;
	}
};

//This is a reflective metal-like material that is used for the sword and the monument rings
class Metal : public Material {
public:
	Metal() {
		matAmbient[0] = 0.75f;
		matAmbient[1] = 0.75f;
		matAmbient[2] = 0.75f;
		matAmbient[3] = 1.f;

		matDiffuse[0] = 0.7f;
		matDiffuse[1] = 0.7f;
		matDiffuse[2] = 0.7f;
		matDiffuse[3] = 1.f;

		matSpecular[0] = 0.8f;
		matSpecular[1] = 0.8f;
		matSpecular[2] = 0.8f;
		matSpecular[3] = 1.f;

		matShininess = 90;
	}
};

//A gold material used for some parts of the sword
class Gold : public Material {
public:
	Gold() {
		matAmbient[0] = 0.8f;
		matAmbient[1] = 0.5f;
		matAmbient[2] = 0.15f;
		matAmbient[3] = 1.f;

		matDiffuse[0] = 0.7f;
		matDiffuse[1] = 0.5f;
		matDiffuse[2] = 0.15f;
		matDiffuse[3] = 1.f;

		matSpecular[0] = 0.8f;
		matSpecular[1] = 0.8f;
		matSpecular[2] = 0.8f;
		matSpecular[3] = 1.f;

		matShininess = 110;
	}
};