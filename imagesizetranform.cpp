#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

Mat src;

const char *window_name = "pic";

vector<Point> pointarray;

double get_angle(Point pt0, Point pt1, Point pt2)
{ // calculate angle between three points
    // gives angle at pt0
    double dt0 = pow((pt1.x - pt2.x), 2) + pow((pt1.y - pt2.y), 2);
    double dt1 = pow((pt2.x - pt0.x), 2) + pow((pt2.y - pt0.y), 2);
    double dt2 = pow((pt1.x - pt0.x), 2) + pow((pt1.y - pt0.y), 2);
    return acos((dt1 + dt2 - dt0) / (2 * sqrt(dt1) * sqrt(dt2)));
}

void fourpointsquare(int event, int x, int y, int, void *param)
{
    if (event == EVENT_LBUTTONDOWN)
    {
        Point &p = (*(Point *)param);
        p.x = x;
        p.y = y;
        if (pointarray.size() < 4)
        { // Get four points
            pointarray.push_back(p);
            circle(src, p, 10, Scalar(0, 0, 255), FILLED, 1, 0);
        }

        if (pointarray.size() == 4)
        { // Draw square according to the given four points
            double ang012 = get_angle(pointarray[0], pointarray[1], pointarray[2]);
            double ang013 = get_angle(pointarray[0], pointarray[1], pointarray[3]);
            double ang023 = get_angle(pointarray[0], pointarray[2], pointarray[3]);
            // cout << ang012 << " " << ang013 << " " << ang023 << "\n ";

            array<double, 3> angle0 = {ang023, ang013, ang012};
            // cout << angle0[0] << " " << angle0[1] << " " << angle0[2] << "\n ";

            auto maxang = distance(angle0.begin(), max_element(angle0.begin(), angle0.end()));

            // cout << a << endl;
            // cout << angle0[a];

            line(src, pointarray[0], pointarray[(maxang + 1) % 3 + 1], Scalar(0, 0, 25), 1, 8, 0);
            line(src, pointarray[0], pointarray[(maxang + 2) % 3 + 1], Scalar(0, 0, 25), 1, 8, 0);
            line(src, pointarray[maxang + 1], pointarray[(maxang + 1) % 3 + 1], Scalar(0, 0, 25), 1, 8, 0);
            line(src, pointarray[maxang + 1], pointarray[(maxang + 2) % 3 + 1], Scalar(0, 0, 25), 1, 8, 0);
        }
        imshow(window_name, src);
        waitKey();
    }
}

// void draw_square(int, void *){

// }

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
    setMouseCallback(window_name, fourpointsquare, &pt);

    imshow(window_name, src);
    waitKey();
}
