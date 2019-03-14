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

cv::Mat Utils::RotateImage(const cv::Mat &source, const double angle)
{
    cv::Point center = cv::Point(source.cols / 2, source.rows / 2);
    cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);
    cv::Rect2f bbox = cv::RotatedRect(cv::Point2f(), source.size(), angle).boundingRect2f();
    rot.at<double>(0, 2) += bbox.width / 2.0 - source.cols / 2.0;
    rot.at<double>(1, 2) += bbox.height / 2.0 - source.rows / 2.0;

    cv::Mat rotated_image;
    cv::warpAffine(source, rotated_image, rot, bbox.size());

    return rotated_image;
}

Utils::~Utils()
{
}
