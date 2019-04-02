/**
 * @file houghcircles.cpp
 * @brief This program demonstrates circle finding with the Hough transform
 */
#include <string>
#include <sstream>
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
    //![load]
    const char* filename = argc >=2 ? argv[1] : "../data/smarties.png";

    // Loads an image
    Mat src = imread( filename, IMREAD_COLOR );

    // Check if image is loaded fine
    if(src.empty()){
        printf(" Error opening image\n");
        printf(" Program Arguments: [image_name -- default %s] \n", filename);
        return -1;
    }
    //![load]

    //![convert_to_gray]
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);
    //![convert_to_gray]

    //![reduce_noise]
    medianBlur(gray, gray, 5);
    //![reduce_noise]
    bool returnSupports = true;

    //![houghcircles]
    vector<Vec4f> circles;
    HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
                 gray.rows/16,  // change this value to detect circles with different distances to each other
                 100, 30, 1, 30, // change min_radius & max_radius to detect larger circles
                 gray, // custom edge source
                 returnSupports
    );
    //![houghcircles]

    //![draw]
    for( size_t i = 0; i < circles.size(); i++ )
    {
        Vec4f c = circles[i];
        Point center = Point(c[0], c[1]);
        // circle center
        circle( src, center, 1, Scalar(0,100,100), 3, LINE_AA);
        // circle outline
        int radius = c[2];
        circle( src, center, radius, Scalar(255,0,255), 3, LINE_AA);

        size_t support = c[3];
        cv::putText( src, ToString(support), center, FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0,255,255), 2 );
    }
    //![draw]

    //![display]
    imshow("detected circles", src);
    waitKey();
    //![display]

    return 0;
}
