#include <string>
#include <opencv2/opencv.hpp>


// PB: pSrc -> imagem <uchar> (CV_8U)
void computeDft(const cv::Mat& pSrc, cv::Mat& pDst);

void showDft(const cv::Mat& pSrc, const std::string title = "DFT");

void showCenteredDft(const cv::Mat& pSrc, const std::string title = "Centered DFT");

void computeInverseDft(const cv::Mat& pSrc, cv::Mat& pDst);

// PB: pFilter -> imagem <cuhar> (CV_8U)
void filterDft(const cv::Mat& pDft, const cv::Mat& pFilter, cv::Mat& pDst);
