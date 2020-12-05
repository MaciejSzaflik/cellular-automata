#include "BriansBrain.h"
#include <opencv2/core/core.hpp>
#include <opencv2\core\base.hpp>
#include <bitset>

#define off 220
#define on 30
#define dying 150

void BriansBrain::initialize(int w, int h)
{
	this->data = cv::Mat::zeros(w, h, CV_8U);

	this->data.forEach<uchar>(
		[](uchar& pixel, const int* position) -> void
		{
			pixel = rand()%10 + 1 > 7 ? on : off;
		}
	);

}

cv::Mat BriansBrain::getStep()
{
	cv::Mat clone = data.clone();

	for (int i = 0; i < clone.cols; i++)
	{
		for (int j = 0; j < clone.rows; j++)
		{
			int a = 0;
			int ic = i * clone.cols;

			if (clone.data[ic + j] == dying)
			{
				data.data[ic + j] = off;
				continue;
			}

			if (clone.data[ic + j] == on)
			{
				data.data[ic + j] = dying;
				continue;
			}

			int im = getRow(i - 1) * clone.cols;
			int ip = getRow(i + 1) * clone.cols;
			int jm = getCol(j - 1);
			int jp = getCol(j + 1);

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
		}
	}

	cv::Mat display;
	data.convertTo(display, CV_8UC3);

	return display;
}