#include <opencv2/opencv.hpp>
#include <string>
#include <cmath>

#include "haarTransform.h"


int main(int argc, char** argv)
{
	// FL: testes de entrada
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
	img.convertTo(img, CV_32F);

    
    cv::Mat haar;
    haarTransform(img, haar);    
    
    // OpenCV needs normalization to properly show the image    
    cv::normalize(haar, haar, 0, 255, cv::NORM_MINMAX, CV_8U);
    cv::imshow("Haar", haar);
    
    
    cv::Mat recursiveHaar;
    recursiveHaarTransform(img, recursiveHaar, 2);
    
    cv::normalize(recursiveHaar, recursiveHaar, 0, 255, cv::NORM_MINMAX, CV_8U);
    cv::imshow("Recursive Haar", recursiveHaar);
        
        
    cv::Mat optimalHaar;
    optimalHaarTransform(img, optimalHaar, 0.5f); 
    
    cv::normalize(optimalHaar, optimalHaar, 0, 255, cv::NORM_MINMAX, CV_8U);
    cv::imshow("Optimal Haar", optimalHaar);
	
	/*

    int teste_data[64] = {88, 88,  89,  90,  92,  94,  96,  97,
                          90, 90,  91,  92,  93,  95,  97,  97,
                          92, 92,  93,  94,  95,  96,  97,  97,
                          93, 93,  94,  95,  96,  96,  96,  96,
                          92, 93,  95,  96,  96,  96,  96,  95,
                          92, 94,  96,  98,  99,  99,  98,  97,
                          94, 96,  99, 101, 103, 103, 102, 101,
                          95, 97, 101, 104, 106, 106, 105, 105};              

    cv::Mat teste = cv::Mat(8, 8, CV_32S, teste_data);
    
    teste.convertTo(teste, CV_32F);
    cv::Mat opth;
    optimalHaarTransform(teste, opth, 0.5f);
    
    std::cout << opth << "\n";*/
    
	
	cv::waitKey();
	
	
	return EXIT_SUCCESS;
}
