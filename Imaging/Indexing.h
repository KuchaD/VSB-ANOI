//
// Created by davelinux on 19.2.19.
//

#ifndef VSB_ANOI_INDEXING_H
#define VSB_ANOI_INDEXING_H

#include "Indexing.h"
class Indexing
{
private:
    cv::Mat mVisitedPoint;
    cv::Mat mIndexImage;
    cv::Mat mSrc;
    cv::Vec3b Colour;
    int Counter = 0;
public:
    Indexing();
    cv::Mat GetIndexImage();
    cv::Mat GetVisitedImage();

    Indexing(cv::Mat &src);
    void Apply(int x, int y);
    ~Indexing();
};



#endif //VSB_ANOI_INDEXING_H
