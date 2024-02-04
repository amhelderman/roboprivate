#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
int main()
{
    Mat img(200, 200, CV_8UC3, Scalar(0, 0, 0));

    Scalar color = Scalar(255, 0, 0);
    circle(img, Point(30, 30), 10, color, 3);

    imshow("Display window", img);
    int k = waitKey(0); // Wait for a keystroke in the window
    return 0;
}