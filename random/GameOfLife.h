#pragma once
#include "Seed.h"
class GameOfLife : public Seed
{
public:
	void initialize(int w, int h);
	cv::Mat getStep();
};

