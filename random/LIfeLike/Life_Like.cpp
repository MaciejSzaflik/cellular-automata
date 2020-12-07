
#include "Life_Like.h"

#define off 220
#define on 30

void Life_Like::initialize(int w, int h, std::string data)
{
	this->universeData = cv::Mat::zeros(w, h, CV_8U);

	this->universeData.forEach<uchar>(
		[](uchar& pixel, const int* position) -> void
		{
			pixel = rand() % 10 + 1 > 8? on : off;
		}
	);

	cv::Mat pRoi = this->universeData(cv::Rect(w/2 - 150, h/2 - 150, 300, 300));
	pRoi.setTo(on);
	pRoi = this->universeData(cv::Rect(w / 2 - 75, h / 2 - 75, 150, 150));
	pRoi.setTo(off);

	int currentSet = 0;

	for (int i = 0; i < data.length(); i++)
	{
		int value = (int)data[i] -'0';
		if (value > 8 || value < 0)
		{
			currentSet++;
		}
		else
		{
			switch (currentSet)
			{
			case 0:
				this->birthCondition[value] = true;
				break;
			case 1:
				this->survivalCondition[value] = true;
				break;
			}
		}
	}
}

cv::Mat Life_Like::getStep()
{
	cv::Mat clone = universeData.clone();
	
	for (int i = 0; i < clone.cols; i++)
	{
		int im = getRow(i - 1) * clone.cols;
		int ip = getRow(i + 1) * clone.cols;
		int ic = i * clone.cols;

		for (int j = 0; j < clone.rows; j++)
		{
			int a = 0;
			
			bool alive = clone.data[ic + j] == on;
			
			j - 1 < 0 ? clone.cols - 1 : j - 1;

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

			if (!alive && birthCondition[a])
			{
				universeData.data[ic + j] = on;
			}
			else if (alive && survivalCondition[a])
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
