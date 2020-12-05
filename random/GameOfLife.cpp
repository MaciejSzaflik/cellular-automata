#include "GameOfLife.h"

#define off 220
#define on 30

void GameOfLife::initialize(int w, int h, std::string data)
{
	this->data = cv::Mat::zeros(w, h, CV_8U);

	this->data.forEach<uchar>(
		[](uchar& pixel, const int* position) -> void
		{
			pixel = rand() % 10 + 1 > 6 ? on : off;
		}
	);

}

cv::Mat GameOfLife::getStep()
{
	cv::Mat clone = data.clone();

	for (int i = 0; i < clone.cols; i++)
	{
		for (int j = 0; j < clone.rows; j++)
		{
			int a = 0;
			int ic = i * clone.cols;

			bool alive = clone.data[ic + j] == on;

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

			if (!alive && a == 3)
			{
				data.data[ic + j] = on;
			}
			else if (alive && (a == 3 || a == 2))
			{
				continue;
			}
			else if (alive)
			{
				data.data[ic + j] = off;
			}
		}
	}

	cv::Mat display;
	data.convertTo(display, CV_8UC3);

	return display;
}