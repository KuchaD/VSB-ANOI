//
// Created by davelinux on 23.2.19.
//

#ifndef VSB_ANOI_POINT_H
#define VSB_ANOI_POINT_H

template<class T>
class Point {
public:
    Point<T>() {

    }

    Point<T>(T x,T y)
            {
        X = x;
        Y = y;
            }

    T X;
    T Y;
};



#endif //VSB_ANOI_POINT_H
