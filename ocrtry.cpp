#include <string>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
    char *outText;

    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    // Initialize tesseract-ocr with English, without specifying tessdata path
    if (api->Init(NULL, "eng"))
    {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    // Open input image with leptonica library
    Pix *image = pixRead("/usr/src/tesseract/testing/phototest.tif");
    api->SetImage(image);
    // Get OCR result
    outText = api->GetUTF8Text();
    printf("OCR output:\n%s", outText);

    // Destroy used object and release memory
    api->End();
    delete api;
    delete[] outText;
    pixDestroy(&image);

    return 0;
    // const char *filename = argc >= 2 ? argv[1] : "examplepic/receipt.png";
    // Mat im = imread(samples::findFile(filename), IMREAD_COLOR); //Load Image

    // string outText, imPath = argv[1];
    // //Mat im = cv::imread(imPath, IMREAD_COLOR);

    // tesseract::TessBaseAPI *ocr = new tesseract::TessBaseAPI();
    // ocr->Init(NULL, "eng", tesseract::OEM_LSTM_ONLY);
    // ocr->SetPageSegMode(tesseract::PSM_AUTO);
    // ocr->SetImage(im.data, im.cols, im.rows, 3, im.step);
    // outText = string(ocr->GetUTF8Text());
    // cout << outText;
    // ocr->End();
    // return 0;
}