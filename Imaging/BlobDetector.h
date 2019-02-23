//
// Created by davelinux on 19.2.19.
//

#ifndef VSB_ANOI_INDEXING_H
#define VSB_ANOI_INDEXING_H

#include "BlobDetector.h"
#include "../Structures/ImgObject.h"
class BlobDetector
{
private:
    cv::Mat mVisitedPoint;
    cv::Mat mIndexImage;
    cv::Mat mSrc;
    cv::Vec3b Colour;
    int Counter = 0;
    std::vector<ImgObject>  *Objects = NULL;
public:
    BlobDetector();
    cv::Mat GetIndexImage();
    cv::Mat GetVisitedImage();

    void Indexing();
    BlobDetector(cv::Mat &src);
    bool Apply(int x, int y);
    double Moments(int p,int q,int Index);
    void CalculateMoments();

    void ShowInformationImage(cv::Mat &Dest);

    ~BlobDetector();
};



#endif //VSB_ANOI_INDEXING_H
