#include "AntFactory.h"

SimpleAnt AntFactory::GetHardAnt(std::string definition, int x, int y, int w, int h, int speed)
{
    SimpleAnt ant = SimpleAnt(x,y,w,h,speed);
    int len = definition.length();

    cv::Vec3b color = cv::Vec3b(0, 0, 0);
    int step = 255 / len;
    for (int i = 0; i < len -1 ; i++)
    {
        cv::Vec3b newColor = cv::Vec3b(i*step/2, i*step/6, 255- i*step);
        ant.steps.push_back(new HardStep(definition[i] == 'R', color[0], color[1], color[2], newColor));
        color[0] = newColor[0];
        color[1] = newColor[1];
        color[2] = newColor[2];
    }

    ant.steps.push_back(new HardStep(definition[len - 1] == 'R', color[0], color[1], color[2], cv::Vec3b(0, 0, 0)));
    return ant;
}
