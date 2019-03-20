//
// Created by daveliinux on 19.3.19.
//

#include <vector>
#include "../Structures/ImgObject.h"
#include "../Structures/Centroid.h"
#ifndef VSB_ANOI_KMEANS_H
#define VSB_ANOI_KMEANS_H


class Kmeans {
private:
    std::vector<Centroid> _Centroids;
    bool Contains(std::vector<Centroid> aCentroids,Centroid Centroid);
    std::map<int,std::vector<ImgObject>*> Process(std::vector<ImgObject>* aData,std::vector<Centroid> aCentroids);
    std::map<int,std::vector<ImgObject>*>  ParallelGetCenterAssignments(std::vector<ImgObject>* aPoints, std::vector<Centroid> aCenters);
    std::vector<Centroid> ParallelGetNewCenters(std::map<int,std::vector<ImgObject>*>  aCenterAssignments,int NumCentorid);
    bool CentersEqual(std::vector<Centroid>  aNewCenters,std::vector<Centroid>  aOldCenters);
public:
    std::map<int,std::vector<ImgObject>*> Cluster(int aClusters,std::vector<ImgObject>* aData);
    void ShowInfo(cv::Mat &Dest, std::map<int,std::vector<ImgObject>*> Objects,cv::Mat IndexImage);
    int ClassToObject(ImgObject& aObject);
    void ShowClassifikation(cv::Mat &Dest, std::vector<ImgObject>* Objects,cv::Mat IndexImage);

};


#endif //VSB_ANOI_KMEANS_H


