/*************************************************************************
	> File Name: logicComp.cpp
	> Author: lengjing
	> Mail: jingleng77@163.com 
	> Created Time: Fri Oct  9 10:08:25 2015
 ************************************************************************/

#include<iostream>
#include<stdio.h>
#include <arm_neon.h>
using namespace std;

inline float32x4_t diffSign(float32x4_t a, float32x4_t b);
inline float diffSign(float a, float b);

int main()
{
    float aArray[4] = {2.0f, 3.0f, 2.0f, 1.0f};
    float bArray[4] = {1.0f, 2.0f, 3.0f, 4.0f};
	float result1 = diffSign(aArray[0],bArray[0]);
	float32x4_t vec_a = vld1q_f32(aArray);
	float32x4_t vec_b = vld1q_f32(bArray);
	float32x4_t vec_result = diffSign(vec_a, vec_b);
	float result2[4];
	vst1q_f32(result2, vec_result);
	printf("result1 = %.2f\n", result1);
	printf("result2 = %.2f\n", result2[0]);
	return 0;
}


inline float diffSign(float a, float b)
{
  return a > b ? 1.0f : a < b ? -1.0f : 0.0f; 
}

inline float32x4_t diffSign(float32x4_t a, float32x4_t b)
{
  uint32x4_t resultTmp0;
  uint32x4_t resultTmp1;
  int32x4_t result;

  resultTmp0 = vcgtq_f32(a,b);
  resultTmp0 = vandq_u32(resultTmp0, vdupq_n_u32(1));

#if 0
  resultTmp1 = vcltq_f32(a,b);
  resultTmp1 = vandq_u32(resultTmp0, vdupq_n_u32(1));

  result = vsubq_u32(resultTmp0, resultTmp1);

  return vcvtq_f32_s32(result);
#endif
  return vcvtq_f32_u32(resultTmp0);
}
