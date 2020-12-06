#include "Seed.h"
#include <opencv2/core/core.hpp>
#include <opencv2\core\base.hpp>
#include <bitset>
#include <string>

#define off 220
#define on 30

void Seed::initialize(int w, int h, std::string data)
{
	this->data = cv::Mat::zeros(w, h, CV_8U);

	this->data.forEach<uchar>(
		[](uchar& pixel, const int* position) -> void
		{
			pixel = off;
		}
	);

	cv::Mat pRoi = this->data(cv::Rect(w - w / 4 ,h -  h / 4, 24, 24));
	pRoi.setTo(on);

	pRoi = this->data(cv::Rect(w - w / 4, h - h / 4, 22, 22));
	pRoi.setTo(off);

}

int Seed::getRow(int a)
{
	if (a < 0)
		return data.rows - 1;
	else if (a > data.rows)
		return 0;
	else
		return a;
}

int Seed::getCol(int a)
{
	if (a < 0)
		return data.cols - 1;
	else if (a > data.cols)
		return 0;
	else
		return a;
}

cv::Mat Seed::getTexture()
{
	cv::Mat display;
	data.convertTo(display, CV_8UC3);

	return display;
}

cv::Mat Seed::getStep()
{
	cv::Mat clone = data.clone();

	for (int i = 0; i < clone.cols; i++)
	{
		int im = getRow(i - 1) * clone.cols;
		int ip = getRow(i + 1) * clone.cols;
		int ic = i * clone.cols;

		for (int j = 0; j < clone.rows; j++)
		{
			int a = 0;
			
			int jm = j - 1 < 0 ? clone.cols - 1 : j - 1;
			int jp = j + 1 > clone.cols - 1 ? 0 : j + 1;

			if (clone.data[im + jp] == on)
				++a;
			if (clone.data[ic + jp] == on)
				++a;
			if (clone.data[ip + jp] == on)
				++a;

			if (clone.data[im + j] == on)
				++a;
			if (clone.data[ip + j] == on)
				++a;

			if (clone.data[im + jm] == on)
				++a;
			if (clone.data[ic + jm] == on)
				++a;
			if (clone.data[ip + jm] == on)
				++a;
			
			if (a == 2)
				data.data[ic + j] = on;
			else
				data.data[ic + j] = off;

		}
	}

	cv::Mat display;
	data.convertTo(display, CV_8UC3);

	return display;
}
