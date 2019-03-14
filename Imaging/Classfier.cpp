//
// Created by daveliinux on 10.3.19.
//

#include "Classfier.h"
#include "../Structures/MyException.h"
#include "../Structures/ObjectTyp.h"
void Classfier::AddClass(std::vector<ImgObject> &aTrainObjects, std::string aName, cv::Vec3b Color) {

    Ethanol Ethalon = Ethanol(aName,Color);
    for(auto& nItem : aTrainObjects)
    {
        Ethalon.set(nItem);
    }

    TypeClass.push_back(Ethalon);

}

Ethanol Classfier::Classification(ImgObject &aObject) {


    Ethanol lResult;
    double lMinGlobal = 100;
    for(auto &Class : TypeClass)
    {
        double lMin  = Class.computeDist(aObject);

        if(lMin < lMinGlobal) {
            lResult = Class;
            lMinGlobal = lMin;
        }

    }

    ObjectTyp* lClass = new ObjectTyp();
    lClass->Name = lResult.getName();

    lClass->Color = lResult.getColor();

    aObject.ObjectClass = lClass;
    return lResult;
}

void Classfier::ShowInfo(cv::Mat &Dest,std::vector<ImgObject> *Objects,cv::Mat IndexImage) {

        if(Objects == NULL)
            throw MyException(" \"[Error] - Objects in image is not define \n");

        Dest = cv::Mat::zeros(IndexImage.rows, IndexImage.cols, CV_8UC3);
        for (int y = 0; y < IndexImage.rows; y++)
        {
            for (int x = 0; x < IndexImage.cols; x++)
            {
                auto Value = IndexImage.at<uchar>(y,x);

                if(IndexImage.at<uchar>(y,x) != 0)
                {
                    if(Objects->at(Value-1).ObjectClass != NULL) {
                        auto Color = Objects->at(Value - 1).ObjectClass->Color;
                        Dest.at<cv::Vec3b>(y, x) = Color;
                    }


                }

            }
        }

        for(int i=0;i < Objects->size();i++)
        {
            if(Objects->at(i).ObjectClass != NULL)
                cv::putText(Dest, Objects->at(i).ObjectClass->Name ,cv::Point(Objects->at(i).CenterOfMass.X,Objects->at(i).CenterOfMass.Y),cv::FONT_HERSHEY_SIMPLEX,0.30, cv::Scalar(255, 255, 255));
        }



}
