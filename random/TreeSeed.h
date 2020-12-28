#pragma once
#include <opencv2/core/types.hpp>

class TreeSeed
{
public:
	cv::Point2i start;

	float angle;
	float angleRandom;

	float length;
	float lengthRandom;

	int childrenMax;
	int childrenMin;

	int fuel;

	TreeSeed();
	TreeSeed(const TreeSeed& seed2);
	std::vector<TreeSeed> getChildren();

private:
	int getRandomBetween(int min, int max);
	float getRandomBetweenF(float min, float max);
	cv::Point2i getPoint(float angle, float len, cv::Point2i start);
};

