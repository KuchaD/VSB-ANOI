//
// Created by davelinux on 19.2.19.
//

#include "Utils.h"
#include <math.h>
#include <opencv2/core/mat.hpp>
#include "../Structures/ImgObject.h"

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
