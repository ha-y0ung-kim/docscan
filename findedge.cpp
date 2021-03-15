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

//int display_dst(const char *caption);

static void Magic_Filter(int, void *)
{

    Canny(dst, dst_canny, lowThreshold, lowThreshold * rat, kernel_size);

    dst_f = Scalar::all(0);
    src.copyTo(dst_f, dst_canny);

    /* vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(dst_canny, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);

    vector<Point> approx;
 */
    imshow(window_name, dst_f);
}

int main(int argc, char **argv)
{

    namedWindow(window_name, WINDOW_AUTOSIZE);

    const char *filename = argc >= 2 ? argv[1] : "examplepic/test1.jpg";

    src = imread(samples::findFile(filename), IMREAD_COLOR); //Load Image
    if (src.empty())
    {
        printf(" Error opening image\n");
        printf(" Usage:\n %s [image_name-- default lena.jpg] \n", argv[0]);
        return EXIT_FAILURE;
    }
    dst = src.clone();

    for (int i = 1; i < 14; i = i + 2)
    {
        GaussianBlur(src, dst, Size(i, i), 0, 0);
    }

    cvtColor(dst, src_bw, COLOR_BGR2GRAY); //Convert image to gray

    for (int i = 3; i < 7; i = i + 2)
    {
        adaptiveThreshold(src_bw, dst, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, i, 2);
    }

    createTrackbar("Min Threshold:", window_name, &lowThreshold, max_lowThreshold, Magic_Filter);

    Magic_Filter(0, 0);
    waitKey();

    return 0;
}