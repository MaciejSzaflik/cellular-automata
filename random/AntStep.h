#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2\core\base.hpp>

class AntStep
{
public:
	bool dir;
	int BThreshold;
	int GThreshold;
	int RThreshold;
	virtual bool check(cv::Vec3b) = 0;
	virtual cv::Vec3b getColor() = 0;
};

class HardStep : public AntStep
{
public:
	HardStep(bool dir, int b, int g, int r, cv::Vec3b color);
	cv::Vec3b color;
	bool check(cv::Vec3b);
	cv::Vec3b getColor();
};

class RandomStep : public AntStep
{
public:
	RandomStep(bool dir, int b, int g, int r, int rand);
	bool check(cv::Vec3b color);
	cv::Vec3b getColor();
	int randFactor;
};



