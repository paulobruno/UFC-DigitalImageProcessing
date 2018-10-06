#include <opencv2/opencv.hpp>


void rgbToCmy(const cv::Mat& pSrc, cv::Mat& pDst);

void cmyToRgb(const cv::Mat& pSrc, cv::Mat& pDst);

void rgbToHsi(const cv::Mat& pSrc, cv::Mat& pDst);

void hsiToRgb(const cv::Mat& pSrc, cv::Mat& pDst);

void cmyToHsi(const cv::Mat& pSrc, cv::Mat& pDst);

void hsiToCmy(const cv::Mat& pSrc, cv::Mat& pDst);

void sepiaFilter(const cv::Mat& pSrc, cv::Mat& pDst);
