#pragma once
#include "Seed.h"

class Life_Like : public Seed
{
public:
	void initialize(int w, int h, std::string data);
	cv::Mat getStep();
protected:
	bool birthCondition[9];
	bool survivalCondition[9];
};
