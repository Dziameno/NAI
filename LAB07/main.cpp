#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
    VideoCapture cap(1); // 0-macbook 1-iphone
    if (!cap.isOpened())
    {
        cout << "Cannot open the web cam" << endl;
        cin.get();
        return -1;
    }

    double dWidth = cap.get(CAP_PROP_FRAME_WIDTH);
    double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT);

    cout << "Resolution of the video : " << dWidth << " x " << dHeight << endl;

    namedWindow("Original", WINDOW_NORMAL);
    namedWindow("Mirrored", WINDOW_NORMAL);

    while (true)
    {
        Mat frame;
        bool bSuccess = cap.read(frame);
        Mat frameMirror;
        flip(frame, frameMirror, 1);

        if (!bSuccess) {
            cout << "Camera stopped working" << endl;
            break;
        }

        imshow("Original", frame);
        imshow("Mirrored", frameMirror);

        if (waitKey(1) == 27) {
            cout << "Esc pressed. Aborting" << endl;
            break;
        }
    }
    return 0;
}
