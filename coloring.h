#include <opencv2/opencv.hpp>


void rgbToCmy(const cv::Mat& pSrc, cv::Mat& pDst);

void cmyToRgb(const cv::Mat& pSrc, cv::Mat& pDst);

void rgbToHsi(const cv::Mat& pSrc, cv::Mat& pDst);

void hsiToRgb(const cv::Mat& pSrc, cv::Mat& pDst);

void cmyToHsi(const cv::Mat& pSrc, cv::Mat& pDst);

void hsiToCmy(const cv::Mat& pSrc, cv::Mat& pDst);

void sepiaFilter(const cv::Mat& pSrc, cv::Mat& pDst);


void chromaKeying(const cv::Mat& pSrc, cv::Mat& pDst, const cv::Vec3b pColorKey, unsigned int pEpsilon = 30);

void imageSubtraction(const cv::Mat& pSrc1, const cv::Mat& pSrc2, cv::Mat& pDst);

void thresholding(const cv::Mat& pSrc, cv::Mat& pDst);

void adjustBrightness(const cv::Mat& pSrc, cv::Mat& pDst);
