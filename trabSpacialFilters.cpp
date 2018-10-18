#include <string>
#include <opencv2/opencv.hpp>
#include <vector>

#include "spacialFiltering.h"


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

    // Median
    cv::Mat medianImg;
    medianFilter(img, medianImg);
    cv::imshow("median", medianImg);
    std::cout << "med\n";

    // Minimum filter
    cv::Mat minImg;
    minimumFilter(img, minImg);
    cv::imshow("minimum", minImg);
    std::cout << "min\n";
    
    // Maximum filter
    cv::Mat maxImg;
    maximumFilter(img, maxImg);
    cv::imshow("maximum", maxImg);
    std::cout << "max\n";

    // Midpoint filter
    cv::Mat midImg;
    midpointFilter(img, midImg);
    cv::imshow("midpoint", midImg);
    std::cout << "mid\n";
        
    // Geometric mean filter
    cv::Mat geomImg;
    geometricMeanFilter(img, geomImg);
    cv::imshow("Geometric mean", geomImg);
    std::cout << "gem\n";
    
    // Harmonic mean filter
    cv::Mat harmImg;
    harmonicMeanFilter(img, harmImg);
    cv::imshow("Harmonic mean", harmImg);
    std::cout << "ham\n";
    
    // Counter harmonic mean filter
    cv::Mat counterHarmImg;
    contraharmonicMeanFilter(img, counterHarmImg, -2);
    cv::imshow("Counter harmonic mean", counterHarmImg);
    std::cout << "cou\n";

    cv::waitKey();
    

    return EXIT_SUCCESS;
}
