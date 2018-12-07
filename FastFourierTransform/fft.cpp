#include <complex>
#include <iostream>
#include <valarray>
#include <vector>
#include <opencv2/opencv.hpp>

 
const double PI = 3.141592653589793238460;

 
// Cooley–Tukey FFT (in-place, divide-and-conquer)
// Higher memory requirements and redundancy although more intuitive
void fft1d(std::valarray<std::complex<double>>& x)
{
    const size_t N = x.size();
    
    if (N <= 1) return;
 
    // divide
    std::valarray<std::complex<double>> even = x[std::slice(0, N/2, 2)];
    std::valarray<std::complex<double>>  odd = x[std::slice(1, N/2, 2)];
 
    // conquer
    fft1d(even);
    fft1d(odd);
 
    // combine
    for (size_t k = 0; k < N/2; ++k)
    {
        std::complex<double> t = std::polar(1.0, -2 * PI * k / N) * odd[k];
        x[k    ] = even[k] + t;
        x[k+N/2] = even[k] - t;
    }
}
 
// inverse fft (in-place)
void ifft1d(std::valarray<std::complex<double>>& x)
{
    // conjugate the complex numbers
    x = x.apply(std::conj);
 
    // forward fft
    fft1d( x );
 
    // conjugate the complex numbers again
    x = x.apply(std::conj);
 
    // scale the numbers
    x /= x.size();
}


void fft2d(const cv::Mat& pSrc, cv::Mat& pReal, cv::Mat& pComplex)
{
    std::complex<double> test[pSrc.rows][pSrc.cols] = {0};
    
    // criando o array de complexos
    for (int i = 0; i < pSrc.rows; ++i)
    {
        for (int j = 0; j < pSrc.cols; ++j)
        {
            test[i][j] = pSrc.at<double>(i,j);
        }
    }
      
    // FFT 1D em cada linha
    for (int i = 0; i < pSrc.rows; ++i)
    {
        std::valarray<std::complex<double>> data(test[i], pSrc.cols);
        
        fft1d(data);
          
        for (int j = 0; j < data.size(); ++j)
        {
            test[i][j] = data[j];
        }
    }
    
    // FFT 1D em cada coluna
    for (int j = 0; j < pSrc.cols; ++j)
    {
        std::valarray<std::complex<double>> data(pSrc.rows);
        
        // Criando o valarray de coluna
        for (int i = 0; i < pSrc.rows; ++i)
        {
            data[i] = test[i][j];
        }
        
        fft1d(data);
          
        for (int i = 0; i < data.size(); ++i)
        {
            test[i][j] = data[i];
        }
    }
        
    
    pReal = cv::Mat::zeros(pSrc.rows, pSrc.cols, CV_64F);
    pComplex = cv::Mat::zeros(pSrc.rows, pSrc.cols, CV_64F);
    
    for (int i =0; i < pSrc.rows; ++i)
    {
        for (int j = 0; j < pSrc.cols; ++j)
        {
            pReal.at<double>(i,j) = std::real(test[i][j]);
            pComplex.at<double>(i,j) = std::imag(test[i][j]);
        }
    }
}


void ifft2d(const cv::Mat& pReal, const cv::Mat& pComplex, cv::Mat& pDst)
{
    // criando o array de complexos
    std::complex<double> test[pReal.rows][pReal.cols] = {0};
    
    for (int i = 0; i < pReal.rows; ++i)
    {
        for (int j = 0; j < pReal.cols; ++j)
        {
            test[i][j] = pReal.at<double>(i,j);
        }
    }
      
    // IFFT 1D em cada coluna
    for (int j = 0; j < pReal.cols; ++j)
    {
        std::valarray<std::complex<double>> data(pReal.rows);
        
        // Criando o valarray de coluna
        for (int i = 0; i < pReal.rows; ++i)
        {
            data[i] = test[i][j];
        }
                
        // forward fft
        ifft1d(data);
          
        for (int i = 0; i < data.size(); ++i)
        {
            test[i][j] = data[i];
        }
    }        
    
    // IFFT 1D em cada linha
    for (int i = 0; i < pReal.rows; ++i)
    {
        std::valarray<std::complex<double>> data(test[i], pReal.cols);
        
        ifft1d(data);
          
        for (int j = 0; j < data.size(); ++j)
        {
            test[i][j] = data[j];
        }
    }
    
    pDst = cv::Mat::zeros(pReal.rows, pReal.cols, CV_64F);
    
    for (int i =0; i < pDst.rows; ++i)
    {
        for (int j = 0; j < pDst.cols; ++j)
        {
            pDst.at<double>(i,j) = std::real(test[i][j]);
        }
    }
}


void showDft(const cv::Mat& pReal, const cv::Mat& pComplex, const std::string title)
{
    cv::Mat magImg;
    cv::magnitude(pReal, pComplex, magImg);

    magImg += cv::Scalar::all(1);
    cv::log(magImg, magImg);
        
    cv::Mat normMag;
    cv::normalize(magImg, normMag, 0, 255, cv::NORM_MINMAX);
    normMag.convertTo(normMag, CV_8U);
    
    cv::imshow(title, normMag);
}


void showCenteredDft(const cv::Mat& pReal, const cv::Mat& pComplex, const std::string title)
{
    cv::Mat magImg;
    cv::magnitude(pReal, pComplex, magImg);

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
    cv::imwrite("rai_original_centered.jpg", normMag);
}


int main(const int argc, const char** argv)
{
    if (3 > argc)
    {
        std::cerr << "Error. No image passed\n"
                  << "Usage: " << argv[0] << " <image> <filter>\n";
        return -1;
    }

	std::string filename(argv[1]);
	cv::Mat img = cv::imread(filename, cv::IMREAD_GRAYSCALE);

	if (img.empty())
	{
		std::cerr << "Error: Cannot read " << filename << "\n";
		return -1;
	}
	
	std::string filtername(argv[2]);
    cv::Mat filter = cv::imread(filtername, cv::IMREAD_GRAYSCALE);
    
    if (filter.empty())
    {
		std::cerr << "Error: Cannot read " << filtername << "\n";
		return -1;
    }
    
    img.convertTo(img, CV_64F, 1.0 / 255.0);
    filter.convertTo(filter, CV_64F, 1.0 / 255.0);
            
    cv::Mat paddedImg;
    cv::copyMakeBorder(img, paddedImg, 0, img.rows, 0, img.cols, cv::BORDER_CONSTANT, cv::Scalar(0));

    cv::Mat realMat, complexMat;
    fft2d(paddedImg, realMat, complexMat);

    cv::Mat ifftMat;
    ifft2d(realMat, complexMat, ifftMat);
    cv::Mat croppedFiltered = ifftMat(cv::Rect(0, 0, ifftMat.cols / 2, ifftMat.rows / 2));
    cv::imshow("Inverse DFT", croppedFiltered);

    
    showDft(realMat, complexMat, "DFT");
    showCenteredDft(realMat, complexMat, "Centered DFT");
        
    cv::Mat filtReal, filtComplex;
    cv::multiply(realMat, filter, filtReal);
    cv::multiply(complexMat, filter, filtComplex);
    showDft(filtReal, filtComplex, "Filtered DFT");
    
    cv::Mat ifftFilt;
    ifft2d(filtReal, filtComplex, ifftFilt);
    cv::Mat croppedIfft = ifftFilt(cv::Rect(0, 0, ifftFilt.cols / 2, ifftFilt.rows / 2));
    cv::imshow("Filtered img", croppedIfft);
    
        
    cv::waitKey();
    

    return 0;
}
