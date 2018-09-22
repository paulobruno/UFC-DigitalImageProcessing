#include "convolution.h"
#include "padding.h"

#include <cstdio>
#include <cmath>
#include <algorithm>


void conv2d(const cv::Mat& pSrc, const cv::Mat& pKernel, cv::Mat& pDst, const Padding pPad)
{
    unsigned int kRows_2 = pKernel.rows / 2;
    unsigned int kCols_2 = pKernel.cols / 2;

    // PB: essa soma com 1 e o resto eh p garantir q funciona par e impar
    pDst = cv::Mat::zeros(pSrc.rows + 1 - pKernel.rows,
                          pSrc.cols + 1 - pKernel.cols,
                          CV_8U);

    int endR = kRows_2 + (pKernel.rows % 2);
    int endC = kCols_2 + (pKernel.cols % 2);
    
    // PB: percorre de 1 .. size-1 tanto se for impar ou par
    for (unsigned int row = kRows_2; row < pSrc.rows + 1 - (kRows_2 + (pKernel.rows % 2)); ++row) 
    { 
        for (unsigned int col = kCols_2; col < pSrc.cols + 1 - (kCols_2 + (pKernel.cols % 2)); ++col) 
        {
            int accumulation = 0;
            
            for (int i = -(int)kRows_2; i < endR; ++i)
            {
                for (int j = -(int)kCols_2; j < endC; ++j) 
                {
                    accumulation += (int)pSrc.at<uchar>(row+i, col+j) * pKernel.at<int>(kRows_2+i, kCols_2+j);
                }
            } 
            
            //pDst.at<uchar>(row, col) = (uchar)(accumulation / kernelSum);
            pDst.at<uchar>(row - kRows_2, col - kCols_2) = (uchar)std::max(0, std::min(255, accumulation));
        }
    }
}


void weightedConv2d(const cv::Mat& pSrc, const cv::Mat& pKernel, cv::Mat& pDst, const Padding pPad)
{
    cv::Mat src;
    
    switch (pPad)
    {
        case WHITE_PADDED:
            addBorder(pSrc, src, 255, pKernel.rows / 2);
            break;
            
        case BLACK_PADDED:
            addBorder(pSrc, src, 0, pKernel.rows / 2);
            break;
            
        default:
            src = pSrc.clone();
            break;
    }

    // PB: essa soma com 1 e o resto eh p garantir q funciona par e impar
    pDst = cv::Mat::zeros(src.rows + 1 - pKernel.rows,
                          src.cols + 1 - pKernel.cols,
                          CV_8U);
                          
    int kernelSum = 0;
    unsigned int kRows_2 = pKernel.rows / 2;
    unsigned int kCols_2 = pKernel.cols / 2;

    int endR = kRows_2 + (pKernel.rows % 2);
    int endC = kCols_2 + (pKernel.cols % 2);
                
    // PB: soma com resto da divisao por 2 eh para garantir que funciona tanto
    //   com kernel de tamanho impar quanto par
    for (int i = 0; i < pKernel.rows; ++i)
    {
        for (int j = 0; j < pKernel.cols; ++j) 
        {
            kernelSum += pKernel.at<int>(i, j);
        }
    }
    
    // PB: percorre de 1 .. size-1 tanto se for impar ou par
    for (unsigned int row = kRows_2; row < src.rows + 1 - (kRows_2 + (pKernel.rows % 2)); ++row) 
    { 
        for (unsigned int col = kCols_2; col < src.cols + 1 - (kCols_2 + (pKernel.cols % 2)); ++col) 
        {
            int accumulation = 0;
            
            for (int i = -(int)kRows_2; i < endR; ++i)
            {
                for (int j = -(int)kCols_2; j < endC; ++j) 
                {
                    accumulation += (int)src.at<uchar>(row+i, col+j) * pKernel.at<int>(kRows_2+i, kCols_2+j);
                }
            } 
            
            pDst.at<uchar>(row - kRows_2, col - kCols_2) = (uchar)std::max(0, std::min(255, accumulation/kernelSum));
        }
    }
}


void sobelFilter(const cv::Mat& pSrc, cv::Mat& pDst, const Padding pPad)
{
    cv::Mat src;
    
    switch (pPad)
    {
        case WHITE_PADDED:
            addBorder(pSrc, src, 255, 1);
            break;
            
        case BLACK_PADDED:
            addBorder(pSrc, src, 0, 1);
            break;
            
        default:
            src = pSrc.clone();
            break;
    }

    // PB: essa soma com 1 e o resto eh p garantir q funciona par e impar
    pDst = cv::Mat::zeros(src.rows - 2,
                          src.cols - 2,
                          CV_8U);
    
    int sobelXValues[9] = {1, 0, -1,
                           2, 0, -2,
                           1, 0, -1};
    int sobelYValues[9] = { 1,  2,  1,
                            0,  0,  0,
                           -1, -2, -1};
    cv::Mat gxKernel = cv::Mat(3, 3, CV_32S, sobelXValues);
    cv::Mat gyKernel = cv::Mat(3, 3, CV_32S, sobelYValues);

    // PB: percorre de 1 .. size-1 tanto se for impar ou par
    for (unsigned int row = 1; row < src.rows - 1; ++row) 
    { 
        for (unsigned int col = 1; col < src.cols - 1; ++col) 
        {
            int accX = 0;
            int accY = 0;
            
            for (int i = -1; i < 2; ++i)
            {
                for (int j = -1; j < 2; ++j) 
                {
                    accX += (int)src.at<uchar>(row+i, col+j) * gxKernel.at<int>(1+i, 1+j);
                    accY += (int)src.at<uchar>(row+i, col+j) * gyKernel.at<int>(1+i, 1+j);
                }
            } 
            
            int magnitude = std::sqrt(accX * accX + accY * accY);
            pDst.at<uchar>(row - 1, col - 1) = (uchar)std::max(0, std::min(255, magnitude));
        }
    }
}

