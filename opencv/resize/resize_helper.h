/*************************************************************************
	> File Name: resize_helper.h
	> Author: lengjing
	> Mail: jingleng77@163.com 
	> Created Time: Fri Oct 16 15:10:22 2015
 ************************************************************************/

#include<iostream>
using namespace std;
using namespace cv;

namespace cv_helper
{
	//compare
	void compare_neon_ge(float *psrc1, float src2,  uchar *pdst, int size);
	void compare_neon_lt(float *psrc1, float src2,  uchar *pdst, int size);
	
	//resize
	typedef float T;
	typedef float WT;
	typedef float AT;
	static const int MAX_ESIZE=16;
	const int ONE = 1;
	static inline int clip(int x, int a, int b)
	{
		return x >= a ? (x < b ? x : b-1) : a;
	}
	void hresize(const T** src, WT** dst, int count,
			const int* xofs, const AT* alpha,
			int swidth, int dwidth, int cn, int xmin, int xmax ); 

	int VResizeLinearVec_32f(const uchar** _src, uchar* _dst, const uchar* _beta, int width );

	void vresize(const WT** src, T* dst, const AT* beta, int width );

	void resize_c_INTER_LINEAR(uchar *src, uchar *dst, int srcstep, int dststep, int depth,
			int cn, Size ssize, Size dsize, double scale_x, double scale_y, 
			int iscale_x, int iscale_y);

};

