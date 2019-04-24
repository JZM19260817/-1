#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main() {
	//��ȡͼ��
	cv::Mat img = cv::imread("D:\\c++\\����ͼ��ʵ��1\\x64\\Debug\\QQͼƬ20190221210406.jpg");
	if (!img.data)
	{
		std::cout << "Error: read image" << std::endl;
		return -1;
	}
	//��ͼ��ת��Ϊ�Ҷ�ͼ
	cv::Mat img_gray{};
	cv::cvtColor(img, img_gray, cv::COLOR_RGB2GRAY);

	//ʹ��Laplacian
	cv::Mat abs_dst{};
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	cv::Laplacian(img_gray, img, ddepth, kernel_size, scale, delta, cv::BORDER_DEFAULT);
	//�������ֵ���������ת����8λ
	cv::convertScaleAbs(img, abs_dst);
	// �ڴ�������ʾavatar  
	cv::imshow("Laplacian", abs_dst);
	// �ȴ�����������󴰿ڹر�       
	cv::waitKey(0);
}