cmake_minimum_required(VERSION 3.13)
project(VSB_ANOI)

set(CMAKE_CXX_STANDARD 17)

add_executable(VSB_ANOI main.cpp Utils/Utils.cpp Utils/Utils.h Imaging/Threshold.cpp Imaging/Threshold.h Imaging/BlobDetector.cpp Imaging/BlobDetector.h Structures/ImgObject.cpp Structures/ImgObject.h Structures/Point.cpp Structures/Point.h Structures/MyException.cpp Structures/MyException.h)


find_package( OpenCV REQUIRED )
target_link_libraries(VSB_ANOI ${OpenCV_LIBS} )

