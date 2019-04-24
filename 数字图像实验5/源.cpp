#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main() {
	//读取图像
	cv::Mat img = cv::imread("D:\\c++\\数字图像实验1\\x64\\Debug\\QQ图片20190221210406.jpg");
	if (!img.data)
	{
		std::cout << "Error: read image" << std::endl;
		return -1;
	}
	//将图像转化为灰度图
	cv::Mat img_gray{};
	cv::cvtColor(img, img_gray, cv::COLOR_RGB2GRAY);

	//使用Laplacian
	cv::Mat abs_dst{};
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	cv::Laplacian(img_gray, img, ddepth, kernel_size, scale, delta, cv::BORDER_DEFAULT);
	//计算绝对值，并将结果转换成8位
	cv::convertScaleAbs(img, abs_dst);
	// 在窗口中显示avatar  
	cv::imshow("Laplacian", abs_dst);
	// 等待按下任意键后窗口关闭       
	cv::waitKey(0);
}