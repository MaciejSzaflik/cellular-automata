#include "WeightedGenerations.h"


#include "Generations.h"
#include <string>
#include <opencv2\imgproc.hpp>

void WeightedGenerations::initialize(int w, int h, std::string data)
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
	int halfstep = step / 2;
	for (int i = 0; i < w; i += step)
	{
		for (int j = 0; j < w; j += step)
		{
			createRectangle(i + halfstep, j + halfstep, 10, colorValues[0]);
			createRectangle(i + halfstep, j + halfstep, 5, colorValues[last]);
			createRectangle(i + halfstep, j + halfstep, 2, colorValues[0]);
		}
	}
}

cv::Mat WeightedGenerations::getStepFilter()
{
	int aliveColor = 255;
	int deadColor = 0;

	cv::Mat transitionTable = cv::Mat::zeros(universeData.rows, universeData.cols, CV_8U);

	cv::threshold(universeData, transitionTable, 254, 1, CV_8U);

	cv::Mat kernel = cv::Mat::ones(3, 3, CV_8U);
	kernel.at<uchar>(1, 1) = 0;
	cv::filter2D(transitionTable, transitionTable, -1, kernel);

	for (int i = 0; i < universeData.cols; i++)
	{
		int im = getRow(i - 1) * universeData.cols;
		int ip = getRow(i + 1) * universeData.cols;
		int ic = i * universeData.cols;

		for (int j = 0; j < universeData.rows; j++)
		{
			int a = 0;
			int myIndex = ic + j;

			bool dead = universeData.data[myIndex] == deadColor;
			bool alive = universeData.data[myIndex] == aliveColor;

			j - 1 < 0 ? universeData.cols - 1 : j - 1;

			int jm = j - 1 < 0 ? universeData.cols - 1 : j - 1;
			int jp = j + 1 > universeData.cols - 1 ? 0 : j + 1;

			a = transitionTable.data[myIndex];

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

cv::Mat WeightedGenerations::getStep()
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
