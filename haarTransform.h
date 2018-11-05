#pragma once

#include <opencv2/opencv.hpp>


float imageEnergy(const cv::Mat& pSrc);

void haarTransform(const cv::Mat& pSrc, cv::Mat& pDst);

void recursiveHaarTransform(const cv::Mat& pSrc, cv::Mat& pDst, const unsigned int pMaxIterations = 2);

void optimalHaarTransform(const cv::Mat& pSrc, cv::Mat& pDst, const float pThreshold = 0.0f);

void threshold(const cv::Mat& pSrc, cv::Mat& pDst, const float pThreshold = 0.0f);
