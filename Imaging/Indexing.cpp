//
// Created by davelinux on 19.2.19.
//

#include <opencv2/core/hal/interface.h>
#include <opencv2/core/mat.hpp>
#include "Indexing.h"
#include "Indexing.h"
#include "../Utils/Utils.h"

Indexing::Indexing() {}
Indexing::Indexing(cv::Mat & src)
{
    mIndexImage = cv::Mat::zeros(src.rows, src.cols, CV_8UC3);
    mVisitedPoint = cv::Mat::zeros(src.rows, src.cols, CV_8UC1);


    this->mSrc = src;
    Counter = 1;
    Utils Utils;

    for (int y = 0; y < src.rows; y++)
    {
        for (int x = 0; x < src.cols; x++)
        {
            Apply(x, y);
            Colour = Utils.RandomColor();
            Counter++;
        }
    }

}

void Indexing::Apply(int x,int y)
{
    if (y >= mSrc.rows  || x >=  mSrc.cols || y < 0  || x < 0)
        return;


    if (mVisitedPoint.at<uchar>(y,x) == 0) {
        mVisitedPoint.at<uchar>(y, x) = 255;

        if (mSrc.at<uchar>(y, x) == 255)
        {
            mIndexImage.at<cv::Vec3b>(y, x) = Colour ;

            Apply(x - 1, y);
            Apply(x, y - 1);
            Apply(x + 1, y);
            Apply(x, y + 1);
            Apply(x - 1, y - 1);
            Apply(x + 1, y - 1);
            Apply(x + 1, y + 1);
            Apply(x + 1, y - 1);


        }


    }

}




Indexing::~Indexing()
{
}

cv::Mat Indexing::GetIndexImage() { return mIndexImage; }

cv::Mat Indexing::GetVisitedImage() { return mVisitedPoint; }
