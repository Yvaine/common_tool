/*************************************************************************
	> File Name: brush.cpp
	> Author: lengjing
	> Mail: jingleng77@163.com 
	> Created Time: Fri Sep 11 06:51:30 2015
 ************************************************************************/

#include<iostream>
#include <stdio.h>
#include <arm_neon.h>
#include <sys/time.h>
using namespace std;

#define SRC_NUM 16
#define DST_NUM 12
#define bw 380 
#define bh 120
#define COST_TIME(tstart, tend) 1000000 * (tend.tv_sec - tstart.tv_sec) + tend.tv_usec- tstart.tv_usec
void origin_brush_at_the_sample();
void neon_brush_at_the_sample();
//void neon_brush_at_the_sample();
void render_stroke_at_the_sample();

void origin_average_stroke_brightness();
void neon_average_stroke_brightness();
void neon_average_stroke_brightness2();
void neon_average_stroke_brightness3();

void origin_average_stroke_brightness_2();
void neon_average_stroke_brightness_2();
void neon_average_stroke_brightness_21();
struct timeval tstart0, tend0, tstart1, tend1, tstart2, tend2,tstart21, tend21, tstart3, tend3;
double time0, time1,time2, time3, time21;
#define LOOP_NUM 1000
//#define PRINT_RESULT
#define TIME
int count = 0;
int main()
{
	//origin_brush_at_the_sample();
	//neon_brush_at_the_sample();
	//render_stroke_at_the_sample();
#ifdef TIME
	int loop = LOOP_NUM;
	while(--loop)
	{
		if (loop == 1)
			count = 1;
	//	origin_average_stroke_brightness();
		//avg_neon = neon_average_stroke_brightness();
		//avg_neon2 = neon_average_stroke_brightness2();
		//avg_neon3 = neon_average_stroke_brightness3();
		origin_average_stroke_brightness_2();
		neon_average_stroke_brightness_2();
		neon_average_stroke_brightness_21();
	}
	time0 = COST_TIME(tstart0, tend0);
	//time1 = COST_TIME(tstart1, tend1);
	time2 = COST_TIME(tstart2, tend2);
	time21 = COST_TIME(tstart21, tend21);
    //time3 = COST_TIME(tstart2, tend2);
	cout << "time ori = " << time0 << endl;
	cout << "time neon = " << time2 << endl;
	cout << "time neon_2 = " << time21 << endl;
	//cout << "time neon2 = " << time2 << endl;
	//cout << "time neon3 = " << time3 << endl;
#endif
#ifdef PRINT_RESULT
    origin_average_stroke_brightness();
    neon_average_stroke_brightness();
	neon_average_stroke_brightness2();
	neon_average_stroke_brightness3();
	origin_average_stroke_brightness_2();
    neon_average_stroke_brightness_2();
    neon_average_stroke_brightness_21();
#endif
	return 0;

}
void origin_brush_at_the_sample()
{
	float psrc[SRC_NUM];
	float pdst[DST_NUM];
	for(int i = 0; i < SRC_NUM; i++)
		psrc[i] = (float)i;
	for(int i = 0; i < DST_NUM; i++)
        pdst[i] = (float)i;

	float color[3] = {0.5, 0.6, 0.7};
	int x1 = 0;
	int x2 = SRC_NUM >> 2;
	int x = x1;
	
	for(; x<x2; x++)
	{
	 	float alpha = psrc[x*4+3];
		int idx = x*3;
		int idx2 = x*4;
		pdst[idx+0] += (psrc[idx2+0] * color[0] - pdst[idx+0]) * alpha;
		pdst[idx+1] += (psrc[idx2+1] * color[1] - pdst[idx+1]) * alpha;
		pdst[idx+2] += (psrc[idx2+2] * color[2] - pdst[idx+2]) * alpha;

		pdst[idx+0] = min(1.f, pdst[idx+0]);
		pdst[idx+1] = min(1.f, pdst[idx+1]);
		pdst[idx+2] = min(1.f, pdst[idx+2]);
	}
	printf("origin result \n");
	for(int x = 0; x < DST_NUM; x++)
	  printf("%.2f ", pdst[x]);
	printf("\n");
}
#if 0
void neon_brush_at_the_sample()
{
	float psrc[SRC_NUM];
	float pdst[DST_NUM];
	for(int i = 0; i < SRC_NUM; i++)
		psrc[i] = (float)i;
	for(int i = 0; i < DST_NUM; i++)
		pdst[i] = (float)i;
	float color[3] = {0.5, 0.6, 0.7};

	int x1 = 0;
	int x2 = SRC_NUM >> 2;
	int x = x1;
	float *psrc1 = psrc + 4 * x;
	float *pdst1 = pdst + 3 * x;
	int reminder = x2 - 3;
	float32x4_t color0 = vdupq_n_f32(color[0]);
	float32x4_t color1 = vdupq_n_f32(color[1]);
	float32x4_t color2 = vdupq_n_f32(color[2]);

	float32x4_t one = vdupq_n_f32(1);
	for(; x < reminder; x += 4)
	{
		float32x4x4_t vsrc = vld4q_f32(psrc1);
		float32x4_t alpha = vsrc.val[3];
		float32x4_t r = vsrc.val[0];
		float32x4_t g = vsrc.val[1];
		float32x4_t b = vsrc.val[2];

		//float32x2_t r1 = vget_low_f32(r);
		//float32x2_t r2 = vget_high_f32(r);

		//printf("%.2f\n", vget_lane_f32(r1, 0));
		//printf("%.2f\n", vget_lane_f32(r1, 1));
		//printf("%.2f\n", vget_lane_f32(r2, 0));
		//printf("%.2f\n", vget_lane_f32(r2, 1));
		//printf("%f %f %f %f", vget_lane_f32(r2,0), vget_lane_f32(g,0), vget_lane_f32(b,0), vget_lan_f32(a, 0));

		float32x4x3_t vdst = vld3q_f32(pdst1);
		float32x4_t rdst = vdst.val[0];
		float32x4_t gdst = vdst.val[1];
		float32x4_t bdst = vdst.val[2];

		float32x4_t tmp0 = vmulq_f32(r, color0);
		float32x4_t tmp1 = vmulq_f32(g, color1);
		float32x4_t tmp2 = vmulq_f32(b, color2);

		tmp0 = vsubq_f32(tmp0, rdst);
		tmp1 = vsubq_f32(tmp1, gdst);
		tmp2 = vsubq_f32(tmp2, bdst);

		rdst = vmlaq_f32(rdst, alpha, tmp0);
		gdst = vmlaq_f32(gdst, alpha, tmp1);
		bdst = vmlaq_f32(bdst, alpha, tmp2);

		rdst = vminq_f32(rdst, one);
		gdst = vminq_f32(gdst, one);
		bdst = vminq_f32(bdst, one);

		float32x4x3_t tmp_dst;

		tmp_dst.val[0] = rdst;
		tmp_dst.val[1] = gdst;
		tmp_dst.val[2] = bdst;

		vst3q_f32(pdst1, tmp_dst);
		pdst1 += 4 * 3;
		psrc1 += 4 * 4;
	}
	if(x < x2){
		for(; x < x2; x++)
		{
			float alpha = psrc[x*4+3];
			int idx = x*3;
			int idx2 = x*4;
			pdst[idx+0] += (psrc[idx2+0] * color[0] - pdst[idx+0]) * alpha;
			pdst[idx+1] += (psrc[idx2+1] * color[1] - pdst[idx+1]) * alpha;
			pdst[idx+2] += (psrc[idx2+2] * color[2] - pdst[idx+2]) * alpha;

			pdst[idx+0] = min(1.f, pdst[idx+0]);
			pdst[idx+1] = min(1.f, pdst[idx+1]);
			pdst[idx+2] = min(1.f, pdst[idx+2]);

		}
	}
	printf("neon result \n");
	for(int x = 0; x < DST_NUM; x++)
		printf("%.2f ", pdst[x]);
		printf("\n");
}

#endif
void render_stroke_at_the_sample()
{
	float psrc[SRC_NUM];
	float pdst[DST_NUM];
	for(int i = 0; i < SRC_NUM; i++)
		psrc[i] = (float)i;
	for(int i = 0; i < DST_NUM; i++)
        pdst[i] = (float)i;

	float color[3] = {0.5, 0.6, 0.7};
	int x1 = 0;
	int x2 = SRC_NUM >> 2;
	int x = x1;
	float *pdst3 = pdst + 3 * x1;
	float *psrc3 = psrc + 4 * x1;

	float *pdst0 = pdst + 3 * x1;
	float *psrc0 = psrc + 4 * x1;
	float *pdst1 = pdst0 + 1;
	float *pdst2 = pdst0 + 2;
	float *psrc1 = psrc0 + 1;
	float *psrc2 = psrc0 + 2;
	float *palpha = psrc0 + 3;
	for(; x<x2; x++)
	{
		if( *palpha < 1e-3 ) continue;
#if 0 
		*pdst3 += (*psrc3++ * color[0] - *pdst3)* *palpha;
		*pdst3 = min(1.f, *pdst3);
		pdst3++;
		*pdst3 += (*psrc3++ * color[1] - *pdst3)* *palpha;
		*pdst3 = min(1.f, *pdst3);
		pdst3++;
		*pdst3 += (*psrc3++ * color[2] - *pdst3)* *palpha;
		*pdst3 = min(1.f, *pdst3);
		pdst3++;
#else
		*pdst0 += (*psrc0 * color[0] - *pdst0)* *palpha;
		*pdst1 += (*psrc1 * color[1] - *pdst1)* *palpha;
		*pdst2 += (*psrc2 * color[2] - *pdst2)* *palpha;
		*pdst0 = min(1.f, *pdst0);
		*pdst1 = min(1.f, *pdst1);
		*pdst2 = min(1.f, *pdst2);

		pdst0 += 3;
		pdst1 += 3;
		pdst2 += 3;
		psrc0 += 4;
		psrc1 += 4;
		psrc2 += 4;
#endif
		palpha += 4;
	}
	printf("stroke result \n");
	for(int x = 0; x < DST_NUM; x++)
		printf("%.2f ", pdst[x]);
		printf("\n");

}


void  origin_average_stroke_brightness()
{
	int src_num = bw * bh;
	int src_size = src_num << 2;
	float psrc[src_size];
	float avg = 0, cnt = 0;
	for(int i = 0; i < src_size; i++)
		psrc[i] = (float)i * 1.0 / 255.0;
	float *pdata = psrc;
	if(count == 1)
		gettimeofday(&tstart0,NULL);
	for(int i=0; i < src_num; i++, pdata += 4)
	{
		pdata[0] += pdata[1] + pdata[2];
		avg = avg + pdata[0] * pdata[3];
		cnt = cnt + pdata[3];
	}
	avg = avg/cnt;
#ifdef PRINT_RESULT
	cout << "ori avg " << avg << "  ori cnt" << cnt << endl;
#endif
	if(count == 1)
		gettimeofday(&tend0,NULL);

}
void  neon_average_stroke_brightness()
{
	int src_num = bw * bh;
	int src_size = src_num << 2;
	float psrc[src_size];
	float avg = 0, cnt = 0;
	for(int i = 0; i < src_size; i++)
		psrc[i] = (float)i * 1.0 / 255.0;
	float *pdata = psrc;
	int i = 0;
	//int loop_num = src_size >> 2;
	float mul_result[4];
	float a[4];
	if(count == 1)
		gettimeofday(&tstart1,NULL);
	for(; i < src_num - 3; i += 4, pdata += 16)
	{
		float32x4x4_t vec_src = vld4q_f32(pdata);
		float32x4_t r_vec = vec_src.val[0];
		float32x4_t g_vec = vec_src.val[1];
		float32x4_t b_vec = vec_src.val[2];
		float32x4_t a_vec = vec_src.val[3];
		float32x4_t tmp0 = vaddq_f32(r_vec, g_vec);
		float32x4_t tmp1 = vaddq_f32(tmp0, b_vec);
		float32x4_t tmp2 = vmulq_f32(a_vec, tmp1);
		vst1q_f32(mul_result, tmp2);
		vst1q_f32(a, a_vec);
		avg += mul_result[0] + mul_result[1] + mul_result[2] + mul_result[3];
		cnt += a[0] + a[1] + a[2] + a[3];
	}

	for(; i < src_num; i++, pdata += 4)
	{
		pdata[0] += pdata[1] + pdata[2];
		avg = avg + pdata[0] * pdata[3];
		cnt = cnt + pdata[3];
	}
	avg = avg/cnt;
#ifdef PRINT_RESULT
	cout << "neon1 avg " << avg << "  neon cnt" << cnt << endl;
#endif
	if(count == 1)
		gettimeofday(&tend1,NULL);
}

void  neon_average_stroke_brightness2()
{
	int src_num = bw * bh;
	int src_size = src_num << 2;
	float psrc[src_size];
	float avg = 0, cnt = 0;
	for(int i = 0; i < src_size; i++)
		psrc[i] = (float)i * 1.0 / 255.0;
	float *pdata = psrc;
	int i = 0;
	int loop_num = src_size >> 2;
	float mul_result[4];
	float a[4];
	if(count == 1)
		gettimeofday(&tstart2,NULL);
	for(; i < src_num - 7; i += 8, pdata += 32)
	{
		float32x4x4_t vec_src = vld4q_f32(pdata);
		float32x4_t r_vec = vec_src.val[0];
		float32x4_t g_vec = vec_src.val[1];
		float32x4_t b_vec = vec_src.val[2];
		float32x4_t a_vec = vec_src.val[3];
		float32x4_t tmp0 = vaddq_f32(r_vec, g_vec);
		float32x4_t tmp1 = vaddq_f32(tmp0, b_vec);
		float32x4_t tmp2 = vmulq_f32(a_vec, tmp1);

		float32x4x4_t vec_src1 = vld4q_f32(pdata + 16);
		float32x4_t r_vec1 = vec_src1.val[0];
		float32x4_t g_vec1 = vec_src1.val[1];
		float32x4_t b_vec1 = vec_src1.val[2];
		float32x4_t a_vec1 = vec_src1.val[3];
		float32x4_t tmp01 = vaddq_f32(r_vec1, g_vec1);
		float32x4_t tmp11 = vaddq_f32(tmp01, b_vec1);
		float32x4_t tmp21 = vmulq_f32(a_vec1, tmp11);

		float32x4_t tmp_addmul2 = vaddq_f32(tmp2, tmp21);
		vst1q_f32(mul_result, tmp_addmul2);
		float32x4_t tmp_adda2 = vaddq_f32(a_vec, a_vec1);
		vst1q_f32(a, tmp_adda2);
		avg += mul_result[0] + mul_result[1] + mul_result[2] + mul_result[3];
		cnt += a[0] + a[1] + a[2] + a[3];

	}

	for(; i < src_num; i++, pdata += 4)
	{
		pdata[0] += pdata[1] + pdata[2];
		avg += avg + pdata[0] * pdata[3];
		cnt += pdata[3];
	}
	avg = avg/cnt;
#ifdef PRINT_RESULT
	cout << "neon2 avg " << avg << "  neon cnt" << cnt << endl;
#endif
	if(count == 1)
    gettimeofday(&tend2,NULL);
}


void  neon_average_stroke_brightness3()
{
	int src_num = bw * bh;
	int src_size = src_num << 2;
	float psrc[src_size];
	float avg = 0, cnt = 0;
	for(int i = 0; i < src_size; i++)
		psrc[i] = (float)i * 1.0 / 255.0;
	float *pdata = psrc;
	int i = 0;
	float mul_result[4];
	float a[4];
	if(count == 1)
    gettimeofday(&tstart2,NULL);
    float32x4_t g_a_vec = vdupq_n_f32(0.0);
    float32x4_t g_addmul_vec =  vdupq_n_f32(0.0);
	for(; i < src_num - 7; i += 8, pdata += 32)
	{
		float32x4x4_t vec_src = vld4q_f32(pdata);
		float32x4_t r_vec = vec_src.val[0];
		float32x4_t g_vec = vec_src.val[1];
		float32x4_t b_vec = vec_src.val[2];
		float32x4_t a_vec = vec_src.val[3];
		float32x4_t tmp0 = vaddq_f32(r_vec, g_vec);
		float32x4_t tmp1 = vaddq_f32(tmp0, b_vec);
		float32x4_t tmp2 = vmulq_f32(a_vec, tmp1);

		float32x4x4_t vec_src1 = vld4q_f32(pdata + 16);
		float32x4_t r_vec1 = vec_src1.val[0];
		float32x4_t g_vec1 = vec_src1.val[1];
		float32x4_t b_vec1 = vec_src1.val[2];
		float32x4_t a_vec1 = vec_src1.val[3];
		float32x4_t tmp01 = vaddq_f32(r_vec1, g_vec1);
		float32x4_t tmp11 = vaddq_f32(tmp01, b_vec1);
		float32x4_t tmp21 = vmulq_f32(a_vec1, tmp11);

		float32x4_t tmp_addmul2 = vaddq_f32(tmp2, tmp21);
		float32x4_t tmp_adda2 = vaddq_f32(a_vec, a_vec1);
		g_a_vec = vaddq_f32(tmp_adda2, g_a_vec);
		g_addmul_vec = vaddq_f32(tmp_addmul2, g_addmul_vec);
	}
	vst1q_f32(a, g_a_vec);
	vst1q_f32(mul_result, g_addmul_vec);
	avg += mul_result[0] + mul_result[1] + mul_result[2] + mul_result[3];
	cnt += a[0] + a[1] + a[2] + a[3];
	for(; i < src_num; i++, pdata += 4)
	{
		pdata[0] += pdata[1] + pdata[2];
		avg = avg + pdata[0] * pdata[3];
		cnt = cnt + pdata[3];
	}
	avg = avg/cnt;
#ifdef PRINT_RESULT
	cout << "neon3 avg " << avg << "  neon cnt" << cnt << endl;
#endif
	if(count == 1)
    gettimeofday(&tend2,NULL);
}

void  origin_average_stroke_brightness_2()
{
	int src_num = bw * bh;
	int src_size = src_num << 2;
	float psrc[src_size];
	float avg = 0, cnt = 0;
	for(int i = 0; i < src_size; i++)
		psrc[i] = (float)i * 1.0 / 255.0;
	float *pdata = psrc;
if(count == 1)
    gettimeofday(&tstart0,NULL);
	for(int i=0; i < src_num; i++, pdata += 4)
	{
		pdata[0] += pdata[1] + pdata[2];
		avg = avg + pdata[0] * pdata[3];
		cnt = cnt + pdata[3];
	}
	avg = avg/cnt;
	pdata = psrc;
	float stroke_alpha = 1.f;
	for(int i=0; i<bw*bh; i++, pdata+=4)
	{
		pdata[0] = (pdata[0] - avg) * 0.5 + 1.0;// increase contrast and brightness
		pdata[1] = pdata[0];
		pdata[2] = pdata[0];
		pdata[3] *= stroke_alpha;			// change overall alpha according to style
	}
#ifdef PRINT_RESULT
	cout << "ori_2 avg " << avg << "  ori cnt " << cnt << endl;
#if 1
	for(int i=0; i < src_size; i++ )
	{
		cout << psrc[i] << " ";
	}
	cout << endl;
#endif
#endif
	if(count == 1)
		gettimeofday(&tend0,NULL);

}

void  neon_average_stroke_brightness_2()
{
	int src_num = bw * bh;
	int src_size = src_num << 2;
	float psrc[src_size];
	float avg = 0, cnt = 0;
	for(int i = 0; i < src_size; i++)
		psrc[i] = (float)i * 1.0 / 255.0;
	float *pdata = psrc;
	int i = 0;
	int loop_num = src_size >> 2;
	float mul_result[4];
	float a[4];
	if(count == 1)
    gettimeofday(&tstart2,NULL);
    float32x4_t g_a_vec = vdupq_n_f32(0.0);
    float32x4_t g_addmul_vec =  vdupq_n_f32(0.0);
	for(; i < src_num - 7; i += 8, pdata += 32)
	{
		float32x4x4_t vec_src = vld4q_f32(pdata);
		float32x4_t r_vec = vec_src.val[0];
		float32x4_t g_vec = vec_src.val[1];
		float32x4_t b_vec = vec_src.val[2];
		float32x4_t a_vec = vec_src.val[3];
		float32x4_t tmp0 = vaddq_f32(r_vec, g_vec);
		float32x4_t tmp1 = vaddq_f32(tmp0, b_vec);
		float32x4_t tmp2 = vmulq_f32(a_vec, tmp1);

		float32x4x4_t vec_src1 = vld4q_f32(pdata + 16);
		float32x4_t r_vec1 = vec_src1.val[0];
		float32x4_t g_vec1 = vec_src1.val[1];
		float32x4_t b_vec1 = vec_src1.val[2];
		float32x4_t a_vec1 = vec_src1.val[3];
		float32x4_t tmp01 = vaddq_f32(r_vec1, g_vec1);
		float32x4_t tmp11 = vaddq_f32(tmp01, b_vec1);
		float32x4_t tmp21 = vmulq_f32(a_vec1, tmp11);

		float32x4_t tmp_addmul2 = vaddq_f32(tmp2, tmp21);
		float32x4_t tmp_adda2 = vaddq_f32(a_vec, a_vec1);
		g_a_vec = vaddq_f32(tmp_adda2, g_a_vec);
		g_addmul_vec = vaddq_f32(tmp_addmul2, g_addmul_vec);
		pdata[0] = vgetq_lane_f32(tmp1,0); 
		pdata[4] = vgetq_lane_f32(tmp1,1); 
		pdata[8] = vgetq_lane_f32(tmp1,2); 
		pdata[12] = vgetq_lane_f32(tmp1,3); 
		pdata[16] = vgetq_lane_f32(tmp11,0); 
		pdata[20] = vgetq_lane_f32(tmp11,1); 
		pdata[24] = vgetq_lane_f32(tmp11,2); 
		pdata[28] = vgetq_lane_f32(tmp11,3); 
	}
	vst1q_f32(a, g_a_vec);
	vst1q_f32(mul_result, g_addmul_vec);
	avg += mul_result[0] + mul_result[1] + mul_result[2] + mul_result[3];
	cnt += a[0] + a[1] + a[2] + a[3];
	for(; i < src_num; i++, pdata += 4)
	{
		pdata[0] += pdata[1] + pdata[2];
		avg = avg + pdata[0] * pdata[3];
		cnt = cnt + pdata[3];
	}
	avg = avg/cnt;
	pdata = psrc;
	float stroke_alpha = 1.f;
	for(int i=0; i < src_num; i++, pdata+=4)
	{
		pdata[0] = (pdata[0] - avg) * 0.5 + 1.0;// increase contrast and brightness
		pdata[1] = pdata[0];
		pdata[2] = pdata[0];
		pdata[3] *= stroke_alpha;			// change overall alpha according to style
	}
#ifdef PRINT_RESULT
	cout << "neon_2 avg " << avg << "  neon cnt " << cnt << endl;
#if 1
	for(int i=0; i < src_size; i++ )
	{
		cout << psrc[i] << " ";
	}
	cout << endl;
#endif
#endif
	if(count == 1)
    gettimeofday(&tend2,NULL);
}

void  neon_average_stroke_brightness_21()
{
	int src_num = bw * bh;
	int src_size = src_num << 2;
	float psrc[src_size];
	float avg = 0, cnt = 0;
	for(int i = 0; i < src_size; i++)
		psrc[i] = (float)i * 1.0 / 255.0;
	float *pdata = psrc;
	int i = 0;
	int loop_num = src_size >> 2;
	float mul_result[4];
	float a[4];
	if(count == 1)
    gettimeofday(&tstart21,NULL);
    float32x4_t g_a_vec = vdupq_n_f32(0.0);
    float32x4_t g_addmul_vec =  vdupq_n_f32(0.0);
	for(; i < src_num - 7; i += 8, pdata += 32)
	{
		float32x4x4_t vec_src = vld4q_f32(pdata);
		float32x4_t r_vec = vec_src.val[0];
		float32x4_t g_vec = vec_src.val[1];
		float32x4_t b_vec = vec_src.val[2];
		float32x4_t a_vec = vec_src.val[3];
		float32x4_t tmp0 = vaddq_f32(r_vec, g_vec);
		float32x4_t tmp1 = vaddq_f32(tmp0, b_vec);
		float32x4_t tmp2 = vmulq_f32(a_vec, tmp1);

		float32x4x4_t vec_src1 = vld4q_f32(pdata + 16);
		float32x4_t r_vec1 = vec_src1.val[0];
		float32x4_t g_vec1 = vec_src1.val[1];
		float32x4_t b_vec1 = vec_src1.val[2];
		float32x4_t a_vec1 = vec_src1.val[3];
		float32x4_t tmp01 = vaddq_f32(r_vec1, g_vec1);
		float32x4_t tmp11 = vaddq_f32(tmp01, b_vec1);
		float32x4_t tmp21 = vmulq_f32(a_vec1, tmp11);

		float32x4_t tmp_addmul2 = vaddq_f32(tmp2, tmp21);
		float32x4_t tmp_adda2 = vaddq_f32(a_vec, a_vec1);
		g_a_vec = vaddq_f32(tmp_adda2, g_a_vec);
		g_addmul_vec = vaddq_f32(tmp_addmul2, g_addmul_vec);
		pdata[0] = vgetq_lane_f32(tmp1,0); 
		pdata[4] = vgetq_lane_f32(tmp1,1); 
		pdata[8] = vgetq_lane_f32(tmp1,2); 
		pdata[12] = vgetq_lane_f32(tmp1,3); 
		pdata[16] = vgetq_lane_f32(tmp11,0); 
		pdata[20] = vgetq_lane_f32(tmp11,1); 
		pdata[24] = vgetq_lane_f32(tmp11,2); 
		pdata[28] = vgetq_lane_f32(tmp11,3); 
	}
	vst1q_f32(a, g_a_vec);
	vst1q_f32(mul_result, g_addmul_vec);
	avg += mul_result[0] + mul_result[1] + mul_result[2] + mul_result[3];
	cnt += a[0] + a[1] + a[2] + a[3];
	for(; i < src_num; i++, pdata += 4)
	{
		pdata[0] += pdata[1] + pdata[2];
		avg = avg + pdata[0] * pdata[3];
		cnt = cnt + pdata[3];
	}
	avg = avg/cnt;
	float avg1 = 1 - avg * 0.5;
	float32x4_t avg_vec = vdupq_n_f32(avg1);
	pdata = psrc;
	float stroke_alpha = 1.f;
	i = 0;
#if 1
	for(; i < src_num - 3; i += 4, pdata += 16)
	{
		float32x4x4_t vec_src = vld4q_f32(pdata);
		float32x4_t r_vec = vec_src.val[0];
		float32x4_t a_vec = vec_src.val[3];
		float32x4_t tmp_vec = vmulq_n_f32(r_vec, 0.5);
		float32x4_t tmp_vec1 = vaddq_f32(tmp_vec, avg_vec); 
	    float32x4_t a_vec1 = vmulq_n_f32(a_vec, stroke_alpha); 	
		float32x4x4_t vec_dst;
		vec_dst.val[0] = tmp_vec1;
		vec_dst.val[1] = tmp_vec1;
		vec_dst.val[2] = tmp_vec1;
		vec_dst.val[3] = a_vec1;
		vst4q_f32(pdata, vec_dst);
	}
#endif
	for(; i < src_num; i++, pdata+=4)
	{
		pdata[0] = pdata[0] * 0.5 + avg;// increase contrast and brightness
		pdata[1] = pdata[0];
		pdata[2] = pdata[0];
		pdata[3] *= stroke_alpha;			// change overall alpha according to style
	}
#if 0
	for(; i < src_num; i++, pdata += 4)
	{
		pdata[0] += pdata[1] + pdata[2];
		avg = avg + pdata[0] * pdata[3];
		cnt = cnt + pdata[3];
	}
	avg = avg/cnt;
	pdata = psrc;
	float stroke_alpha = 1.f;
	for(int i=0; i<bw*bh; i++, pdata+=4)
	{
		pdata[0] = (pdata[0] - avg) * 0.5 + 1.0;// increase contrast and brightness
		pdata[1] = pdata[0];
		pdata[2] = pdata[0];
		pdata[3] *= stroke_alpha;			// change overall alpha according to style
	}
#endif

#ifdef PRINT_RESULT
	cout << "neon_21 avg " << avg << "  neon cnt " << cnt << endl;
#if 1
	for(int i=0; i < src_size; i++ )
	{
		cout << psrc[i] << " ";
	}
	cout << endl;
#endif
#endif
	if(count == 1)
    gettimeofday(&tend21,NULL);
}
