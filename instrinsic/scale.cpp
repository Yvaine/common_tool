/*************************************************************************
	> File Name: scale.cpp
	> Author: lengjing
	> Mail: jingleng77@163.com 
	> Created Time: Fri Oct  9 14:36:03 2015
 ************************************************************************/

#include<iostream>
#include <stdio.h>
#include <arm_neon.h>
#include <sys/time.h>
using namespace std;
//#define SRC_NUM 2073600  
#define SRC_NUM 207360  
//#define DST_NUM 207360  
#define DST_NUM 207360 
void origin_scale_at_the_sample();
void neon_scale_at_the_sample();
void opt_scale_at_the_sample();
#define COUNT_TIME
#define COST_TIME(tstart, tend) 1000000 * (tend.tv_sec - tstart.tv_sec) + tend.tv_usec- tstart.tv_usec
int main()
{
  origin_scale_at_the_sample();
  opt_scale_at_the_sample();
  //neon_scale_at_the_sample();

  return 0;
}


void origin_scale_at_the_sample()
{
	float ptex[SRC_NUM];
	float pout[DST_NUM];
	for(int i = 0; i < SRC_NUM; i++)
		ptex[i] = (float)i;
	for(int i = 0; i < DST_NUM; i++)
        pout[i] = (float)i;

	int num = DST_NUM / 3;
	float wt = 0.1f;
#ifdef COUNT_TIME
    struct timeval tstart1, tend1, tstart2, tend2;
	gettimeofday(&tstart1, NULL);
#endif
	for(int y=0; y < num; y++)
	{
		float scale = (ptex[y*3+0]+ptex[y*3+1]+ptex[y*3+2]) * wt;
		pout[y*3+0] *= scale;
		pout[y*3+1] *= scale;
		pout[y*3+2] *= scale;
	}
#ifdef COUNT_TIME
	gettimeofday(&tend1, NULL);
	double time1 = COST_TIME(tstart1, tend1);
	printf("origin cost %.2f\n", time1/1000);
#endif
	
#ifdef PRINT_RESULT
	for(int x = 0; x < DST_NUM; x++)
	  printf("%.2f ", pout[x]);
	printf("\n");
#endif
}

void opt_scale_at_the_sample()
{
	float ptex[SRC_NUM];
	float pout[DST_NUM];
	for(int i = 0; i < SRC_NUM; i++)
		ptex[i] = (float)i;
	for(int i = 0; i < DST_NUM; i++)
        pout[i] = (float)i;

	int num = DST_NUM / 3;
	float wt = 0.1f;
#ifdef COUNT_TIME
    struct timeval tstart1, tend1, tstart2, tend2;
	gettimeofday(&tstart1, NULL);
#endif
	for(int y=0; y < num; y++)
	{
		int tmp = y * 3;
		int tmp1 = tmp + 1;
		int tmp2 = tmp + 2;
		float scale = (ptex[tmp]+ptex[tmp1]+ptex[tmp2]) * wt;
		pout[tmp] *= scale;
		pout[tmp1] *= scale;
		pout[tmp2] *= scale;
	}
#ifdef COUNT_TIME
	gettimeofday(&tend1, NULL);
	double time1 = COST_TIME(tstart1, tend1);
	printf("opt cost %.2f\n", time1/1000);
#endif
	
#ifdef PRINT_RESULT
	for(int x = 0; x < DST_NUM; x++)
	  printf("%.2f ", pout[x]);
	printf("\n");
#endif
}
void neon_scale_at_the_sample()
{
	float ptex[SRC_NUM];
	float pout[DST_NUM];
	for(int i = 0; i < SRC_NUM; i++)
		ptex[i] = (float)i;
	for(int i = 0; i < DST_NUM; i++)
        pout[i] = (float)i;

	int num = DST_NUM / 3;
	float wt = 0.1f;
#ifdef COUNT_TIME
    struct timeval tstart1, tend1, tstart2, tend2;
	gettimeofday(&tstart1, NULL);
#endif
	int x = num - 3;
	int y = 0;
	//float32x4_t wt_vec = vdupq_n_f32(wt);
	float32_t wt_t = (float32_t)wt;
	float * psrc = ptex;
	float * pdst = pout;
#if 0
	for(; y < x; y += 4)
	{
       float32x4x3_t tex_vec = vld3q_f32(psrc);
	   float32x4_t tex_r = tex_vec.val[0];
	   float32x4_t tex_g = tex_vec.val[1];
	   float32x4_t tex_b = tex_vec.val[2];
	   float32x4_t tmp0 = vaddq_f32(tex_r, tex_g);
	   tmp0 = vaddq_f32(tmp0, tex_b);
	   float32x4_t scale_vec = vmulq_n_f32(tmp0,wt_t);
	   float32x4x3_t out_vec = vld3q_f32(pdst);
	   float32x4_t out_r = out_vec.val[0];
	   float32x4_t out_g = out_vec.val[1];
	   float32x4_t out_b = out_vec.val[2];
	   out_r = vmulq_f32(scale_vec, out_r);
	   out_g = vmulq_f32(scale_vec, out_g);
	   out_b = vmulq_f32(scale_vec, out_b);
	   out_vec.val[0] = out_r;
	   out_vec.val[1] = out_g;
	   out_vec.val[2] = out_b;

	   vst3q_f32(pdst, out_vec);
	   psrc += 12;
	   pdst += 12;
	}
#else
	for(; y < x; y += 4)
	{
       float32x4x3_t tex_vec = vld3q_f32(psrc);
	   float32x4_t tex_r = tex_vec.val[0];
	   float32x4_t tex_g = tex_vec.val[1];
	   float32x4_t tex_b = tex_vec.val[2];
	   float32x4_t tmp0 = vmulq_n_f32(tex_r, wt_t);
	   tmp0 = vmlaq_n_f32(tmp0, tex_g, wt_t);
	   float32x4_t scale_vec = vmlaq_n_f32(tmp0, tex_b, wt_t);
	   float32x4x3_t out_vec = vld3q_f32(pdst);
	   float32x4_t out_r = out_vec.val[0];
	   float32x4_t out_g = out_vec.val[1];
	   float32x4_t out_b = out_vec.val[2];
	   out_r = vmulq_f32(scale_vec, out_r);
	   out_g = vmulq_f32(scale_vec, out_g);
	   out_b = vmulq_f32(scale_vec, out_b);
	   out_vec.val[0] = out_r;
	   out_vec.val[1] = out_g;
	   out_vec.val[2] = out_b;

	   vst3q_f32(pdst, out_vec);
	   psrc += 12;
	   pdst += 12;
	}
#endif
	for(; y < num; y++)
	{
		float scale = (ptex[y*3+0]+ptex[y*3+1]+ptex[y*3+2]) * wt;
		pout[y*3+0] *= scale;
		pout[y*3+1] *= scale;
		pout[y*3+2] *= scale;
	}
#ifdef COUNT_TIME
	gettimeofday(&tend1, NULL);
	double time1 = COST_TIME(tstart1, tend1);
	printf("neon cost %.2f\n", time1/1000);
#endif
#ifdef PRINT_RESULT
	for(int x = 0; x < DST_NUM; x++)
	  printf("%.2f ", pout[x]);
	printf("\n");
#endif
}
