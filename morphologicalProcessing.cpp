
#include <opencv2/opencv.hpp>
#include <cstdio>
#include <cmath>

void erosion(const cv::Mat& pSrc, cv::Mat& pDst, const int erosionSize)
{
	cv::Mat structuralElement = getStructuringElement( cv::MORPH_ELLIPSE,
                       cv::Size( 2*erosionSize + 1, 2*erosionSize+1 ),
                       cv::Point( erosionSize, erosionSize ) );
	int minimumPointValue = 999; // FL: Valor minimo que sera atribuido ao ponto coincidente ao
								 // central do elemento estrutural na imagem de destino
	pDst = cv::Mat::zeros(pSrc.rows, pSrc.cols, CV_8U);

	for (unsigned int i = 0; i < pSrc.rows-1 - structuralElement.rows; ++i)
	{
		for (unsigned int j = 0; j < pSrc.cols-1 - structuralElement.cols; ++j)
		{


			for (unsigned int k = 0; k < structuralElement.rows; ++k)
			{
				for (unsigned int l = 0; l < structuralElement.cols; ++l)
				{
					if ((1 == (int)structuralElement.at<uchar>(k, l)) && (minimumPointValue > (int)pSrc.at<uchar>(i+k, j+l)))
					{
						minimumPointValue = (int)pSrc.at<uchar>(i+k, j+l);
					}
				}
			}
			pDst.at<uchar>(i+erosionSize, j+erosionSize) = minimumPointValue;
			minimumPointValue = 999;
		}	
	}
}

void dilation(const cv::Mat& pSrc, cv::Mat& pDst, const int dilationSize)
{
	cv::Mat structuralElement = getStructuringElement( cv::MORPH_ELLIPSE,
                       cv::Size( 2*dilationSize + 1, 2*dilationSize+1 ),
                       cv::Point( dilationSize, dilationSize ) );

	int maximumPointValue = -1; // FL: Valor minimo que sera atribuido ao ponto coincidente ao
								 // central do elemento estrutural na imagem de destino
	
	pDst = cv::Mat::zeros(pSrc.rows, pSrc.cols, CV_8U);

	for (unsigned int i = 0; i < pSrc.rows-1 - structuralElement.rows; ++i)
	{
		for (unsigned int j = 0; j < pSrc.cols-1 - structuralElement.cols; ++j)
		{


			for (unsigned int k = 0; k < structuralElement.rows; ++k)
			{
				for (unsigned int l = 0; l < structuralElement.cols; ++l)
				{
					if ((1 == (int)structuralElement.at<uchar>(k, l)) && (maximumPointValue < (int)pSrc.at<uchar>(i+k, j+l)))
					{
						maximumPointValue = (int)pSrc.at<uchar>(i+k, j+l);
					}
				}
			}
			pDst.at<uchar>(i+dilationSize, j+dilationSize) = maximumPointValue;
			maximumPointValue = -1;
		}	
	}
}

void morphologicalGradient(const cv::Mat& pSrc, cv::Mat& pDst)
{
	cv::Mat erosionImg, dilationImg;
	const int elementSize = 20;

	pDst = cv::Mat::zeros(pSrc.rows, pSrc.cols, CV_8U);

	erosion(pSrc, erosionImg, elementSize);

	dilation(pSrc, dilationImg, elementSize);

	for (unsigned i = 0; i < pDst.rows; ++i)
	{
		for (unsigned j = 0; j < pDst.cols; ++j)
		{
			pDst.at<uchar>(i, j) = dilationImg.at<uchar>(i, j) - erosionImg.at<uchar>(i, j);
		}
	}
}

int main(int argc, char** argv)
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

	cv::imshow(filename, img);

	cv::Mat erosionImg;
	erosion(img, erosionImg, 3);
	cv::imshow("Erosion", erosionImg);

	cv::Mat dilationImg;
	dilation(img, dilationImg, 10);
	cv::imshow("Dilation", dilationImg);

	cv::Mat gradientImg;
	morphologicalGradient(img, gradientImg);
	cv::imshow("Morphological Gradient", gradientImg);

	cv::waitKey();
	return 0;
}