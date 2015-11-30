/*************************************************************************
	> File Name: compare.cpp
	> Author: lengjing
	> Mail: jingleng77@163.com 
	> Created Time: Fri Sep 18 16:34:21 2015
 ************************************************************************/

//#include<iostream>
#include <opencv2/opencv.hpp>
#include <arm_neon.h>
#include <stdio.h>
#include <sys/time.h>
using namespace cv;
typedef unsigned char uchar;

#define COST_TIME(tstart, tend) 1000000 * (tend.tv_sec - tstart.tv_sec) + tend.tv_usec- tstart.tv_usec
#define COL 800
#define ROW 800
#define SIZE COL * ROW
#if 0
void compare_cv_equ(float *psrc1, float src2, uchar *pdst, int cols, int rows, int cmpop);
void compare_neon_equ(float *psrc1, float src2,  uchar *pdst, int cols, int rows, int cmpop);
void compare_cv_ge(float *psrc1, float src2, uchar *pdst, int cols, int rows, int cmpop); // greater than or equal 
void compare_neon_ge(float *psrc1, float src2,  uchar *pdst, int cols, int rows, int cmpop);
void compare_cv_lt(float *psrc1, float src2, uchar *pdst, int cols, int rows, int cmpop); // less than
void compare_neon_lt(float *psrc1, float src2,  uchar *pdst, int cols, int rows, int cmpop);
#else
void compare_cv_equ(float *psrc1, float src2, uchar *pdst, int size, int cmpop);
void compare_neon_equ(float *psrc1, float src2,  uchar *pdst, int size, int cmpop);
void compare_cv_ge(float *psrc1, float src2, uchar *pdst, int size, int cmpop); // greater than or equal 
void compare_neon_ge(float *psrc1, float src2,  uchar *pdst, int size, int cmpop);
void compare_cv_lt(float *psrc1, float src2, uchar *pdst, int size, int cmpop); // less than
void compare_neon_lt(float *psrc1, float src2,  uchar *pdst, int size, int cmpop);
#endif

int main(int argc, char **argv)
{
    float srcArray1[SIZE];
    float srcArray2[SIZE];
    uchar srcDst[SIZE];
    uchar srcDst2[SIZE];
	for(int i = 0; i < SIZE; i++){
		srcArray1[i] = (float)(i + 30);
	}
	float test = 52.0;
	printf("opencv result \n");
    //compare_cv(srcArray1, srcArray2, srcDst, cols, rows, 0);
    struct timeval tstart1, tend1, tstart2, tend2;
	gettimeofday(&tstart1, NULL);
    //compare_cv_equ(srcArray1, test, srcDst, SIZE, 0);
    compare_cv_ge(srcArray1, test, srcDst, SIZE, 0);
	gettimeofday(&tend1, NULL);
	printf("neon result \n");
   //compare_ori(srcArray1, srcArray2, srcDst, cols, rows, 0);
	gettimeofday(&tstart2, NULL);
	//compare_neon_equ(srcArray1, test, srcDst2, SIZE, 0);
	compare_neon_ge(srcArray1, test, srcDst2, SIZE, 0);
	gettimeofday(&tend2, NULL);
	double time1 = COST_TIME(tstart1, tend1);
	double time2 = COST_TIME(tstart2, tend2);
	printf("opencv cost %.2f\n", time1/1000);
	printf("neon cost %.2f\n", time2/1000);

    return 0;
}
#if 0
void compare_cv_equ(float *psrc1, float src2, uchar *pdst, int size, int cmpop)
{
	Mat srcMat1(ROW, COL, CV_32FC1, psrc1);
	//Mat srcMat2(rows, cols, CV_32FC1, psrc2);
	Mat dstMat(ROW, COL, CV_8UC1, pdst);
	compare(srcMat1, src2, dstMat, CMP_EQ);
#if 1
	for(int i = 0; i < ROW; i++){
		for(int j = 0; j < COL; j++){
			printf("%d ", dstMat.at<uchar>(i,j));
		}
		printf("\n");
	}
#endif
}

void compare_neon_equ(float *psrc1, float src2,  uchar *pdst, int size, int cmpop)
{
	int remainder = size - 7;
	float32x4_t vsrc2 = vdupq_n_f32(src2);
	int i = 0;
	for(; i < remainder; i += 8){
		float32x4_t vsrc1_32x4 = vld1q_f32(psrc1 + i ); 
		float32x4_t vsrc2_32x4 = vld1q_f32(psrc1 + i + 4); 
		uint32x4_t vdst1 = vceqq_f32(vsrc1_32x4, vsrc2);
		uint32x4_t vdst2 = vceqq_f32(vsrc2_32x4, vsrc2);
		uint16x4_t vdst1_16x4 = vmovn_u32(vdst1);
		uint16x4_t vdst2_16x4 = vmovn_u32(vdst2);
		uint16x8_t vdst_16x8 = vcombine_u16(vdst1_16x4, vdst2_16x4);
		uint8x8_t vdst_8x8 = vmovn_u16(vdst_16x8);
		vst1_u8(pdst + i, vdst_8x8);
	}
	for( ; i < size; i++){
		pdst[i] = (psrc1[i] == src2 ) ? 255 : 0;  
	}

#if 1
for(int i = 0; i < ROW; i++){
	for(int j = 0; j < COL; j++){
			printf("%d ", (unsigned int)pdst[i * COL + j]);
		}
		printf("\n");
	}
#endif
}
#endif
void compare_cv_ge(float *psrc1, float src2, uchar *pdst, int size, int cmpop)
{
	Mat srcMat1(ROW, COL, CV_32FC1, psrc1);
	//Mat srcMat2(rows, cols, CV_32FC1, psrc2);
	Mat dstMat;
	compare(srcMat1, src2, dstMat, CMP_GE);
#if 0
	for(int i = 0; i < ROW; i++){
		for(int j = 0; j < COL; j++){
			printf("%d ", dstMat.at<uchar>(i,j));
		}
		printf("\n");
	}
#endif
}

void compare_neon_ge(float *psrc1, float src2,  uchar *pdst, int size, int cmpop)
{
	int remainder = size - 7;
	float32x4_t vsrc2 = vdupq_n_f32(src2);
	int i = 0;
	for(; i < remainder; i += 8){
		float32x4_t vsrc1_32x4 = vld1q_f32(psrc1 + i ); 
		float32x4_t vsrc2_32x4 = vld1q_f32(psrc1 + i + 4); 
		uint32x4_t vdst1 = vcgeq_f32(vsrc1_32x4, vsrc2);
		uint32x4_t vdst2 = vcgeq_f32(vsrc2_32x4, vsrc2);
		uint16x4_t vdst1_16x4 = vmovn_u32(vdst1);
		uint16x4_t vdst2_16x4 = vmovn_u32(vdst2);
		uint16x8_t vdst_16x8 = vcombine_u16(vdst1_16x4, vdst2_16x4);
		uint8x8_t vdst_8x8 = vmovn_u16(vdst_16x8);
		vst1_u8(pdst + i, vdst_8x8);
	}
	for( ; i < size; i++){
		pdst[i] = (psrc1[i] >= src2 ) ? 255 : 0;  
	}

#if 0
for(int i = 0; i < ROW; i++){
	for(int j = 0; j < COL; j++){
			printf("%d ", (unsigned int)pdst[i * COL + j]);
		}
		printf("\n");
	}
#endif
}
