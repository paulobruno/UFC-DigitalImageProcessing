#pragma once

#include "padding.h"
#include <opencv2/opencv.hpp>


void conv2d(const cv::Mat& pSrc, const cv::Mat& pKernel, cv::Mat& pDst, const Padding pPad = NOT_PADDED);

void weightedConv2d(const cv::Mat& pSrc, const cv::Mat& pKernel, cv::Mat& pDst, const Padding pPad = NOT_PADDED);

void sobelFilter(const cv::Mat& pSrc, cv::Mat& pDst, const Padding pPad = NOT_PADDED);
