
#include "Generations.h"
#include <string>
#include <opencv2\imgproc.hpp>

void Generations::initialize(int w, int h, std::string data)
{
	this->universeData = cv::Mat::zeros(w, h, CV_8U);

	int currentSet = 0;

	std::vector<std::string> splited = splitDataString(data);
	getArrayToFill(splited[0], birthCondition);
	getArrayToFill(splited[1], survivalCondition);
	generations = std::stoi(splited[2]);
	
	int step = MAX(1, 255 / generations);

	colorValues[0] = 255;
	int last = 0;

	for (int i = 1; i < generations; i++)
	{
		colorValues[255 - (step * (i - 1))] = last = 255 - (step * i);
	}
	colorValues[last] = 0;

	step = w / 4;
	int halfstep = step/2;
	for (int i = 0; i < w; i += step)
	{
		for (int j = 0; j < w; j += step)
		{
			createRectangle(i + halfstep, j+ halfstep, 10, colorValues[0]);
			createRectangle(i + halfstep, j+ halfstep, 5, colorValues[last]);
			createRectangle(i + halfstep, j+ halfstep, 2, colorValues[0]);
		}
	}

	/*this->data.forEach<uchar>(
		[this, last](uchar& pixel, const int* position) -> void
		{
			pixel = rand() % 10 + 1 > 6 ? colorValues[0] : colorValues[last];
		}
	);*/

	//cv::GaussianBlur(this->data, this->data, cv::Size(7, 7), 0);
	//cv::threshold(this->data, this->data, 128, 255, cv::THRESH_BINARY);
}

void Generations::createRectangle(int xCenter, int yCenter, int size, int value)
{
	cv::Mat pRoi = this->universeData(cv::Rect(xCenter - size/2, yCenter - size/2, size, size));
	pRoi.setTo(value);
}

void Generations::getArrayToFill(std::string data, bool* array)
{
	for (int i = 0; i < data.length(); i++)
	{
		int value = (int)data[i] - '0';
		if (value > 8 || value < 0)
		{
			continue;
		}
		else
		{
			array[value] = true;
		}
	}
}

std::vector<std::string> Generations::splitDataString(std::string data)
{
	std::stringstream test(data);
	std::string segment;
	std::vector<std::string> seglist;

	while (std::getline(test, segment, '/'))
	{
		seglist.push_back(segment);
	}

	return seglist;
}

cv::Mat Generations::getStep()
{
	cv::Mat clone = universeData.clone();
	int aliveColor = 255;
	int deadColor = 0;

	for (int i = 0; i < clone.cols; i++)
	{
		int im = getRow(i - 1) * clone.cols;
		int ip = getRow(i + 1) * clone.cols;
		int ic = i * clone.cols;

		for (int j = 0; j < clone.rows; j++)
		{
			int a = 0;
			int myIndex = ic + j;

			bool dead = clone.data[myIndex] == deadColor;
			bool alive = clone.data[myIndex] == aliveColor;

			j - 1 < 0 ? clone.cols - 1 : j - 1;

			int jm = j - 1 < 0 ? clone.cols - 1 : j - 1;
			int jp = j + 1 > clone.cols - 1 ? 0 : j + 1;

			if (clone.data[im + jp] == aliveColor)
				++a;
			if (clone.data[ic + jp] == aliveColor)
				++a;
			if (clone.data[ip + jp] == aliveColor)
				++a;

			if (clone.data[im + j] == aliveColor)
				++a;
			if (clone.data[ip + j] == aliveColor)
				++a;

			if (clone.data[im + jm] == aliveColor)
				++a;
			if (clone.data[ic + jm] == aliveColor)
				++a;
			if (clone.data[ip + jm] == aliveColor)
				++a;

			if (dead && birthCondition[a])
			{
				universeData.data[myIndex] = aliveColor;
			}
			else if (alive && survivalCondition[a])
			{
				continue;
			}
			else if (!dead)
			{
				universeData.data[myIndex] = colorValues[universeData.data[myIndex]];
			}

		}
	}

	cv::Mat display;
	universeData.convertTo(display, CV_8UC3);
	applyColorMap(display, display, cv::COLORMAP_INFERNO);
	return display;
}
