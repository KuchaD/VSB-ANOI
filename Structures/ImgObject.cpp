//
// Created by davelinux on 20.2.19.
//

#include "ImgObject.h"
#include "../Utils/Utils.h"

cv::Vec3b ImgObject::GetColor() {
    if(this->Color == NULL)
    {

        auto RandColor = Utils::RandomColor();
        this->Color = new cv::Vec3b(RandColor[0],RandColor[1],RandColor[2]);

        return *this->Color;
    }
    return *this->Color;
}

void ImgObject::SetColor(cv::Vec3b* aColor) {
    this->Color = aColor;

}

ImgObject::~ImgObject() {
    Color = NULL;
    delete(Color);
}
