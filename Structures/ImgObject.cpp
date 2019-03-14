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

    ObjectClass = NULL;
    delete(ObjectClass );
}

void ImgObject::PrintToConsole() {

    std::cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄"  << std::endl ;
    std::cout << "OBJECT: " << name << " [X: " << CenterOfMass.X << " Y: " << CenterOfMass.Y << "] " << std::endl;
    std::cout << "INDEX: " <<  this->Index << std::endl;
    std::cout << "AREA: " <<  this->Area << std::endl;
    std::cout << "PERIMETR: " <<  this->Perimetr << std::endl;
    std::cout << "F1: " <<  this->F1 << std::endl;
    std::cout << "F2: " <<  this->F2 << std::endl;

    std::cout << "═══════════════════════════"<< std::endl;
    std::cout << "M00: " <<  this->M00 << std::endl;
    std::cout << "M10: " <<  this->M01 << std::endl;
    std::cout << "M01: " <<  this->M10 << std::endl;


    std::cout << "▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄" << std::endl;

}
