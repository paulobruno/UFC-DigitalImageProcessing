#pragma once

#include <opencv2/opencv.hpp>


enum Padding
{
	NOT_PADDED = 0,
	WHITE_PADDED = 1,
	BLACK_PADDED = 2
};


void conv2d(const cv::Mat& pSrc, const cv::Mat& pKernel, cv::Mat& pDst, const Padding pPad = NOT_PADDED);

void weightedConv2d(const cv::Mat& pSrc, const cv::Mat& pKernel, cv::Mat& pDst, const Padding pPad = NOT_PADDED);

void addBorder(const cv::Mat& pSrc, cv::Mat& pDst, const uchar pBorderValue, const unsigned int pBorderSize);
