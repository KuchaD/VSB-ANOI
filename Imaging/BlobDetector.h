//
// Created by davelinux on 19.2.19.
//

#ifndef VSB_ANOI_INDEXING_H
#define VSB_ANOI_INDEXING_H

#include "Indexing.h"
#include "ImgObject.h"
class Indexing
{
private:
    cv::Mat mVisitedPoint;
    cv::Mat mIndexImage;
    cv::Mat mSrc;
    cv::Vec3b Colour;
    int Counter = 0;
    std::vector<ImgObject> Objects;
public:
    Indexing();
    cv::Mat GetIndexImage();
    cv::Mat GetVisitedImage();

    Indexing(cv::Mat &src);
    bool Apply(int x, int y);
    double Moments(int p,int q,int Index);
    void CalculateMoments();
    ~Indexing();
};



#endif //VSB_ANOI_INDEXING_H
