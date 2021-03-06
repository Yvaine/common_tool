


void compare_neon_ge(float *psrc1, float src2,  uchar *pdst, int size)
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
}

void compare_neon_lt(float *psrc1, float src2,  uchar *pdst, int size)
{
	int remainder = size - 7;
	float32x4_t vsrc2 = vdupq_n_f32(src2);
	int i = 0;
	for(; i < remainder; i += 8){
		float32x4_t vsrc1_32x4 = vld1q_f32(psrc1 + i ); 
		float32x4_t vsrc2_32x4 = vld1q_f32(psrc1 + i + 4); 
		uint32x4_t vdst1 = vcltq_f32(vsrc1_32x4, vsrc2);
		uint32x4_t vdst2 = vcltq_f32(vsrc2_32x4, vsrc2);
		uint16x4_t vdst1_16x4 = vmovn_u32(vdst1);
		uint16x4_t vdst2_16x4 = vmovn_u32(vdst2);
		uint16x8_t vdst_16x8 = vcombine_u16(vdst1_16x4, vdst2_16x4);
		uint8x8_t vdst_8x8 = vmovn_u16(vdst_16x8);
		vst1_u8(pdst + i, vdst_8x8);
	}
	for( ; i < size; i++){
		pdst[i] = (psrc1[i] < src2 ) ? 255 : 0;  
	}
}
