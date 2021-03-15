#include <iostream>
#include <string>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/photo.hpp"

using namespace std;
using namespace cv;

int BLUR_VALUE = 0;
int MAX_VALUE = 100;

int THRESHOLD_VALUE = 0;
int const MAX_THR_VALUE = 255;

int DENOISE_VALUE = 0;
int const MAX_DN_VALUE = 255;

Mat src;
Mat dst;
Mat src_bw;

string window_name = "Magic Filter Demo";
string trackbar_value = "Blur";
string trackbar2_value = "Threshold";
string trackbar3_value = "Denoising";

//int display_dst(const char *caption);

static void Magic_Filter(int, void *)
{
    dst = src.clone();

    for (int i = 1; i < BLUR_VALUE; i = i + 2)
    {
        GaussianBlur(src, dst, Size(i, i), 0, 0);
    }

    cvtColor(dst, src_bw, COLOR_BGR2GRAY); //Convert image to gray

    for (int i = 3; i < THRESHOLD_VALUE; i = i + 2)
    {
        adaptiveThreshold(src_bw, dst, MAX_THR_VALUE, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, i, 2);
    }
    // for (int i = 3; i < DENOISE_VALUE; i = i + 2)
    // {
    //     fastNlMeansDenoising(dst, dst, i, 7, 21);
    // }

    imshow(window_name, dst);
}

int main(int argc, char **argv)
{

    namedWindow(window_name, WINDOW_AUTOSIZE);
    createTrackbar(trackbar_value, window_name, &BLUR_VALUE, MAX_VALUE, Magic_Filter);
    createTrackbar(trackbar2_value, window_name, &THRESHOLD_VALUE, MAX_THR_VALUE, Magic_Filter); // Create a Trackbar to choose Threshold value
    createTrackbar(trackbar3_value, window_name, &DENOISE_VALUE, MAX_DN_VALUE, Magic_Filter);    // Create a Trackbar to choose Threshold value

    string filename = argc >= 2 ? argv[1] : "lena.jpg";

    src = imread(samples::findFile(filename), IMREAD_COLOR); //Load Image
    if (src.empty())
    {
        cout << " Error opening image" << endl;
        cout << " Usage:" << endl << argv[0] << " [image_name-- default lena.jpg]" << endl;
        return EXIT_FAILURE;
    }

    Magic_Filter(0, 0);
    waitKey();

    return 0;
}