//
// Created by daveliinux on 19.3.19.
//

#include "Kmeans.h"
#include "../Structures/Point.h"
#include "../Structures/MyException.h"
#include <iostream>
#include <random>
#include <list>
std::map<int,std::vector<ImgObject>*> Kmeans::Cluster(int aClusters,std::vector<ImgObject>* aData) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, aData->size()-1);

    std::vector<Centroid> lRandomCenteriods;
    int lClusters = aClusters;
    int lPickedPointCount = 0;

    while (lPickedPointCount < aClusters)
    {
        int r = dis(gen);
        auto Obj = aData->at(r);
        Centroid Choose = Centroid(Obj.F1,Obj.F2,Obj.F3);

        if (!Contains(lRandomCenteriods,Choose))
        {
            lRandomCenteriods.push_back(Choose);
            lPickedPointCount++;
        }
    }


    return Process(aData, lRandomCenteriods );

}

bool Kmeans::Contains(std::vector<Centroid> aCentroids, Centroid aCentroid) {

    for(auto& nItem : aCentroids)
    {
        if(nItem.X == aCentroid.X && nItem.Y == aCentroid.Y && nItem.Z == aCentroid.Z )
        {
            return true;
        }

    }

    return false;

}

std::map<int,std::vector<ImgObject>*> Kmeans::Process(std::vector<ImgObject>* aData, std::vector<Centroid> aCentroids) {

    std::map<int,std::vector<ImgObject>*> lCenterAssignments = ParallelGetCenterAssignments(aData, aCentroids);

    std::vector<Centroid> lOldCenters ;
    while (true)
    {
        std::vector<Centroid> lNewCenters = ParallelGetNewCenters(lCenterAssignments,aCentroids.size());
        _Centroids = lNewCenters;

        if (CentersEqual(lNewCenters, lOldCenters))
        {
            break;
        }
        lCenterAssignments = ParallelGetCenterAssignments(aData, lNewCenters);
        lOldCenters = lNewCenters;
    }

    return lCenterAssignments;
}

std::map<int,std::vector<ImgObject>*> Kmeans::ParallelGetCenterAssignments(std::vector<ImgObject>* aPoints, std::vector<Centroid> aCenters) {

    std::map<int,std::vector<ImgObject>*> lCenterAssignments;

    for(int i=0; i < aCenters.size();i++)
    {
        std::vector<ImgObject>* lV = new std::vector<ImgObject>();
        lCenterAssignments[i] = lV;
    }

    for(auto &nPoint : *aPoints)
    {
            double x = nPoint.F1;
            double y = nPoint.F2;
            double z = nPoint.F3;

            Centroid *lClosestCenter = nullptr;
            double lClosestCenterDistance = std::numeric_limits<double>::max();

            for(auto & pickedPoint : aCenters)
            {
                double lCenterX = pickedPoint.X;
                double lCenterY = pickedPoint.Y;
                double lCenterZ = pickedPoint.Z;

                double lDistance = std::sqrt(std::pow(x - lCenterX, 2) + std::pow(y - lCenterY, 2) +  std::pow(z - lCenterZ, 2) );

                if (lDistance < lClosestCenterDistance)
                {
                    lClosestCenterDistance = lDistance;
                    lClosestCenter = &pickedPoint;
                }
            }

        for (int i = 0; i < aCenters.size() ; ++i) {

            if(lClosestCenter->X == aCenters[i].X && lClosestCenter->Y == aCenters[i].Y && lClosestCenter->Z == aCenters[i].Z)
                lCenterAssignments[i]->push_back(nPoint);
        }
    }

    return lCenterAssignments;

}

std::vector<Centroid> Kmeans::ParallelGetNewCenters(std::map<int, std::vector<ImgObject>*> aCenterAssignments,int NumCentorid) {

    std::vector<Centroid> lNewCenteroids ;


    for (int i = 0; i <  NumCentorid; ++i) {


            double lTotalX = 0;
            double lTotalY = 0;
            double lTotalZ = 0;

            std::vector<ImgObject>* Points = aCenterAssignments[i];
            for (int j = 0; j < Points->size() ; ++j) {
                Centroid point = Centroid( Points->at(j).F1,Points->at(j).F2,Points->at(j).F3);

                  lTotalX += point.X;
                  lTotalY += point.Y;
                  lTotalZ += point.Z;
              }

            double lAverageX = lTotalX / Points->size();
            double lAverageY = lTotalY / Points->size();
            double lAverageZ = lTotalZ / Points->size();

            Centroid lNewCenter = Centroid(lAverageX,lAverageY,lAverageZ);
            lNewCenteroids.push_back(lNewCenter);

    }


    return lNewCenteroids;
}

bool Kmeans::CentersEqual(std::vector<Centroid> aNewCenters, std::vector<Centroid> aOldCenters) {
    if (aNewCenters.size() == 0 || aNewCenters.size() == 0)
    {
        return false;
    }

    for(auto& newCenter : aNewCenters)
    {
        bool lFound = false;
        for (auto& oldCenter : aOldCenters)
        {
            if (newCenter.X == oldCenter.X && newCenter.Y == oldCenter.Y && newCenter.Z == oldCenter.Z)
            {
                lFound = true;
                break;
            }
        }

        if (!lFound)
        {
            return false;
        }
    }
    return true;
}

//Pouze pro kontrolu Kmeans nauceni
void Kmeans::ShowInfo(cv::Mat &Dest, std::map<int,std::vector<ImgObject>*> Objects, cv::Mat IndexImage) {

    cv::Vec3b colors[] = {cv::Vec3b(255, 0, 0), cv::Vec3b(0, 255, 0), cv::Vec3b(0, 0, 255), cv::Vec3b(0, 255, 255),cv::Vec3b(100, 25, 255)};
    Dest = cv::Mat::zeros(IndexImage.rows, IndexImage.cols, CV_8UC3);

    for (int i = 0; i < 4; ++i) {
        auto lTest = Objects[i];
        for (int j = 0; j < lTest->size(); ++j) {

            for (int y = 0; y < IndexImage.rows; y++) {
                for (int x = 0; x < IndexImage.cols; x++) {
                    auto Value = IndexImage.at<uchar>(y, x);

                    if (IndexImage.at<uchar>(y, x) == lTest->at(j).Index) {


                        Dest.at<cv::Vec3b>(y, x) = colors[i];


                    }

                }

            }


        }
    }
}

int Kmeans::ClassToObject(ImgObject &aObject) {



            double x = aObject.F1;
            double y = aObject.F2;
            double z = aObject.F3;

            Centroid *lClosestCenter = nullptr;
            double lClosestCenterDistance = std::numeric_limits<double>::max();

            int i = 0;
            int lBestIndex = 0;
            for(auto & pickedPoint : _Centroids)
            {
                double lCenterX = pickedPoint.X;
                double lCenterY = pickedPoint.Y;
                double lCenterZ = pickedPoint.Z;

                double lDistance = std::sqrt(std::pow(x - lCenterX, 2) + std::pow(y - lCenterY, 2) +  std::pow(z - lCenterZ, 2) );

                if (lDistance < lClosestCenterDistance)
                {
                    lClosestCenterDistance = lDistance;
                    lClosestCenter = &pickedPoint;
                    lBestIndex = i;
                }

                i++;
            }


    return  lBestIndex ;


}
