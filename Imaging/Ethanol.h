//
// Created by daveliinux on 10.3.19.
//

#ifndef VSB_ANOI_OBJECTCLASS_H
#define VSB_ANOI_OBJECTCLASS_H

#include "../Structures/ImgObject.h"
#include "iostream"
#include "vector"
#include "opencv2/opencv.hpp"


class Ethanol {
public:
    Ethanol(std::string aName,cv::Vec3b aColor);
    Ethanol(){};
    ~Ethanol();
    void set(ImgObject object);
    double computeDist(ImgObject & object);
    double getX();
    double getY();
    std::string getName();
    cv::Vec3b getColor();
private:
    cv::Vec3b Color;
    double X,Y,Z, sumX, sumY, sumZ;
    int numberElements;
    std::string Name;

};


#endif //VSB_ANOI_OBJECTCLASS_H
