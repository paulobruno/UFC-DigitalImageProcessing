#include <string>
#include <opencv2/opencv.hpp>


int main(int argc, const char** argv)
{
	cv::Mat m = cv::Mat::zeros(4,4,CV_8U);

	std::cout << m << "\n";


	return 0;
}