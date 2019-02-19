//
// Created by davelinux on 19.2.19.
//

#include "Utils.h"
Utils::Utils()
{
}

cv::Vec3b Utils::RandomColor()
{

    cv::Vec3b lRandom = cv::Vec3b(rand() % 230, rand() % 230, rand() % 230);

    return lRandom;
}


Utils::~Utils()
{
}
