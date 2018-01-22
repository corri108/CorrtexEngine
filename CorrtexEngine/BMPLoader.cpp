#include "stdafx.h"
#include "BMPLoader.h"


BMPLoader::BMPLoader()
{

}

BMPLoader::~BMPLoader()
{

}

GLuint BMPLoader::LoadBMP(const char *filePath)
{
	//declare data
	unsigned int headerSize = 54;
	unsigned char header[54];
	unsigned int dataSection;
	unsigned int width, height;
	unsigned int imageSize;
	unsigned char* pixelData;

	//open file
	FILE* file = fopen(filePath, "rb");
	if (!file)
	{
		printf("Error opening file with filepath: %s\n", filePath);
		return 0;
	}

	//check for .BMP header
	if (fread(header, 1, headerSize, file) != headerSize)
	{
		printf("File has an incorrect BMP format: %s\n", filePath);
		return false;
	}

	//double check BMP header:
	if (header[0] != 'B' || header[1] != 'M')
	{
		printf("File has an incorrect BMP format: %s\n", filePath);
		return false;
	}

	//get correct amounts for each property using the header we just loaded
	dataSection = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	//if information is missing (sometimes BMP files are missing info), lets make it up
	if (imageSize == 0)
	{
		imageSize = width * height * 3;//each location has R, G, B, and A
	}
	if (dataSection == 0)
	{
		dataSection = headerSize;
	}

	//now we are ready to actually read!
	pixelData = new unsigned char[imageSize];
	fread(pixelData, 1, imageSize, file);
	fclose(file);

	GLuint texID;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixelData);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	return texID;
}