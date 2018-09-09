#pragma once

#include <opencv2/opencv.hpp>


enum Padding
{
	NOT_PADDED = 0,
	WHITE_PADDED = 1,
	BLACK_PADDED = 2
};


void conv2d(const cv::Mat& pSrc, const cv::Mat& pKernel, cv::Mat& pDst);

void paddedConv2d(const cv::Mat& pSrc, const cv::Mat& pKernel, cv::Mat& pDst, const Padding = WHITE_PADDED);

void weightedConv2d(const cv::Mat& pSrc, const cv::Mat& pKernel, cv::Mat& pDst);
