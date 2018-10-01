#include <string>
#include <opencv2/opencv.hpp>

#include "fourierTransform.h"


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
    
    
    // Imagem original
    cv::imshow("ruido", img);

    // Calcula a DFT
    cv::Mat dftOfImg;
    computeDft(img, dftOfImg);
    
    // DFT normal
    showDft(dftOfImg);
    
    // DFT centralizada
    showCenteredDft(dftOfImg);
    
    // Inverse DFT
    cv::Mat inverseDft;
    computeInverseDft(dftOfImg, inverseDft);
    cv::imshow("Inverse DFT img", inverseDft);
    
    // Cropped Img
    cv::Mat croppedImg = inverseDft(cv::Rect(0, 0, inverseDft.cols / 2, inverseDft.rows / 2));
    cv::imshow("Cropped img", croppedImg);
        
    cv::waitKey();
    
    // Filtered DFT img
    cv::imshow("Filter", filter);
    
    cv::Mat filteredDft;
    filterDft(dftOfImg, filter, filteredDft);
    
    showDft(filteredDft, "filtered Dft");
    showCenteredDft(filteredDft, "filtered centered Dft");
    
    cv::Mat filteredInvImg;
    computeInverseDft(filteredDft, filteredInvImg);
    
    cv::Mat croppedFiltered = filteredInvImg(cv::Rect(0, 0, filteredInvImg.cols / 2, filteredInvImg.rows / 2));
    cv::imshow("Filtered img", croppedFiltered);
    
    cv::waitKey();
    
    return 0;
}
