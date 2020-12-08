#include "WeightedGenerations.h"

#include "Generations.h"
#include <string>
#include <opencv2\imgproc.hpp>

void WeightedGenerations::initialize(int w, int h, std::string data)
{
	this->universeData = cv::Mat::zeros(h, w, CV_8U);

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

	//createRectangle(w/2, w/2, 1, colorValues[0]);

	/*step = w / 4;
	int halfstep = step / 2;
	for (int i = 0; i < w; i += step)
	{
		for (int j = 0; j < h; j += step)
		{
			createRectangle(i + halfstep, j + halfstep, 2, colorValues[0]);
			//createRectangle(i + halfstep, j + halfstep, 5, colorValues[last]);
			//createRectangle(i + halfstep, j + halfstep, 2, colorValues[0]);
		}
	}*/

	universeData.forEach<uchar>(
		[](uchar& pixel, const int* position) -> void
		{
			pixel = rand() % 10 + 1 > 6 ? 255 : 0;
		}
	);


	kernel = cv::Mat::ones(3, 3, CV_8U);
	kernel.at<uchar>(1, 1) = 0;
}

cv::Mat WeightedGenerations::getStepFilter()
{
	int aliveColor = 255;
	int deadColor = 0;

	cv::Mat transitionTable = cv::Mat::zeros(universeData.rows, universeData.cols, CV_8U);

	cv::threshold(universeData, transitionTable, aliveColor - 1, 1, CV_8U);
	cv::filter2D(transitionTable, transitionTable, -1, kernel);

	cv::Mat iterable;
	std::vector<cv::Mat> channels(2);
	channels[0] = universeData;
	channels[1] = transitionTable;
	cv::merge(channels, iterable);

	iterable.forEach<cv::Vec2b>(
		[aliveColor, deadColor, this](cv::Vec2b& pixel, const int* position) -> void
		{
			int currentCell = pixel.val[0];
			int a = pixel.val[1];

			if (currentCell == deadColor && birthCondition[a])
			{
				pixel.val[0] = aliveColor;
			}
			else if (currentCell == aliveColor && survivalCondition[a])
			{
			}
			else if (currentCell != deadColor)
			{
				pixel.val[0] = colorValues[currentCell];
			}

		}
	);

	cv::Mat display;

	cv::split(iterable, channels);
	channels[0].copyTo(universeData);
	universeData.convertTo(display, CV_8UC3);
	applyColorMap(display, display, cv::COLORMAP_INFERNO);
	return display;
}

cv::Mat WeightedGenerations::getStep()
{
	cv::Mat clone = universeData.clone();
	int aliveColor = 255;
	int deadColor = 0;

	for (int i = 0; i < clone.rows; i++)
	{
		int im = getRow(i - 1) * clone.cols;
		int ip = getRow(i + 1) * clone.cols;
		int ic = i * clone.cols;

		for (int j = 0; j < clone.cols; j++)
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
