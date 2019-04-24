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
	Mat img = imread("D:\\c++\\����ͼ��ʵ��1\\x64\\Debug\\QQͼƬ20190221210406.jpg");
	imshow("src", img);
	Mat erodeElement = getStructuringElement(MORPH_RECT, Size(10, 10)); // ����ں�
	Mat dilateElement = getStructuringElement(MORPH_RECT, Size(10, 10)); // ����ں�
	erode(img, img, erodeElement); // ��ʴ����
	imshow("erode", img);
	dilate(img, img, dilateElement); // ���ͺ���
	imshow("dilate", img);
	waitKey(0);
}