#include "Rule.h"
#include <bitset> 


Rule::Rule(int rule)
{
	iter = 0;
	this->rule = std::bitset<8>(rule).to_string();
}


void Rule::initializeRandom(cv::Mat image)
{
	cv::Vec3b& cell = image.at<cv::Vec3b>(image.rows/2, image.cols/2);
	iter = 1;
	image.at<cv::Vec3b>(image.rows / 2, image.cols / 2) = cell;
	
	for (int j = 0; j < image.cols; j++)
	{
		cv::Vec3b& cell = image.at<cv::Vec3b>(0, j);
		cell[0] = rand() % 2 == 1 ? 30 : 220;
		image.at<cv::Vec3b>(0, j) = cell;
	}
}

void Rule::initializeSingle(cv::Mat image)
{
	cv::Vec3b& cell = image.at<cv::Vec3b>(0, image.cols / 2);
	cell[0] = 30;
	image.at<cv::Vec3b>(0, image.cols / 2) = cell;
	iter = 1;
}

void Rule::step(cv::Mat image)
{
	cv::Mat clone = image.clone();

	for (int j = 0; j < image.cols; j++)
	{
		cv::Vec3b& cell = image.at<cv::Vec3b>(iter, j);
		int iIndex = decWrap(iter, image.rows - 1);
		cv::Vec3b& a1 = clone.at<cv::Vec3b>(iIndex, decWrap(j, image.cols - 1));
		cv::Vec3b& a2 = clone.at<cv::Vec3b>(iIndex, j);
		cv::Vec3b& a3 = clone.at<cv::Vec3b>(iIndex, incWrap(j, image.cols - 1));

		int color = decide(a1[0] == 30, a2[0] == 30, a3[0] == 30) ? 30 : 220;
		
		cell[0] = color;
		cell[1] = color;
		cell[2] = color;
		image.at<cv::Vec3b>(iter, j) = cell;
	}

	iter = incWrap(iter, image.rows - 1);
}

int Rule::decWrap(int val, int replace)
{
	return val - 1 < 0 ? replace : val - 1;
}

int Rule::incWrap(int val, int max)
{
	return val + 1 > max ? 0 : val + 1;
}

bool Rule::decide(bool a, bool b, bool c)
{
	std::bitset<3> set;
	set[0] = a;
	set[1] = b;
	set[2] = c;
	int value = (int)set.to_ulong();
	return rule[value] == '1';
}
