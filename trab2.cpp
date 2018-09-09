#include <string>
#include <opencv2/opencv.hpp>
#include <vector>

#include "convolution.h"


int main(int argc, const char** argv)
{
	if (2 > argc)
	{
		std::cout << "Error: incorrect number of args.\n"
				   << "Usage: " << argv[0] << " <image>\n";
		return -1;
	}

	std::string filename(argv[1]);

	cv::Mat img = cv::imread(filename, cv::IMREAD_GRAYSCALE);

	if (img.empty())
	{
		std::cerr << "Error: Cannot read " << filename << "\n";
		return -1;
	}

	cv::imshow(filename, img); // Imagem original


    int sobelValues[9] = { 1,  2,  1,
                           0,  0,  0,
                          -1, -2, -1};
    cv::Mat sobelMask = cv::Mat(3, 3, CV_32S, sobelValues);
    
    cv::Mat sobelImg;
    conv2d(img, sobelMask, sobelImg);
    
    cv::imshow("sobel", sobelImg);
    
    
    int wAvgValues[9] = {2, 4, 2,
                         4, 8, 4,
                         2, 4, 2};
    cv::Mat wAvgMask = cv::Mat(3, 3, CV_32S, wAvgValues);
    
    cv::Mat wAvgImg;
    weightedConv2d(img, wAvgMask, wAvgImg);
    
    cv::imshow("wAvg", wAvgImg);


    cv::waitKey();
    

    return EXIT_SUCCESS;
}
