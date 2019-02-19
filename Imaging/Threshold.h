//
// Created by davelinux on 19.2.19.
//

#ifndef VSB_ANOI_THRESHOLD_H
#define VSB_ANOI_THRESHOLD_H

class Threshold
{
private:
    int mValue;
public:
    Threshold(int aValue) { mValue = aValue; };
    void Apply (cv::Mat &src, cv::Mat  &dest);
    ~Threshold();
};



#endif //VSB_ANOI_THRESHOLD_H
