#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {

    VideoCapture cap(0); // 0-macbook 1-iphone
    if (!cap.isOpened())
    {
        cout << "Cannot open the web cam" << endl;
        cin.get();
        return -1;
    }


    namedWindow("Original", WINDOW_NORMAL);
    namedWindow("Mirrored", WINDOW_NORMAL);

    while (true)
    {
        Mat frame, thresh, contour_img, new_img;
        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;


        bool bSuccess = cap.read(frame);
        Mat frameMirror;
        flip(frame, frameMirror, 1);

        if (!bSuccess) {
            cout << "Camera stopped working" << endl;
            break;
        }

//        imshow("Original", frame);
        imshow("Mirrored", frameMirror);

        if (waitKey(1) == 27) {
            cout << "Esc pressed. Aborting" << endl;
            break;
        }

        chrono::steady_clock::time_point start = chrono::steady_clock::now();

        cvtColor(frameMirror, thresh, COLOR_BGR2GRAY);
        threshold(thresh, thresh, 150, 255, THRESH_BINARY);
        findContours(thresh, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
        contour_img = Mat::zeros(thresh.size(), CV_8UC3);
        drawContours(frameMirror, contours, -1, Scalar(0, 255, 0), 3);


        chrono::steady_clock::time_point end = chrono::steady_clock::now();

        imshow("Contours", frameMirror);

        cout << chrono::duration_cast<chrono::milliseconds>(end- start).count() << "ms" << endl;
    }
    return 0;
}
