#pragma once
#include "Life_Like.h"

class Generations : public Life_Like
{
public:
	void initialize(int w, int h, std::string data);
	void createRectangle(int xCenter, int yCenter, int size, int value);
	void getArrayToFill(std::string data, bool* array);
	std::vector<std::string> splitDataString(std::string data);
	cv::Mat getStep();
protected:
	int generations;
	int colorValues[256];
	cv::Mat kernel;
};

