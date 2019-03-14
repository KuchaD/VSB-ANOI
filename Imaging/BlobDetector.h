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
    void CalculateArea();
    double CalculteMomentsWithCenterOfMass(int p,int q,int i,Point<int> CenterOfMass );
    double Perimetr(int i);
    double CalF1(int Perimeter,int Area);
    double CalF2(int u11,int u20,int u02);
    void ShowInformationImage(cv::Mat &Dest);
    void ShowInfo();
    std::vector<ImgObject>  *GetObjects(){ return  Objects;}
    double ComputeAngleF3(int Index);

    cv::Mat getIndexImage(){ return  mIndexImage;}
    ~BlobDetector();
};



#endif //VSB_ANOI_INDEXING_H
