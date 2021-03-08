#include <iostream>
#include <string>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"

using namespace std;
using namespace cv;

int DELAY_CAPTION = 1500;
int DELAY_BLUR = 100;
int MAX_KERNEL_LENGTH = 31;

Mat src;
Mat dst;

int display_dst(const char *caption);

int main(int argc, char **argv)
{
    const char *filename = argc >= 2 ? argv[1] : "lena.jpg";
    src = imread(samples::findFile(filename), IMREAD_COLOR);
    if (src.empty())
    {
        printf(" Error opening image\n");
        printf(" Usage:\n %s [image_name-- default lena.jpg] \n", argv[0]);
        return EXIT_FAILURE;
    }

    dst = src.clone();

    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
    {
        blur(src, dst, Size(i, i), Point(-1, -1));
        if (display_dst("homogeneous blur") != 0)
        {
            return 0;
        }
    }
    /*

    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
    {
        GaussianBlur(src, dst, Size(i, i), 0, 0);
        if (display_dst("Gaussian_Blur") != 0)
        {
            return 0;
        }
    }
    

    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
    {
        medianBlur(src, dst, i);
        if (display_dst("median_blur") != 0)
        {
            return 0;
        }
    }

    for (int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2)
    {
        bilateralFilter(src, dst, i, i * 2, i / 2);
        if (display_dst("Bilateral_Blur") != 0)
        {
            return 0;
        }
    } */

    return 0;
}

int display_dst(const char *caption)
{
    string filename = caption;
    filename = filename + ".jpg";
    imwrite(filename, dst);
    return 0;
}
