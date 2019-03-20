#include <iostream>
#include "opencv2/opencv.hpp"
#include "Imaging/Threshold.h"
#include "Imaging/BlobDetector.h"
#include "Utils/Utils.h"
#include "Structures/MyException.h"
#include "Imaging/Classfier.h"
#include "Imaging/Kmeans.h"
#include "BackPropagation/NeuralNetwork.h"

void NeuralNetworkCV();

int main() {
    try {
        /*
        cv::Mat src_8uc1_img;
        src_8uc1_img = cv::imread("../images/train04.png",
                                  cv::IMREAD_GRAYSCALE); // load color image from file system to Mat variable, this will be loaded using 8 bits (uchar)

        if (src_8uc1_img.empty()) {
            printf("Unable to read input file (%s, %d).", __FILE__, __LINE__);
        }


        //cv 1
        cv::imshow("Train", src_8uc1_img);
        Threshold lTH = Threshold(127);

        cv::Mat dest_8uc1_img;
        lTH.Apply(src_8uc1_img, dest_8uc1_img);

        //cv::imshow("Train_thres", dest_8uc1_img);

        BlobDetector lBlobDetect = BlobDetector(dest_8uc1_img);
        //cv::imshow("BlobDetector", lBlobDetect.GetIndexImage());
        lBlobDetect.Indexing();

        //cv 2
        lBlobDetect.CalculateMoments();

        cv::Mat info_img;
        lBlobDetect.ShowInformationImage(info_img);

        cv::namedWindow("Show Info Image", cv::WINDOW_NORMAL);
        cv::imshow("Show Info Image", info_img);

        //cv3 Ethanols
        auto lObjects = lBlobDetect.GetObjects();
        Classfier lClassfier = Classfier();

        std::vector<ImgObject> lTrainSet;
        std::string name[] = {"Ctverec", "Hvezda", "Obdelnik","Kruh"};
        cv::Vec3b colors[] = { cv::Vec3b(255, 0, 0), cv::Vec3b(0, 255, 0), cv::Vec3b(0, 0, 255), cv::Vec3b(0, 255, 255) ,cv::Vec3b(100, 25, 255) };

        int j = 0;

        for(int i = 0; i < lObjects->size();i++){

            lTrainSet.push_back(lObjects->at(i));

            if( (i+1) % 4 == 0)
            {
                lClassfier.AddClass(lTrainSet, name[j], colors[j]);
                j++;

                lTrainSet.clear();
            }


        }

        for (auto  etalon : lClassfier.getClass()) {
            std::cout << "x =" << etalon.getX() << " y=" << etalon.getY() << " " << etalon.getName() << "\n";
        }

        std::cout.flush();



        // KLASIFIKACE

        cv::Mat srcTest_8uc1_img;
        srcTest_8uc1_img = cv::imread("../images/test04.png",
                                  cv::IMREAD_GRAYSCALE); // load color image from file system to Mat variable, this will be loaded using 8 bits (uchar)

        if (srcTest_8uc1_img.empty()) {
            printf("Unable to read input file (%s, %d).", __FILE__, __LINE__);
        }


        Threshold lTHr = Threshold(127);

        cv::Mat destTest_8uc1_img;
        lTH.Apply(srcTest_8uc1_img, destTest_8uc1_img);

        BlobDetector lBlobDetectTest = BlobDetector(destTest_8uc1_img);
        lBlobDetectTest.Indexing();

        //cv 2
        lBlobDetectTest.CalculateMoments();
        lBlobDetectTest.ShowInfo();

        cv::Mat info_img2;
        auto lObjectsTest = lBlobDetectTest.GetObjects();

        for(int i=0;i < lObjectsTest->size();i++){
            lClassfier.Classification(lObjectsTest->at(i));
        }

        lClassfier.ShowInfo(info_img2,lBlobDetectTest.GetObjects(),lBlobDetectTest.getIndexImage());

        cv::namedWindow("Show Info Image2", cv::WINDOW_NORMAL);
        cv::imshow("Show Info Image2", info_img2);

        //K-means

        BlobDetector lBlobDetectTest3 = BlobDetector(destTest_8uc1_img);
        lBlobDetectTest3.Indexing();

        lBlobDetectTest3.CalculateMoments();
        lBlobDetectTest3.ShowInfo();


        auto lObjectsTest3 = lBlobDetectTest3.GetObjects();
        Kmeans Kmeans;

        auto l = Kmeans.Cluster(4,lBlobDetect.GetObjects());

        for(int i=0;i < lObjectsTest3->size();i++){
            lObjectsTest3->at(i).K_meansClass = Kmeans.ClassToObject(lObjectsTest3->at(i));
            std::cout <<  lObjectsTest3->at(i).K_meansClass << std::endl;
            std::cout.flush();
        }


        cv::Mat info_img3;
        Kmeans.ShowInfo(info_img3,l,lBlobDetect.getIndexImage());
        //Kmeans.ShowClassifikation(info_img3,lObjectsTest3,lBlobDetectTest3.getIndexImage());


        cv::namedWindow("Show Info Image3", cv::WINDOW_NORMAL);
        cv::imshow("Show Info Image3", info_img3);
         */

        NeuralNetworkCV();

    }catch(MyException e) {
        std::cout << "EXCEPTION: " << e.what();
    }
    cv::waitKey(0); // wait until keypressed

}
void NeuralNetworkCV() {

    cv::Mat src_8uc1_img;
    src_8uc1_img = cv::imread("../images/train04.png",
                              cv::IMREAD_GRAYSCALE); // load color image from file system to Mat variable, this will be loaded using 8 bits (uchar)

    if (src_8uc1_img.empty()) {
        printf("Unable to read input file (%s, %d).", __FILE__, __LINE__);
    }
    Threshold lTH = Threshold(127);

    cv::Mat dest_8uc1_img;
    lTH.Apply(src_8uc1_img, dest_8uc1_img);
    BlobDetector lBlobDetect = BlobDetector(dest_8uc1_img);
    lBlobDetect.Indexing();

    lBlobDetect.CalculateMoments();
    auto lObjectsTrain = lBlobDetect.GetObjects(); // Train Obj
    NeuralNetwork nn = NeuralNetwork(3,8,4);

    std::vector<std::vector<double>> training_set;
    std::vector<std::vector<double>> R;
    int j = 0;

    for(int i = 0; i < lObjectsTrain->size();i++){

        std::vector<double> lTranObj;
        lTranObj.push_back(lObjectsTrain->at(i).F1);
        lTranObj.push_back(lObjectsTrain->at(i).F2);
        lTranObj.push_back(lObjectsTrain->at(i).F3);

        training_set.push_back(lTranObj);

        std::vector<double> lR;
        for (int k = 0; k < 4 ; ++k) {
            if(k == j)
                lR.push_back(1);
            else
                lR.push_back(0);
        }

        R.push_back(lR);

        if( (i+1) % 4 == 0)
        {
            j++;
        }



    }

    for (int i = 0; i < 10000; ++i) {
        for (int j = 0; j < training_set.size(); ++j) {


            auto input = training_set[j];
            auto output = R[j];

            nn.Train(input, output);


        }
    }

    //Test Train
    for (int j = 0; j < training_set.size(); ++j) {
        auto l = nn.feed_forward(training_set[j]);

        std::cout << nn.MaxIndex(l) << std::endl;
        std::cout.flush();
    }
    //Test Data

    cv::Mat srcTest_8uc1_img;
    srcTest_8uc1_img = cv::imread("../images/test04.png",
                                  cv::IMREAD_GRAYSCALE); // load color image from file system to Mat variable, this will be loaded using 8 bits (uchar)

    if (srcTest_8uc1_img.empty()) {
        printf("Unable to read input file (%s, %d).", __FILE__, __LINE__);
    }


    Threshold lTHr = Threshold(127);

    cv::Mat destTest_8uc1_img;
    lTH.Apply(srcTest_8uc1_img, destTest_8uc1_img);

    BlobDetector lBlobDetectTest = BlobDetector(destTest_8uc1_img);
    lBlobDetectTest.Indexing();

    //cv 2
    lBlobDetectTest.CalculateMoments();
    lBlobDetectTest.ShowInfo();

    cv::Mat info_img2;
    auto lObjectsTest = lBlobDetectTest.GetObjects();

    std::vector<std::vector<double>> lTest;
    for(int i = 0; i < lObjectsTest->size();i++){

        std::vector<double> lTranObj;
        lTranObj.push_back(lObjectsTest->at(i).F1);
        lTranObj.push_back(lObjectsTest->at(i).F2);
        lTranObj.push_back(lObjectsTest->at(i).F3);

        lTest.push_back(lTranObj);


    }
    std::cout << " TEST" << std::endl;
    for (int j = 0; j < lTest.size(); ++j) {

        auto l = nn.MaxIndex(nn.feed_forward(lTest[j]));
        lObjectsTest->at(j).K_meansClass = l;
        std::cout << l << std::endl;
        std::cout.flush();
    }

    Kmeans Kmeans;
    Kmeans.ShowClassifikation(info_img2,lObjectsTest,lBlobDetectTest.getIndexImage());


    cv::namedWindow("Show Info Image3", cv::WINDOW_NORMAL);
    cv::imshow("Show Info Image3", info_img2);


}



