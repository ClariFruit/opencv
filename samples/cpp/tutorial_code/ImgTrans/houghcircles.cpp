/**
 * @file houghcircles.cpp
 * @brief This program demonstrates circle finding with the Hough transform
 */
#include <string>
#include <sstream>
#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;
using namespace std;

template <typename T>
std::string ToString(T val)
{
    std::stringstream stream;
    stream << val;
    return stream.str();
}

int main(int argc, char** argv)
{
    Mat img = Mat(100, 100, CV_8U, Scalar(0));
    circle(img, Point(30, 30), 20, Scalar(200));
    circle(img, Point(70, 70), 20, Scalar(100));

    bool returnSupports = true;

    //![houghcircles]
    vector<Vec4f> circles;
    HoughCircles(img, circles, HOUGH_GRADIENT, 1,
                 img.rows/16,  // change this value to detect circles with different distances to each other
                 100, 1, 1, 30, // change min_radius & max_radius to detect larger circles
                 img, // custom edges
                 returnSupports
    );
    //![houghcircles]

    for(int i = 0; i < 2; i++) {
        std::cout << circles[i] << std::endl;
    }

    return 0;
}
