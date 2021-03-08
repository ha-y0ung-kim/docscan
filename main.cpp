#include <iostream>
#include <string>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

int BLUR_TYPE = 0;
int MAX_TYPE = 3;
int BLUR_VALUE = 0;
int MAX_VALUE = 100;

int THRESHOLD_VALUE = 0;
int THRESHOLD_TYPE = 0;
int const MAX_THR_VALUE = 255;
int const MAX_THR_TYPE = 6;
int const MAX_BINARY_VALUE = 255;

Mat src;
Mat dst;
Mat src_bw;

const char *window_name = "Blur Demo";
const char *trackbar_type = "Type: \n 0: Homogeneous \n 1: Gaussian \n 2: median_blur \n 3: Bilateral_Blur";
const char *trackbar_value = "Value";

const char *window2_name = "Threshold Demo";
const char *trackbar2_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted \n 5: adaptive mean \n 6: adaptive gaussian";
const char *trackbar2_value = "Value";

//int display_dst(const char *caption);

static void Blur_Demo(int, void *)
{
    dst = src.clone();

    if (BLUR_TYPE == 0)
    {
        for (int i = 1; i < BLUR_VALUE; i = i + 2)
        {
            blur(src, dst, Size(i, i), Point(-1, -1));
        }
    }

    if (BLUR_TYPE == 1)
    {
        for (int i = 1; i < BLUR_VALUE; i = i + 2)
        {
            GaussianBlur(src, dst, Size(i, i), 0, 0);
        }
    }
    if (BLUR_TYPE == 2)
    {
        for (int i = 1; i < BLUR_VALUE; i = i + 2)
        {
            medianBlur(src, dst, i);
        }
    }
    if (BLUR_TYPE == 3)
    {
        for (int i = 1; i < BLUR_VALUE; i = i + 2)
        {
            bilateralFilter(src, dst, i, i * 2, i / 2);
        }
    }
    imshow(window_name, dst);
}

static void Threshold_Demo(int, void *)
{
    dst = src_bw.clone();

    if (THRESHOLD_TYPE <= 4)
    {
        /* 0: Binary
     1: Binary Inverted
     2: Threshold Truncated
     3: Threshold to Zero
     4: Threshold to Zero Inverted
    */
        threshold(src_bw, dst, THRESHOLD_VALUE, MAX_BINARY_VALUE, THRESHOLD_TYPE);
    }
    else if (THRESHOLD_TYPE == 5)
    {
        for (int i = 1; i < THRESHOLD_VALUE; i = i + 2)
        {
            adaptiveThreshold(src_bw, dst, MAX_THR_VALUE, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, i, 0);
        }
    }
    else if (THRESHOLD_TYPE == 6)
    {
        for (int i = 1; i < THRESHOLD_VALUE; i = i + 2)
        {
            adaptiveThreshold(src_bw, dst, MAX_THR_VALUE, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, i, 0);
        }
    }
    imshow(window2_name, dst);
}

int main(int argc, char **argv)
{
    // For blur
    namedWindow(window_name, WINDOW_AUTOSIZE);
    createTrackbar(trackbar_type, window_name, &BLUR_TYPE, MAX_TYPE, Blur_Demo);
    createTrackbar(trackbar_value, window_name, &BLUR_VALUE, MAX_VALUE, Blur_Demo);

    const char *filename = argc >= 2 ? argv[1] : "lena.jpg";

    src = imread(samples::findFile(filename), IMREAD_COLOR); //Load Image
    if (src.empty())
    {
        printf(" Error opening image\n");
        printf(" Usage:\n %s [image_name-- default lena.jpg] \n", argv[0]);
        return EXIT_FAILURE;
    }

    cvtColor(src, src_bw, COLOR_BGR2GRAY); //Convert image to gray

    namedWindow(window2_name, WINDOW_AUTOSIZE);
    createTrackbar(trackbar2_type, window2_name, &THRESHOLD_TYPE, MAX_THR_TYPE, Threshold_Demo);    // Create a Trackbar to choose type of Threshold
    createTrackbar(trackbar2_value, window2_name, &THRESHOLD_VALUE, MAX_THR_VALUE, Threshold_Demo); // Create a Trackbar to choose Threshold value
    Threshold_Demo(0, 0);

    Blur_Demo(0, 0);
    waitKey();

    return 0;
}

// int display_dst(const char *caption)
// {
//     string filename = caption;
//     filename = filename + ".jpg";
//     imwrite(filename, dst);
//     return 0;
// }
