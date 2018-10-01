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

void geometricMeanFilter(const cv::Mat& pSrc, cv::Mat& pDst, const unsigned int size, const Padding pPad)
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

            int result = 1;
            for (unsigned int i = 0; i < values.size(); ++i)
            {
                result = result*values(i);
            }
            result = std::pow(result, 1/values.size());

            // PB: ajusta o resultado para [0,255]			   
            pDst.at<uchar>(row - 1, col - 1) = (uchar)std::max(0, std::min(255, result));
        }
    }
}

void hatmonicMeanFilter(const cv::Mat& pSrc, cv::Mat& pDst, const unsigned int size, const Padding pPad)
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

            int result = 0;
            for (unsigned int i = 0; i < values.size(); ++i)
            {
                result = result + values(i);
            }
            result = values.size()/result;

            // PB: ajusta o resultado para [0,255]			   
            pDst.at<uchar>(row - 1, col - 1) = (uchar)std::max(0, std::min(255, result));
        }
    }
}

void counterHarmonicMeanFilter(const cv::Mat& pSrc, cv::Mat& pDst, const unsigned int size, const Padding pPad, int q) // FL: esse argumento q define o expoente q da expressão
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

            int result = 0;
            for (unsigned int i = 0; i < values.size(); ++i)
            {
                result = result + values(i);
            }
            result = std::pow(result, q+1)/std::pow(result, q);

            // PB: ajusta o resultado para [0,255]			   
            pDst.at<uchar>(row - 1, col - 1) = (uchar)std::max(0, std::min(255, result));
        }
    }
}

void minimumFilter(const cv::Mat& pSrc, cv::Mat& pDst, const unsigned int size, const Padding pPad)
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

            // FL: Ordenando o vector values e usando seu primeiro valor, no ind zero (o menor valor depois da ordenação)
            std::sort(values.begin(), values.end());
            int result = (int)values.at(0);

            // PB: ajusta o resultado para [0,255]			   
            pDst.at<uchar>(row - 1, col - 1) = (uchar)std::max(0, std::min(255, result));
        }
    }
}

void maximumFilter(const cv::Mat& pSrc, cv::Mat& pDst, const unsigned int size, const Padding pPad)
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

            // FL: ordenando o vector values e pegando o seu ultimo valor (o mais alto)
            std::sort(values.begin(), values.end());
            int result = (int)values.at(values.size() - 1);

            // PB: ajusta o resultado para [0,255]			   
            pDst.at<uchar>(row - 1, col - 1) = (uchar)std::max(0, std::min(255, result));
        }
    }
}

void midpointFilter(const cv::Mat& pSrc, cv::Mat& pDst, const unsigned int size, const Padding pPad)
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

            // FL: ordenando o vector values e pegando o seu ultimo valor (o mais alto)
            std::sort(values.begin(), values.end());
            int result = 0.5*(values.begin() + values.end());

            // PB: ajusta o resultado para [0,255]             
            pDst.at<uchar>(row - 1, col - 1) = (uchar)std::max(0, std::min(255, result));
        }
    }


    int int main(int argc, char const *argv[])
    {
        /* code */
        return 0;
    }