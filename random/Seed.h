#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2\core\base.hpp>

class Seed
{
public:
	cv::Mat data;
	void initialize(int w, int h);
	cv::Mat getStep();
private:
	int getRow(int a);
	int getCol(int a);
};

