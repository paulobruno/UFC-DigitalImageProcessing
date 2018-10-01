#pragma once

#include "padding.h"
#include <opencv2/opencv.hpp>
#include <vector>


void medianFilter(const cv::Mat& pSrc, cv::Mat& pDst, const unsigned int size = 3, const Padding pPad = NOT_PADDED);

void geometricMeanFilter(const cv::Mat& pSrc, cv::Mat& pDst, const unsigned int size, const Padding pPad);

void hatmonicMeanFilter(const cv::Mat& pSrc, cv::Mat& pDst, const unsigned int size, const Padding pPad);

void counterHarmonicMeanFilter(const cv::Mat& pSrc, cv::Mat& pDst, const unsigned int size, const Padding pPad, int q)

void minimumFilter(const cv::Mat& pSrc, cv::Mat& pDst, const unsigned int size, const Padding pPad);

void maximumFilter(const cv::Mat& pSrc, cv::Mat& pDst, const unsigned int size, const Padding pPad)