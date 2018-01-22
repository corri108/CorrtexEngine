#pragma once
#include "glew.h"

class BMPLoader
{
public:
	BMPLoader();
	~BMPLoader();
	GLuint LoadBMP(const char *filePath);
};

