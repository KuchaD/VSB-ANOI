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
#include <math.h>

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
                    lSum += pow(x,p) * pow(y,q);// mSrc.at<uchar>(y,x);
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

        lObj.Index = i;
        double M00 = Moments(0,0,i);
        double M10 = Moments(1,0,i);
        double M01 = Moments(0,1,i);

        lObj.CenterOfMass.X= M10/M00;
        lObj.CenterOfMass.Y= M01/M00;
        lObj.Area = M00;
        lObj.M00 = M00;
        lObj.M01 = M01;
        lObj.M10 = M10;

        int u11 = CalculteMomentsWithCenterOfMass(1,1,i,lObj.CenterOfMass);
        int u20 = CalculteMomentsWithCenterOfMass(2,0,i,lObj.CenterOfMass);
        int u02 = CalculteMomentsWithCenterOfMass(0,2,i,lObj.CenterOfMass);
        lObj.Perimetr = Perimetr(i);
        lObj.F1 = CalF1(lObj.Perimetr,lObj.Area);
        lObj.F2 = CalF2(u11,u20,u02);
        lObj.F3 = ComputeAngleF3(i);

        Objects->push_back(lObj);
        std::cout <<  i <<" | "<<"X: " << lObj.CenterOfMass.X << " Y: " << lObj.CenterOfMass.Y << " P " << lObj.Perimetr << " F1 "<< lObj.F1 << " F2 " << lObj.F2 <<  "\n";





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


    for(int i=0;i < Objects->size();i++)
    {

       cv::putText(Dest,  "A: "+  std::to_string(Objects->at(i).Area),cv::Point(Objects->at(i).CenterOfMass.X,Objects->at(i).CenterOfMass.Y),cv::FONT_HERSHEY_SIMPLEX,0.30, cv::Scalar(255, 255, 255));
       cv::putText(Dest,  "P: "+  std::to_string(Objects->at(i).Perimetr),cv::Point(Objects->at(i).CenterOfMass.X,Objects->at(i).CenterOfMass.Y+10),cv::FONT_HERSHEY_SIMPLEX,0.30, cv::Scalar(255, 255, 255));
    }

}

void BlobDetector::CalculateArea() {

    for(int i=0;i < Objects->size();i++)
    {
        Objects->at(i).Area = Moments(0,0,Objects->at(i).Index);

    }
}

double BlobDetector::CalculteMomentsWithCenterOfMass(int p, int q, int i, Point<int> CenterOfMass) {

        double lSum = 0;
        for (int y = 0; y < mIndexImage.rows; y++)
        {
            for (int x = 0; x < mIndexImage.cols; x++)
            {
                if(i == mIndexImage.at<uchar>(y,x))
                    lSum += pow(x-CenterOfMass.X,p) * pow(y-CenterOfMass.Y,q);// * mSrc.at<uchar>(y,x);
            }
        }


    return lSum;


}

double BlobDetector::Perimetr(int i) {

    int Perimeter = 0;
    for (int y = 0; y < mIndexImage.rows; y++)
    {
        for (int x = 0; x < mIndexImage.cols; x++)
        {
            if(mIndexImage.at<uchar>(y,x) == i)
            {
                uchar Up, Down, Left, Right;

                if (x >= 0 && x < mIndexImage.cols)
                    Left = mIndexImage.at<uchar>(y, x-1);
                else
                    Left = i;

                if (x >= 0 && x < mIndexImage.cols)
                    Right = mIndexImage.at<uchar>(y, x+1);
                else
                    Right = i;


                if (y >= 0 && y < mIndexImage.rows)
                    Up = mIndexImage.at<uchar>(y-1, x);
                else
                    Up = i;

                if (y >= 0 && y < mIndexImage.rows)
                    Down = mIndexImage.at<uchar>(y+1, x);
                else
                    Down = i;


                if (!(Left == i && Right == i && Up == i && Down == i))
                    Perimeter++;
            }
        }
    }

    return Perimeter;
}

double BlobDetector::CalF1(int Perimeter, int Area) {


    return (pow(Perimeter,2)/(100*Area));
}

double BlobDetector::CalF2(int u11, int u20, int u02){

 double umax = (u20 + u02)*0.5 + 0.5*( sqrt(4*pow(u11,2) + pow((u20 - u02),2)) );
 double umin = 0.5*(u20 + u02) - 0.5* (sqrt( 4*pow(u11,2) + pow((u20 - u02),2)) );

 return umax/umin;
}

void BlobDetector::ShowInfo() {
    for(int i=0;i < Objects->size();i++) {
        Objects->at(i).PrintToConsole();

    }

    }

double BlobDetector::ComputeAngleF3(int Index) {
    int N_min = 0, S_min = mIndexImage.rows + 1, E_min = mIndexImage.cols + 1, W_min = 0;
    int N_max = 1, S_max = 1, E_max = 1, W_max = 1;

    cv::Mat highlited = cv::Mat::zeros(mIndexImage.rows, mIndexImage.cols, CV_8UC1);;

    for (int y = 0; y < mIndexImage.rows; y++) {
        for (int x = 0; x < mIndexImage.cols; x++) {
            if (mIndexImage.at<uchar>(y, x) == Index) {
                highlited.at<uchar>(y, x) = 255;
            }
        }
    }

    for (int angle = 0; angle <= 90; angle = angle + 5) {
        cv::Mat rotated = Utils::RotateImage(highlited, angle);
        int N_temp = mIndexImage.rows + 1, S_temp = 0, E_temp = 0, W_temp = mIndexImage.cols + 1;

        for (int y = 0; y < rotated.rows; y++) {
            for (int x = 0; x < rotated.cols; x++) {
                if (rotated.at<uchar>(y, x) != 0) {
                    if (N_temp > y) N_temp = y;
                    if (S_temp < y) S_temp = y;
                    if (E_temp < x) E_temp = x;
                    if (W_temp > x) W_temp = x;
                }
            }
        }


        if (((E_temp - W_temp) * (S_temp - N_temp)) < ((E_min - W_min) * (S_min - N_min))) {
            E_min = E_temp;
            W_min = W_temp;
            S_min = S_temp;
            N_min = N_temp;
        }

        if (((E_temp - W_temp) * (S_temp - N_temp)) > ((E_max - W_max) * (S_max - N_max))) {
            E_max = E_temp;
            W_max = W_temp;
            S_max = S_temp;
            N_max = N_temp;
        }
    }

    return (double) ((E_max - W_max) * (S_max - N_max)) / ((E_min - W_min) * (S_min - N_min));

}



