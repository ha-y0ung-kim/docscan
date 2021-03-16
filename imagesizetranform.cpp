#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

Mat src;

const char *window_name = "pic";

vector<Point> pointarray;

void mouse_callback(int event, int x, int y, int, void *param)
{
    if (event == EVENT_LBUTTONDOWN)
    {

        //Mat &src = (*(Mat *)param);
        Point &p = (*(Point *)param);
        p.x = x;
        p.y = y;
        if (pointarray.size() < 4)
        {
            pointarray.push_back(p);
            circle(src, p, 10, Scalar(0, 0, 255), FILLED, 1, 0);
        }

        imshow(window_name, src);
        waitKey();
    }
}

int main(int argc, char **argv)
{

    const char *filename = argc >= 2 ? argv[1] : "examplepic/test4.jpg";
    src = imread(samples::findFile(filename), IMREAD_COLOR); //Load Image
    if (src.empty())
    {
        cout << " Error opening image" << endl;
        cout << " Usage:" << endl
             << argv[0] << " [image_name-- default lena.jpg]" << endl;
        return EXIT_FAILURE;
    }
    namedWindow(window_name, WINDOW_AUTOSIZE);
    Point pt;
    setMouseCallback(window_name, mouse_callback, &pt);

    imshow(window_name, src);
    waitKey();

    cout << pointarray << endl;

    //     int arx[4] = {pointarray.at(0).x, pointarray.at(1).x, pointarray.at(2).x, pointarray.at(3).x};

    //     int ary[4] = {pointarray.at(0).y, pointarray.at(1).y, pointarray.at(2).y, pointarray.at(3).y};

    //     int a = max_element(arx[0], arx+4);

    // //    int b = max_element(ary[0], ary[3]);
    //     cout << a;
}