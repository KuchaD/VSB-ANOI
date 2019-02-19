#include <iostream>
#include "opencv2/opencv.hpp"

int main() {
    cv::Mat open;
    open = cv::Mat::zeros(100,100,CV_8U);
    cv::imshow("test",open);

    cv::waitKey();
    return 0;
}
