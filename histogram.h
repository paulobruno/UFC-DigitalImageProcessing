#pragma once

#include <opencv2/opencv.hpp>


void showHistogram(const cv::Mat& pHist, cv::Mat& pDst, const unsigned int pWidth, const unsigned int pHeight);

void calcHistogram(const cv::Mat& pSrc, cv::Mat& pDst);

void negativeFilter(const cv::Mat& pSrc, cv::Mat& pDst);

void equalizeHistogram(const cv::Mat& pSrc, cv::Mat& pDst);

void logarithmicFilter(const cv::Mat& pSrc, cv::Mat& pDst, const unsigned int c);

void powerFilter(const cv::Mat& pSrc, cv::Mat& pDst, const unsigned int c, const unsigned int gama); 

void linearParts(const cv::Mat& pSrc, const unsigned int x1, const unsigned int y1, const unsigned int x2, const unsigned int y2, cv::Mat& pDst);