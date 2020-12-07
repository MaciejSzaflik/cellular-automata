#include "GameOfLife.h"

#define off 220
#define on 30

void GameOfLife::initialize(int w, int h, std::string data)
{
	this->universeData = cv::Mat::zeros(w, h, CV_8U);

	this->universeData.forEach<uchar>(
		[](uchar& pixel, const int* position) -> void
		{
			pixel = rand() % 10 + 1 > 6 ? on : off;
		}
	);

}

cv::Mat GameOfLife::getStep()
{
	cv::Mat clone = universeData.clone();

	for (int i = 0; i < clone.cols; i++)
	{
		int ic = i * clone.cols;
		int im = getRow(i - 1) * clone.cols;
		int ip = getRow(i + 1) * clone.cols;

		for (int j = 0; j < clone.rows; j++)
		{
			int a = 0;

			bool alive = clone.data[ic + j] == on;

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

			if (!alive && a == 3)
			{
				universeData.data[ic + j] = on;
			}
			else if (alive && (a == 3 || a == 2))
			{
				continue;
			}
			else if (alive)
			{
				universeData.data[ic + j] = off;
			}
		}
	}

	cv::Mat display;
	universeData.convertTo(display, CV_8UC3);

	return display;
}