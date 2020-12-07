#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdlib.h>    
#include <time.h> 
#include "Ants/SimpleAnt.h"
#include "Ants/AntFactory.h"
#include "Rule/Rule.h"
#include "LifeLike/Seed.h"
#include "LifeLike/BriansBrain.h"
#include "LifeLike/GameOfLife.h"
#include "LifeLike/Life_Like.h"
#include "LifeLike/Generations.h"
#include "LifeLike/WeightedGenerations.h"

using namespace cv;
using namespace std;


int main()
{
	int w = 256, h = 256;
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

	WeightedGenerations seed = WeightedGenerations();
	seed.initialize(w, h, "34678/234/24");

	Generations generations = Generations();
	generations.initialize(w, h, "34678/234/24");

	image = seed.getTexture();
	resize(image, imS, Size(w * scale, h * scale), 0, 0, 0);

	imshow("display", imS);


	waitKey(0);

	for (int i = 0; i < 100; i++)
	{
		image = seed.getStep();
		resize(image, imS, Size(w * scale, h * scale), 0, 0, 0);

		imshow("display", imS);

		waitKey(10);
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
