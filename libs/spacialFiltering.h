#pragma once

#include "padding.h"
#include <opencv2/opencv.hpp>
#include <vector>


void medianFilter(const cv::Mat& pSrc, cv::Mat& pDst, const unsigned int size = 3, const Padding pPad = NOT_PADDED);

void geometricMeanFilter(const cv::Mat& pSrc, cv::Mat& pDst, const unsigned int size = 3, const Padding pPad = NOT_PADDED);

void harmonicMeanFilter(const cv::Mat& pSrc, cv::Mat& pDst, const unsigned int size = 3, const Padding pPad = NOT_PADDED);

void contraharmonicMeanFilter(const cv::Mat& pSrc, cv::Mat& pDst, const int q, const unsigned int size = 3, const Padding pPad = NOT_PADDED);

void minimumFilter(const cv::Mat& pSrc, cv::Mat& pDst, const unsigned int size = 3, const Padding pPad = NOT_PADDED);

void maximumFilter(const cv::Mat& pSrc, cv::Mat& pDst, const unsigned int size = 3, const Padding pPad = NOT_PADDED);

void midpointFilter(const cv::Mat& pSrc, cv::Mat& pDst, const unsigned int size = 3, const Padding pPad = NOT_PADDED);
