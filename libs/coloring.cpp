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
  pDst = cv::Mat::zeros(pSrc.size(), CV_8UC3);

  for (unsigned int i = 0; i < pSrc.rows; ++i)
  {
    for (unsigned int j = 0; j < pSrc.cols; ++j)
    {
      double H, S, I, B, G, R, PI = 3.14159265359;

      B = normToTrigFuncInput( pSrc.at<cv::Vec3b>(i, j).val[0] );
      G = normToTrigFuncInput( pSrc.at<cv::Vec3b>(i, j).val[1] );
      R = normToTrigFuncInput( pSrc.at<cv::Vec3b>(i, j).val[2] );

      double theta = std::acos(0.5*((R-G) + (R-B))/std::sqrt(pow((R-G), 2) + (R-B)*(G-B)));

      // FL: Cada canal representará H, S e I
      if (B <= G)
      {
        H = theta; // H
      } else
      {
        H = 2.0*PI - theta; // H
      }
      S = 1.0 - (3.0/(R + G + B))*std::min(R, std::min(G, B)) ; // S
      I = (R + G + B)/3.0; // I


      pDst.at<cv::Vec3b>(i, j).val[0] = normToGreatIntervalValues( H );
      pDst.at<cv::Vec3b>(i, j).val[1] = normToGreatIntervalValues( S );
      pDst.at<cv::Vec3b>(i, j).val[2] = normToGreatIntervalValues( I );
    }
  }
}

void hsiToRgb(const cv::Mat& pSrc, cv::Mat& pDst)
{
  double B, G, R, H, S, I, PI = 3.14159265359;
  pDst = cv::Mat::zeros(pSrc.size(), CV_8UC3);

  for (unsigned int i = 0; i < pSrc.rows; ++i)
  {
    for (unsigned int j = 0; j < pSrc.cols; ++j)
    {
      // FL: Assumindo que os canais da matriz na imagem se comportam dessa maneira abaixo
      H = 2.0*PI*normToTrigFuncInput( pSrc.at<cv::Vec3b>(i, j).val[0] );
      S = normToTrigFuncInput( pSrc.at<cv::Vec3b>(i, j).val[1] );
      I = normToTrigFuncInput( pSrc.at<cv::Vec3b>(i, j).val[2] );

      // FL: Cada canal representará B, G e R
      if ((0.0 <= H) && ((2.0/3.0)*PI > H))
      {
        B = I*(1.0-S); // B
        R = I*(1.0 + (S*std::cos(H))/(std::cos((PI/3.0) - H))); // R
        G = 3.0*I - (R+B); // G
      }
      else if (((2.0/3.0)*PI <= H) && ((4.0/3.0)*PI > H))
      {
        H = H - (2.0/3.0)*PI;

        R = I*(1.0-S); // R
        G = I*(1.0 + (S*std::cos(H))/(std::cos((PI/3.0) - H))); // G
        B = 3.0*I - (R+G); // B
      }
      else if (((4.0/3.0)*PI <= H) && (2.0*PI > H))
      {
        H = H - (4.0/3.0)*PI;

        G = I*(1.0-S); // G
        B = I*(1.0 + (S*std::cos(H))/(std::cos((PI/3.0) - H))); // B
        R = 3.0*I - (G+B); // R
      }

      pDst.at<cv::Vec3b>(i, j).val[0] = normToGreatIntervalValues( B );
      pDst.at<cv::Vec3b>(i, j).val[1] = normToGreatIntervalValues( G );
      pDst.at<cv::Vec3b>(i, j).val[2] = normToGreatIntervalValues( R );
    }
  }
}

void cmyToHsi(const cv::Mat& pSrc, cv::Mat& pDst)
{
  cmyToRgb(pSrc, pDst);
  rgbToHsi(pSrc, pDst);
}

void hsiToCmy(const cv::Mat& pSrc, cv::Mat& pDst)
{
  hsiToRgb(pSrc, pDst);
  rgbToCmy(pSrc, pDst);
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


void chromaKeying(const cv::Mat& pSrc, cv::Mat& pDst, const cv::Vec3b pColorKey, const cv::Vec3b pEpsilon)
{
    pDst = cv::Mat::zeros(pSrc.size(), CV_8UC3);


    for (unsigned int y = 0; y < pSrc.rows; ++y)
    {
        for (unsigned int x = 0; x < pSrc.cols; ++x)
        {
            cv::Vec3b intensity = pSrc.at<cv::Vec3b>(y,x);


            //std::cout << intensity << " " << pColorKey << "\n";

            for (unsigned int channel = 0; channel < 3; ++channel)
            {
                if ((intensity.val[channel] > (pColorKey.val[channel] + pEpsilon.val[channel])) || (intensity.val[channel] < (pColorKey.val[channel] - pEpsilon.val[channel])))
                {
                  pDst.at<cv::Vec3b>(y,x) = pSrc.at<cv::Vec3b>(y,x);
                  break;
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


float normToTrigFuncInput(double value)
{
  //if (127.5 > value)
    //value = value - 127.5;
  return value/190.0;
}

float normToGreatIntervalValues(double value)
{
  return value*190.0;
}
