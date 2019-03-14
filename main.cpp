#include <iostream>
#include "opencv2/opencv.hpp"
#include "Imaging/Threshold.h"
#include "Imaging/BlobDetector.h"
#include "Utils/Utils.h"
#include "Structures/MyException.h"
#include "Imaging/Classfier.h"

int main() {
    try {
        cv::Mat src_8uc1_img;
        src_8uc1_img = cv::imread("../images/train.png",
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
        cv::Vec3b colors[] = { cv::Vec3b(255, 0, 0), cv::Vec3b(0, 255, 0), cv::Vec3b(0, 0, 255), cv::Vec3b(0, 255, 255) };

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
        srcTest_8uc1_img = cv::imread("../images/test02.png",
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

    }catch(MyException e)
    {
        std::cout << "EXCEPTION: " << e.what();
    }
    //cv::Mat gray_8uc1_img; // declare variable to hold grayscale version of img variable, gray levels wil be represented using 8 bits (uchar)
    //cv::Mat gray_32fc1_img; // declare variable to hold grayscale version of img variable, gray levels wil be represented using 32 bits (float)

    //cv::cvtColor(src_8uc3_img, gray_8uc1_img, CV_BGR2GRAY); // convert input color image to grayscale one, CV_BGR2GRAY specifies direction of conversion
    //gray_8uc1_img.convertTo(gray_32fc1_img, CV_32FC1, 1.0 / 255.0); // convert grayscale image from 8 bits to 32 bits, resulting values will be in the interval 0.0 - 1.0

    //int x = 10, y = 15; // pixel coordinates

    //uchar p1 = gray_8uc1_img.at<uchar>(y, x); // read grayscale value of a pixel, image represented using 8 bits
    //float p2 = gray_32fc1_img.at<float>(y, x); // read grayscale value of a pixel, image represented using 32 bits
    //cv::Vec3b p3 = src_8uc3_img.at<cv::Vec3b>(y, x); // read color value of a pixel, image represented using 8 bits per color channel

    //// print values of pixels
    //printf("p1 = %d\n", p1);
    //printf("p2 = %f\n", p2);
    //printf("p3[ 0 ] = %d, p3[ 1 ] = %d, p3[ 2 ] = %d\n", p3[0], p3[1], p3[2]);

    //gray_8uc1_img.at<uchar>(y, x) = 0; // set pixel value to 0 (black)

    //// draw a rectangle
    //cv::rectangle(gray_8uc1_img, cv::Point(65, 84), cv::Point(75, 94),
    //	cv::Scalar(50), CV_FILLED);

    //// declare variable to hold gradient image with dimensions: width= 256 pixels, height= 50 pixels.
    //// Gray levels wil be represented using 8 bits (uchar)
    //cv::Mat gradient_8uc1_img(50, 256, CV_8UC1);

    //// For every pixel in image, assign a brightness value according to the x coordinate.
    //// This wil create a horizontal gradient.
    //for (int y = 0; y < gradient_8uc1_img.rows; y++) {
    //	for (int x = 0; x < gradient_8uc1_img.cols; x++) {
    //		gradient_8uc1_img.at<uchar>(y, x) = x;
    //	}
    //}

    // diplay images

    cv::waitKey(0); // wait until keypressed

}