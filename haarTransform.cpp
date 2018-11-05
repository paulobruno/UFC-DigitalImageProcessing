#include <opencv2/opencv.hpp>
#include <cmath>
#include "haarTransform.h"


float imageEnergy(const cv::Mat& pSrc)
{
	float energy = 0.0f;

	for (unsigned int i = 0; i < pSrc.rows; ++i)
	{
		for (unsigned int j = 0; j < pSrc.cols; ++j)
		{
			energy += std::abs(pSrc.at<float>(i, j));
		}
	}

	return energy;
}


void haarTransform(const cv::Mat& pSrc, cv::Mat& pDst)
{
    cv::Mat H1 = cv::Mat::zeros(pSrc.size(), CV_32F);

    unsigned int size_w = pSrc.cols /2;
    unsigned int size_h = pSrc.rows /2;

    for (unsigned int i = 0, j = 0; i < size_h, j < size_w; i+=2, ++j)
    {
        H1.at<float>(  i, j) = 0.5f;
        H1.at<float>(i+1, j) = 0.5f;
    }

    for (unsigned int i = 0, j = size_w; i < size_h, j < pSrc.cols; i+=2, ++j)
    {
        H1.at<float>(  i, j) =  0.5f;
        H1.at<float>(i+1, j) = -0.5f;
    }
    
    cv::Mat H1T;
    cv::transpose(H1, H1T);
    
    cv::Mat A;
    A = pSrc * H1;
    pDst = H1T * A;
}


void recursiveHaarTransform(const cv::Mat& pSrc, cv::Mat& pDst, const unsigned int pMaxIterations)
{
    if (0 >= pMaxIterations)
    {
        pDst = pSrc.clone();
        return;
    }
    
    cv::Mat haarImg;
    haarTransform(pSrc, haarImg);
    
    unsigned int size_w = pSrc.cols /2;
    unsigned int size_h = pSrc.rows /2;

    cv::Rect topLeftRect = cv::Rect(0, 0, size_w, size_h);
    cv::Rect topRightRect = cv::Rect(size_w, 0, size_w, size_h);
    cv::Rect bottomLeftRect = cv::Rect(0, size_h, size_w, size_h);
    cv::Rect bottomRightRect = cv::Rect(size_w, size_h, size_w, size_h);

    cv::Mat topLeftMat = haarImg(topLeftRect);
    cv::Mat topRightMat = haarImg(topRightRect);
    cv::Mat bottomLeftMat = haarImg(bottomLeftRect);
    cv::Mat bottomRightMat = haarImg(bottomRightRect);

    recursiveHaarTransform(topLeftMat, topLeftMat, pMaxIterations - 1);
    recursiveHaarTransform(topRightMat, topRightMat, pMaxIterations - 1);
    recursiveHaarTransform(bottomLeftMat, bottomLeftMat, pMaxIterations - 1);
    recursiveHaarTransform(bottomRightMat, bottomRightMat, pMaxIterations - 1);

    pDst = cv::Mat::zeros(pSrc.size(), CV_32F);

    topLeftMat.copyTo(pDst(topLeftRect));
    topRightMat.copyTo(pDst(topRightRect));
    bottomLeftMat.copyTo(pDst(bottomLeftRect));
    bottomRightMat.copyTo(pDst(bottomRightRect));
}


void normalHaarTransform(const cv::Mat& pSrc, cv::Mat& pDst, const unsigned int pMaxIterations)
{
    if ((0 >= pMaxIterations) || (1 == pSrc.rows))
    {
        pDst = pSrc.clone();
        return;
    }

    cv::Mat haarImg;
    haarTransform(pSrc, haarImg);
    
    unsigned int size_w = pSrc.cols /2;
    unsigned int size_h = pSrc.rows /2;

    cv::Rect topLeftRect = cv::Rect(0, 0, size_w, size_h);
    cv::Rect topRightRect = cv::Rect(size_w, 0, size_w, size_h);
    cv::Rect bottomLeftRect = cv::Rect(0, size_h, size_w, size_h);
    cv::Rect bottomRightRect = cv::Rect(size_w, size_h, size_w, size_h);

    cv::Mat topLeftMat = haarImg(topLeftRect);
    cv::Mat topRightMat = haarImg(topRightRect);
    cv::Mat bottomLeftMat = haarImg(bottomLeftRect);
    cv::Mat bottomRightMat = haarImg(bottomRightRect);

    normalHaarTransform(topLeftMat, topLeftMat, pMaxIterations-1);

    pDst = cv::Mat::zeros(pSrc.size(), CV_32F);

    topLeftMat.copyTo(pDst(topLeftRect));
    topRightMat.copyTo(pDst(topRightRect));
    bottomLeftMat.copyTo(pDst(bottomLeftRect));
    bottomRightMat.copyTo(pDst(bottomRightRect));    
}

void optimalHaarTransform(const cv::Mat& pSrc, cv::Mat& pDst, const float pThreshold, const unsigned int pMaxIterations)
{
    if ((0 >= pMaxIterations) || (1 == pSrc.rows))
    {
        pDst = pSrc.clone();
        return;
    }

    cv::Mat haarImg;
    haarTransform(pSrc, haarImg);
    
    threshold(haarImg, haarImg, pThreshold);
    /*
    std::cout << "step:\n";
    std::cout << pSrc << "\n";
    std::cout << haarImg << "\n";
    std::cout << imageEnergy(pSrc) << " " << imageEnergy(haarImg) << "\n\n";
*/
    if (imageEnergy(pSrc) <= imageEnergy(haarImg))
    {
        pDst = pSrc.clone();
        return;
    }

    unsigned int size_w = pSrc.cols /2;
    unsigned int size_h = pSrc.rows /2;

    cv::Rect topLeftRect = cv::Rect(0, 0, size_w, size_h);
    cv::Rect topRightRect = cv::Rect(size_w, 0, size_w, size_h);
    cv::Rect bottomLeftRect = cv::Rect(0, size_h, size_w, size_h);
    cv::Rect bottomRightRect = cv::Rect(size_w, size_h, size_w, size_h);

    cv::Mat topLeftMat = haarImg(topLeftRect);
    cv::Mat topRightMat = haarImg(topRightRect);
    cv::Mat bottomLeftMat = haarImg(bottomLeftRect);
    cv::Mat bottomRightMat = haarImg(bottomRightRect);

    optimalHaarTransform(topLeftMat, topLeftMat, pThreshold, pMaxIterations-1);
    optimalHaarTransform(topRightMat, topRightMat, pThreshold, pMaxIterations-1);
    optimalHaarTransform(bottomLeftMat, bottomLeftMat, pThreshold, pMaxIterations-1);
    optimalHaarTransform(bottomRightMat, bottomRightMat, pThreshold, pMaxIterations-1);

    pDst = cv::Mat::zeros(pSrc.size(), CV_32F);

    topLeftMat.copyTo(pDst(topLeftRect));
    topRightMat.copyTo(pDst(topRightRect));
    bottomLeftMat.copyTo(pDst(bottomLeftRect));
    bottomRightMat.copyTo(pDst(bottomRightRect));
}


void threshold(const cv::Mat& pSrc, cv::Mat& pDst, const float pThreshold)
{
    pDst = pSrc.clone();
    
    //std::cout << "\tt: " << pThreshold << "\n";
    //std::cout << "\t" << pSrc << "\n";

    for (unsigned int i = 0; i < pSrc.rows; ++i)
    {
        for (unsigned int j = 0; j < pSrc.cols; ++j)
        {
            if (std::abs(pDst.at<float>(i,j)) < pThreshold)
            {
                pDst.at<float>(i,j) = 0.0f;
            }
        }
    }
    
    //std::cout << "\t" << pDst << "\n";
}
