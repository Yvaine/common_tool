/*************************************************************************
	> File Name: resize_helper.cpp
	> Author: lengjing
	> Mail: jingleng77@163.com 
	> Created Time: Fri Oct 16 15:09:52 2015
 ************************************************************************/

#include<iostream>
using namespace std;


void cv_helper::compare_neon_ge(float *psrc1, float src2,  uchar *pdst, int size)
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

void cv_helper::compare_neon_lt(float *psrc1, float src2,  uchar *pdst, int size)
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
void cv_helper::hresize(const T** src, WT** dst, int count,
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
int cv_hepler::VResizeLinearVec_32f(const uchar** _src, uchar* _dst, const uchar* _beta, int width )
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
		return 0;
}

void cv_helper::vresize(const WT** src, T* dst, const AT* beta, int width )
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

void cv_helper::resize_c_INTER_LINEAR(uchar *src, uchar *dst, int srcstep, int dststep, int depth,int cn, 
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
