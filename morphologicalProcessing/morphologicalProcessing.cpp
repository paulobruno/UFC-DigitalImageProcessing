#include <opencv2/opencv.hpp>
#include <cstdio>
#include <cmath>
#include <cstdlib>


void erosion(const cv::Mat& pSrc, cv::Mat& pDst, const int erosionSize)
{
	cv::Mat structuralElement = getStructuringElement( cv::MORPH_ELLIPSE,
                       cv::Size( 2*erosionSize + 1, 2*erosionSize+1 ),
                       cv::Point( erosionSize, erosionSize ) );
	int minimumPointValue = 999; // FL: Valor minimo que sera atribuido ao ponto coincidente ao
								 // central do elemento estrutural na imagem de destino
 
	cv::Mat dst = cv::Mat::zeros(pSrc.rows, pSrc.cols, CV_8U);

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
			
			dst.at<uchar>(i+erosionSize, j+erosionSize) = minimumPointValue;
			minimumPointValue = 999;
		}	
	}
	
	pDst = dst.clone();
}


void dilation(const cv::Mat& pSrc, cv::Mat& pDst, const int dilationSize)
{
	cv::Mat structuralElement = getStructuringElement( cv::MORPH_ELLIPSE,
                       cv::Size( 2*dilationSize + 1, 2*dilationSize+1 ),
                       cv::Point( dilationSize, dilationSize ) );

	int maximumPointValue = -1; // FL: Valor minimo que sera atribuido ao ponto coincidente ao
								 // central do elemento estrutural na imagem de destino
	
	cv::Mat dst = cv::Mat::zeros(pSrc.rows, pSrc.cols, CV_8U);

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
			dst.at<uchar>(i+dilationSize, j+dilationSize) = maximumPointValue;
			maximumPointValue = -1;
		}	
	}
	
	pDst = dst.clone();
}


void opening(const cv::Mat& pSrc, cv::Mat& pDst, const int elementRadius)
{
    cv::Mat erosionImg;
    
	erosion(pSrc, erosionImg, elementRadius);

	dilation(erosionImg, pDst, elementRadius);
}


void closing(const cv::Mat& pSrc, cv::Mat& pDst, const int elementRadius)
{
    cv::Mat dilationImg;
    
	dilation(pSrc, dilationImg, elementRadius);
	
	erosion(dilationImg, pDst, elementRadius);
}


void morphologicalGradient(const cv::Mat& pSrc, cv::Mat& pDst, const int elementSize)
{
	cv::Mat erosionImg, dilationImg;

	cv::Mat dst = cv::Mat::zeros(pSrc.rows, pSrc.cols, CV_8U);

	erosion(pSrc, erosionImg, elementSize);

	dilation(pSrc, dilationImg, elementSize);

	for (unsigned i = 0; i < dst.rows; ++i)
	{
		for (unsigned j = 0; j < dst.cols; ++j)
		{
			dst.at<uchar>(i, j) = dilationImg.at<uchar>(i, j) - erosionImg.at<uchar>(i, j);
		}
	}
	
	pDst = dst.clone();
}


int main(int argc, char** argv)
{
	if (3 > argc)
	{
		std::cout << "Error: incorrect number of args.\n"
				   << "Usage: " << argv[0] << " <image> <structuring element size>\n";
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
	
	const int elementSize = atoi(argv[2]);


	cv::Mat erosionImg;
	erosion(img, erosionImg, elementSize);
	cv::imshow("Erosion", erosionImg);

	cv::Mat dilationImg;
	dilation(img, dilationImg, elementSize);
	cv::imshow("Dilation", dilationImg);

	cv::Mat openingImg;
	opening(img, openingImg, elementSize);
	cv::imshow("Opening", openingImg);
	
	cv::Mat closingImg;
	closing(img, closingImg, elementSize);
	cv::imshow("Closing", closingImg);
	
	cv::Mat gradientImg;
	morphologicalGradient(img, gradientImg, elementSize);
	cv::imshow("Morphological Gradient", gradientImg);

	cv::waitKey();
	
	
	return 0;
}
