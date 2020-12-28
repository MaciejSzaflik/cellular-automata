#include "TreeSeed.h"
#include <math.h>

#define PI 3.14159265

TreeSeed::TreeSeed()
{
}

TreeSeed::TreeSeed(const TreeSeed& seed2)
{
    start = seed2.start;

    angle = seed2.angle;
    angleRandom = seed2.angleRandom;

    length = seed2.length;
    lengthRandom = seed2.lengthRandom;

    childrenMax = seed2.childrenMax;
    childrenMin = seed2.childrenMin;

    fuel = seed2.fuel;
}

std::vector<TreeSeed> TreeSeed::getChildren()
{
    TreeSeed ch1 = *this;
    TreeSeed ch2 = *this;
    ch1.start = getPoint(-angle, length, start);
    ch2.start = getPoint(-angle - 90, length, start);
    std::vector<TreeSeed> toReturn;
    toReturn.push_back(ch1);
    toReturn.push_back(ch2);
    return toReturn;
}

int TreeSeed::getRandomBetween(int min, int max)
{
    int n = max - min + 1;
    int i = rand() % n;
    if (i < 0) i = -i;
    return min + i;
}

float TreeSeed::getRandomBetweenF(float min, float max)
{
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = max - min;
    float r = random * diff;
    return min + r;
}

cv::Point2i TreeSeed::getPoint(float angle, float len, cv::Point2i start)
{
    float radian = angle * PI / 180.0;
    
    int x = (int)(start.x  + len * cosf(radian));
    int y = (int)(start.y  + len * sinf(radian));

    return cv::Point2i(x,y);
}
