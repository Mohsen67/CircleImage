// CircleImage.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Circle.h"
#include "ImageFile.h"
#include <vector>

void Help()
{
	std::cout << "Please call one of the following methods\n" <<
		"start(name, width, height)\n" <<
		"circle(radius, centerX, centerY)\n" <<
		"exit\n";
}

int main()
{
	Help();
	auto imageFile = std::make_shared<ImageFile>();
	while (true)
	{
		std::string input;
		std::getline(std::cin, input);
		if (input == "exit")
			return 0;

		//find method name
		auto index = input.find("(");
		if (index == std::string::npos)
		{
			Help();
			continue;
		}
		auto method = input.substr(0, index);

		// find input params
		input = input.substr(index + 1, input.size());
	    index = input.find(")");
		if (index == std::string::npos || index != input.size() - 1)
		{
			continue;
			Help();
		}
		input = input.substr(0, input.size() - 1);
		std::vector<std::string> inputParams;
		while (index != std::string::npos)
		{
			index = input.find(",");
			inputParams.push_back(input.substr(0, index));
			input = input.substr(index + 2, input.size());
		}

		if (inputParams.size() != 3)
		{
			Help();
			continue;
		}
		 
		if (method == "start")
		{
			auto fileName = inputParams[0];
			auto width = std::stoi(inputParams[1]);
			auto height = std::stoi(inputParams[2]);
			imageFile->CreateFile(fileName, width, height);
			std::cout << "\""<<imageFile->Name << "\" Created!\n";
			continue;
		}
		else if (method == "circle")
		{
			if (imageFile->Name == "")
			{
				std::cout << "PLEASE CREATE AN IMAGE FIRST! \n";
				continue;
			}
			auto radius = std::stoi(inputParams[0]);
			auto centerX = std::stoi(inputParams[1]);
			auto centerY = std::stoi(inputParams[2]);
			auto circle = std::make_shared<Circle>(radius, centerX, centerY, imageFile->Width, imageFile->Height);
			
			imageFile->WriteData(circle->Data);
			std::cout << "circle wrote on the image! \n";
			continue;
		}

		Help();
	}
	
	return 0;
}
