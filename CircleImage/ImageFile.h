#pragma once
#include <string>
#include <vector>

class ImageFile
{
public:
	// size of the image
	int Width;
	int Height;
	std::string Name;

	ImageFile();
	void WriteImageDimOnFile(std::ofstream fileStream);
	// create a  file and write size of the image on it
	void CreateFile(std::string& fieName, int width, int height);
	void WriteData(std::vector<std::vector<unsigned char>> data);
	~ImageFile();
private:
	// check if a file with the same name is already exist
	bool FileExists(const std::string &fileName);
};

