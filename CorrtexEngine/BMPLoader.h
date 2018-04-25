#pragma once
#include "glew.h"

//helper class to load BMP files
class BMPLoader
{
public:
	BMPLoader();
	~BMPLoader();
	GLuint LoadBMP(const char *filePath);
};

