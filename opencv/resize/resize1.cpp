/*************************************************************************
	> File Name: resize.cpp
	> Author: lengjing
	> Mail: jingleng77@163.com 
	> Created Time: Sat Oct 10 14:37:50 2015
 ************************************************************************/

#include<iostream>
using namespace std;

#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
//#include <arm_neon.h>
#include <stdio.h>
//#include <sys/time.h>
using namespace cv;
using namespace std;
typedef unsigned char uchar;
typedef float T;
typedef float WT;
typedef float AT;
static const int MAX_ESIZE=16;
#define ONE 1

#define COST_TIME(tstart, tend) 1000000 * (tend.tv_sec - tstart.tv_sec) + tend.tv_usec- tstart.tv_usec

static inline int clip(int x, int a, int b)
{
    return x >= a ? (x < b ? x : b-1) : a;
}

void get_output(Mat input, Mat &input1);
void resize_cv_INTER_NEAREST(Mat &src, Mat &dst,Size dsize, double fx, double fy);
void resize_opt_INTER_NEAREST(Mat &src, Mat &dst, Size dsize, double fx, double fy);
void resize_opt_INTER_NEAREST2(Mat &src, Mat &dst, Size dsize, double fx, double fy);
void resize_neon(Mat &src, Mat &dst,Size dsize, double fx, double fy);

void resize_cv_INTER_LINEAR(Mat &src, Mat &dst,Size dsize, double fx, double fy);
void resize_opt_INTER_LINEAR(Mat &src, Mat &dst,Size dsize, double fx, double fy);
void resize_opt_INTER_AREAFAST2(Mat &src, Mat &dst,Size dsize, double fx, double fy);
void resize_neon_INTER_AREAFAST(Mat &src, Mat &dst,Size dsize, double fx, double fy);
void resize_opt_INTER_LINEAR(Mat &src, Mat &dst,Size dsize, double fx, double fy);

void resize_c_INTER_LINEAR(Mat &src, Mat &dst,Size dsize, double fx, double fy);

void resize_c_INTER_LINEAR(uchar *src, uchar *dst, int srcstep, int dststep, int depth,int cn, 
						   Size ssize, Size dsize, double scale_x, double scale_y, 
						   int iscale_x, int iscale_y);

int main(int argc, const char** argv)
{
	Mat input, input_gray;
	Mat _input = imread("autumn.jpg"); 
	if( _input.depth() == CV_32F)
		_input.copyTo(input);
	else
		_input.convertTo(input, CV_32F, 1/ 255.);
	cvtColor(input, input_gray, CV_BGR2GRAY);

	Mat dst1, dst2, dst3, dst4,dst5;
	double fx = 0.717;
	double fy = 0.717;
	Size dsize = Size(saturate_cast<int>(input.cols * fx),
            saturate_cast<int>(input.rows * fy));
	//Size dsize = Size(round(fx * input.cols), round(fy * input.rows));
	dst1.create(dsize, input.type());
	dst2.create(dsize, input.type());
	dst3.create(dsize, input.type());
	dst4.create(dsize, input.type());
	dst5.create(dsize, input.type());
 	resize_cv_INTER_LINEAR(input, dst3, dsize, fx, fy);
	resize_cv_INTER_LINEAR(input, dst4, dsize, fx, fy);
	int depth = input.depth(), cn = input.channels();
	int srcstep = input.step;
	int dststep = dst3.step;
	uchar *pSrc = input.data;
	uchar *pDst = dst5.data;
	Size ssize = input.size();
    double scale_x = 1./fx, scale_y = 1./fy;
    int iscale_x = saturate_cast<int>(scale_x);
	int iscale_y = saturate_cast<int>(scale_y);
	resize_c_INTER_LINEAR(pSrc, pDst, srcstep, dststep, depth, cn, 
						   ssize, dsize, scale_x,  scale_y, 
						    iscale_x,  iscale_y);
#if 0
    struct timeval tstart1, tend1, tstart2, tend2;
    struct timeval tstart3, tend3, tstart4, tend4;
	gettimeofday(&tstart1, NULL);
	resize_cv_INTER_NEAREST(input, dst1, Size(), fx, fy);
	gettimeofday(&tend1, NULL);
	gettimeofday(&tstart2, NULL);
	resize_opt_INTER_NEAREST2(input, dst2, Size(), fx, fy);
	gettimeofday(&tend2, NULL);
    //resize_opt_INTER_NEAREST(input, dst2, dsize, fx, fy);
	gettimeofday(&tstart3, NULL);
	resize_cv_INTER_LINEAR(input, dst3, Size(), fx, fy);
	gettimeofday(&tend3, NULL);
	gettimeofday(&tstart4, NULL);
    //resize_opt_INTER_LINEAR2(input, dst4, Size(), fx, fy);
    resize_neon_INTER_LINEAR(input, dst4, Size(), fx, fy);
	gettimeofday(&tend4, NULL);
	
	double time1 = COST_TIME(tstart1, tend1);
	double time2 = COST_TIME(tstart2, tend2);
	double time3 = COST_TIME(tstart3, tend3);
	double time4 = COST_TIME(tstart4, tend4);
#endif
	//printf("opencv Nearestcost %.2f\n", time1/1000);
	//printf("opt Nearest cost %.2f\n", time2/1000);
	//printf("opencv Linear cost %.2f\n", time3/1000);
	//printf("opt Linear cost %.2f\n", time4/1000);
	//printf("neon Linear cost %.2f\n", time4/1000);
	//imwrite("result_cv_INTER_NEAREST.jpg", dst1);
	//imwrite("result_opt_INTER_NEAREST.jpg", dst2);
#if 0
	get_output(input, input1);
	get_output(dst1, dst1_1);
	get_output(dst2, dst2_1);
	get_output(dst3, dst3_1);
	get_output(dst4, dst4_1);
#endif
	imwrite("input.jpg", input);

	//imwrite("result_cv_INTER_NEAREST.jpg", dst1);
	//imwrite("result_opt_INTER_NEAREST.jpg", dst2);
	imwrite("result_cv_INTER_LINEAR.jpg", dst3);
	imwrite("result_opt_INTER_LINEAR.jpg", dst4);
	imwrite("result_c_INTER_LINEAR.jpg", dst5);
	//cout  << dst3 << endl;
	//cout <<  dst4 << endl;

	return 0;
}
#if 0
void resize_cv_INTER_NEAREST(Mat &src, Mat &dst,Size dsize, double fx, double fy)
{
	resize(src, dst, Size(),0.5,0.5, 0);
}

void resize_opt_INTER_NEAREST(Mat &src, Mat &dst, Size dsize, double fx, double fy)
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

void resize_opt_INTER_NEAREST2(Mat &src, Mat &dst, Size dsize, double fx, double fy)
{
	Size ssize = src.size();
	Size dsize_ = dst.size();
    //Mat dst_tmp = Mat(dsize, src.type(), Scalar::all(0));
	double scale_x = 1.0f / fx;
	double scale_y = 1.0f / fy;

    AutoBuffer<int> _x_ofs(dsize_.width);
    int* x_ofs = _x_ofs;
    int pix_size = (int)src.elemSize();
    int pix_size4 = (int)(pix_size / sizeof(int));
    double ifx = 1./fx, ify = 1./fy;
    int x;

    for( x = 0; x < dsize_.width; x++ )
    {
        int sx = cvFloor(x*ifx);
        x_ofs[x] = std::min(sx, ssize.width-1)*pix_size;
    }

    Range range(0, dsize_.height);
        int y;

        for( y = range.start; y < range.end; y++ )
        {
            uchar* D = dst.data + dst.step*y;
            int sy = std::min(cvFloor(y*ify), ssize.height-1);
            const uchar* S = src.data + src.step*sy;

            switch( pix_size )
            {
            case 1:
                for( x = 0; x <= dsize_.width - 2; x += 2 )
                {
                    uchar t0 = S[x_ofs[x]];
                    uchar t1 = S[x_ofs[x+1]];
                    D[x] = t0;
                    D[x+1] = t1;
                }

                for( ; x < dsize_.width; x++ )
                    D[x] = S[x_ofs[x]];
                break;
            case 2:
                for( x = 0; x < dsize_.width; x++ )
                    *(ushort*)(D + x*2) = *(ushort*)(S + x_ofs[x]);
                break;
            case 3:
                for( x = 0; x < dsize_.width; x++, D += 3 )
                {
                    const uchar* _tS = S + x_ofs[x];
                    D[0] = _tS[0]; D[1] = _tS[1]; D[2] = _tS[2];
                }
                break;
            case 4:
                for( x = 0; x < dsize_.width; x++ )
                    *(int*)(D + x*4) = *(int*)(S + x_ofs[x]);
                break;
            case 6:
                for( x = 0; x < dsize_.width; x++, D += 6 )
                {
                    const ushort* _tS = (const ushort*)(S + x_ofs[x]);
                    ushort* _tD = (ushort*)D;
                    _tD[0] = _tS[0]; _tD[1] = _tS[1]; _tD[2] = _tS[2];
                }
                break;
            case 8:
                for( x = 0; x < dsize_.width; x++, D += 8 )
                {
                    const int* _tS = (const int*)(S + x_ofs[x]);
                    int* _tD = (int*)D;
                    _tD[0] = _tS[0]; _tD[1] = _tS[1];
                }
                break;
            case 12:
                for( x = 0; x < dsize_.width; x++, D += 12 )
                {
                    const int* _tS = (const int*)(S + x_ofs[x]);
                    int* _tD = (int*)D;
                    _tD[0] = _tS[0]; _tD[1] = _tS[1]; _tD[2] = _tS[2];
                }
                break;
            default:
                for( x = 0; x < dsize_.width; x++, D += pix_size )
                {
                    const int* _tS = (const int*)(S + x_ofs[x]);
                    int* _tD = (int*)D;
                    for( int k = 0; k < pix_size4; k++ )
                        _tD[k] = _tS[k];
                }
            }
        }
}

void resize_neon_INTER_NEAREST(Mat &src, Mat &dst,Size dsize, double fx, double fy)
{

    
}
#endif
void resize_cv_INTER_LINEAR(Mat &src, Mat &dst,Size dsize, double fx, double fy)
{
	resize(src, dst, Size(), fx, fy, 1);
}

#if 0
void resize_opt_INTER_LINEAR(Mat &src, Mat &dst,Size dsize, double fx, double fy)
{
	uchar* dataDst = dst.data;
	int stepDst = dst.step;
	uchar* dataSrc = src.data;
	int stepSrc = src.step;
	double scale_x = 1.0 / fx;
	double scale_y = 1.0 / fy;
	int iscale_x = saturate_cast<int>(scale_x);
    int iscale_y = saturate_cast<int>(scale_y);
	bool is_area_fast = std::abs(scale_x - iscale_x) < DBL_EPSILON &&
                std::abs(scale_y - iscale_y) < DBL_EPSILON;
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
#endif
#if 0
void resize_opt_INTER_AREAFAST2(Mat &src, Mat &dst,Size dsize, double fx, double fy)
{
	int depth = src.depth(), cn = src.channels();
    size_t srcstep = src.step / src.elemSize1(); //5760 
	Size ssize = src.size(), dsize_ = dst.size();
	Size ssize1 = ssize;
	Size dsize1_ = dsize_;
    double scale_x = 1./fx, scale_y = 1./fy;
    int iscale_x = saturate_cast<int>(scale_x);
    int iscale_y = saturate_cast<int>(scale_y);
	int area = iscale_x*iscale_y; //4
	AutoBuffer<int> _ofs(area + dsize_.width*cn);
	int* ofs = _ofs;
    int* xofs = ofs + area;
		
	float scale = 1.f/(area);
    int dwidth1 = (ssize.width/scale_x)*cn;
    dsize1_.width *= cn;
    ssize1.width *= cn;
    int dy, dx, k = 0;
	int sx, sy;
	
	for( sy = 0, k = 0; sy < iscale_y; sy++ )
        for( sx = 0; sx < iscale_x; sx++ )
            ofs[k++] = (int)(sy*srcstep + sx*cn);

    for( dx = 0; dx < dsize_.width; dx++ )
    {
        int j = dx * cn;
        sx = iscale_x * j;
        for( k = 0; k < cn; k++ )
            xofs[j + k] = sx + k;
    }
        

		Range range(0, dst.rows);

        for( dy = range.start; dy < range.end; dy++ )
        {
            T* D = (T*)(dst.data + dst.step*dy);
            int sy0 = dy*scale_y;
            int w = sy0 + scale_y <= ssize1.height ? dwidth1 : 0;

            if( sy0 >= ssize1.height )
            {
                for( dx = 0; dx < dsize1_.width; dx++ )
                    D[dx] = 0;
                continue;
            }

#if 0
			{
				const T* nextS = (const T*)((const uchar*)src.data + src.step);
				int dx = 0;

				if (cn == 1)
					for( ; dx < w; ++dx )
					{
						int index = dx*2;
						D[dx] = (T)((S[index] + S[index+1] + nextS[index] + nextS[index+1] + 2) >> 2);
					}
				else if (cn == 3)
					for( ; dx < w; dx += 3 )
					{
						int index = dx*2;
						D[dx] = (T)((S[index] + S[index+3] + nextS[index] + nextS[index+3] + 2) >> 2);
						D[dx+1] = (T)((S[index+1] + S[index+4] + nextS[index+1] + nextS[index+4] + 2) >> 2);
						D[dx+2] = (T)((S[index+2] + S[index+5] + nextS[index+2] + nextS[index+5] + 2) >> 2);
					}
				else
					{
						assert(cn == 4);
						for( ; dx < w; dx += 4 )
						{
							int index = dx*2;
							D[dx] = (T)((S[index] + S[index+4] + nextS[index] + nextS[index+4] + 2) >> 2);
							D[dx+1] = (T)((S[index+1] + S[index+5] + nextS[index+1] + nextS[index+5] + 2) >> 2);
							D[dx+2] = (T)((S[index+2] + S[index+6] + nextS[index+2] + nextS[index+6] + 2) >> 2);
							D[dx+3] = (T)((S[index+3] + S[index+7] + nextS[index+3] + nextS[index+7] + 2) >> 2);
						}
					}
			}
#endif
			dx = 0;
		    const T* tmp_src  = (const T*)(src.data + src.step * sy0)
            for( ; dx < w; dx++ )
            {
				vec_S = v
				const T* S = tmp_src + xofs[dx];
                WT sum = 0;
                k = 0;
                #if CV_ENABLE_UNROLLED
                for( ; k <= area - 4; k += 4 )
                    sum += S[ofs[k]] + S[ofs[k+1]] + S[ofs[k+2]] + S[ofs[k+3]];
                #endif
                for( ; k < area; k++ )
                    sum += S[ofs[k]];

                D[dx] = saturate_cast<T>(sum * scale);
            }

            for( ; dx < dsize1_.width; dx++ )
            {
                WT sum = 0;
                int count = 0, sx0 = xofs[dx];
                if( sx0 >= ssize1.width )
                    D[dx] = 0;

                for( int sy = 0; sy < scale_y; sy++ )
                {
                    if( sy0 + sy >= ssize1.height )
                        break;
                    const T* S = (const T*)(src.data + src.step*(sy0 + sy)) + sx0;
                    for( int sx = 0; sx < scale_x*cn; sx += cn )
                    {
                        if( sx0 + sx >= ssize1.width )
                            break;
                        sum += S[sx];
                        count++;
                    }
                }

                D[dx] = saturate_cast<T>((float)sum/count);
            }
        }
}
#endif
#if 0
void resize_neon_INTER_AREAFAST(Mat &src, Mat &dst,Size dsize, double fx, double fy)
{
	int depth = src.depth(), cn = src.channels();
    size_t srcstep = src.step / src.elemSize1(); //5760 
	Size ssize = src.size(), dsize_ = dst.size();
	Size ssize1 = ssize;
	Size dsize1_ = dsize_;
    double scale_x = 1./fx, scale_y = 1./fy;
    int iscale_x = saturate_cast<int>(scale_x);
    int iscale_y = saturate_cast<int>(scale_y);
	int area = iscale_x*iscale_y; //4
	AutoBuffer<int> _ofs(area + dsize_.width*cn);
	int* ofs = _ofs;
	int* xofs = ofs + area;

	float scale = 1.f/(area);
	int dwidth1 = (ssize.width/scale_x)*cn;
	dsize1_.width *= cn;
	ssize1.width *= cn;
	int dy, dx, k = 0;
	int sx, sy;

	for( sy = 0, k = 0; sy < iscale_y; sy++ )
		for( sx = 0; sx < iscale_x; sx++ )
			ofs[k++] = (int)(sy*srcstep + sx*cn);

	for( dx = 0; dx < dsize_.width; dx++ )
	{
		int j = dx * cn;
		sx = iscale_x * j;
		for( k = 0; k < cn; k++ )
			xofs[j + k] = sx + k;
	}


	Range range(0, dst.rows);

	for( dy = range.start; dy < range.end; dy++ )
	{
		T* D = (T*)(dst.data + dst.step*dy);
		int sy0 = dy*scale_y;
		int w = sy0 + scale_y <= ssize1.height ? dwidth1 : 0;

		if( sy0 >= ssize1.height )
		{
			for( dx = 0; dx < dsize1_.width; dx++ )
				D[dx] = 0;
			continue;
		}

		dx = 0;
#if 1
#if 0
		const T * S_tmp = (const T*)(src.data + src.step * sy0)
		int remainder = w - 3;
		for( ; dx < remainder; dx += 4)
		{
			const T * S = S_tmp + xofs[dx];
			float32x4_t vec1 = vld1q_f32(S  + ofs[0]);
			float32x4_t vec2 = vld1q_f32(S  + ofs[1]);
			float32x4_t vec3 = vld1q_f32(S  + ofs[2]);
			float32x4_t vec4 = vld1q_f32(S  + ofs[3]);
			float32x4_t vectmp0 = vaddq_f32(vec1,vec2);
			float32x4_t vectmp1 = vaddq_f32(vec3,vec4);
			float32x4_t vectmp2 = vaddq_f32(vectmp0,vectmp1);
			vectmp2 = vmulq_n_f32(vectmp2, scale);
			vst1q_f32(D + dx, vectmp2);
		}
#else
		const T * S_tmp = (const T*)(src.data + src.step * sy0)
		for( ; dx < remainder; dx += 4)
		{
			float32x4_t vec_xofs = vld1q_f32(xofs[dx]);
			uint32x4_t S = vaddq_n_u32(S_tmp, vec_xofs);
			float32x4_t vec1 = vld1q_f32(S  + ofs[0]);
			float32x4_t vec2 = vld1q_f32(S  + ofs[1]);
			float32x4_t vec3 = vld1q_f32(S  + ofs[2]);
			float32x4_t vec4 = vld1q_f32(S  + ofs[3]);
			float32x4_t vectmp0 = vaddq_f32(vec1,vec2);
			float32x4_t vectmp1 = vaddq_f32(vec3,vec4);
			float32x4_t vectmp2 = vaddq_f32(vectmp0,vectmp1);
			vectmp2 = vmulq_n_f32(vectmp2, scale);
			vst1q_f32(D + dx, vectmp2);
		}

#endif
		for( ; dx < w; dx++ )
		{
			const T* S = (const T*)(src.data + src.step * sy0) + xofs[dx];
			WT sum = 0;
			k = 0;
			for( ; k < area; k++ )
				sum += S[ofs[k]];
			D[dx] = saturate_cast<T>(sum * scale);
			//D[dx] = float(sum * scale);
		}
#else
		for( ; dx < w; dx++ )
		{
			const T* S = (const T*)(src.data + src.step * sy0) + xofs[dx];
			WT sum = 0;
			k = 0;
			for( ; k < area; k++ )
				sum += S[ofs[k]];
			//D[dx] = saturate_cast<T>(sum * scale);
			D[dx] = float(sum * scale);
		}
#endif
		for( ; dx < dsize1_.width; dx++ )
		{
			WT sum = 0;
			int count = 0, sx0 = xofs[dx];
			if( sx0 >= ssize1.width )
				D[dx] = 0;

			for( int sy = 0; sy < scale_y; sy++ )
			{
				if( sy0 + sy >= ssize1.height )
					break;
				const T* S = (const T*)(src.data + src.step*(sy0 + sy)) + sx0;
				for( int sx = 0; sx < scale_x*cn; sx += cn )
				{
					if( sx0 + sx >= ssize1.width )
						break;
					sum += S[sx];
					count++;
				}
			}

			D[dx] = saturate_cast<T>((float)sum/count);
		}
	}
}
#endif

#if 1
// HResizeLinear
void hresize(const T** src, WT** dst, int count,
                const int* xofs, const AT* alpha,
                int swidth, int dwidth, int cn, int xmin, int xmax ) 
{
    int dx, k;
	int dx0 = 0;
    for( k = 0; k <= count - 2; k++ )
    {
        const T *S0 = src[k], *S1 = src[k+1];
        WT *D0 = dst[k], *D1 = dst[k+1];
        for( dx = dx0; dx < xmax; dx++ )
        {
            int sx = xofs[dx];
            WT a0 = alpha[dx*2], a1 = alpha[dx*2+1];
            WT t0 = S0[sx]*a0 + S0[sx + cn]*a1;
            WT t1 = S1[sx]*a0 + S1[sx + cn]*a1;
            D0[dx] = t0; D1[dx] = t1;
        }

        for( ; dx < dwidth; dx++ )
        {
            int sx = xofs[dx];
            D0[dx] = WT(S0[sx]*ONE); D1[dx] = WT(S1[sx]*ONE);
        }
    }

    for( ; k < count; k++ )
    {
        const T *S = src[k];
        WT *D = dst[k];
        for( dx = 0; dx < xmax; dx++ )
        {
            int sx = xofs[dx];
            D[dx] = S[sx]*alpha[dx*2] + S[sx+cn]*alpha[dx*2+1];
        }

        for( ; dx < dwidth; dx++ )
            D[dx] = WT(S[xofs[dx]]*ONE);
    }
}
int VResizeLinearVec_32f(const uchar** _src, uchar* _dst, const uchar* _beta, int width )
{
#if 0
        if( !checkHardwareSupport(CV_CPU_SSE) )
            return 0;

        const float** src = (const float**)_src;
        const float* beta = (const float*)_beta;
        const float *S0 = src[0], *S1 = src[1];
        float* dst = (float*)_dst;
        int x = 0;

        __m128 b0 = _mm_set1_ps(beta[0]), b1 = _mm_set1_ps(beta[1]);

        if( (((size_t)S0|(size_t)S1)&15) == 0 )
            for( ; x <= width - 8; x += 8 )
            {
                __m128 x0, x1, y0, y1;
                x0 = _mm_load_ps(S0 + x);
                x1 = _mm_load_ps(S0 + x + 4);
                y0 = _mm_load_ps(S1 + x);
                y1 = _mm_load_ps(S1 + x + 4);

                x0 = _mm_add_ps(_mm_mul_ps(x0, b0), _mm_mul_ps(y0, b1));
                x1 = _mm_add_ps(_mm_mul_ps(x1, b0), _mm_mul_ps(y1, b1));

                _mm_storeu_ps( dst + x, x0);
                _mm_storeu_ps( dst + x + 4, x1);
            }
        else
            for( ; x <= width - 8; x += 8 )
            {
                __m128 x0, x1, y0, y1;
                x0 = _mm_loadu_ps(S0 + x);
                x1 = _mm_loadu_ps(S0 + x + 4);
                y0 = _mm_loadu_ps(S1 + x);
                y1 = _mm_loadu_ps(S1 + x + 4);

                x0 = _mm_add_ps(_mm_mul_ps(x0, b0), _mm_mul_ps(y0, b1));
                x1 = _mm_add_ps(_mm_mul_ps(x1, b0), _mm_mul_ps(y1, b1));

                _mm_storeu_ps( dst + x, x0);
                _mm_storeu_ps( dst + x + 4, x1);
            }

        return x;
#endif
}
//struct VResizeLinear

void vresize(const WT** src, T* dst, const AT* beta, int width )
{
    WT b0 = beta[0], b1 = beta[1];
    const WT *S0 = src[0], *S1 = src[1];

    int x = VResizeLinearVec_32f((const uchar**)src, (uchar*)dst, (const uchar*)beta, width);
    #if CV_ENABLE_UNROLLED
    for( ; x <= width - 4; x += 4 )
    {
        WT t0, t1;
        t0 = S0[x]*b0 + S1[x]*b1;
        t1 = S0[x+1]*b0 + S1[x+1]*b1;
        dst[x] = saturate_cast<WT>(t0); dst[x+1] = saturate_cast<WT>(t1);
        t0 = S0[x+2]*b0 + S1[x+2]*b1;
        t1 = S0[x+3]*b0 + S1[x+3]*b1;
        dst[x+2] = saturate_cast<WT>(t0); dst[x+3] = saturate_cast<WT>(t1);
    }
    #endif
    for( ; x < width; x++ )
        dst[x] = saturate_cast<WT>(S0[x]*b0 + S1[x]*b1);
}



void resize_opt_INTER_LINEAR(Mat &src, Mat &dst,Size dsize, double fx, double fy)
{
	int depth = src.depth(), cn = src.channels();
	Size ssize = src.size();
    double scale_x = 1./fx, scale_y = 1./fy;
    int k, sx, sy, dx, dy;

	int iscale_x = saturate_cast<int>(scale_x);
	int iscale_y = saturate_cast<int>(scale_y);
	int xmin = 0, xmax = dsize.width, width = dsize.width*cn;
   
    int ksize=0, ksize2;
	ksize = 2;
	ksize2 = ksize/2;
	AutoBuffer<uchar> _buffer((width + dsize.height)*(sizeof(int) + sizeof(float)*ksize));
    int* xofs = (int*)(uchar*)_buffer;
    int* yofs = xofs + width;
    float* alpha = (float*)(yofs + dsize.height);
    short* ialpha = (short*)alpha;
    float* beta = alpha + width*ksize;
    short* ibeta = ialpha + width*ksize;
    float cbuf[MAX_ESIZE];
	for( dx = 0; dx < dsize.width; dx++ )
    {
		fx = (float)((dx+0.5)*scale_x - 0.5);
		sx = cvFloor(fx);
		fx -= sx;
		if( sx < ksize2-1 )
		{
		xmin = dx+1;
		if( sx < 0 )
			fx = 0, sx = 0;
		}

        if( sx + ksize2 >= ssize.width )
        {
            xmax = std::min( xmax, dx );
            if( sx >= ssize.width-1 )
                fx = 0, sx = ssize.width-1;
        }
		for( k = 0, sx *= cn; k < cn; k++ )
		xofs[dx*cn + k] = sx + k;
		
		cbuf[0] = 1.f - fx;
		cbuf[1] = fx;
			
		for( k = 0; k < ksize; k++ )
			alpha[dx*cn*ksize + k] = cbuf[k];
		for( ; k < cn*ksize; k++ )
			alpha[dx*cn*ksize + k] = alpha[dx*cn*ksize + k - ksize];
	}
	for( dy = 0; dy < dsize.height; dy++ )
    {
        
		fy = (float)((dy+0.5)*scale_y - 0.5);
		sy = cvFloor(fy);
		fy -= sy;
		yofs[dy] = sy;
		cbuf[0] = 1.f - fy;
        cbuf[1] = fy;
		for( k = 0; k < ksize; k++ )
                beta[dy*ksize + k] = cbuf[k];
		
	}
    ssize.width *= cn;
    dsize.width *= cn;
    xmin *= cn;
    xmax *= cn;
    // image resize is a separable operation. In case of not too strong

    Range range(0, dsize.height);

        int bufstep = (int)alignSize(dsize.width, 16);
        AutoBuffer<WT> _buffer1(bufstep*ksize);
        const T* srows[MAX_ESIZE]={0};
        WT* rows[MAX_ESIZE]={0};
        int prev_sy[MAX_ESIZE];

        for(int k = 0; k < ksize; k++ )
        {
            prev_sy[k] = -1;
            rows[k] = (WT*)_buffer1 + bufstep*k;
        }

        const AT* beta_ = beta + ksize * range.start;

        for( dy = range.start; dy < range.end; dy++, beta_ += ksize )
        {
            int sy0 = yofs[dy], k0=ksize, k1=0, ksize2 = ksize/2;

            for(int k = 0; k < ksize; k++ )
            {
                int sy = clip(sy0 - ksize2 + 1 + k, 0, ssize.height);
                for( k1 = std::max(k1, k); k1 < ksize; k1++ )
                {
                    if( sy == prev_sy[k1] ) // if the sy-th row has been computed already, reuse it.
                    {
                        if( k1 > k )
                            memcpy( rows[k], rows[k1], bufstep*sizeof(rows[0][0]) );
                        break;
                    }
                }
                if( k1 == ksize )
                    k0 = std::min(k0, k); // remember the first row that needs to be computed
                srows[k] = (T*)(src.data + src.step*sy);
                prev_sy[k] = sy;
            }

            if( k0 < ksize )
                hresize( (const T**)(srows + k0), (WT**)(rows + k0), ksize - k0, xofs, (const AT*)(alpha),
                        ssize.width, dsize.width, cn, xmin, xmax ); // HResizeLinear operator()
            vresize( (const WT**)rows, (T*)(dst.data + dst.step*dy), beta_, dsize.width ); // 
        }
}


void resize_c_INTER_LINEAR(uchar *src, uchar *dst, int srcstep, int dststep, int depth,int cn, 
						   Size ssize, Size dsize, double scale_x, double scale_y, 
						   int iscale_x, int iscale_y)
{
    int k, sx, sy, dx, dy;


	int xmin = 0, xmax = dsize.width, width = dsize.width*cn;
    float fx, fy;
    int ksize, ksize2;
	ksize = 2;
	ksize2 = ksize/2;
	AutoBuffer<uchar> _buffer((width + dsize.height)*(sizeof(int) + sizeof(float)*ksize));
    int* xofs = (int*)(uchar*)_buffer;
    int* yofs = xofs + width;
    float* alpha = (float*)(yofs + dsize.height);
    short* ialpha = (short*)alpha;
    float* beta = alpha + width*ksize;
    short* ibeta = ialpha + width*ksize;
    float cbuf[MAX_ESIZE];
	for( dx = 0; dx < dsize.width; dx++ )
    {
		fx = (float)((dx+0.5)*scale_x - 0.5);
		sx = cvFloor(fx);
		fx -= sx;
		if( sx < ksize2-1 )
		{
		xmin = dx+1;
		if( sx < 0 )
			fx = 0, sx = 0;
		}

        if( sx + ksize2 >= ssize.width )
        {
            xmax = std::min( xmax, dx );
            if( sx >= ssize.width-1 )
                fx = 0, sx = ssize.width-1;
        }
		for( k = 0, sx *= cn; k < cn; k++ )
		xofs[dx*cn + k] = sx + k;
		
		cbuf[0] = 1.f - fx;
		cbuf[1] = fx;
			
		for( k = 0; k < ksize; k++ )
			alpha[dx*cn*ksize + k] = cbuf[k];
		for( ; k < cn*ksize; k++ )
			alpha[dx*cn*ksize + k] = alpha[dx*cn*ksize + k - ksize];
	}
	for( dy = 0; dy < dsize.height; dy++ )
    {
        
		fy = (float)((dy+0.5)*scale_y - 0.5);
		sy = cvFloor(fy);
		fy -= sy;
		yofs[dy] = sy;
		cbuf[0] = 1.f - fy;
        cbuf[1] = fy;
		for( k = 0; k < ksize; k++ )
                beta[dy*ksize + k] = cbuf[k];
		
	}
    ssize.width *= cn;
    dsize.width *= cn;
    xmin *= cn;
    xmax *= cn;
    // image resize is a separable operation. In case of not too strong

    Range range(0, dsize.height);

        int bufstep = (int)alignSize(dsize.width, 16);
        AutoBuffer<WT> _buffer1(bufstep*ksize);
        const T* srows[MAX_ESIZE]={0};
        WT* rows[MAX_ESIZE]={0};
        int prev_sy[MAX_ESIZE];

        for(int k = 0; k < ksize; k++ )
        {
            prev_sy[k] = -1;
            rows[k] = (WT*)_buffer1 + bufstep*k;
        }

        const AT* beta_ = beta + ksize * range.start;

        for( dy = range.start; dy < range.end; dy++, beta_ += ksize )
        {
            int sy0 = yofs[dy], k0=ksize, k1=0, ksize2 = ksize/2;

            for(int k = 0; k < ksize; k++ )
            {
                int sy = clip(sy0 - ksize2 + 1 + k, 0, ssize.height);
                for( k1 = std::max(k1, k); k1 < ksize; k1++ )
                {
                    if( sy == prev_sy[k1] ) // if the sy-th row has been computed already, reuse it.
                    {
                        if( k1 > k )
                            memcpy( rows[k], rows[k1], bufstep*sizeof(rows[0][0]) );
                        break;
                    }
                }
                if( k1 == ksize )
                    k0 = std::min(k0, k); // remember the first row that needs to be computed
                srows[k] = (T*)(src + srcstep*sy);
                prev_sy[k] = sy;
            }

            if( k0 < ksize )
                hresize( (const T**)(srows + k0), (WT**)(rows + k0), ksize - k0, xofs, (const AT*)(alpha),
                        ssize.width, dsize.width, cn, xmin, xmax ); // HResizeLinear operator()
            vresize( (const WT**)rows, (T*)(dst + dststep*dy), beta_, dsize.width ); // 
        }
}




#endif
