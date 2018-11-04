#include <opencv2/opencv.hpp>
#include <cmath>
#include "haarTransform.h"

unsigned int imgEnergy(const cv::Mat& pSrc)
{
	unsigned int energy = 0;

	for (unsigned int i = 0; i < pSrc.rows; ++i)
	{
		for (unsigned int j = 0; j < pSrc.cols; ++j)
		{
			energy += std::abs(pSrc.at<uchar>(i, j));
		}
	}

	return energy;
}