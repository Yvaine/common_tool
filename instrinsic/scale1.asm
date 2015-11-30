
scale1.o:     file format elf32-littlearm


Disassembly of section .init:

00008418 <_init>:
    8418:	e92d4008 	push	{r3, lr}
    841c:	eb000057 	bl	8580 <call_weak_fn>
    8420:	e8bd8008 	pop	{r3, pc}

Disassembly of section .plt:

00008424 <.plt>:
    8424:	e52de004 	push	{lr}		; (str lr, [sp, #-4]!)
    8428:	e59fe004 	ldr	lr, [pc, #4]	; 8434 <_init+0x1c>
    842c:	e08fe00e 	add	lr, pc, lr
    8430:	e5bef008 	ldr	pc, [lr, #8]!
    8434:	00008bcc 	.word	0x00008bcc
    8438:	e28fc600 	add	ip, pc, #0, 12
    843c:	e28cca08 	add	ip, ip, #8, 20	; 0x8000
    8440:	e5bcfbcc 	ldr	pc, [ip, #3020]!	; 0xbcc
    8444:	e28fc600 	add	ip, pc, #0, 12
    8448:	e28cca08 	add	ip, ip, #8, 20	; 0x8000
    844c:	e5bcfbc4 	ldr	pc, [ip, #3012]!	; 0xbc4
    8450:	e28fc600 	add	ip, pc, #0, 12
    8454:	e28cca08 	add	ip, ip, #8, 20	; 0x8000
    8458:	e5bcfbbc 	ldr	pc, [ip, #3004]!	; 0xbbc
    845c:	e28fc600 	add	ip, pc, #0, 12
    8460:	e28cca08 	add	ip, ip, #8, 20	; 0x8000
    8464:	e5bcfbb4 	ldr	pc, [ip, #2996]!	; 0xbb4
    8468:	e28fc600 	add	ip, pc, #0, 12
    846c:	e28cca08 	add	ip, ip, #8, 20	; 0x8000
    8470:	e5bcfbac 	ldr	pc, [ip, #2988]!	; 0xbac
    8474:	4778      	bx	pc
    8476:	46c0      	nop			; (mov r8, r8)
    8478:	e28fc600 	add	ip, pc, #0, 12
    847c:	e28cca08 	add	ip, ip, #8, 20	; 0x8000
    8480:	e5bcfba0 	ldr	pc, [ip, #2976]!	; 0xba0

Disassembly of section .text:

00008488 <main>:
    8488:	b500      	push	{lr}
    848a:	f5ad 1dca 	sub.w	sp, sp, #1654784	; 0x194000
    848e:	f5ad 5d80 	sub.w	sp, sp, #4096	; 0x1000
    8492:	efc0 4054 	vmov.i32	q10, #4	; 0x00000004
    8496:	b081      	sub	sp, #4
    8498:	eddf 0b1d 	vldr	d16, [pc, #116]	; 8510 <main+0x88>
    849c:	eddf 1b1e 	vldr	d17, [pc, #120]	; 8518 <main+0x90>
    84a0:	f50d 234a 	add.w	r3, sp, #827392	; 0xca000
    84a4:	f503 6200 	add.w	r2, r3, #2048	; 0x800
    84a8:	466b      	mov	r3, sp
    84aa:	fffb 2660 	vcvt.f32.s32	q9, q8
    84ae:	ef60 08e4 	vadd.i32	q8, q8, q10
    84b2:	f943 2add 	vst1.64	{d18-d19}, [r3 :64]!
    84b6:	4293      	cmp	r3, r2
    84b8:	d1f7      	bne.n	84aa <main+0x22>
    84ba:	f50d 234a 	add.w	r3, sp, #827392	; 0xca000
    84be:	efc0 4054 	vmov.i32	q10, #4	; 0x00000004
    84c2:	f503 6300 	add.w	r3, r3, #2048	; 0x800
    84c6:	eddf 0b12 	vldr	d16, [pc, #72]	; 8510 <main+0x88>
    84ca:	eddf 1b13 	vldr	d17, [pc, #76]	; 8518 <main+0x90>
    84ce:	f503 224a 	add.w	r2, r3, #827392	; 0xca000
    84d2:	f502 6200 	add.w	r2, r2, #2048	; 0x800
    84d6:	fffb 2660 	vcvt.f32.s32	q9, q8
    84da:	ef60 08e4 	vadd.i32	q8, q8, q10
    84de:	f943 2add 	vst1.64	{d18-d19}, [r3 :64]!
    84e2:	4293      	cmp	r3, r2
    84e4:	d1f7      	bne.n	84d6 <main+0x4e>
    84e6:	f50d 214a 	add.w	r1, sp, #827392	; 0xca000
    84ea:	4668      	mov	r0, sp
    84ec:	f501 6100 	add.w	r1, r1, #2048	; 0x800
    84f0:	ed9f 0a0b 	vldr	s0, [pc, #44]	; 8520 <main+0x98>
    84f4:	f44f 3287 	mov.w	r2, #69120	; 0x10e00
    84f8:	f000 f89c 	bl	8634 <_Z24neon_scale_at_the_samplePfS_fi>
    84fc:	2000      	movs	r0, #0
    84fe:	f50d 1dca 	add.w	sp, sp, #1654784	; 0x194000
    8502:	f50d 5d80 	add.w	sp, sp, #4096	; 0x1000
    8506:	b001      	add	sp, #4
    8508:	f85d fb04 	ldr.w	pc, [sp], #4
    850c:	f3af 8000 	nop.w
    8510:	00000000 	.word	0x00000000
    8514:	00000001 	.word	0x00000001
    8518:	00000002 	.word	0x00000002
    851c:	00000003 	.word	0x00000003
    8520:	3dcccccd 	.word	0x3dcccccd

00008524 <_GLOBAL__sub_I_main>:
    8524:	b510      	push	{r4, lr}
    8526:	f241 0434 	movw	r4, #4148	; 0x1034
    852a:	f2c0 0401 	movt	r4, #1
    852e:	4620      	mov	r0, r4
    8530:	f7ff ef94 	blx	845c <_init+0x44>
    8534:	f248 4168 	movw	r1, #33896	; 0x8468
    8538:	f241 022c 	movw	r2, #4140	; 0x102c
    853c:	4620      	mov	r0, r4
    853e:	f2c0 0100 	movt	r1, #0
    8542:	f2c0 0201 	movt	r2, #1
    8546:	e8bd 4010 	ldmia.w	sp!, {r4, lr}
    854a:	f7ff bf93 	b.w	8474 <_init+0x5c>
    854e:	bf00      	nop

00008550 <_start>:
    8550:	f04f 0b00 	mov.w	fp, #0
    8554:	f04f 0e00 	mov.w	lr, #0
    8558:	bc02      	pop	{r1}
    855a:	466a      	mov	r2, sp
    855c:	b404      	push	{r2}
    855e:	b401      	push	{r0}
    8560:	f8df c010 	ldr.w	ip, [pc, #16]	; 8574 <_start+0x24>
    8564:	f84d cd04 	str.w	ip, [sp, #-4]!
    8568:	4803      	ldr	r0, [pc, #12]	; (8578 <_start+0x28>)
    856a:	4b04      	ldr	r3, [pc, #16]	; (857c <_start+0x2c>)
    856c:	f7ff ef6a 	blx	8444 <_init+0x2c>
    8570:	f7ff ef62 	blx	8438 <_init+0x20>
    8574:	00008745 	.word	0x00008745
    8578:	00008489 	.word	0x00008489
    857c:	00008705 	.word	0x00008705

00008580 <call_weak_fn>:
    8580:	e59f3014 	ldr	r3, [pc, #20]	; 859c <call_weak_fn+0x1c>
    8584:	e59f2014 	ldr	r2, [pc, #20]	; 85a0 <call_weak_fn+0x20>
    8588:	e08f3003 	add	r3, pc, r3
    858c:	e7932002 	ldr	r2, [r3, r2]
    8590:	e3520000 	cmp	r2, #0
    8594:	012fff1e 	bxeq	lr
    8598:	eaffffac 	b	8450 <_init+0x38>
    859c:	00008a70 	.word	0x00008a70
    85a0:	00000024 	.word	0x00000024

000085a4 <deregister_tm_clones>:
    85a4:	4b07      	ldr	r3, [pc, #28]	; (85c4 <deregister_tm_clones+0x20>)
    85a6:	f241 0030 	movw	r0, #4144	; 0x1030
    85aa:	f2c0 0001 	movt	r0, #1
    85ae:	1a1b      	subs	r3, r3, r0
    85b0:	2b06      	cmp	r3, #6
    85b2:	d800      	bhi.n	85b6 <deregister_tm_clones+0x12>
    85b4:	4770      	bx	lr
    85b6:	f240 0300 	movw	r3, #0
    85ba:	f2c0 0300 	movt	r3, #0
    85be:	2b00      	cmp	r3, #0
    85c0:	d0f8      	beq.n	85b4 <deregister_tm_clones+0x10>
    85c2:	4718      	bx	r3
    85c4:	00011033 	.word	0x00011033

000085c8 <register_tm_clones>:
    85c8:	f241 0330 	movw	r3, #4144	; 0x1030
    85cc:	f241 0030 	movw	r0, #4144	; 0x1030
    85d0:	f2c0 0301 	movt	r3, #1
    85d4:	f2c0 0001 	movt	r0, #1
    85d8:	1a1b      	subs	r3, r3, r0
    85da:	109b      	asrs	r3, r3, #2
    85dc:	eb03 73d3 	add.w	r3, r3, r3, lsr #31
    85e0:	1059      	asrs	r1, r3, #1
    85e2:	d100      	bne.n	85e6 <register_tm_clones+0x1e>
    85e4:	4770      	bx	lr
    85e6:	f240 0200 	movw	r2, #0
    85ea:	f2c0 0200 	movt	r2, #0
    85ee:	2a00      	cmp	r2, #0
    85f0:	d0f8      	beq.n	85e4 <register_tm_clones+0x1c>
    85f2:	4710      	bx	r2

000085f4 <__do_global_dtors_aux>:
    85f4:	b510      	push	{r4, lr}
    85f6:	f241 0430 	movw	r4, #4144	; 0x1030
    85fa:	f2c0 0401 	movt	r4, #1
    85fe:	7823      	ldrb	r3, [r4, #0]
    8600:	b91b      	cbnz	r3, 860a <__do_global_dtors_aux+0x16>
    8602:	f7ff ffcf 	bl	85a4 <deregister_tm_clones>
    8606:	2301      	movs	r3, #1
    8608:	7023      	strb	r3, [r4, #0]
    860a:	bd10      	pop	{r4, pc}

0000860c <frame_dummy>:
    860c:	f640 700c 	movw	r0, #3852	; 0xf0c
    8610:	f2c0 0001 	movt	r0, #1
    8614:	b508      	push	{r3, lr}
    8616:	6803      	ldr	r3, [r0, #0]
    8618:	b12b      	cbz	r3, 8626 <frame_dummy+0x1a>
    861a:	f240 0300 	movw	r3, #0
    861e:	f2c0 0300 	movt	r3, #0
    8622:	b103      	cbz	r3, 8626 <frame_dummy+0x1a>
    8624:	4798      	blx	r3
    8626:	e8bd 4008 	ldmia.w	sp!, {r3, lr}
    862a:	e7cd      	b.n	85c8 <register_tm_clones>

0000862c <_Z26origin_scale_at_the_samplev>:
    862c:	4770      	bx	lr
    862e:	bf00      	nop

00008630 <_Z23opt_scale_at_the_samplev>:
    8630:	4770      	bx	lr
    8632:	bf00      	nop

00008634 <_Z24neon_scale_at_the_samplePfS_fi>:
    8634:	b5f0      	push	{r4, r5, r6, r7, lr}
    8636:	f1a2 0e03 	sub.w	lr, r2, #3  lr = x
    863a:	f1be 0f00 	cmp.w	lr, #0
    863e:	dd5f      	ble.n	8700 <_Z24neon_scale_at_the_samplePfS_fi+0xcc>
    8640:	460c      	mov	r4, r1
    8642:	4607      	mov	r7, r0
    8644:	2600      	movs	r6, #0                 //r6 = y
    8646:	463d      	mov	r5, r7                     // r7 = ptex
    8648:	4623      	mov	r3, r4                     // r4 = pout
    864a:	f965 658d 	vld3.32	{d22,d24,d26}, [r5]!  //r5 = psrc
    864e:	3604      	adds	r6, #4                // r6 = y
    8650:	45b6      	cmp	lr, r6
    8652:	f107 0730 	add.w	r7, r7, #48	; 0x30
    8656:	f963 058d 	vld3.32	{d16,d18,d20}, [r3]! // r3 = pdst
    865a:	f965 758f 	vld3.32	{d23,d25,d27}, [r5]
    865e:	ee10 5a10 	vmov	r5, s0
    8662:	ef46 cde8 	vadd.f32	q14, q11, q12
    8666:	f963 158f 	vld3.32	{d17,d19,d21}, [r3]
    866a:	ef4c cdea 	vadd.f32	q14, q14, q13   // q14 = tmp0
    866e:	ee07 5b10 	vmov.32	d7[0], r5
    8672:	ffec c9c7 	vmul.f32	q14, q14, d7[0]
    8676:	ff4c 6df0 	vmul.f32	q11, q14, q8
    867a:	ff4c 8df2 	vmul.f32	q12, q14, q9
    867e:	ff4c adf4 	vmul.f32	q13, q14, q10
    8682:	f944 658f 	vst3.32	{d22,d24,d26}, [r4]
    8686:	f104 0430 	add.w	r4, r4, #48	; 0x30
    868a:	f943 758f 	vst3.32	{d23,d25,d27}, [r3]
    868e:	dcda      	bgt.n	8646 <_Z24neon_scale_at_the_samplePfS_fi+0x12>
    8690:	1f13      	subs	r3, r2, #4
    8692:	f023 0303 	bic.w	r3, r3, #3
    8696:	3304      	adds	r3, #4
    8698:	429a      	cmp	r2, r3
    869a:	dd30      	ble.n	86fe <_Z24neon_scale_at_the_samplePfS_fi+0xca>
    869c:	eb03 0343 	add.w	r3, r3, r3, lsl #1
    86a0:	eb02 0242 	add.w	r2, r2, r2, lsl #1
    86a4:	f100 0508 	add.w	r5, r0, #8
    86a8:	009c      	lsls	r4, r3, #2
    86aa:	eb05 0382 	add.w	r3, r5, r2, lsl #2
    86ae:	f104 0208 	add.w	r2, r4, #8
    86b2:	4411      	add	r1, r2
    86b4:	4410      	add	r0, r2
    86b6:	ed10 7a02 	vldr	s14, [r0, #-8]
    86ba:	4602      	mov	r2, r0
    86bc:	300c      	adds	r0, #12
    86be:	ed50 7a04 	vldr	s15, [r0, #-16]
    86c2:	4298      	cmp	r0, r3
    86c4:	edd2 5a00 	vldr	s11, [r2]
    86c8:	ee77 7a27 	vadd.f32	s15, s14, s15
    86cc:	ed11 6a02 	vldr	s12, [r1, #-8]
    86d0:	ed11 7a01 	vldr	s14, [r1, #-4]
    86d4:	edd1 6a00 	vldr	s13, [r1]
    86d8:	ee77 7aa5 	vadd.f32	s15, s15, s11
    86dc:	ee67 7a80 	vmul.f32	s15, s15, s0
    86e0:	ee26 6a27 	vmul.f32	s12, s12, s15
    86e4:	ee27 7a27 	vmul.f32	s14, s14, s15
    86e8:	ed01 6a02 	vstr	s12, [r1, #-8]
    86ec:	ee66 7aa7 	vmul.f32	s15, s13, s15
    86f0:	ed01 7a01 	vstr	s14, [r1, #-4]
    86f4:	ee17 5a90 	vmov	r5, s15
    86f8:	f841 5b0c 	str.w	r5, [r1], #12
    86fc:	d1db      	bne.n	86b6 <_Z24neon_scale_at_the_samplePfS_fi+0x82>
    86fe:	bdf0      	pop	{r4, r5, r6, r7, pc}
    8700:	2300      	movs	r3, #0
    8702:	e7c9      	b.n	8698 <_Z24neon_scale_at_the_samplePfS_fi+0x64>

00008704 <__libc_csu_init>:
    8704:	e92d 43f8 	stmdb	sp!, {r3, r4, r5, r6, r7, r8, r9, lr}
    8708:	4607      	mov	r7, r0
    870a:	4e0c      	ldr	r6, [pc, #48]	; (873c <__libc_csu_init+0x38>)
    870c:	4688      	mov	r8, r1
    870e:	4d0c      	ldr	r5, [pc, #48]	; (8740 <__libc_csu_init+0x3c>)
    8710:	4691      	mov	r9, r2
    8712:	447e      	add	r6, pc
    8714:	f7ff ee80 	blx	8418 <_init>
    8718:	447d      	add	r5, pc
    871a:	1b76      	subs	r6, r6, r5
    871c:	10b6      	asrs	r6, r6, #2
    871e:	d00a      	beq.n	8736 <__libc_csu_init+0x32>
    8720:	3d04      	subs	r5, #4
    8722:	2400      	movs	r4, #0
    8724:	3401      	adds	r4, #1
    8726:	f855 3f04 	ldr.w	r3, [r5, #4]!
    872a:	4638      	mov	r0, r7
    872c:	4641      	mov	r1, r8
    872e:	464a      	mov	r2, r9
    8730:	4798      	blx	r3
    8732:	42b4      	cmp	r4, r6
    8734:	d1f6      	bne.n	8724 <__libc_csu_init+0x20>
    8736:	e8bd 83f8 	ldmia.w	sp!, {r3, r4, r5, r6, r7, r8, r9, pc}
    873a:	bf00      	nop
    873c:	000087f2 	.word	0x000087f2
    8740:	000087e4 	.word	0x000087e4

00008744 <__libc_csu_fini>:
    8744:	4770      	bx	lr
    8746:	bf00      	nop

Disassembly of section .fini:

00008748 <_fini>:
    8748:	e92d4008 	push	{r3, lr}
    874c:	e8bd8008 	pop	{r3, pc}
