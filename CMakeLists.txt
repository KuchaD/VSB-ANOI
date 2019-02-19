cmake_minimum_required(VERSION 3.13)
project(VSB_ANOI)

set(CMAKE_CXX_STANDARD 17)

add_executable(VSB_ANOI main.cpp)


find_package( OpenCV REQUIRED )
target_link_libraries(VSB_ANOI ${OpenCV_LIBS} )

