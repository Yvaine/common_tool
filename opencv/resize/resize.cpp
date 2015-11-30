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
#include <arm_neon.h>
#include <stdio.h>
#include <sys/time.h>
using namespace cv;
using namespace std;
typedef unsigned char uchar;
typedef float T;
typedef float WT;
#define COST_TIME(tstart, tend) 1000000 * (tend.tv_sec - tstart.tv_sec) + tend.tv_usec- tstart.tv_usec


void get_output(Mat input, Mat &input1);
void resize_cv_INTER_NEAREST(Mat &src, Mat &dst,Size dsize, double fx, double fy);
void resize_opt_INTER_NEAREST(Mat &src, Mat &dst, Size dsize, double fx, double fy);
void resize_opt_INTER_NEAREST2(Mat &src, Mat &dst, Size dsize, double fx, double fy);
void resize_neon(Mat &src, Mat &dst,Size dsize, double fx, double fy);

void resize_cv_INTER_LINEAR(Mat &src, Mat &dst,Size dsize, double fx, double fy);
void resize_opt_INTER_LINEAR(Mat &src, Mat &dst,Size dsize, double fx, double fy);
void resize_opt_INTER_LINEAR2(Mat &src, Mat &dst,Size dsize, double fx, double fy);
void resize_neon_INTER_LINEAR(Mat &src, Mat &dst,Size dsize, double fx, double fy);

int main(int argc, const char** argv)
{
	Mat input, input_gray;
	Mat _input = imread("autumn.jpg"); 
	if( _input.depth() == CV_32F)
		_input.copyTo(input);
	else
		_input.convertTo(input, CV_32F, 1/ 255.);
	cvtColor(input, input_gray, CV_BGR2GRAY);

	Mat dst1, dst2, dst3, dst4, dst5, dst6;
	double fx = 0.5; // 0.717
	double fy = 0.5; // 0.717
	Size dsize = Size(saturate_cast<int>(input.cols * fx),
            saturate_cast<int>(input.rows * fy));
	//Size dsize = Size(round(fx * input.cols), round(fy * input.rows));
	dst1.create(dsize, input.type());
	dst2.create(dsize, input.type());
	dst3.create(dsize, input.type());
	dst4.create(dsize, input.type());
	dst5.create(dsize, input.type());
	dst6.create(dsize, input.type());
    struct timeval tstart1, tend1, tstart2, tend2;
    struct timeval tstart3, tend3, tstart4, tend4, tstart5, tend5, tstart6, tend6;
	gettimeofday(&tstart1, NULL);
	//resize_cv_INTER_NEAREST(input, dst1, Size(), fx, fy);
	gettimeofday(&tend1, NULL);
	gettimeofday(&tstart2, NULL);
	//resize_opt_INTER_NEAREST2(input, dst2, Size(), fx, fy);
	gettimeofday(&tend2, NULL);
    //resize_opt_INTER_NEAREST(input, dst2, dsize, fx, fy);
	gettimeofday(&tstart3, NULL);
	resize_cv_INTER_LINEAR(input, dst3, Size(), fx, fy);
	gettimeofday(&tend3, NULL);
	gettimeofday(&tstart4, NULL);
    resize_opt_INTER_LINEAR(input, dst4, Size(), fx, fy);
    //resize_neon_INTER_LINEAR(input, dst4, Size(), fx, fy);
	gettimeofday(&tend4, NULL);
	gettimeofday(&tstart5, NULL);
    resize_opt_INTER_LINEAR2(input, dst5, Size(), fx, fy);
	gettimeofday(&tend5, NULL);
	gettimeofday(&tstart6, NULL);
    resize_neon_INTER_LINEAR(input, dst6, Size(), fx, fy);
	gettimeofday(&tend6, NULL);
	
	double time1 = COST_TIME(tstart1, tend1);
	double time2 = COST_TIME(tstart2, tend2);
	double time3 = COST_TIME(tstart3, tend3);
	double time4 = COST_TIME(tstart4, tend4);
	double time5 = COST_TIME(tstart5, tend5);
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
	imwrite("result_cv_INTER_NEAREST.jpg", dst1);
	imwrite("result_opt_INTER_NEAREST.jpg", dst2);
	imwrite("result_cv_INTER_LINEAR.jpg", dst3);
	imwrite("result_opt_INTER_LINEAR.jpg", dst4);
	imwrite("result_opt_INTER_LINEAR2.jpg", dst5);
	imwrite("result_neon_INTER_LINEAR.jpg", dst6);
	//cout  << dst3 << endl;
	//cout <<  dst4 << endl;

	return 0;
}
#if 1
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

// opencv
void resize_opt_INTER_LINEAR2(Mat &src, Mat &dst,Size dsize, double fx, double fy)
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
            for( ; dx < w; dx++ )
            {
                const T* S = (const T*)(src.data + src.step * sy0) + xofs[dx];
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
// neon
void resize_neon_INTER_LINEAR(Mat &src, Mat &dst,Size dsize, double fx, double fy)
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
		int remainder = w - 3;
		for( ; dx < remainder; dx += 4)
		{
			const T * S = (const T*)(src.data + src.step * sy0) + xofs[dx];
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
