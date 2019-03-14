//
// Created by daveliinux on 10.3.19.
//

#ifndef VSB_ANOI_CLASSFIER_H
#define VSB_ANOI_CLASSFIER_H

#include "vector"
#include "Ethanol.h"
#include "../Structures/ImgObject.h"

#include <iostream>
#include "opencv2/opencv.hpp"
class Classfier {
private:
    std::vector<Ethanol> TypeClass;
public:
    void AddClass(std::vector<ImgObject> &aTrainObjects,std::string aName, cv::Vec3b Color);
    std::vector<Ethanol>& getClass(){ return  TypeClass;}
    Ethanol Classification(ImgObject &aObject);
    void ShowInfo(cv::Mat &Dest,std::vector<ImgObject> *Objects,cv::Mat IndexImage) ;




};


#endif //VSB_ANOI_CLASSFIER_H
