#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdlib.h>    
#include <time.h> 
#include "SimpleAnt.h"
#include "AntFactory.h"

using namespace cv;
using namespace std;


int main()
{
	int w = 400, h = 400;
	int wH = w / 2, wQ = w / 4, hH = h / 2, hQ = h / 4;
	int scale = 2;
	Mat image = Mat::zeros(w, h, CV_8UC3);
	Mat imS = Mat::zeros(w*scale, h*scale, CV_8UC3);
	int dir = 0;
	int itr = 1000;

	srand(time(NULL));

	
	SimpleAnt ants[] = {
		AntFactory::GetHardAnt("LRLLLLRRRLLR",w / 2 + wQ, h / 2 - hQ, w, h, itr*10),
		AntFactory::GetHardAnt("RL",w / 2 - wQ, h / 2 - hQ, w, h, itr),
		AntFactory::GetHardAnt("RLRLRLRLRLRR",w / 2 - wQ, h / 2 + hQ, w, h, itr),
		AntFactory::GetHardAnt("RRLLLRLRLRRL",w / 2 + wQ, h / 2 + hQ, w, h, itr)
	};

	for (int i = 0; i < 10000; i++)
	{
		for (SimpleAnt& ant : ants)
		{
			ant.step(image);
		}

		if (scale > 0)
		{
			resize(image, imS, Size(w * scale, h * scale),0,0,0);
		}
		imshow("Display Window", imS);
		waitKey(33);
	}

	waitKey(0);


	return 0;
}
