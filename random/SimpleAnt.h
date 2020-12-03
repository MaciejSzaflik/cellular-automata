#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2\core\base.hpp>
#include "AntStep.h"

class SimpleAnt
{
public:
	SimpleAnt(int x,int y, int w, int h, int speed);
	std::vector<AntStep*> steps;
	int mod(int a, int b);
	void step(cv::Mat image);
private:
	int x, y, w, h, dir, speed, i;
	void wrap();
	void changePosition();
};

