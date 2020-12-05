
#include "Life_Like.h"

#define off 220
#define on 30

void Life_Like::initialize(int w, int h, std::string data)
{
	this->data = cv::Mat::zeros(w, h, CV_8U);

	this->data.forEach<uchar>(
		[](uchar& pixel, const int* position) -> void
		{
			pixel = rand() % 10 + 1 > 20 ? on : off;
		}
	);

	cv::Mat pRoi = this->data(cv::Rect(w/2, h/2, 6, 6));
	pRoi.setTo(on);
	pRoi = this->data(cv::Rect(w / 2, h / 2, 2, 2));
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
				this->b.set(value);
				break;
			case 1:
				this->s.set(value);
				break;
			}
		}
	}
}

cv::Mat Life_Like::getStep()
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

			if (!alive && b[a])
			{
				data.data[ic + j] = on;
			}
			else if (alive && s[a])
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
