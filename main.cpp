#include <string>
#include <opencv2/opencv.hpp>
#include <vector>

#include "histogram.h"


int main(int argc, const char** argv)
{
	if (2 > argc)
	{
		std::cout << "Error: incorrect number of args.\n"
				   << "Usage: " << argv[0] << " <image>\n";
		return -1;
	}

	std::string filename(argv[1]);

	cv::Mat img = cv::imread(filename, cv::IMREAD_GRAYSCALE);

	if (img.empty())
	{
		std::cerr << "Error: Cannot read " << filename << "\n";
		return -1;
	}

	//cv::imshow(filename, img);

	cv::Mat hist;
	calcHistogram(img, hist);

	cv::Mat histImg;
	showHistogram(hist, histImg, 512, 400);
	//cv::imshow("histImg", histImg);

	cv::Mat eqImg;
	equalizeHistogram(img, eqImg);
	//cv::imshow("eq_hist.jpg", eqImg);

	cv::Mat eqHist;
	calcHistogram(eqImg, eqHist);

	cv::Mat eqhimg;
	showHistogram(eqHist, eqhimg, 512, 400);
	//cv::imshow("eq", eqhimg);

	cv::Mat negative;
	negativeFilter(img, negative);
	//cv::imshow("neg", negative);

	cv::Mat logImg;
	logarithmicFilter(img, logImg, 50);
	//cv::imshow("log", logImg);

	cv::Mat gama;
	powerFilter(img, gama, 1, 0.8f);
	//cv::imshow("gama", gama);

	cv::Mat linear;
	linearParts(img, 100, 180, 150, 120, linear);
	//cv::imshow("linear", linear);

    std::vector<cv::Mat> slices;
    bitPlaneSlice(img, slices);

    for (unsigned int i = 0; i < slices.size(); ++i)
    {
        cv::imshow("slice" + std::to_string(i), slices.at(i));
    }

	cv::waitKey();

	return 0;
}