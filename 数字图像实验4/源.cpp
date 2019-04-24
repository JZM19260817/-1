#include <cstdlib>  
#include <iostream>  
#include <opencv2\core\core.hpp>  
#include <opencv2\highgui\highgui.hpp>  
#include <opencv2\imgproc\imgproc.hpp>  
#define CV_LOAD_IMAGE_GRAYSCALE 0
using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("D:\\c++\\数字图像实验1\\x64\\Debug\\QQ图片20190221210406.jpg");
	imshow("src", img);
	Mat erodeElement = getStructuringElement(MORPH_RECT, Size(10, 10)); // 获得内核
	Mat dilateElement = getStructuringElement(MORPH_RECT, Size(10, 10)); // 获得内核
	erode(img, img, erodeElement); // 腐蚀函数
	imshow("erode", img);
	dilate(img, img, dilateElement); // 膨胀函数
	imshow("dilate", img);
	waitKey(0);
}