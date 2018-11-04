#include "haarTransform.h"

#include <string>
#include <opencv2/opencv.hpp>
#include <cmath>

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


	unsigned int energy = imgEnergy(img);
}