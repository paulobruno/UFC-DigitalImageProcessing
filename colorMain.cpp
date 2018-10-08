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
    rgbToCmy(img, cmyImg);

    cv::Mat hsiImg;
    rgbToCmy(img, hsiImg);
    
    cv::Mat sepiaImg;
    sepiaFilter(img, sepiaImg);
    cv::imshow("Sepia", sepiaImg);
    
    cv::Mat matA = cv::imread("soccer.jpg", cv::IMREAD_COLOR);
    cv::Mat matB = cv::imread("americanFootball.jpg", cv::IMREAD_COLOR);    
    cv::Mat subtractImg;
    imageSubtraction(matA, matB, subtractImg);
    cv::imshow("Subtraction", subtractImg);
    
    cv::Mat threshImg;
    thresholding(img, threshImg, 80);
    cv::imshow("Threshold", threshImg);
    
    cv::Mat chromaImg = cv::imread("chroma_key.jpg", cv::IMREAD_COLOR);
    cv::Vec3b key = {90, 160, 170};
    cv::Mat keyedMat;
    chromaKeying(chromaImg, keyedMat, key, 20);
    cv::imshow("Chroma Key", keyedMat);
    
    cv::Mat brightMat;
    adjustBrightness(img, brightMat, 50);
    cv::imshow("Bright", brightMat);

    cv::Mat contrastMat;
    adjustContrast(img, contrastMat, 0.5f);
    cv::imshow("Contrast", contrastMat);

    cv::Mat brightContrastMat;
    adjustBrightAndContrast(img, brightContrastMat, 0.5f, 50);
    cv::imshow("Bright and Contrast", brightContrastMat);
    
	cv::waitKey();
	

	return 0;
}
