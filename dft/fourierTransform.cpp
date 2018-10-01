#include "fourierTransform.h"


void computeDft(const cv::Mat& pSrc, cv::Mat& pDst)
{   
    cv::Mat paddedImg;
    cv::copyMakeBorder(pSrc, paddedImg, 0, pSrc.rows, 0, pSrc.cols, cv::BORDER_CONSTANT, cv::Scalar(0));

    cv::Mat paddedFloat;
    paddedImg.convertTo(paddedFloat, CV_32F, 1.0f / 255.0f);

    cv::Mat planes[2] = {paddedFloat, cv::Mat::zeros(paddedFloat.size(), CV_32F)};
    
    cv::Mat complexI;
    cv::merge(planes, 2, complexI);

    cv::Mat dftImg;
    cv::dft(complexI, dftImg, cv::DFT_COMPLEX_OUTPUT);
    
    pDst = dftImg.clone();
}


void showDft(const cv::Mat& pSrc, const std::string title)
{
    cv::Mat planes[2] = {cv::Mat::zeros(pSrc.size(), CV_32F), cv::Mat::zeros(pSrc.size(), CV_32F)};
    
    cv::split(pSrc, planes);
    
    cv::Mat magImg;
    cv::magnitude(planes[0], planes[1], magImg);

    magImg += cv::Scalar::all(1);
    cv::log(magImg, magImg);
        
    cv::Mat normMag;
    cv::normalize(magImg, normMag, 0, 255, cv::NORM_MINMAX);
    normMag.convertTo(normMag, CV_8U);
    
    cv::imshow(title, normMag);
}


void showCenteredDft(const cv::Mat& pSrc, const std::string title)
{
    cv::Mat planes[2] = {cv::Mat::zeros(pSrc.size(), CV_32F), cv::Mat::zeros(pSrc.size(), CV_32F)};
    
    cv::split(pSrc, planes);
    
    cv::Mat magImg;
    cv::magnitude(planes[0], planes[1], magImg);

    magImg += cv::Scalar::all(1);
    cv::log(magImg, magImg);
         
    int cx = magImg.cols/2;
    int cy = magImg.rows/2;
    
    cv::Mat q0 = magImg(cv::Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    cv::Mat q1 = magImg(cv::Rect(cx, 0, cx, cy));  // Top-Right
    cv::Mat q2 = magImg(cv::Rect(0, cy, cx, cy));  // Bottom-Left
    cv::Mat q3 = magImg(cv::Rect(cx, cy, cx, cy)); // Bottom-Right

    cv::Mat tmp;                         // swap quadrants (Top-Left with Bottom-Right)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);
    
    cv::Mat normMag;
    cv::normalize(magImg, normMag, 0, 255, cv::NORM_MINMAX);
    normMag.convertTo(normMag, CV_8U);
    
    cv::imshow(title, normMag);
}


void computeInverseDft(const cv::Mat& pSrc, cv::Mat& pDst)
{
    cv::Mat invDft;
    
    cv::idft(pSrc, invDft, cv::DFT_REAL_OUTPUT | cv::DFT_SCALE);
    
    pDst = invDft.clone();
}

void filterDft(const cv::Mat& pDft, const cv::Mat& pFilter, cv::Mat& pDst)
{   
    cv::Mat convertedFilter;
    pFilter.convertTo(convertedFilter, CV_32FC2, (1.0f/255.0f));
        
    cv::Mat planes[2] = {convertedFilter, convertedFilter};
    cv::Mat filter;
    cv::merge(planes, 2, filter);
    
    cv::Mat filtered;
    cv::multiply(pDft, filter, filtered);
    
    pDst = filtered.clone();
}

