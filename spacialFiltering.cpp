#include "spacialFiltering.h"
#include "padding.h"

#include <cstdio>
#include <cmath>
#include <algorithm>


void medianFilter(const cv::Mat& pSrc, cv::Mat& pDst, const unsigned int size, const Padding pPad)
{
    unsigned int kRows_2 = size / 2;
    unsigned int kCols_2 = size / 2;
    
    int endR = kRows_2 + (size % 2);
    int endC = kCols_2 + (size % 2);
    
    cv::Mat src;
    
    switch (pPad)
    {
        case WHITE_PADDED:
            addBorder(pSrc, src, 255, kRows_2);
            break;
            
        case BLACK_PADDED:
            addBorder(pSrc, src, 0, kCols_2);
            break;
            
        default:
            src = pSrc.clone();
            break;
    }

    // PB: essa soma com 1 e o resto eh p garantir q funciona par e impar
    pDst = cv::Mat::zeros(src.rows + 1 - size,
                          src.cols + 1 - size,
                          CV_8U);
    
    // PB: percorre de 1 .. size-1 tanto se for impar ou par
    for (unsigned int row = kRows_2; row < src.rows + 1 - (kRows_2 + (size % 2)); ++row) 
    { 
        for (unsigned int col = kCols_2; col < src.cols + 1 - (kCols_2 + (size % 2)); ++col) 
        {
        	std::vector<uchar> values;
             
            for (int i = -(int)kRows_2; i < endR; ++i)
            {
                for (int j = -(int)kCols_2; j < endC; ++j) 
                {
                    values.push_back(src.at<uchar>(row+i, col+j));
                }
            } 
            
            std::sort(values.begin(), values.end());
            int result = (int)values.at(4);

            // PB: ajusta o resultado para [0,255]			   
            pDst.at<uchar>(row - 1, col - 1) = (uchar)std::max(0, std::min(255, result));
        }
    }
}
