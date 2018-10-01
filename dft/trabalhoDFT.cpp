#include <string>
#include <opencv2/opencv.hpp>


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
    
    filter.convertTo(filter, CV_32F, (1.0f/255.0f));
    

    cv::Mat paddedImg;
    cv::copyMakeBorder(img, paddedImg, 0, img.rows, 0, img.cols, cv::BORDER_CONSTANT, cv::Scalar(0));

    paddedImg.convertTo(paddedImg, CV_32F);

    cv::Mat planes[] = {paddedImg, cv::Mat::zeros(paddedImg.size(), CV_32F)};
    cv::Mat complexI;
    cv::merge(planes, 2, complexI); 

    cv::dft(complexI, complexI);

    cv::split(complexI, planes);
    cv::magnitude(planes[0], planes[1], planes[0]);
    cv::Mat magImg = planes[0];

    magImg += cv::Scalar::all(1);
    cv::log(magImg, magImg);

//    magImg = magImg(cv::Rect(0, 0, img.cols, img.rows));

    cv::Mat normMag;
    cv::normalize(magImg, normMag, 0, 255, cv::NORM_MINMAX);
    normMag.convertTo(normMag, CV_8U);
   
    
    //cv::Mat filteredMag;
    //cv::multiply(magImg, filter, filteredMag);
    
    //magImg = filteredMag.clone();
    

    /*
    cv::Mat invplanes[] = {filteredMag, cv::Mat::zeros(paddedImg.size(), CV_32F)};
    cv::Mat invComplexI;
    cv::merge(invplanes, 2, invComplexI);
    
    cv::idft(filteredMag, invComplexI);
    
    cv::split(invComplexI, invplanes);
    cv::magnitude(invplanes[0], invplanes[1], invplanes[0]);
    cv::Mat invMag = invplanes[0];
    
    cv::normalize(invMag, invMag, 0, 255, cv::NORM_MINMAX);
    invMag.convertTo(invMag, CV_8U);
    
    cv::imshow("inv", invMag);
    */
    
    
    //cv::normalize(filteredMag, filteredMag, 0, 255, cv::NORM_MINMAX);
    //filteredMag.convertTo(filteredMag, CV_8U);
    
    cv::imshow("img", img);
    cv::imshow("a", normMag);
   // cv::imshow("filtered", filteredMag);
    cv::waitKey();
    cv::imwrite("raichu_fourier.jpg", normMag);
    
    
    int cx = magImg.cols/2;
    int cy = magImg.rows/2;
    
//    std::cout << cx << "\n";

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
    
    cv::normalize(magImg, magImg, 0, 255, cv::NORM_MINMAX);
    magImg.convertTo(magImg, CV_8U);
    
    cv::imshow("b", magImg);
    cv::waitKey();
    cv::imwrite("raichu_fourier_centeres.jpg", magImg);
    
    
    return 0;
}
