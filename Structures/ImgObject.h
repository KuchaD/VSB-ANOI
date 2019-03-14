//
// Created by davelinux on 20.2.19.
//

#ifndef VSB_ANOI_IMGOBJECT_H
#define VSB_ANOI_IMGOBJECT_H

#include <opencv2/opencv.hpp>
#include "iostream"
#include "Point.h"
#include "ObjectTyp.h"

class ImgObject {
private:
    cv::Vec3b* Color = NULL;
public:
    ImgObject(){Color = NULL,ObjectClass = NULL;}
    std::string name;
    int Index;
    ObjectTyp* ObjectClass;

    double M00;
    double M10;
    double M01;

    Point<int> CenterOfMass;
    int Perimetr;
    int Area;
    double F1;
    double F2;
    double F3;
    double umin;
    double umax;
    cv::Vec3b GetColor();
    void SetColor(cv::Vec3b* aColor);
    void PrintToConsole();
    ~ImgObject();
};



#endif //VSB_ANOI_IMGOBJECT_H
