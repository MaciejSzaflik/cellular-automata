#pragma once
#include "SimpleAnt.h"
#include <string>

class AntFactory
{
public:
	static SimpleAnt GetHardAnt(std::string definition, int x, int y, int w, int h, int speed);
private:
	AntFactory() {}
};

