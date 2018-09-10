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
	
	
    // Imagem original
	cv::imshow(filename, img);


    // Average
    int averageValues[25] = {1, 1, 1, 1, 1,
                             1, 1, 1, 1, 1,
                             1, 1, 1, 1, 1,
                             1, 1, 1, 1, 1,
                             1, 1, 1, 1, 1};
    cv::Mat averageMask = cv::Mat(5, 5, CV_32S, averageValues);

    cv::Mat averageImg;
    weightedConv2d(img, averageMask, averageImg);

    cv::imshow("average", averageImg);

       
    // Weighted average
    int wAvgValues[9] = {2, 4, 2,
                         4, 8, 4,
                         2, 4, 2};
    cv::Mat wAvgMask = cv::Mat(3, 3, CV_32S, wAvgValues);
    
    cv::Mat wAvgImg;
    weightedConv2d(img, wAvgMask, wAvgImg);
    
    cv::imshow("wAvg", wAvgImg);
    

    // Sobel X
    int sobelXValues[9] = {1, 0, -1,
                           2, 0, -2,
                           1, 0, -1};
    cv::Mat sobelXMask = cv::Mat(3, 3, CV_32S, sobelXValues);
    
    cv::Mat sobelXImg;
    conv2d(img, sobelXMask, sobelXImg);
    
    cv::imshow("sobelX", sobelXImg);
    
    
    // Sobel Y
    int sobelYValues[9] = { 1,  2,  1,
                            0,  0,  0,
                           -1, -2, -1};
    cv::Mat sobelYMask = cv::Mat(3, 3, CV_32S, sobelYValues);
    
    cv::Mat sobelYImg;
    conv2d(img, sobelYMask, sobelYImg);
    
    cv::imshow("sobelY", sobelYImg);


    // Sobel
    cv::Mat sobelImg;
    sobelFilter(img, sobelImg);
    cv::imshow("sobel", sobelImg);
    

    // Laplacian
    int laplacianValues[9] = {0,-1,0,
    						 -1,4,-1,
    						 0,-1, 0};
    const cv::Mat laplacianMask = cv::Mat(3, 3 ,CV_32S ,laplacianValues);

    cv::Mat laplacianImg;
    conv2d(img, laplacianMask, laplacianImg);
    cv::imshow("laplacian", laplacianImg);
    
    
    // Highboost
    int c = 1;
    int highboostValues[9] = {-1,  -1, -1,
                              -1, c+8, -1,
                              -1,  -1, -1};
    cv::Mat highboostMask = cv::Mat(3, 3, CV_32S, highboostValues);
    
    cv::Mat highboostImg;
    conv2d(img, highboostMask, highboostImg);
    
    cv::imshow("highboost", highboostImg);


    // Median
    cv::Mat medianImg;
    medianFilter(img, medianImg);

    cv::imshow("median", medianImg);
    
    
    cv::waitKey();
    

    return EXIT_SUCCESS;
}
