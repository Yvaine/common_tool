/*************************************************************************
	> File Name: resize.cpp
	> Author: lengjing
	> Mail: jingleng77@163.com 
	> Created Time: Sat Oct 10 14:37:50 2015
 ************************************************************************/

#include<iostream>
using namespace std;

#include <opencv2/opencv.hpp>
#include <arm_neon.h>
#include <stdio.h>
#include <sys/time.h>
using namespace cv;
typedef unsigned char uchar;

#define COST_TIME(tstart, tend) 1000000 * (tend.tv_sec - tstart.tv_sec) + tend.tv_usec- tstart.tv_usec

void resize_cv_INTER_NEAREST(Mat &src, Mat &dst,Size dsize, double fx, double fy);
void resize_opt_INTER_NEAREST(Mat &src, Mat &dst, Size dszie, double fx, double fy);
void resize_neon(Mat &src, Mat &dst,Size dsize, double fx, double fy);

void resize_opt_INTER_LINEAR(Mat &src, Mat &dst,Size dsize, double fx, double fy);
void resize_cv_INTER_LINEAR(Mat &src, Mat &dst,Size dsize, double fx, double fy);

int main()
{
	Mat img = imread("autumn.jpg", 2|4);
	Mat dst1, dst2;
	double fx = 0.5;
	double fy = 0.5;
	Size dsize = Size(round(fx * img.cols), round(fy * img.rows));
	dst2.create(dsize, img.type());
	//resize_cv_INTER_NEAREST(img, dst1, Size(), fx, fy);
    //resize_opt_INTER_NEAREST(img, dst2, dsize, fx, fy);
	resize_cv_INTER_LINEAR(img, dst1, Size(), fx, fy);
    resize_opt_INTER_LINEAR(img, dst2, dsize, fx, fy);
	
	//imwrite("result_cv_INTER_NEAREST.jpg", dst1);
	//imwrite("result_opt_INTER_NEAREST.jpg", dst2);
	imwrite("result_cv_INTER_LINEAR.jpg", dst1);
	imwrite("result_opt_INTER_LINEAR.jpg", dst2);
}

void resize_cv_INTER_NEAREST(Mat &src, Mat &dst,Size dsize, double fx, double fy)
{
	resize(src, dst, Size(),0.5,0.5, 0);
}

void resize_opt_INTER_NEAREST(Mat &src, Mat &dst, Size dszie, double fx, double fy)
{
    //Mat dst_tmp = Mat(dsize, src.type(), Scalar::all(0));
	double scale_x = 1 / fx;
	double scale_y = 1 / fy;

	for(int i = 0; i < dst.rows; ++i)
	{
        int sy = cvFloor(i * scale_y); 
		//sy = std::min(sy, dst.rows -1);
		for(int j = 0; j < dst.cols; ++j)
		{
			int sx = cvFloor(j * scale_x);
			//sx = std::min(sx, dst.cols - 1);
			dst.at<Vec3b>(i,j) = src.at<Vec3b>(sy, sx);
		}
	}
}
void resize_neon_INTER_NEAREST(Mat &src, Mat &dst,Size dsize, double fx, double fy)
{

    
}

void resize_cv_INTER_LINEAR(Mat &src, Mat &dst,Size dsize, double fx, double fy)
{
	resize(src, dst, Size(), fx, fy, 1);
}

void resize_opt_INTER_LINEAR(Mat &src, Mat &dst,Size dsize, double fx, double fy)
{
	uchar* dataDst = dst.data;
	int stepDst = dst.step;
	uchar* dataSrc = src.data;
	int stepSrc = src.step;
	double scale_x = 1 / fx;
	double scale_y = 1 / fy;

	for(int i = 0; i < dst.rows; ++i)
	{
		float fy = (float)((i + 0.5) * scale_y - 0.5);
		int sy = cvFloor(fy);
		fy -= sy;

		short cbufy[2];
		cbufy[0] = saturate_cast<short>((1.f - fy) * 2048);
		cbufy[1] = 2048 - cbufy[0];

		for(int j = 0; j < dst.cols; ++j)
		{
			float fx = (float)((j + 0.5) * scale_x - 0.5);
			int sx = cvFloor(fx);
			fx -= sx;

			if(sx < 0){
				fx = 0; sx = 0;
			}
			if(sx >= src.cols - 1){
			    fx = 0; sx = src.cols -2;
			}
			short cbufx[2];
			cbufx[0] = saturate_cast<short>((1.f - fx) * 2048);
			cbufx[1] = 2048 - cbufx[0];

			for(int k =0; k < src.channels(); ++k)
			{
				*(dataDst + i * stepDst + 3 * j + k) =( 
					*(dataSrc + sy * stepSrc + 3 * sx + k) * cbufx[0] * cbufy[0] +
					*(dataSrc + (sy + 1) * stepSrc + 3 * sx + k) * cbufx[0] * cbufy[1] +
					*(dataSrc + sy * stepSrc + 3 * (sx + 1) + k) * cbufx[1] * cbufy[0] +
					*(dataSrc + (sy + 1) * stepSrc + 3 * (sx + 1) + k) * cbufx[1] * cbufy[1]) >> 22; 
			}
		}
	}
}
