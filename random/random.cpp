#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdlib.h>    
#include <time.h> 
#include "SimpleAnt.h"
#include "AntFactory.h"
#include "Rule.h"
#include "Seed.h"

using namespace cv;
using namespace std;


int main()
{
	int w = 200, h = 200;
	int wH = w / 2, wQ = w / 4, hH = h / 2, hQ = h / 4;
	int scale = 3;
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

	Seed seed = Seed();
	seed.initialize(w, h);
	imshow("display", imS);
	waitKey(0);

	for (int i = 0; i < 500; i++)
	{
		image = seed.getStep();
		resize(image, imS, Size(w * scale, h * scale), 0, 0, 0);

		imshow("display", imS);
		waitKey(33);
	}

	waitKey(0);


	return 0;
}

void createAndWriteRules()
{
	int w = 256, h = 256;
	int scale = 2;
	Mat image = Mat::zeros(w, h, CV_8UC3);
	Mat imS = Mat::zeros(w * scale, h * scale, CV_8UC3);
	for (int i = 0; i < 256; i++)
	{
		image = Mat::zeros(w, h, CV_8UC3);
		imS = Mat::zeros(w * scale, h * scale, CV_8UC3);
		Rule rule = Rule(i);
		rule.initializeRandom(image);

		for (int i = 0; i < h; i++)
		{
			rule.step(image);
		}

		resize(image, imS, Size(w * scale, h * scale), 0, 0, 0);
		imwrite("rule_" + rule.rule + "_random.png", imS);

		cout << rule.rule << endl;
	}
}
