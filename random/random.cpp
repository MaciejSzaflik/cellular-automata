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
#include "TreeGenerator.h"

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

	TreeGenerator treeGenerator;
	treeGenerator.initialize(w, h);

	for (int i = 0; i < 40; i++)
	{
		image = treeGenerator.getStep();
		resize(image, imS, Size(w * scale, h * scale), 0, 0, 0);
		imshow("display", imS);
		waitKey(33);
	}
	waitKey(0);

	return 0;
}

void lifeLike(int w, int h, int scale, Mat image, Mat imS)
{
	WeightedGenerations seed2 = WeightedGenerations();
	seed2.initialize(w, h, "34678/234/24");

	imshow("display", imS);

	waitKey(0);

	for (int i = 0; i < 200; i++)
	{
		image = seed2.getStep();
		resize(image, imS, Size(w * scale, h * scale), 0, 0, 0);
		imshow("display", imS);
		waitKey(33);
	}
	waitKey(0);
}

void ants(int w, int wQ, int h, int hQ, int itr)
{
	SimpleAnt ants[] = {
		AntFactory::GetHardAnt("LRLLLLRRRLLR",w / 2 + wQ, h / 2 - hQ, w, h, itr * 10),
		AntFactory::GetHardAnt("RL",w / 2 - wQ, h / 2 - hQ, w, h, itr),
		AntFactory::GetHardAnt("RLRLRLRLRLRR",w / 2 - wQ, h / 2 + hQ, w, h, itr),
		AntFactory::GetHardAnt("RRLLLRLRLRRL",w / 2 + wQ, h / 2 + hQ, w, h, itr)
	};
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
