#include <iostream>
#include <string>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/photo.hpp"

using namespace std;
using namespace cv;

int lowThreshold = 0;
const int max_lowThreshold = 100;
const int rat = 3;
const int kernel_size = 3;

Mat src;
Mat dst;
Mat src_bw;
Mat dst_canny;
Mat dst_f;

const char *window_name = "Magic Filter Demo";
const char *trackbar_value = "Blur";
const char *trackbar2_value = "Threshold";
const char *trackbar3_value = "Denoising";

RNG rng(12345);

//int display_dst(const char *caption);

static void Magic_Filter(int, void *)
{
    //blur(src_bw, dst_canny, Size(3, 3));

    Canny(src_bw, dst_canny, lowThreshold, lowThreshold * rat, kernel_size);

    //dst = Scalar::all(0);
    //src.copyTo(dst, dst_canny);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(dst_canny, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    Mat drawing = Mat::zeros(dst_canny.size(), CV_8UC3);
    for (size_t i = 0; i < contours.size(); i++)
    {
        Scalar color = Scalar(rng.uniform(0, 256), rng.uniform(0, 256), rng.uniform(0, 256));
        drawContours(drawing, contours, (int)i, color, 2, LINE_8, hierarchy, 0);
    }
    imshow(window_name, drawing);
    //vector<Point> approx;

    // imshow(window_name, dst);
}

int main(int argc, char **argv)
{

    namedWindow(window_name, WINDOW_AUTOSIZE);

    const char *filename = argc >= 2 ? argv[1] : "examplepic/test4.jpg";

    src = imread(samples::findFile(filename), IMREAD_COLOR); //Load Image
    if (src.empty())
    {
        printf(" Error opening image\n");
        printf(" Usage:\n %s [image_name-- default lena.jpg] \n", argv[0]);
        return EXIT_FAILURE;
    }
    dst = src.clone();

    dst.create(src.size(), src.type());
    cvtColor(src, src_bw, COLOR_BGR2GRAY); //Convert image to gray

    createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, Magic_Filter);

    Magic_Filter(0, 0);
    waitKey();

    return 0;
}