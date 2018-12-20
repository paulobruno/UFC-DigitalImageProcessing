#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <iostream>
#include <string>


int main(const int argc, const char** argv)
{
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);

    cv::Mat filter(width, height, CV_8U, cv::Scalar::all(255));
    
    int option;
    bool running = true;
    
    while (running)
    {
        cv::imshow("filter", filter);
        cv::waitKey();
        
        std::cout << "\n 1 - Add line\n"
                  << " 2 - Add circle\n"
                  << " 3 - Add filled circle\n"
                  << " 5 - Save filter\n"
                  << " 9 - Exit\n\n"
                  << " Option: ";
        
        std::cin >> option;
        
        switch (option)
        {
            int x1, x2, y1, y2;
            int cx, cy, r;
                        
            case 1:                
                std::cout << "\nx1: ";
                std::cin >> x1;
                std::cout << "y1: ";
                std::cin >> y1;
                std::cout << "x2: ";
                std::cin >> x2;
                std::cout << "y2: ";
                std::cin >> y2;
                
                cv::line(filter, cv::Point(x1,y1), cv::Point(x2,y2), cv::Scalar(0), 5);
                break;
                
            case 2:                
                std::cout << "\ncx: ";
                std::cin >> cx;
                std::cout << "cy: ";
                std::cin >> cy;
                std::cout << "r: ";
                std::cin >> r;
                
                cv::circle(filter, cv::Point(cx,cy), r, cv::Scalar(0), 5);
                break;
                
            case 3:                
                std::cout << "\ncx: ";
                std::cin >> cx;
                std::cout << "cy: ";
                std::cin >> cy;
                std::cout << "r: ";
                std::cin >> r;
                
                cv::circle(filter, cv::Point(cx,cy), r, cv::Scalar(0), CV_FILLED, 5);
                break;
                
            case 5:                
                cv::imwrite("filter.bmp", filter);
                std::cout << "Saved as filter.bmp\n";
                break;
                
            case 9:
                running = false;
                break;
                
            default:
                std::cout << "Wrong option!\n";
                break;
        }
    }
    

    return EXIT_SUCCESS;
}
