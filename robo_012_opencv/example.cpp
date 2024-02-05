#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
 #include "opencv2/imgproc/imgproc.hpp" // Gaussian Blur, Canny
#include <iostream>
#include <stdexcept>
#include <chrono>
#include <thread>
#include <csignal>

using namespace cv;

const std::string WINDOW_NAME = "Video";
const std::string VIDEO_PATH = "/pwd/sample.webm";


VideoCapture getVideo() {

     VideoCapture cap(VIDEO_PATH); 

     if (cap.isOpened() == false)  
     {
          throw std::invalid_argument("Cannot open the video file");
     }

     return cap;
}

void handleMouseEvent(int event, int x, int y, int flags, void* userdata)
{
     if  ( event == EVENT_LBUTTONDOWN )
     {
          std::cout << "Clicked at " << x << "  " << y  << std::endl;
     }
}

Mat frameWithCircle() {

    Mat img(200, 200, CV_8UC3, Scalar(0, 0, 0));

    Scalar color = Scalar(255, 0, 0);
    circle(img, Point(30, 30), 10, color, 3);
    
    return img;
}


Mat blur(Mat frame) {
     Mat blurred_frame;
     GaussianBlur(frame, blurred_frame, Size(15, 15), 0);
     return blurred_frame;
}

Mat rotate(Mat frame) {
     Mat out;
     int width, height = frame.size().width, frame.size().height;
     Mat matRotation = getRotationMatrix2D( Point(width, height, (45 - 180), 1 );
     warpAffine( frame, out, matRotation, frame.size() );
     return frame;
}

int main()
{
     using namespace std::chrono_literals;

     imshow(WINDOW_NAME, frameWithCircle());

     setMouseCallback(WINDOW_NAME, handleMouseEvent, NULL);

     VideoCapture cap = getVideo();

     double fps = cap.get(CAP_PROP_FPS);

     if (fps == 0.0) {
          throw std::invalid_argument("Cannot get fps");
     }

     double period_milliseconds = 1000.0 / fps;

     std::cout << "fps: " << fps << std::endl;
     std::cout << "period_milliseconds: " << period_milliseconds << std::endl;

     while (true) {
          Mat frame;

          // Get time now.
          auto start = std::chrono::high_resolution_clock::now();
          
          if (!cap.read(frame)) {
               std::cout << "End of video" << std::endl;
               break;
          }
          if (waitKey(1) == 27) {
               std::cout << "Esc key is pressed by user. Stopping the video" << std::endl;
               break;
          }

          imshow(WINDOW_NAME, rotate(blur(frame)));

          auto end = std::chrono::high_resolution_clock::now();
          auto time_to_wait = std::chrono::duration<double, std::milli>(period_milliseconds) - (end - start);

          // If we've spent more time than we should, don't wait.
          if (time_to_wait.count() > 0) {
               std::this_thread::sleep_for(time_to_wait);
          }


     }
     return 0;
}