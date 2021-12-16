#pragma once

#include <opencv2/opencv.hpp>
#include <vector>


void negativeFilter(const cv::Mat& pSrc, cv::Mat& pDst);

void logarithmicFilter(const cv::Mat& pSrc, cv::Mat& pDst, const unsigned int c);

void powerFilter(const cv::Mat& pSrc, cv::Mat& pDst, const unsigned int c, const float gama); 

void linearParts(const cv::Mat& pSrc, const unsigned int x1, const unsigned int y1, const unsigned int x2, const unsigned int y2, cv::Mat& pDst);

void bitPlaneSlice(const cv::Mat& pSrc, std::vector<cv::Mat>& pSlices);
