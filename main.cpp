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

Mat src;
Mat dst;

const char *window_name = "Blur Demo";
const char *trackbar_type = "Type: \n 0: Homogeneous \n 1: Gaussian \n 2: median_blur \n 3: Bilateral_Blur";
const char *trackbar_value = "Value";

int display_dst(const char *caption);

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

int main(int argc, char **argv)
{
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
