#include "AntStep.h"


HardStep::HardStep(bool dir, int b, int g, int r, cv::Vec3b color)
{
    this->dir = dir;
    this->BThreshold = b;
    this->GThreshold = g;
    this->RThreshold = r;
    this->color = color;
}


RandomStep::RandomStep(bool dir, int b, int g, int r, int rand)
{
    this->dir = dir;
    this->BThreshold = b;
    this->GThreshold = g;
    this->RThreshold = r;
    this->randFactor = rand;
}

bool RandomStep::check(cv::Vec3b color)
{
    if(dir)
        return BThreshold >= color[0] || GThreshold >= color[1] || RThreshold >= color[2];
    else
        return BThreshold < color[0] || GThreshold < color[1] || RThreshold < color[2];
}

cv::Vec3b RandomStep::getColor()
{
    return cv::Vec3b(
        std::min(255,(BThreshold + rand() % randFactor)),
        std::min(255,(GThreshold + rand() % randFactor)),
        std::min(255,(RThreshold + rand() % randFactor))
    );
}

bool HardStep::check(cv::Vec3b color)
{
    return BThreshold == color[0] && GThreshold == color[1] && RThreshold == color[2];
}

cv::Vec3b HardStep::getColor()
{
    return color;
}
