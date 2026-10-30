
@{{BLOCK(librery_back_16x32_bn_gfx)

@=======================================================================
@
@	librery_back_16x32_bn_gfx, 16x32@4, 
@	+ palette 16 entries, not compressed
@	+ 8 tiles Metatiled by 2x4 not compressed
@	Total size: 32 + 256 = 288
@
@	Time-stamp: 2026-10-25, 14:41:54
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global librery_back_16x32_bn_gfxTiles		@ 256 unsigned chars
	.hidden librery_back_16x32_bn_gfxTiles
librery_back_16x32_bn_gfxTiles:
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x11111111,0x22222221
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x11111111,0x12222222
	.word 0x33333321,0x33333321,0x33333321,0x33333321,0x33333321,0x11111111,0x33333331,0x44444441
	.word 0x13333333,0x13333333,0x14333333,0x14333333,0x14444333,0x11111111,0x14433333,0x14444444
	.word 0x34444441,0x44444441,0x33333441,0x44444441,0x33344431,0x44444431,0x44444441,0x44444441
	.word 0x14333333,0x14444444,0x14444443,0x14444444,0x14333333,0x14444444,0x14444444,0x14444444
	.word 0x44444441,0x44444441,0x44444441,0x44444441,0x44444441,0x44444441,0x44444441,0x11111111
	.word 0x14444444,0x14444444,0x14444444,0x14444444,0x14444444,0x14444444,0x14444444,0x11111111

	.section .rodata
	.align	2
	.global librery_back_16x32_bn_gfxPal		@ 32 unsigned chars
	.hidden librery_back_16x32_bn_gfxPal
librery_back_16x32_bn_gfxPal:
	.hword 0x03E0,0x110B,0x4F5A,0x368F,0x260B,0x1911,0x05FA,0x479F
	.hword 0x2549,0x0000,0x0421,0x0421,0x0421,0x0421,0x0421,0x0421

@}}BLOCK(librery_back_16x32_bn_gfx)
