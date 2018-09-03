#include "filtering.h"
#include <math.h>
#include <algorithm>


void negativeFilter(const cv::Mat& pSrc, cv::Mat& pDst)
{
	pDst = cv::Mat::zeros(pSrc.rows, pSrc.cols, CV_8U);

	for (unsigned int i = 0; i < pSrc.rows; ++i) 
	{
		for (unsigned int j = 0; j < pSrc.cols; ++j) 
		{
			pDst.at<uchar>(i, j) = 255 - pSrc.at<uchar>(i, j);
		}
	}
}


void logarithmicFilter(const cv::Mat& pSrc, cv::Mat& pDst, const unsigned int c)
{
	pDst = cv::Mat::zeros(pSrc.rows, pSrc.cols, CV_8U);

	for (unsigned int i = 0; i < pSrc.rows; ++i) 
	{
		for (unsigned int j = 0; j < pSrc.cols; ++j) 
		{
	        	pDst.at<uchar>(i, j) = (uchar)std::min(255.0f, ((float)c * (float)log((float)pSrc.at<uchar>(i, j) + 1.0f)));
		}
	}
}


void powerFilter(const cv::Mat& pSrc, cv::Mat& pDst, const unsigned int c, const float gama) 
{
	pDst = cv::Mat::zeros(pSrc.rows, pSrc.cols, CV_8U);

	for (unsigned int i = 0; i < pSrc.rows; ++i) 
	{
		for (unsigned int j = 0; j < pSrc.cols; ++j) 
		{
			pDst.at<uchar>(i, j) = (uchar)std::min(255.0f, (float)c * (float)pow((float)pSrc.at<uchar>(i, j), gama) );
		}
	}
}

// TODO: verificar se 255 > x2 >= x1 e 255 > y2 >= y1 
void linearParts(const cv::Mat& pSrc, const unsigned int x1, const unsigned int y1, const unsigned int x2, const unsigned int y2, cv::Mat& pDst)
{
	float a1 = (float)y1 / (float)x1;
	float b1 = 0.0f;

	float a2 = ((float)y2 - (float)y1) / ((float)x2 - (float)x1);
	float b2 = (float)y2 - a2 * (float)x2;

	float a3 = (255.0f - (float)y2) / (255.0f - (float)x2);
	float b3 = 255.0f * (1.0f - a3);

	cv::Mat lookUpTable = cv::Mat::zeros(1, 256, CV_8U);

	for (unsigned int i = 0; i < x1; ++i)
	{
		lookUpTable.at<uchar>(0, i) = (uchar)(a1 * (float)i + b1);
	}

	for (unsigned int i = x1; i < x2; ++i)
	{
		lookUpTable.at<uchar>(0, i) = (uchar)(a2 * (float)i + b2);
	}

	for (unsigned int i = x2; i < 256; ++i)
	{
		lookUpTable.at<uchar>(0, i) = (uchar)(a3 * (float)i + b3);
	}

	pDst = cv::Mat::zeros(pSrc.rows, pSrc.cols, CV_8U);

	for (unsigned int i = 0; i < pSrc.rows; ++i) 
	{
		for (unsigned int j = 0; j < pSrc.cols; ++j) 
		{
			pDst.at<uchar>(i, j) = lookUpTable.at<uchar>(0, pSrc.at<uchar>(i, j));
		}
	}
}


void bitPlaneSlice(const cv::Mat& pSrc, std::vector<cv::Mat>& pSlices)
{
    pSlices.clear();

    for (unsigned int i = 0; i < 8; ++i)
    {
        cv::Mat temp = cv::Mat::zeros(pSrc.size(), CV_8U);
        pSlices.push_back(temp);
    }

    std::cout << (int)(156 & (2 << 1)) << "\n";

    for (unsigned int i = 0; i < pSrc.rows; ++i)
    {
        for (unsigned int j = 0; j < pSrc.cols; ++j)
        {
            for (unsigned int b = 0; b < 8; ++b)
            {
                pSlices.at(b).at<uchar>(i, j) = pSrc.at<uchar>(i, j) & (1 << b);
            }
        }
    }

    // Debug: imagem completa formada por todos os slices, deve ficar igual aa original
    /*cv::Mat temp = cv::Mat::zeros(pSrc.size(), CV_8U);
    pSlices.push_back(temp);
    for (unsigned int i = 0; i < pSrc.rows; ++i)
    {
        for (unsigned int j = 0; j < pSrc.cols; ++j)
        {
            for (unsigned int b = 0; b < 8; ++b)
            {
                pSlices.at(8).at<uchar>(i, j) |= pSlices.at(b).at<uchar>(i, j);
            }
        }
    }*/
}