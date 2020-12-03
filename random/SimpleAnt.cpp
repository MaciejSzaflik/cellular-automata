#include "SimpleAnt.h"
#include <iostream>


SimpleAnt::SimpleAnt(int x, int y, int w, int h, int speed)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->speed = speed;
	this->dir = 0;
	this->i = 0;
}

int SimpleAnt::mod(int a, int b)
{
	int r = a % b;
	return r < 0 ? r + b : r;
}

void SimpleAnt::wrap()
{
	if (y < 0)
		y = h - 1;
	if (x < 0)
		x = w - 1;
	if (x >= w)
		x = 0;
	if (y >= h)
		y = 0;

}

void SimpleAnt::changePosition()
{
	switch (dir)
	{
	case 0:
		x += 1;
		break;
	case 1:
		y -= 1;
		break;
	case 2:
		x -= 1;
		break;
	case 3:
		y += 1;
		break;
	}
}

void SimpleAnt::step(cv::Mat image)
{
	for (int i = 0;i<speed;i++)
	{
		cv::Vec3b& color = image.at<cv::Vec3b>(x, y);
		for (AntStep* step : steps)
		{
			if (step->check(color))
			{
				if(step->dir)
					dir = this->mod(dir + 1, 4);
				else
					dir = this->mod(dir - 1, 4);

				color = step->getColor();
				break;
			}
		}

		image.at<cv::Vec3b>(x, y) = color;

		changePosition();

		wrap();
	}
}