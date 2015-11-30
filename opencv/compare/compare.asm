
compare.o:     file format elf32-littlearm


Disassembly of section .text:

00000000 <_Z13compare_cv_gePffPhii>:
   0:	b5f0      	push	{r4, r5, r6, r7, lr}
   2:	4603      	mov	r3, r0
   4:	ed2d 8b02 	vpush	{d8}
   8:	f500 121c 	add.w	r2, r0, #2555904	; 0x270000
   c:	f502 5280 	add.w	r2, r2, #4096	; 0x1000
  10:	f44f 6e48 	mov.w	lr, #3200	; 0xc80
  14:	2704      	movs	r7, #4
  16:	eddf 2b4a 	vldr	d18, [pc, #296]	; 140 <_Z13compare_cv_gePffPhii+0x140>
  1a:	eddf 3b4b 	vldr	d19, [pc, #300]	; 148 <_Z13compare_cv_gePffPhii+0x148>
  1e:	b0af      	sub	sp, #188	; 0xbc
  20:	eddf 0b4b 	vldr	d16, [pc, #300]	; 150 <_Z13compare_cv_gePffPhii+0x150>
  24:	eddf 1b4c 	vldr	d17, [pc, #304]	; 158 <_Z13compare_cv_gePffPhii+0x158>
  28:	a912      	add	r1, sp, #72	; 0x48
  2a:	a803      	add	r0, sp, #12
  2c:	9316      	str	r3, [sp, #88]	; 0x58
  2e:	9318      	str	r3, [sp, #96]	; 0x60
  30:	f10d 0c50 	add.w	ip, sp, #80	; 0x50
  34:	2300      	movs	r3, #0
  36:	921a      	str	r2, [sp, #104]	; 0x68
  38:	9219      	str	r2, [sp, #100]	; 0x64
  3a:	ad1e      	add	r5, sp, #120	; 0x78
  3c:	aa22      	add	r2, sp, #136	; 0x88
  3e:	ae2c      	add	r6, sp, #176	; 0xb0
  40:	edcd 2b12 	vstr	d18, [sp, #72]	; 0x48
  44:	edcd 3b14 	vstr	d19, [sp, #80]	; 0x50
  48:	ac20      	add	r4, sp, #128	; 0x80
  4a:	9317      	str	r3, [sp, #92]	; 0x5c
  4c:	edcd 0b20 	vstr	d16, [sp, #128]	; 0x80
  50:	edcd 1b22 	vstr	d17, [sp, #136]	; 0x88
  54:	931b      	str	r3, [sp, #108]	; 0x6c
  56:	eeb0 8a40 	vmov.f32	s16, s0
  5a:	932d      	str	r3, [sp, #180]	; 0xb4
  5c:	932c      	str	r3, [sp, #176]	; 0xb0
  5e:	9328      	str	r3, [sp, #160]	; 0xa0
  60:	9327      	str	r3, [sp, #156]	; 0x9c
  62:	9326      	str	r3, [sp, #152]	; 0x98
  64:	9324      	str	r3, [sp, #144]	; 0x90
  66:	9325      	str	r3, [sp, #148]	; 0x94
  68:	9329      	str	r3, [sp, #164]	; 0xa4
  6a:	f8cd c070 	str.w	ip, [sp, #112]	; 0x70
  6e:	951d      	str	r5, [sp, #116]	; 0x74
  70:	f8cd e078 	str.w	lr, [sp, #120]	; 0x78
  74:	971f      	str	r7, [sp, #124]	; 0x7c
  76:	922a      	str	r2, [sp, #168]	; 0xa8
  78:	962b      	str	r6, [sp, #172]	; 0xac
  7a:	f7ff fffe 	bl	0 <_ZN2cv11_InputArrayC1ERKNS_3MatE>
  7e:	eeb7 0ac8 	vcvt.f64.f32	d0, s16
  82:	4669      	mov	r1, sp
  84:	a808      	add	r0, sp, #32
  86:	ac20      	add	r4, sp, #128	; 0x80
  88:	ed8d 0b00 	vstr	d0, [sp]
  8c:	f7ff fffe 	bl	0 <_ZN2cv11_InputArrayC1ERKd>
  90:	ac20      	add	r4, sp, #128	; 0x80
  92:	a80d      	add	r0, sp, #52	; 0x34
  94:	4621      	mov	r1, r4
  96:	f7ff fffe 	bl	0 <_ZN2cv12_OutputArrayC1ERNS_3MatE>
  9a:	a803      	add	r0, sp, #12
  9c:	a908      	add	r1, sp, #32
  9e:	aa0d      	add	r2, sp, #52	; 0x34
  a0:	2302      	movs	r3, #2
  a2:	f7ff fffe 	bl	0 <_ZN2cv7compareERKNS_11_InputArrayES2_RKNS_12_OutputArrayEi>
  a6:	9b25      	ldr	r3, [sp, #148]	; 0x94
  a8:	b163      	cbz	r3, c4 <_Z13compare_cv_gePffPhii+0xc4>
  aa:	f3bf 8f5f 	dmb	sy
  ae:	e853 2f00 	ldrex	r2, [r3]
  b2:	1e50      	subs	r0, r2, #1
  b4:	e843 0100 	strex	r1, r0, [r3]
  b8:	2900      	cmp	r1, #0
  ba:	d1f8      	bne.n	ae <_Z13compare_cv_gePffPhii+0xae>
  bc:	2a01      	cmp	r2, #1
  be:	f3bf 8f5f 	dmb	sy
  c2:	d030      	beq.n	126 <_Z13compare_cv_gePffPhii+0x126>
  c4:	982b      	ldr	r0, [sp, #172]	; 0xac
  c6:	2300      	movs	r3, #0
  c8:	9a2a      	ldr	r2, [sp, #168]	; 0xa8
  ca:	42b0      	cmp	r0, r6
  cc:	9328      	str	r3, [sp, #160]	; 0xa0
  ce:	9327      	str	r3, [sp, #156]	; 0x9c
  d0:	9326      	str	r3, [sp, #152]	; 0x98
  d2:	9324      	str	r3, [sp, #144]	; 0x90
  d4:	6013      	str	r3, [r2, #0]
  d6:	9325      	str	r3, [sp, #148]	; 0x94
  d8:	d001      	beq.n	de <_Z13compare_cv_gePffPhii+0xde>
  da:	f7ff fffe 	bl	0 <_ZN2cv8fastFreeEPv>
  de:	9b17      	ldr	r3, [sp, #92]	; 0x5c
  e0:	b163      	cbz	r3, fc <_Z13compare_cv_gePffPhii+0xfc>
  e2:	f3bf 8f5f 	dmb	sy
  e6:	e853 2f00 	ldrex	r2, [r3]
  ea:	1e50      	subs	r0, r2, #1
  ec:	e843 0100 	strex	r1, r0, [r3]
  f0:	2900      	cmp	r1, #0
  f2:	d1f8      	bne.n	e6 <_Z13compare_cv_gePffPhii+0xe6>
  f4:	2a01      	cmp	r2, #1
  f6:	f3bf 8f5f 	dmb	sy
  fa:	d010      	beq.n	11e <_Z13compare_cv_gePffPhii+0x11e>
  fc:	981d      	ldr	r0, [sp, #116]	; 0x74
  fe:	2300      	movs	r3, #0
 100:	9a1c      	ldr	r2, [sp, #112]	; 0x70
 102:	42a8      	cmp	r0, r5
 104:	931a      	str	r3, [sp, #104]	; 0x68
 106:	9319      	str	r3, [sp, #100]	; 0x64
 108:	9318      	str	r3, [sp, #96]	; 0x60
 10a:	9316      	str	r3, [sp, #88]	; 0x58
 10c:	6013      	str	r3, [r2, #0]
 10e:	9317      	str	r3, [sp, #92]	; 0x5c
 110:	d001      	beq.n	116 <_Z13compare_cv_gePffPhii+0x116>
 112:	f7ff fffe 	bl	0 <_ZN2cv8fastFreeEPv>
 116:	b02f      	add	sp, #188	; 0xbc
 118:	ecbd 8b02 	vpop	{d8}
 11c:	bdf0      	pop	{r4, r5, r6, r7, pc}
 11e:	a812      	add	r0, sp, #72	; 0x48
 120:	f7ff fffe 	bl	0 <_ZN2cv3Mat10deallocateEv>
 124:	e7ea      	b.n	fc <_Z13compare_cv_gePffPhii+0xfc>
 126:	4620      	mov	r0, r4
 128:	f7ff fffe 	bl	0 <_ZN2cv3Mat10deallocateEv>
 12c:	e7ca      	b.n	c4 <_Z13compare_cv_gePffPhii+0xc4>
 12e:	4620      	mov	r0, r4
 130:	f7ff fffe 	bl	0 <_Z13compare_cv_gePffPhii>
 134:	a812      	add	r0, sp, #72	; 0x48
 136:	f7ff fffe 	bl	0 <_Z13compare_cv_gePffPhii>
 13a:	f7ff fffe 	bl	0 <__cxa_end_cleanup>
 13e:	e7f9      	b.n	134 <_Z13compare_cv_gePffPhii+0x134>
 140:	42ff4005 	.word	0x42ff4005
 144:	00000002 	.word	0x00000002
 148:	00000320 	.word	0x00000320
 14c:	00000320 	.word	0x00000320
 150:	42ff0000 	.word	0x42ff0000
	...

00000160 <_Z15compare_neon_gePffPhii>:
 160:	b4f0      	push	{r4, r5, r6, r7}
 162:	1fd7      	subs	r7, r2, #7
 164:	2f00      	cmp	r7, #0
 166:	fff4 0c40 	vdup.32	q8, d0[0]
 16a:	dd35      	ble.n	1d8 <_Z15compare_neon_gePffPhii+0x78>
 16c:	4605      	mov	r5, r0
 16e:	2300      	movs	r3, #0
 170:	462c      	mov	r4, r5
 172:	18ce      	adds	r6, r1, r3
 174:	f964 2a8d 	vld1.32	{d18-d19}, [r4]!
 178:	3308      	adds	r3, #8
 17a:	ff42 2ee0 	vcge.f32	q9, q9, q8
 17e:	429f      	cmp	r7, r3
 180:	f964 4a8f 	vld1.32	{d20-d21}, [r4]
 184:	f105 0520 	add.w	r5, r5, #32
 188:	ff44 4ee0 	vcge.f32	q10, q10, q8
 18c:	fff6 2222 	vmovn.i32	d18, q9
 190:	fff6 4224 	vmovn.i32	d20, q10
 194:	ef64 31b4 	vorr	d19, d20, d20
 198:	fff2 2222 	vmovn.i16	d18, q9
 19c:	f946 270f 	vst1.8	{d18}, [r6]
 1a0:	dce6      	bgt.n	170 <_Z15compare_neon_gePffPhii+0x10>
 1a2:	f1a2 0308 	sub.w	r3, r2, #8
 1a6:	f023 0307 	bic.w	r3, r3, #7
 1aa:	3308      	adds	r3, #8
 1ac:	429a      	cmp	r2, r3
 1ae:	dd11      	ble.n	1d4 <_Z15compare_neon_gePffPhii+0x74>
 1b0:	eb00 0083 	add.w	r0, r0, r3, lsl #2
 1b4:	440a      	add	r2, r1
 1b6:	440b      	add	r3, r1
 1b8:	ecf0 7a01 	vldmia	r0!, {s15}
 1bc:	eeb4 0ae7 	vcmpe.f32	s0, s15
 1c0:	eef1 fa10 	vmrs	APSR_nzcv, fpscr
 1c4:	bf94      	ite	ls
 1c6:	f04f 31ff 	movls.w	r1, #4294967295
 1ca:	2100      	movhi	r1, #0
 1cc:	f803 1b01 	strb.w	r1, [r3], #1
 1d0:	4293      	cmp	r3, r2
 1d2:	d1f1      	bne.n	1b8 <_Z15compare_neon_gePffPhii+0x58>
 1d4:	bcf0      	pop	{r4, r5, r6, r7}
 1d6:	4770      	bx	lr
 1d8:	2300      	movs	r3, #0
 1da:	e7e7      	b.n	1ac <_Z15compare_neon_gePffPhii+0x4c>
 1dc:	f3af 8000 	nop.w

Disassembly of section .text._ZN2cv3MatD2Ev:

00000000 <_ZN2cv3MatD1Ev>:
   0:	b538      	push	{r3, r4, r5, lr}
   2:	4604      	mov	r4, r0
   4:	6943      	ldr	r3, [r0, #20]
   6:	b163      	cbz	r3, 22 <_ZN2cv3MatD1Ev+0x22>
   8:	f3bf 8f5f 	dmb	sy
   c:	e853 2f00 	ldrex	r2, [r3]
  10:	1e51      	subs	r1, r2, #1
  12:	e843 1500 	strex	r5, r1, [r3]
  16:	2d00      	cmp	r5, #0
  18:	d1f8      	bne.n	c <_ZN2cv3MatD1Ev+0xc>
  1a:	2a01      	cmp	r2, #1
  1c:	f3bf 8f5f 	dmb	sy
  20:	d010      	beq.n	44 <_ZN2cv3MatD1Ev+0x44>
  22:	6ae0      	ldr	r0, [r4, #44]	; 0x2c
  24:	f104 0130 	add.w	r1, r4, #48	; 0x30
  28:	6aa2      	ldr	r2, [r4, #40]	; 0x28
  2a:	2300      	movs	r3, #0
  2c:	4288      	cmp	r0, r1
  2e:	6223      	str	r3, [r4, #32]
  30:	61e3      	str	r3, [r4, #28]
  32:	61a3      	str	r3, [r4, #24]
  34:	6123      	str	r3, [r4, #16]
  36:	6013      	str	r3, [r2, #0]
  38:	6163      	str	r3, [r4, #20]
  3a:	d001      	beq.n	40 <_ZN2cv3MatD1Ev+0x40>
  3c:	f7ff fffe 	bl	0 <_ZN2cv8fastFreeEPv>
  40:	4620      	mov	r0, r4
  42:	bd38      	pop	{r3, r4, r5, pc}
  44:	f7ff fffe 	bl	0 <_ZN2cv3Mat10deallocateEv>
  48:	e7eb      	b.n	22 <_ZN2cv3MatD1Ev+0x22>
  4a:	bf00      	nop

Disassembly of section .text.startup:

00000000 <main>:
   0:	b5f0      	push	{r4, r5, r6, r7, lr}
   2:	f240 0400 	movw	r4, #0
   6:	ed2d 8b04 	vpush	{d8-d9}
   a:	f2c0 0400 	movt	r4, #0
   e:	6821      	ldr	r1, [r4, #0]
  10:	f649 0e24 	movw	lr, #38948	; 0x9824
  14:	efc0 6054 	vmov.i32	q11, #4	; 0x00000004
  18:	f2c0 0e3a 	movt	lr, #58	; 0x3a
  1c:	efc1 405e 	vmov.i32	q10, #30	; 0x0000001e
  20:	eddf 0b5b 	vldr	d16, [pc, #364]	; 190 <main+0x190>
  24:	eddf 1b5c 	vldr	d17, [pc, #368]	; 198 <main+0x198>
  28:	f5ad 1d6a 	sub.w	sp, sp, #3833856	; 0x3a8000
  2c:	f5ad 5dc1 	sub.w	sp, sp, #6176	; 0x1820
  30:	b083      	sub	sp, #12
  32:	a808      	add	r0, sp, #32
  34:	44ee      	add	lr, sp
  36:	f500 121c 	add.w	r2, r0, #2555904	; 0x270000
  3a:	f502 5280 	add.w	r2, r2, #4096	; 0x1000
  3e:	4603      	mov	r3, r0
  40:	f8ce 1000 	str.w	r1, [lr]
  44:	ef60 28e4 	vadd.i32	q9, q8, q10
  48:	ef60 08e6 	vadd.i32	q8, q8, q11
  4c:	fffb 2662 	vcvt.f32.s32	q9, q9
  50:	f943 2add 	vst1.64	{d18-d19}, [r3 :64]!
  54:	4293      	cmp	r3, r2
  56:	d1f5      	bne.n	44 <main+0x44>
  58:	f240 0000 	movw	r0, #0
  5c:	f246 77d8 	movw	r7, #26584	; 0x67d8
  60:	f2c0 0000 	movt	r0, #0
  64:	f6cf 77c5 	movt	r7, #65477	; 0xffc5
  68:	f7ff fffe 	bl	0 <puts>
  6c:	2100      	movs	r1, #0
  6e:	4668      	mov	r0, sp
  70:	f246 76e8 	movw	r6, #26600	; 0x67e8
  74:	f7ff fffe 	bl	0 <gettimeofday>
  78:	f641 0028 	movw	r0, #6184	; 0x1828
  7c:	f44f 4244 	mov.w	r2, #50176	; 0xc400
  80:	f2c0 0027 	movt	r0, #39	; 0x27
  84:	4468      	add	r0, sp
  86:	f2c0 0209 	movt	r2, #9
  8a:	ed9f 0a47 	vldr	s0, [pc, #284]	; 1a8 <main+0x1a8>
  8e:	2300      	movs	r3, #0
  90:	f6a0 0104 	subw	r1, r0, #2052	; 0x804
  94:	a808      	add	r0, sp, #32
  96:	f7ff fffe 	bl	0 <main>
  9a:	2100      	movs	r1, #0
  9c:	a802      	add	r0, sp, #8
  9e:	f6cf 76c5 	movt	r6, #65477	; 0xffc5
  a2:	f7ff fffe 	bl	0 <gettimeofday>
  a6:	f240 0000 	movw	r0, #0
  aa:	f2c0 0000 	movt	r0, #0
  ae:	f246 75f0 	movw	r5, #26608	; 0x67f0
  b2:	f7ff fffe 	bl	0 <puts>
  b6:	2100      	movs	r1, #0
  b8:	a804      	add	r0, sp, #16
  ba:	f6cf 75c5 	movt	r5, #65477	; 0xffc5
  be:	f7ff fffe 	bl	0 <gettimeofday>
  c2:	f64d 0328 	movw	r3, #55336	; 0xd828
  c6:	f44f 4244 	mov.w	r2, #50176	; 0xc400
  ca:	f2c0 0330 	movt	r3, #48	; 0x30
  ce:	446b      	add	r3, sp
  d0:	ed9f 0a35 	vldr	s0, [pc, #212]	; 1a8 <main+0x1a8>
  d4:	f2a3 4104 	subw	r1, r3, #1028	; 0x404
  d8:	f2c0 0209 	movt	r2, #9
  dc:	2300      	movs	r3, #0
  de:	a808      	add	r0, sp, #32
  e0:	f7ff fffe 	bl	160 <main+0x160>
  e4:	2100      	movs	r1, #0
  e6:	a806      	add	r0, sp, #24
  e8:	ed9f 8b2d 	vldr	d8, [pc, #180]	; 1a0 <main+0x1a0>
  ec:	f7ff fffe 	bl	0 <gettimeofday>
  f0:	f649 0e28 	movw	lr, #38952	; 0x9828
  f4:	f2c0 0e3a 	movt	lr, #58	; 0x3a
  f8:	44ee      	add	lr, sp
  fa:	9802      	ldr	r0, [sp, #8]
  fc:	f244 2340 	movw	r3, #16960	; 0x4240
 100:	f85e 1007 	ldr.w	r1, [lr, r7]
 104:	f2c0 030f 	movt	r3, #15
 108:	9a03      	ldr	r2, [sp, #12]
 10a:	f85e 7006 	ldr.w	r7, [lr, r6]
 10e:	1a46      	subs	r6, r0, r1
 110:	f85e 5005 	ldr.w	r5, [lr, r5]
 114:	f240 0100 	movw	r1, #0
 118:	fb03 2606 	mla	r6, r3, r6, r2
 11c:	1bef      	subs	r7, r5, r7
 11e:	9d01      	ldr	r5, [sp, #4]
 120:	f2c0 0100 	movt	r1, #0
 124:	9807      	ldr	r0, [sp, #28]
 126:	1b75      	subs	r5, r6, r5
 128:	9a05      	ldr	r2, [sp, #20]
 12a:	ee07 5a90 	vmov	s15, r5
 12e:	fb03 0307 	mla	r3, r3, r7, r0
 132:	eef8 0be7 	vcvt.f64.s32	d16, s15
 136:	2001      	movs	r0, #1
 138:	1a9b      	subs	r3, r3, r2
 13a:	ee07 3a90 	vmov	s15, r3
 13e:	eec0 1b88 	vdiv.f64	d17, d16, d8
 142:	eeb8 9be7 	vcvt.f64.s32	d9, s15
 146:	ec53 2b31 	vmov	r2, r3, d17
 14a:	f7ff fffe 	bl	0 <__printf_chk>
 14e:	f240 0100 	movw	r1, #0
 152:	f2c0 0100 	movt	r1, #0
 156:	2001      	movs	r0, #1
 158:	eec9 0b08 	vdiv.f64	d16, d9, d8
 15c:	ec53 2b30 	vmov	r2, r3, d16
 160:	f7ff fffe 	bl	0 <__printf_chk>
 164:	f649 0024 	movw	r0, #38948	; 0x9824
 168:	f2c0 003a 	movt	r0, #58	; 0x3a
 16c:	4468      	add	r0, sp
 16e:	6802      	ldr	r2, [r0, #0]
 170:	2000      	movs	r0, #0
 172:	6823      	ldr	r3, [r4, #0]
 174:	429a      	cmp	r2, r3
 176:	d107      	bne.n	188 <main+0x188>
 178:	f50d 1d6a 	add.w	sp, sp, #3833856	; 0x3a8000
 17c:	f50d 5dc1 	add.w	sp, sp, #6176	; 0x1820
 180:	b003      	add	sp, #12
 182:	ecbd 8b04 	vpop	{d8-d9}
 186:	bdf0      	pop	{r4, r5, r6, r7, pc}
 188:	f7ff fffe 	bl	0 <__stack_chk_fail>
 18c:	f3af 8000 	nop.w
 190:	00000000 	.word	0x00000000
 194:	00000001 	.word	0x00000001
 198:	00000002 	.word	0x00000002
 19c:	00000003 	.word	0x00000003
 1a0:	00000000 	.word	0x00000000
 1a4:	408f4000 	.word	0x408f4000
 1a8:	42500000 	.word	0x42500000

000001ac <_GLOBAL__sub_I_main>:
 1ac:	b510      	push	{r4, lr}
 1ae:	f240 0400 	movw	r4, #0
 1b2:	f2c0 0400 	movt	r4, #0
 1b6:	4620      	mov	r0, r4
 1b8:	f7ff fffe 	bl	0 <_ZNSt8ios_base4InitC1Ev>
 1bc:	f240 0100 	movw	r1, #0
 1c0:	f240 0200 	movw	r2, #0
 1c4:	4620      	mov	r0, r4
 1c6:	f2c0 0100 	movt	r1, #0
 1ca:	f2c0 0200 	movt	r2, #0
 1ce:	e8bd 4010 	ldmia.w	sp!, {r4, lr}
 1d2:	f7ff bffe 	b.w	0 <__aeabi_atexit>
 1d6:	bf00      	nop
