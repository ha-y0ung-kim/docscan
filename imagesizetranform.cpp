#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace std;
using namespace cv;

Mat src, srcori;

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

            array<double, 3> angle0 = {ang023, ang013, ang012};

            auto maxang = distance(angle0.begin(), max_element(angle0.begin(), angle0.end()));

            line(src, pointarray[0], pointarray[(maxang + 1) % 3 + 1], Scalar(0, 0, 25), 1, 8, 0);
            line(src, pointarray[0], pointarray[(maxang + 2) % 3 + 1], Scalar(0, 0, 25), 1, 8, 0);
            line(src, pointarray[maxang + 1], pointarray[(maxang + 1) % 3 + 1], Scalar(0, 0, 25), 1, 8, 0);
            line(src, pointarray[maxang + 1], pointarray[(maxang + 2) % 3 + 1], Scalar(0, 0, 25), 1, 8, 0);
        }
        imshow(window_name, src);
        waitKey();
    }
}

array<Point, 4> odersquarepoints(vector<Point> ptarray)
{
    // put the Four edge point in oder
    //  1 ┏━━━┓ 2
    //    ┃   ┃
    //  4 ┗━━━┛ 3
    array<Point, 4> oderedpoint;

    array<int, 4> xpoints = {ptarray[0].x, ptarray[1].x, ptarray[2].x, ptarray[3].x};
    auto a = distance(xpoints.begin(), min_element(xpoints.begin(), xpoints.end()));
    oderedpoint[0] = ptarray[a];
    xpoints[a] = src.cols;
    a = distance(xpoints.begin(), min_element(xpoints.begin(), xpoints.end()));
    if (oderedpoint[0].y > ptarray[a].y)
    {
        oderedpoint[3] = oderedpoint[0];
        oderedpoint[0] = ptarray[a];
    }
    else
    {
        oderedpoint[3] = ptarray[a];
    }

    xpoints = {ptarray[0].x, ptarray[1].x, ptarray[2].x, ptarray[3].x};
    a = distance(xpoints.begin(), max_element(xpoints.begin(), xpoints.end()));
    oderedpoint[1] = ptarray[a];
    xpoints[a] = 0;
    a = distance(xpoints.begin(), max_element(xpoints.begin(), xpoints.end()));
    if (oderedpoint[1].y > ptarray[a].y)
    {
        oderedpoint[2] = oderedpoint[1];
        oderedpoint[1] = ptarray[a];
    }
    else
    {
        oderedpoint[2] = ptarray[a];
    }
    return oderedpoint;
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
    srcori = src.clone();
    namedWindow(window_name, WINDOW_AUTOSIZE);

    Point pt;
    // Get the four edge points of the document
    setMouseCallback(window_name, fourpointsquare, &pt);

    imshow(window_name, src);
    waitKey();

    // put the Four edge point in oder
    array<Point, 4> oderedpoint;
    oderedpoint = odersquarepoints(pointarray);

    // Transform the image according to the edge points of the document
    Point2f srcpoint[4];
    Point2f dstpoint[4];

    Mat lambda(2, 4, CV_32FC1);
    Mat dst;

    lambda = Mat::zeros(src.rows, src.cols, src.type());
    for (int i = 0; i < 4; i++)
    {
        srcpoint[i] = Point2f(oderedpoint[i].x, oderedpoint[i].y);
    }

    dstpoint[0] = Point2f(0, 0);
    dstpoint[1] = Point2f(src.cols, 0);
    dstpoint[2] = Point2f(src.cols, src.rows);
    dstpoint[3] = Point2f(0, src.rows);

    lambda = getPerspectiveTransform(srcpoint, dstpoint);
    warpPerspective(srcori, dst, lambda, dst.size());

    imshow(window_name, dst);
    waitKey();
}
