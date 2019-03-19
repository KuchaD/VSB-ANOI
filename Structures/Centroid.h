//
// Created by daveliinux on 19.3.19.
//

#ifndef VSB_ANOI_CENTROID_H
#define VSB_ANOI_CENTROID_H


class Centroid {
public:
    double X;
    double Y;
    double Z;

    Centroid();
    Centroid(double X,double Y,double Z)
    {
        this->X = X;
        this->Y = Y;
        this->Z = Z;

    }
};


#endif //VSB_ANOI_CENTROID_H
