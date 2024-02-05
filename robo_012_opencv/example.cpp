#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <stdexcept>
#include <chrono>
#include <thread>
#include <csignal>

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

     double fps = cap.get(CAP_PROP_FPS);

     if (fps == 0.0) {
          throw std::invalid_argument("Cannot get fps");
     }

     using namespace std::chrono_literals;


     double period_milliseconds = 1000.0 / fps;

     std::cout << "fps: " << fps << std::endl;
     std::cout << "period_milliseconds: " << period_milliseconds << std::endl;

     while (!is_interrupted) {
          Mat frame;

          // Get time now.
          auto start = std::chrono::high_resolution_clock::now();
          
          if (!cap.read(frame)) {
               std::cout << "End of video" << std::endl;
               break;
          }

          imshow("Display window", frame);

          if (waitKey(10) == 27) {
               std::cout << "Esc key is pressed by user. Stopping the video" << std::endl;
               break;
          }

          // Get time we've spent loading frame in milliseconds.
          auto end = std::chrono::high_resolution_clock::now();

          auto time_to_wait = std::chrono::duration<double, std::milli>(period_milliseconds) - (end - start);


          // If we've spent more time than we should, don't wait.
          if (time_to_wait.count() > 0) {
               std::this_thread::sleep_for(time_to_wait);
          }


     }
     return 0;
}