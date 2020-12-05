#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2\core\base.hpp>

class Seed
{
public:
	cv::Mat data;
	virtual void initialize(int w, int h);
	virtual cv::Mat getStep();
	cv::Mat getTexture();
protected:
	int getRow(int a);
	int getCol(int a);
};

