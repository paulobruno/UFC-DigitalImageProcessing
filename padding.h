#pragma once

#include <opencv2/opencv.hpp>


enum Padding
{
	NOT_PADDED = 0,
	WHITE_PADDED = 1,
	BLACK_PADDED = 2
};


void addBorder(const cv::Mat& pSrc, cv::Mat& pDst, const uchar pBorderValue, const unsigned int pBorderSize);
