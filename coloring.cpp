#include "coloring.h"
#include <opencv2/opencv.hpp>


void rgbToCmy(const cv::Mat& pSrc, cv::Mat& pDst)
{
  pDst = cv::Mat::zeros(pSrc.size(), CV_8UC3);

  for (unsigned int i = 0; i < pSrc.rows; ++i)
  {
    for (unsigned int j = 0; j < pSrc.cols; ++j)
    {
      for (int channel = 0; channel < 3; ++channel)
      {
        pDst.at<cv::Vec3b>(i, j).val[channel] = 255 - pSrc.at<cv::Vec3b>(i, j).val[channel];
      }
    }
  }
}

void cmyToRgb(const cv::Mat& pSrc, cv::Mat& pDst)
{
  // FL: Coloquei o mesmo código do rgbToCmy
  pDst = cv::Mat::zeros(pSrc.size(), CV_8UC3);

  for (unsigned int i = 0; i < pSrc.rows; ++i)
  {
    for (unsigned int j = 0; j < pSrc.cols; ++j)
    {
      for (int channel = 0; channel < 3; ++channel)
      {
        pDst.at<cv::Vec3b>(i, j).val[channel] = 255 - pSrc.at<cv::Vec3b>(i, j).val[channel];
      }
    }
  }
}

void rgbToHsi(const cv::Mat& pSrc, cv::Mat& pDst)
{

}

void hsiToRgb(const cv::Mat& pSrc, cv::Mat& pDst)
{

}

void cmyToHsi(const cv::Mat& pSrc, cv::Mat& pDst)
{

}

void hsiToCmy(const cv::Mat& pSrc, cv::Mat& pDst)
{

}

void sepiaFilter(const cv::Mat& pSrc, cv::Mat& pDst)
{

}


void chromaKeying(const cv::Mat& pSrc, cv::Mat& pDst, const cv::Vec3b pColorKey, unsigned int pEpsilon)
{
    pDst = cv::Mat::zeros(pSrc.size(), CV_8U);

    for (unsigned int y = 0; y < pSrc.rows; ++y)
    {
        for (unsigned int x = 0; x < pSrc.cols; ++x)
        {
            cv::Vec3b intensity = pSrc.at<cv::Vec3b>(y,x);

            for (unsigned int channel = 0; channel < 3; ++channel)
            {
                if ((intensity.val[channel] > (pColorKey.val[channel] + 20)) || (intensity.val[channel] < (pColorKey.val[channel] - 20)))
                {
                    pDst.at<cv::Vec3b>(y,x).val[channel] = pSrc.at<cv::Vec3b>(y,x).val[channel];
                }
            }
        }
    }
}


void imageSubtraction(const cv::Mat& pSrc1, const cv::Mat& pSrc2, cv::Mat& pDst)
{
    pDst = cv::Mat::zeros(pSrc1.size(), CV_8U);

    for (unsigned int y = 0; y < pSrc1.rows; ++y)
    {
        for (unsigned int x = 0; x < pSrc1.cols; ++x)
        {
            for (unsigned int channel = 0; channel < 3; ++channel)
            {
                pDst.at<cv::Vec3b>(y,x).val[channel] = pSrc1.at<cv::Vec3b>(y,x).val[channel] - pSrc2.at<cv::Vec3b>(y,x).val[channel];
            }
        }
    }
}


void thresholding(const cv::Mat& pSrc, cv::Mat& pDst, const uchar pThreshold)
{
    pDst = cv::Mat::zeros(pSrc.size(), CV_8U);

    for (unsigned int y = 0; y < pSrc.rows; ++y)
    {
        for (unsigned int x = 0; x < pSrc.cols; ++x)
        {
            for (unsigned int channel = 0; channel < 3; ++channel)
            {
                pDst.at<cv::Vec3b>(y,x).val[channel] = pSrc.at<cv::Vec3b>(y,x).val[channel] >= pThreshold;
            }
        }
    }
}


void adjustBrightness(const cv::Mat& pSrc, cv::Mat& pDst)
{

}
