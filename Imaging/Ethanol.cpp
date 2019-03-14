//
// Created by daveliinux on 10.3.19.
//

#include "Ethanol.h"


Ethanol::Ethanol(std::string aName,cv::Vec3b aColor) {
    this->X = this->Y = this->Z = 0.0;
    this->sumX = this->sumY = this->sumZ = 0.0;
    this->numberElements = 0;
    this->Name = aName;
    this->Color = aColor;

}

void Ethanol::set(ImgObject object)  {
    this->sumX += object.F1;
    this->sumY += object.F2;
    this->sumZ += object.F3;
    this->numberElements += 1;
    this->X = (this->sumX / this->numberElements);
    this->Y = (this->sumY / this->numberElements);
    this->Z = (this->sumZ / this->numberElements);
}

double Ethanol::getX() {
    return this->X;
}

double Ethanol::getY() {
    return this->Y;
}

double Ethanol::computeDist(ImgObject & object) {
    double res = (this->X - object.F1) * (this->X - object.F1);
    res += (this->Y - object.F2) * (this->Y - object.F2);
    res += (this->Z - object.F3) * (this->Z - object.F3);

    return std::sqrt(res);
}

std::string Ethanol::getName() {
    return this->Name;
}

Ethanol::~Ethanol() {

}


cv::Vec3b Ethanol::getColor() {
    return Color;
}
