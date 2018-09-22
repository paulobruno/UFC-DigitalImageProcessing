#include "padding.h"

#include <opencv2/opencv.hpp>


void addBorder(const cv::Mat& pSrc, cv::Mat& pDst, const uchar pBorderValue, const unsigned int pBorderSize)
{
    pDst = cv::Mat(pSrc.rows + 2*pBorderSize, pSrc.cols + 2*pBorderSize, CV_8U, cv::Scalar(pBorderValue));
    
    for (unsigned int row = 0; row < pSrc.rows; ++row) 
    { 
        for (unsigned int col = 0; col < pSrc.cols; ++col) 
        {
            pDst.at<uchar>(row + pBorderSize, col + pBorderSize) = pSrc.at<uchar>(row, col);
        }
    }
}