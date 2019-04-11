#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
#define CV_LOAD_IMAGE_GRAYSCALE 0
int main(int a,char **p) 
{
	Mat input = imread("D:\\c++\\数字图像实验1\\x64\\Debug\\QQ图片20190221210406.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	imshow("灰度图像", input);
	int w = getOptimalDFTSize(input.cols);
	int h = getOptimalDFTSize(input.rows);
	Mat padded;
	copyMakeBorder(input, padded, 0, h - input.rows, 0, w - input.cols, BORDER_CONSTANT, Scalar::all(0));
	padded.convertTo(padded, CV_32FC1);
	imshow("padded", padded);
	for (int i = 0; i < padded.rows; i++)//中心化操作，其余操作和上一篇博客的介绍一样
	{
		float *ptr = padded.ptr<float>(i);
		for (int j = 0; j < padded.cols; j++)	ptr[j] *= pow(-1, i + j);
	}
	Mat plane[] = { padded,Mat::zeros(padded.size(),CV_32F) };
	Mat complexImg;
	merge(plane, 2, complexImg);
	dft(complexImg, complexImg);
	//************************gaussian****************************
	Mat gaussianBlur(padded.size(), CV_32FC2);
	Mat gaussianSharpen(padded.size(), CV_32FC2);
	float D0 = 2 * 10 * 10;
	for (int i = 0; i < padded.rows; i++)
	{
		float*p = gaussianBlur.ptr<float>(i);
		float*q = gaussianSharpen.ptr<float>(i);
		for (int j = 0; j < padded.cols; j++)
		{
			float d = pow(i - padded.rows / 2, 2) + pow(j - padded.cols / 2, 2);
			p[2 * j] = expf(-d / D0);
			p[2 * j + 1] = expf(-d / D0);

			q[2 * j] = 1 - expf(-d / D0);
			q[2 * j + 1] = 1 - expf(-d / D0);
		}
	}
	multiply(complexImg, gaussianBlur, gaussianBlur);//矩阵元素对应相乘法，注意，和矩阵相乘区分
	multiply(complexImg, gaussianSharpen, gaussianSharpen);
	//*****************************************************************	
	split(complexImg, plane);
	magnitude(plane[0], plane[1], plane[0]);
	plane[0] += Scalar::all(1);
	log(plane[0], plane[0]);
	normalize(plane[0], plane[0], 1, 0, NORM_MINMAX);
	imshow("dft", plane[0]);
	//******************************************************************
	split(gaussianBlur, plane);
	magnitude(plane[0], plane[1], plane[0]);
	plane[0] += Scalar::all(1);
	log(plane[0], plane[0]);
	normalize(plane[0], plane[0], 1, 0, NORM_MINMAX);
	imshow("gaussianBlur", plane[0]);

	split(gaussianSharpen, plane);
	magnitude(plane[0], plane[1], plane[0]);
	plane[0] += Scalar::all(1);
	log(plane[0], plane[0]);
	normalize(plane[0], plane[0], 1, 0, NORM_MINMAX);
	imshow("gaussianSharpen", plane[0]);
	//******************************************************************
	//*************************idft*************************************
	idft(gaussianBlur, gaussianBlur);
	idft(gaussianSharpen, gaussianSharpen);
	split(gaussianBlur, plane);
	magnitude(plane[0], plane[1], plane[0]);
	normalize(plane[0], plane[0], 1, 0, NORM_MINMAX);
	imshow("idft-gaussianBlur", plane[0]);

	split(gaussianSharpen, plane);
	magnitude(plane[0], plane[1], plane[0]);
	normalize(plane[0], plane[0], 1, 0, NORM_MINMAX);
	imshow("idft-gaussianSharpen", plane[0]);

	waitKey();
	return 0;
}