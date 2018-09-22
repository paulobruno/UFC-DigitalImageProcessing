#pragma once

#include "padding.h"
#include <opencv2/opencv.hpp>
#include <vector>


void medianFilter(const cv::Mat& pSrc, cv::Mat& pDst, const unsigned int size = 3, const Padding pPad = NOT_PADDED);
