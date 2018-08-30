#include "histogram.h"

#define T_MAX 255


void showHistogram(const cv::Mat& pHist, cv::Mat& pDst, const unsigned int pWidth, const unsigned int pHeight)
{
	int hist_size = 256;	
	int binWidth = cvRound((double) pWidth / hist_size);
	
	pDst = cv::Mat::zeros(pHeight, pWidth, CV_8U);
	cv::normalize(pHist, pHist, 0, pHeight, cv::NORM_MINMAX, -1, cv::Mat());
	
	for (unsigned int i = 1; i < hist_size; ++i)
	{
		cv::line(pDst, cv::Point(binWidth * (i-1), pHeight - pHist.at<int>(i-1)) ,
				 cv::Point(binWidth * (i), pHeight - pHist.at<int>(i)),
				 cv::Scalar(255, 255, 255), 2, 8, 0);
	}
}


void calcHistogram(const cv::Mat& pSrc, cv::Mat& pDst)
{
	// Entrada: pSrc - matriz da imagem;
	//			pDst - vetor do histograma.

	pDst = cv::Mat::zeros(1, 256, CV_32S);

	for (int i = 0; i < pSrc.rows; i++) 
	{
		for (int j = 0; j < pSrc.cols; j++) 
		{
			pDst.at<int>(0, pSrc.at<uchar>(i, j)) += 1;
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


void equalizeHistogram(const cv::Mat& pSrc, cv::Mat& pDst)
{
	cv::Mat hist;
	calcHistogram(pSrc, hist);

	cv::Mat cdf = cv::Mat::zeros(1, 256, CV_32S);

	cdf.at<int>(0, 0) = hist.at<int>(0, 0);

	for (unsigned int i = 1; i < hist.cols; ++i) 
	{
		cdf.at<int>(0, i) = cdf.at<int>(0, i-1) + hist.at<int>(0, i);
	}

	int cdf_min = 0;	

	for (unsigned int i = 0; i < cdf.cols; ++i) 
	{
		if (0 < cdf.at<int>(0, i))
		{
			cdf_min = cdf.at<int>(0, i);
			break;
		}
	}

	cv::Mat hv = cv::Mat::zeros(1, 256, CV_8U);

	for (unsigned int i = 0; i < cdf.cols; ++i) 
	{
		if (0 != cdf.at<int>(0, i))
		{
			hv.at<uchar>(0, i) = (uchar)(255.0f * (float)(cdf.at<int>(0, i) - cdf_min) / (float)((pSrc.rows * pSrc.cols) - cdf_min));
		}
	}

	pDst = cv::Mat::zeros(pSrc.rows, pSrc.cols, CV_8U);

	for (unsigned int i = 0; i < pSrc.rows; ++i) 
	{
		for (unsigned int j = 0; j < pSrc.cols; ++j) 
		{
			pDst.at<uchar>(i, j) = hv.at<uchar>(0, pSrc.at<uchar>(i, j));
		}
	}
}