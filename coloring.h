#include <opencv2/opencv.hpp>


void rgbToCmy(const cv::Mat& pSrc, cv::Mat& pDst);

void cmyToRgb(const cv::Mat& pSrc, cv::Mat& pDst);

void rgbToHsi(const cv::Mat& pSrc, cv::Mat& pDst);

void hsiToRgb(const cv::Mat& pSrc, cv::Mat& pDst);

void cmyToHsi(const cv::Mat& pSrc, cv::Mat& pDst);

void hsiToCmy(const cv::Mat& pSrc, cv::Mat& pDst);

void sepiaFilter(const cv::Mat& pSrc, cv::Mat& pDst);


void chromaKeying(const cv::Mat& pSrc, cv::Mat& pDst, const cv::Vec3b pColorKey, unsigned char pEpsilon = 20);

void imageSubtraction(const cv::Mat& pSrc1, const cv::Mat& pSrc2, cv::Mat& pDst);

void thresholding(const cv::Mat& pSrc, cv::Mat& pDst, const uchar pThreshold);

void adjustBrightness(const cv::Mat& pSrc, cv::Mat& pDst, const uchar pBrightness);

void adjustContrast(const cv::Mat& pSrc, cv::Mat& pDst, const float pGain);

void adjustBrightAndContrast(const cv::Mat& pSrc, cv::Mat& pDst, const float pGain, const uchar pBrightness);
