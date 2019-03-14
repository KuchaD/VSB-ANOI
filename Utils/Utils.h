//
// Created by davelinux on 19.2.19.
//

#ifndef VSB_ANOI_UTILS_H
#define VSB_ANOI_UTILS_H


#include <opencv2/core/matx.hpp>


class Utils
{
public:
    Utils();
    static cv::Vec3b RandomColor();
    static cv::Mat RotateImage(const cv::Mat &source, const double angle);
    ~Utils();
};

#endif //VSB_ANOI_UTILS_H
