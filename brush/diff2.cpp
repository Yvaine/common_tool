/*************************************************************************
	> File Name: diff2.cpp
	> Author: lengjing
	> Mail: jingleng77@163.com 
	> Created Time: Tue Oct 13 15:27:30 2015
 ************************************************************************/

#include<iostream>
using namespace std;

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
