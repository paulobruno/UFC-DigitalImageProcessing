#include "convolution.h"

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
                    accumulation += (int)pSrc.at<uchar>(row+i, col+j) * pKernel.at<int>(1+i, 1+j);
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
    for (int i = -(int)kRows_2; i < endR; ++i)
    {
        for (int j = -(int)kCols_2; j < endC; ++j) 
        {
            kernelSum += pKernel.at<int>(1+i, 1+j);
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
                    accumulation += (int)src.at<uchar>(row+i, col+j) * pKernel.at<int>(1+i, 1+j);
                }
            } 
            
            pDst.at<uchar>(row - kRows_2, col - kCols_2) = (uchar)std::max(0, std::min(255, accumulation/kernelSum));
        }
    }
}


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
