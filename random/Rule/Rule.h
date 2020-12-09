#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2\core\base.hpp>
#include <string>

class Rule
{
public:
	int iter;
	std::string rule;
	Rule(int ruleValue);
	void initializeRandom(cv::Mat image);
	void initializeSingle(cv::Mat image);
	void step(cv::Mat image);
private:
	int decWrap(int val, int replace);
	int incWrap(int val, int max);
	bool decide(bool a, bool b, bool c);
};

