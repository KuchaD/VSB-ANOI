//
// Created by davelinux on 19.2.19.
//

#include <opencv2/core/hal/interface.h>
#include <opencv2/core/mat.hpp>
#include "Indexing.h"
#include "Indexing.h"
#include "../Utils/Utils.h"
#include "ImgObject.h"

Indexing::Indexing() {}
Indexing::Indexing(cv::Mat & src)
{
    mIndexImage = cv::Mat::zeros(src.rows, src.cols, CV_8UC3);
    mVisitedPoint = cv::Mat::zeros(src.rows, src.cols, CV_8UC1);


    this->mSrc = src;
    this->Counter = 1;
    Utils Utils;

    for (int y = 0; y < src.rows; y++)
    {
        for (int x = 0; x < src.cols; x++)
        {
            auto Change = Apply(x, y);
            if(Change) {
                Colour = Utils.RandomColor();
                this->Counter++;
            }
        }
    }

}

bool Indexing::Apply(int x,int y)
{
    if (y >= mSrc.rows  || x >=  mSrc.cols || y < 0  || x < 0)
        return false;


    if (mVisitedPoint.at<uchar>(y,x) == 0) {

        mVisitedPoint.at<uchar>(y, x) = 255;

        if (mSrc.at<uchar>(y, x) == 255)
        {
            mIndexImage.at<uchar>(y, x) = Counter;

            Apply(x - 1, y);
            Apply(x, y - 1);
            Apply(x + 1, y);
            Apply(x, y + 1);
            Apply(x - 1, y - 1);
            Apply(x + 1, y - 1);
            Apply(x + 1, y + 1);
            Apply(x - 1, y + 1);

            return true;
        }


    }
    return false;
}


Indexing::~Indexing()
{
}

cv::Mat Indexing::GetIndexImage() { return mIndexImage; }

cv::Mat Indexing::GetVisitedImage() { return mVisitedPoint; }

double Indexing::Moments(int p,int q, int Index) {

        double lSum = 0;
        for (int y = 0; y < mIndexImage.rows; y++)
        {
            for (int x = 0; x < mIndexImage.cols; x++)
            {
                if(Index == mIndexImage.at<uchar>(y,x))
                    lSum += pow(x,p) * pow(y,q) ; //mSrc.at<uchar>(y,x);
            }
        }

    return lSum;


}

void Indexing::CalculateMoments()
{
    for(int i=1;i < Counter;i++)
    {
        ImgObject lObj;

        lObj.Index = i+1;
        lObj.MomentsX = Moments(1,0,i)/Moments(0,0,i);
        lObj.MomentsY = Moments(0,1,i)/Moments(0,0,i);

        Objects.push_back(lObj);
        std::cout <<  i <<" | "<<"X: " << lObj.MomentsX << " Y: " << lObj.MomentsY << "\n";
        std::cout.flush();
    }
}
