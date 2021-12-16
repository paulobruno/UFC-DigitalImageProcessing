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

    cv::Mat rgbImg;
    cmyToRgb(cmyImg, rgbImg);
    cv::imshow("cmyRgb", rgbImg);


    cv::Mat hsiImg;
    rgbToHsi(img, hsiImg);
    cv::imshow("rgbHsi", hsiImg);

    cv::Mat rgbFromHsiImg;
    hsiToRgb(hsiImg, rgbFromHsiImg); // FL: peguei a matriz em hsi para devolver os valores em rgb
    cv::imshow("hsiRgb", rgbFromHsiImg);

    cv::Mat cmyFromHsiImg;
    hsiToCmy(img, cmyFromHsiImg);
    cv::imshow("hsiCmy", cmyFromHsiImg);

    cv::Mat hsiFromCmyImg;
    cmyToHsi(img, hsiFromCmyImg);
    cv::imshow("cmyHsi", hsiFromCmyImg);

    cv::Mat sepiaImg;
    sepiaFilter(img, sepiaImg);
    cv::imshow("Sepia", sepiaImg);

    cv::Mat chromaImg = cv::imread("chroma_key.jpg", cv::IMREAD_COLOR);
    cv::Mat keyedMat;
    cv::Vec3b key = {25, 175, 55};
    cv::Vec3b pEpsilon = {25, 80, 25};
    chromaKeying(chromaImg, keyedMat, key, pEpsilon);
    cv::imshow("Chroma Key", keyedMat);

    cv::waitKey();


    return 0;
}
