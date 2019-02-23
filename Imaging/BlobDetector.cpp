//
// Created by davelinux on 19.2.19.
//

#include <opencv2/core/hal/interface.h>
#include <opencv2/core/mat.hpp>
#include "BlobDetector.h"
#include "BlobDetector.h"
#include "../Utils/Utils.h"
#include "../Structures/ImgObject.h"
#include "../Structures/MyException.h"

BlobDetector::BlobDetector() {}
BlobDetector::BlobDetector(cv::Mat & src)
{
    mIndexImage = cv::Mat::zeros(src.rows, src.cols, CV_8UC1);
    mVisitedPoint = cv::Mat::zeros(src.rows, src.cols, CV_8UC1);


    this->mSrc = src;
    this->Counter = 0;

}

void BlobDetector::Indexing() {
    this->Counter = 1;
    Utils Utils;

    for (int y = 0; y < mSrc.rows; y++)
    {
        for (int x = 0; x < mSrc.cols; x++)
        {
            auto Change = Apply(x, y);
            if(Change) {
                this->Counter++;
            }
        }
    }

    Objects = new std::vector<ImgObject>();
    std::cout << "Found "<< Counter-1 << " objects" << "\n";
}

bool BlobDetector::Apply(int x,int y)
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


cv::Mat BlobDetector::GetIndexImage() { return mIndexImage; }

cv::Mat BlobDetector::GetVisitedImage() { return mVisitedPoint; }

double BlobDetector::Moments(int p,int q, int Index) {

        double lSum = 0;
        for (int y = 0; y < mIndexImage.rows; y++)
        {
            for (int x = 0; x < mIndexImage.cols; x++)
            {
                if(Index == mIndexImage.at<uchar>(y,x))
                    lSum += pow(x,p) * pow(y,q) * mSrc.at<uchar>(y,x);
            }
        }

    return lSum;


}

void BlobDetector::CalculateMoments()
{
    if(Objects == NULL) {
        throw MyException(" \"[Error] - Objects in image is not define \n");
    }

    if(Counter == 0)
    {
        std::cout << "[Error] No Detections Objects in the Image.(First use Indexing)"<< "\n";
        return;
    }

    for(int i=1;i < Counter;i++)
    {
        ImgObject lObj ;

        lObj.Index = i+1;
        double M00 = Moments(0,0,i);
        lObj.Moments.X= Moments(1,0,i)/M00;
        lObj.Moments.Y= Moments(0,1,i)/M00;

        Objects->push_back(lObj);
        std::cout <<  i <<" | "<<"X: " << lObj.Moments.X << " Y: " << lObj.Moments.Y << "\n";

    }
    std::cout.flush();
}

BlobDetector::~BlobDetector() {
    Objects = NULL;
    delete Objects;
}

void BlobDetector::ShowInformationImage(cv::Mat &Dest) {
    if(Objects == NULL)
        throw MyException(" \"[Error] - Objects in image is not define \n");



    Dest = cv::Mat::zeros(mIndexImage.rows, mIndexImage.cols, CV_8UC3);
    for (int y = 0; y < mIndexImage.rows; y++)
    {
        for (int x = 0; x < mIndexImage.cols; x++)
        {
            auto Value = mIndexImage.at<uchar>(y,x);

            if(mIndexImage.at<uchar>(y,x) != 0)
            {
                auto Color = Objects->at(Value-1).GetColor();
                Dest.at<cv::Vec3b>(y,x) = Color;
            }

        }
    }


}




