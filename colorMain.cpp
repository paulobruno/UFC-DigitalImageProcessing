#include <string>
#include <opencv2/opencv.hpp>
#include <vector>

#include "coloring.h"


int main(int argc, const char** argv)
{
    if (2 > argc)
    {
        std::cout << "Error: incorrect number of args.\n"
				   << "Usage: " << argv[0] << " <image>\n";
            return -1;
    }

    std::string filename(argv[1]);

    cv::Mat img = cv::imread(filename, cv::IMREAD_COLOR);

    if (img.empty())
    {
        std::cerr << "Error: Cannot read " << filename << "\n";
        return -1;
    }


    cv::imshow(filename, img); // Imagem original
    cv::Mat cmyImg;
    rgbToCmy(img, cmyImg); // teste
    cv::imshow("rgbCmy", cmyImg);

    cv::Mat rgbFromCmyImg;
    cmyToRgb(cmyImg, rgbFromCmyImg);
    cv::imshow("cmyRgb", rgbFromCmyImg);

/*
    cv::Mat hsiImg;
    rgbToCmy(img, hsiImg);

    cv::Mat sepiaImg;
    sepiaFilter(img, sepiaImg);
    cv::imshow("Sepia", sepiaImg);
*/

    cv::waitKey();


    return 0;
}
