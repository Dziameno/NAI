#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv) {

    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        cout << "Cannot open the web cam" << endl;
        cin.get();
        return -1;
    }

    while (true) {

        Mat frame,frameMirror, hsv, mask, result;
        vector<vector<Point>> contours;
        vector<Vec4i> hierarchy;

        bool bSuccess = cap.read(frame);
        flip(frame, frameMirror, 1);

        if (!bSuccess) {
            cout << "Camera stopped working" << endl;
            break;
        }

        cvtColor(frameMirror, hsv, COLOR_BGR2HSV);
        inRange(hsv, Scalar(100, 150, 0), Scalar(140, 255, 255), mask);
        findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        sort(contours.begin(), contours.end(), [](const vector<Point>& c1, const vector<Point>& c2) {
            return contourArea(c1, false) > contourArea(c2, false);
            });


        if (contours.size() > 1) {
            Rect rect1 = boundingRect(contours[0]);
            Rect rect2 = boundingRect(contours[1]);
            rectangle(frameMirror, rect1, Scalar(0, 255, 0), 2);
            rectangle(frameMirror, rect2, Scalar(0, 255, 0), 2);


            Point point1 = Point(rect1.x + rect1.width / 2, rect1.y + rect1.height / 2 + 20);
            Point point2 = Point(rect1.x + rect1.width / 2, rect1.y + rect1.height / 2 -20);
            Point point3 = Point(rect2.x + rect2.width / 2, rect2.y + rect2.height / 2 -20);
            Point point4 = Point(rect2.x + rect2.width / 2, rect2.y + rect2.height / 2 + 20);


            circle(frameMirror, point1, 5, Scalar(0, 0, 255), -1);
            circle(frameMirror, point2, 5, Scalar(0, 0, 255), -1);
            circle(frameMirror, point3, 5, Scalar(0, 0, 255), -1);
            circle(frameMirror, point4, 5, Scalar(0, 0, 255), -1);
            

            if (point1.y - point4.y > -5 && point2.y - point3.y < 5) {
                line(frameMirror, point1, point4, Scalar(0, 0, 255), 2);
                line(frameMirror, point2, point3, Scalar(0, 0, 255), 2);
            }


        }

        imshow("Webcam", frameMirror);

        if (waitKey(1) == 27) {
            cout << "Esc pressed. Aborting" << endl;
            break;
        }

    }

    return 0;
}
