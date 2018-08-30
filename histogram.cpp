#include "histogram.h"
#include <math.h>

#define T_MAX 255


void showHistogram(const cv::Mat& pHist, cv::Mat& pDst, const unsigned int pWidth, const unsigned int pHeight)
{
	cv::Mat img = cv::Mat::zeros(pWidth, pHeight, CV_8U);


}


void calcHistogram(const cv::Mat& pSrc, cv::Mat& pDst)
{
	// Entrada: pSrc - matriz da imagem;
	//			pDst - vetor do histograma.

	pDst = cv::Mat::zeros(1, 256, CV_8U);

	for (int i = 0; i < pSrc.rows; i++) {
		for (int j = 0; j < pSrc.cols; j++) {
			pDst.at<uchar>(0 ,pSrc.at<uchar>(i, j)) += 1;
		}
	}
}



void negativeFIlter(const cv::Mat& pSrc, cv::Mat& pDst)
{
	pDst = cv::Mat::zeros(pSrc.rows, pSrc.cols, CV_8U);

	for (unsigned int i = 0; i < pSrc.rows; ++i) 
	{
		for (unsigned int j = 0; j < pSrc.cols; ++j) 
		{
			pDst.at<uchar>(i, j) = T_MAX - pSrc.at<uchar>(i, j);
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
        	pDst.at<uchar>(i, j) = c*log(1 - pSrc.at<uchar>(i, j));
		}
	}
}

void powerFilter(const cv::Mat pSrc, cv::Mat pDst, const unsigned int c, const unsigned int gama) 
{
	pDst = cv::Mat::zeros(pSrc.rows, pSrc.cols, CV_8U);

	for (unsigned int i = 0; i < pSrc.rows; ++i) 
	{
		for (unsigned int j = 0; j < pSrc.cols; ++j) 
		{
        	pDst.at<uchar>(i, j) = c*pow(pSrc.at<uchar>(i, j), gama);
		}
	}
}
