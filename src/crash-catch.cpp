#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Rect cropRect(0,0,0,0);
Point P1(0,0);
Point P2(0,0);
Mat ROI;
bool clicked = false;

void on_mouse( int event, int x, int y, int f, void *ptr ){

    switch(event){
        case CV_EVENT_LBUTTONDOWN:
          clicked=true;
          P1.x=x;
          P1.y=y;
          P2.x=x;
          P2.y=y;
          break;
        case CV_EVENT_LBUTTONUP:
          P2.x=x;
          P2.y=y;
          clicked=false;
          break;
        case CV_EVENT_MOUSEMOVE:
          if(clicked){
          P2.x=x;
          P2.y=y;
          }
          break;
        default:
           break;
    }


    if(clicked) {
     if(P1.x>P2.x){
       cropRect.x=P2.x;
       cropRect.width=P1.x-P2.x;
     } else {
       cropRect.x=P1.x;
       cropRect.width=P2.x-P1.x;
     }

     if(P1.y>P2.y){
       cropRect.y=P2.y;
       cropRect.height=P1.y-P2.y;
     } else {
       cropRect.y=P1.y;
       cropRect.height=P2.y-P1.y;
     }
    }

}


int main(int argc, char* argv[]) {

	//TODO create command line file input
    VideoCapture cap("../data/crash.mp4"); // open the video file for reading
    if ( !cap.isOpened() ) {
         cout << "Cannot open the video file" << endl;
         return -1;
    }

    cap.set(CV_CAP_PROP_POS_MSEC, 37000); //start the video at 25s

    double fps = cap.get(CV_CAP_PROP_FPS); //get the frames per seconds of the video

     cout << "Frame per seconds : " << fps << endl;

     //create windows
    namedWindow("Src Video",CV_WINDOW_NORMAL);
    namedWindow("Inv Video",CV_WINDOW_NORMAL);
    namedWindow("Cropped",CV_WINDOW_NORMAL);
    Mat frame, inv, resized;

    while(cap.read(frame)) {

		//invert video to make num plate clearer
        bitwise_not(frame,inv );
        imshow("Src Video", frame);
        imshow("Inv Video", inv);
        setMouseCallback("Inv Video",on_mouse, &frame );

        if(cropRect.width > 0 && cropRect.height > 0){
            ROI = inv(cropRect);
			//TODO create command line option
			//blur image if needed
            // blur( ROI, ROI, Size( 20, 20 ) );
            for (int y = 0; y < ROI.rows; ++y)
              for (int x = 0; x < ROI.cols; ++x)
              {
                  cv::Vec3b & pixel = ROI.at<cv::Vec3b>(y, x);
                  // if pixel is white
                  if (pixel[0] != 255 && pixel[1] != 255 && pixel[2] != 255)
                  {
                      // set alpha to zero:
                      pixel[0] = 0;
                      pixel[1] = 0;
                      pixel[2] = 0;

                  }
              }
            // GaussianBlur( ROI, ROI, Size( 0, 0 ), 0, 0 );
            imshow("Cropped",ROI);
        }

        char key = waitKey();
        if(key == 'q') {
          break;
        }else if(key == 's') {
			//TODO increment and not overwrite
         imwrite("../data/saved.png", inv);
         cout << "saved" << endl;
        }else if(key == 'r') {
         cout << "rect reset" << endl;
         cropRect.width = 0;
         cropRect.height = 0;
       }

    }

    return 0;

}
