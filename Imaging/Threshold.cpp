//
// Created by davelinux on 19.2.19.
//

#include <opencv2/core/mat.hpp>
#include "Threshold.h"

void Threshold::Apply(cv::Mat& src, cv::Mat& dest)
{
    dest = cv::Mat(src.rows, src.cols, CV_8UC1);
    for (int y = 0; y < src.rows; y++)
    {
        for (int x =0; x < src.cols; x++)
        {
            if (src.at<uchar>(y,x) >= mValue)
            {
                dest.at<uchar>(y, x) = 255;
            }
            else
            {
                dest.at<uchar>(y,x) = 0;
            }
        }
    }
}

Threshold::~Threshold()
{
}
