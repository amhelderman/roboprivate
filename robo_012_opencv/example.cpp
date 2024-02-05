#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdexcept>

using namespace cv;


VideoCapture setupVideo() {
      //open the video file for reading
     VideoCapture cap("/pwd/sample.webm"); 

     // if not success, exit program
     if (cap.isOpened() == false)  
     {
          throw std::invalid_argument("Cannot open the video file");
     }

     return cap;
}

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
     if  ( event == EVENT_LBUTTONDOWN )
     {
          std::cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
     }
     else if  ( event == EVENT_RBUTTONDOWN )
     {
          std::cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
     }
     else if  ( event == EVENT_MBUTTONDOWN )
     {
          std::cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
     }
     else if ( event == EVENT_MOUSEMOVE )
     {
          std::cout << "Mouse move over the window - position (" << x << ", " << y << ")" << std::endl;

     }
}

Mat frameWithCircle() {

    Mat img(200, 200, CV_8UC3, Scalar(0, 0, 0));

    Scalar color = Scalar(255, 0, 0);
    circle(img, Point(30, 30), 10, color, 3);
    
    return img;
}

int main()
{


     imshow("Display window", frameWithCircle());
     setMouseCallback("Display window", CallBackFunc, NULL);

     VideoCapture cap = setupVideo();

     while (true) {
          Mat frame;
          
          if (!cap.read(frame)) {
               std::cout << "End of video" << std::endl;
               break;
          }

          imshow("Display window", frame);

          if (waitKey(10) == 27) {
               std::cout << "Esc key is pressed by user. Stopping the video" << std::endl;
               break;
          }
          
     }
     return 0;
}