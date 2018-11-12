#include "pch.h"
#include "ImageFile.h"

#include <direct.h>
#include <fstream>
#include <iomanip>
#include<iostream>
#include <sstream> 
#include <cstdio>


const std::string EXTENSION = ".img";

std::string GetCurrentWorkingDir(void) {
	char buff[FILENAME_MAX];
	_getcwd(buff, FILENAME_MAX);
	std::string currentWorkingDir(buff);
	return currentWorkingDir + "\\";
}

ImageFile::ImageFile(): Width(0), Height(0), Name("")
{
}


void ImageFile::CreateFile(std::string& fileName, int width, int height)
{
	Width = width;
	Height = height;
	if(Width <= 0 || Height <= 0 || Width >= pow(CHAR_MAX, 4) || Width >= pow(CHAR_MAX, 4))
		return;

	auto i = 1;
	auto currentFileName = fileName;
	while(FileExists(currentFileName))
	{
		std::ostringstream postfix;
		postfix << std::setw(3) << std::setfill('0') << i;
		currentFileName = fileName + postfix.str();
		i++;
	}

	
	std::ofstream fileStream;
	Name= GetCurrentWorkingDir() + currentFileName + EXTENSION;
	fileStream.open(Name, std::ios::binary);
	WriteImageDimOnFile(std::move(fileStream));
	fileStream.close();
}

void ImageFile::WriteImageDimOnFile(std::ofstream fileStream)
{
	auto width = static_cast<unsigned char*>(static_cast<void*>(&Width));
	auto height = static_cast<unsigned char*>(static_cast<void*>(&Height));
	fileStream.write(reinterpret_cast<char*>(width), 4 * sizeof(char));
	fileStream.write(reinterpret_cast<char*>(height), 4 * sizeof(char));
}

void ImageFile::WriteData(std::vector<std::vector<unsigned char>> data)
{
	std::ofstream fileStream;
	fileStream.open(Name, std::ofstream::app|std::ios::binary);
	for(auto i = 0; i < Width; i++)
	{
		for(auto j = 0; j < Height; j++)
			fileStream.write(reinterpret_cast<char*>(&data[i][j]), sizeof(char));
	}
	fileStream.close();
}

bool ImageFile::FileExists(const std::string &fileName)
{
	auto imageFileName = GetCurrentWorkingDir() + fileName + EXTENSION;
	std::ifstream ifFile(imageFileName.c_str());
	return static_cast<bool>(ifFile);
}


ImageFile::~ImageFile()
= default;
