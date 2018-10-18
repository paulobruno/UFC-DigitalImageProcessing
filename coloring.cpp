#include "coloring.h"
#include <opencv2/opencv.hpp>
#include <cmath>


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
    pDst = cv::Mat::zeros(pSrc.size(), CV_8UC3);
    
    for (unsigned int y = 0; y < pSrc.rows; ++y)
    {
        for (unsigned int x = 0; x < pSrc.cols; ++x)
        {
            float blue = (float)pSrc.at<cv::Vec3b>(y,x).val[0];
            float green = (float)pSrc.at<cv::Vec3b>(y,x).val[1];
            float red = (float)pSrc.at<cv::Vec3b>(y,x).val[2];
            
            int  newBlue = (int)(0.272f * red) + (0.534 * green) + (0.131 * blue);
            int newGreen = (int)(0.349f * red) + (0.686f * green) + (0.168 * blue);
            int   newRed = (int)(0.393f * red) + (0.769f * green) + (0.189 * blue);
            
            pDst.at<cv::Vec3b>(y,x).val[0] = (uchar)std::max(0, std::min(255, newBlue));
            pDst.at<cv::Vec3b>(y,x).val[1] = (uchar)std::max(0, std::min(255, newGreen));
            pDst.at<cv::Vec3b>(y,x).val[2] = (uchar)std::max(0, std::min(255, newRed));
        }
    }
}


void chromaKeying(const cv::Mat& pSrc, cv::Mat& pDst, const cv::Vec3b pColorKey, unsigned char pEpsilon)
{
<<<<<<< HEAD
    pDst = cv::Mat::zeros(pSrc.size(), CV_8U);

=======
    pDst = cv::Mat::zeros(pSrc.size(), CV_8UC3);
    
>>>>>>> c3b00e8d3c1095355a13569427212d9f80b9ce62
    for (unsigned int y = 0; y < pSrc.rows; ++y)
    {
        for (unsigned int x = 0; x < pSrc.cols; ++x)
        {
            cv::Vec3b intensity = pSrc.at<cv::Vec3b>(y,x);
<<<<<<< HEAD

=======
            
            //std::cout << intensity << " " << pColorKey << "\n";
>>>>>>> c3b00e8d3c1095355a13569427212d9f80b9ce62
            for (unsigned int channel = 0; channel < 3; ++channel)
            {
                if ((intensity.val[channel] > (pColorKey.val[channel] + pEpsilon)) || (intensity.val[channel] < (pColorKey.val[channel] - pEpsilon)))
                {
                    pDst.at<cv::Vec3b>(y,x).val[channel] = pSrc.at<cv::Vec3b>(y,x).val[channel];
                }
            }
        }
    }
}


void imageSubtraction(const cv::Mat& pSrc1, const cv::Mat& pSrc2, cv::Mat& pDst)
{
    pDst = cv::Mat::zeros(pSrc1.size(), CV_8UC3);

    for (unsigned int y = 0; y < pSrc1.rows; ++y)
    {
        for (unsigned int x = 0; x < pSrc1.cols; ++x)
        {
            for (unsigned int channel = 0; channel < 3; ++channel)
            {
                int value = (int)pSrc1.at<cv::Vec3b>(y,x).val[channel] - (int)pSrc2.at<cv::Vec3b>(y,x).val[channel];
                pDst.at<cv::Vec3b>(y,x).val[channel] = (uchar)std::max(0, std::min(255, value));
            }
        }
    }
}


void thresholding(const cv::Mat& pSrc, cv::Mat& pDst, const uchar pThreshold)
{
    pDst = cv::Mat::zeros(pSrc.size(), CV_8UC3);

    for (unsigned int y = 0; y < pSrc.rows; ++y)
    {
        for (unsigned int x = 0; x < pSrc.cols; ++x)
        {
            for (unsigned int channel = 0; channel < 3; ++channel)
            {
                pDst.at<cv::Vec3b>(y,x).val[channel] = 255 * (pSrc.at<cv::Vec3b>(y,x).val[channel] >= pThreshold);
            }
        }
    }
}


void adjustBrightness(const cv::Mat& pSrc, cv::Mat& pDst, const uchar pBrightness)
{
    pDst = cv::Mat::zeros(pSrc.size(), CV_8UC3);

    for (unsigned int y = 0; y < pSrc.rows; ++y)
    {
        for (unsigned int x = 0; x < pSrc.cols; ++x)
        {
            for (unsigned int channel = 0; channel < 3; ++channel)
            {
                int value = (int)pSrc.at<cv::Vec3b>(y,x).val[channel] + (int)pBrightness;
                pDst.at<cv::Vec3b>(y,x).val[channel] = (uchar)std::max(0, std::min(255, value));
            }
        }
    }
}


void adjustContrast(const cv::Mat& pSrc, cv::Mat& pDst, const float pGain)
{
    pDst = cv::Mat::zeros(pSrc.size(), CV_8UC3);

    for (unsigned int y = 0; y < pSrc.rows; ++y)
    {
        for (unsigned int x = 0; x < pSrc.cols; ++x)
        {
            for (unsigned int channel = 0; channel < 3; ++channel)
            {
                int value = (float)pSrc.at<cv::Vec3b>(y,x).val[channel] * pGain;
                pDst.at<cv::Vec3b>(y,x).val[channel] = (uchar)std::max(0, std::min(255, value));
            }
        }
    }
}


void adjustBrightAndContrast(const cv::Mat& pSrc, cv::Mat& pDst, const float pGain, const uchar pBrightness)
{
    pDst = cv::Mat::zeros(pSrc.size(), CV_8UC3);

    for (unsigned int y = 0; y < pSrc.rows; ++y)
    {
        for (unsigned int x = 0; x < pSrc.cols; ++x)
        {
            for (unsigned int channel = 0; channel < 3; ++channel)
            {
                int value = (float)pSrc.at<cv::Vec3b>(y,x).val[channel] * pGain + (float)pBrightness;
                pDst.at<cv::Vec3b>(y,x).val[channel] = (uchar)std::max(0, std::min(255, value));
            }
        }
    }
}