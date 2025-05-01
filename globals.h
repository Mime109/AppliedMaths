#pragma once

#define POINT_LIGHT			0
#define SPOT_LIGHT			1
#define DIRECTIONAL_LIGHT	0

/////////////////////////////////////////////////////////
// a few globally defined structures 
/////////////////////////////////////////////////////////

struct sMeshInfo
{
	char name[32];
	int meshID;
	int shaderID;
};

struct sVec2f
{
	float x, y;
};

struct sVec3f
{
	float x, y, z;
};

struct sRGB
{
	float r, g, b;
};

struct sShaderDetails
{
	char filename[256];
	unsigned long types[6];
};

