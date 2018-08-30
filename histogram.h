#pragma once

#include <opencv2/opencv.hpp>


void showHistogram(const cv::Mat& pHist, cv::Mat& pDst, const unsigned int pWidth, const unsigned int pHeight);

void calcHistogram(const cv::Mat& pSrc, cv::Mat& pDst);

void negativeFIlter(const cv::Mat& pSrc, cv::Mat& pDst);

void equalizeHistogram(const cv::Mat& pSrc, cv::Mat& pDst);