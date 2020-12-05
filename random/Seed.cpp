#include "Seed.h"
#include <opencv2/core/core.hpp>
#include <opencv2\core\base.hpp>
#include <bitset>

#define zero 220
#define one 30

void Seed::initialize(int w, int h)
{
	this->data = cv::Mat::zeros(w, h, CV_8U);


	this->data.forEach<uchar>(
		[](uchar& pixel, const int* position) -> void
		{
			pixel = zero;
		}
	);

	cv::Mat pRoi = this->data(cv::Rect(w - w / 4 ,h -  h / 4, 24, 24));
	pRoi.setTo(one);

	pRoi = this->data(cv::Rect(w - w / 4, h - h / 4, 22, 22));
	pRoi.setTo(zero);

}

inline int Seed::getRow(int a)
{
	if (a < 0)
		return data.rows - 1;
	else if (a > data.rows)
		return 0;
	else
		return a;
}

inline int Seed::getCol(int a)
{
	if (a < 0)
		return data.cols - 1;
	else if (a > data.cols)
		return 0;
	else
		return a;
}

cv::Mat Seed::getStep()
{
	cv::Mat clone = data.clone();

	for (int i = 0; i < clone.cols; i++)
	{
		for (int j = 0; j < clone.rows; j++)
		{
			int a = 0;
			int ic = i * clone.cols;
			int im = getRow(i - 1) * clone.cols;
			int ip = getRow(i + 1) * clone.cols;
			int jm = getCol(j - 1);
			int jp = getCol(j + 1);

			if (clone.data[im + jp] == one)
				++a;
			if (clone.data[ic + jp] == one)
				++a;
			if (clone.data[ip + jp] == one)
				++a;

			if (clone.data[im + j] == one)
				++a;
			if (clone.data[ip + j] == one)
				++a;

			if (clone.data[im + jm] == one)
				++a;
			if (clone.data[ic + jm] == one)
				++a;
			if (clone.data[ip + jm] == one)
				++a;
			
			if (a == 2)
				data.data[ic + j] = one;
			else
				data.data[ic + j] = zero;

		}
	}

	cv::Mat display;
	data.convertTo(display, CV_8UC3);

	return display;
}
