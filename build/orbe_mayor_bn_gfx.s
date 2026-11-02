
@{{BLOCK(orbe_mayor_bn_gfx)

@=======================================================================
@
@	orbe_mayor_bn_gfx, 16x16@4, 
@	+ palette 16 entries, not compressed
@	+ 4 tiles Metatiled by 2x2 not compressed
@	Total size: 32 + 128 = 160
@
@	Time-stamp: 2026-11-01, 17:41:55
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global orbe_mayor_bn_gfxTiles		@ 128 unsigned chars
	.hidden orbe_mayor_bn_gfxTiles
orbe_mayor_bn_gfxTiles:
	.word 0x88800000,0x66680000,0x66668000,0x55666800,0xDD556680,0xDDD56668,0x4DDD5668,0x44DD5668
	.word 0x00000888,0x00008666,0x00086666,0x00866655,0x086655DD,0x86665DDD,0x8665DDD4,0x8665DD44
	.word 0x44DD5668,0x4DDD5668,0xDDD56668,0xDD556680,0x55666800,0x66668000,0x66680000,0x88800000
	.word 0x8665DD44,0x8665DDD4,0x86665DDD,0x086655DD,0x00866655,0x00086666,0x00008666,0x00000888

	.section .rodata
	.align	2
	.global orbe_mayor_bn_gfxPal		@ 32 unsigned chars
	.hidden orbe_mayor_bn_gfxPal
orbe_mayor_bn_gfxPal:
	.hword 0x03E0,0x533E,0x2DF7,0x250F,0x0000,0x2967,0x1AAE,0x1CF5
	.hword 0x0EDE,0x310A,0x4511,0x4999,0x5ABF,0x0DFE,0x7BDB,0x6F25

@}}BLOCK(orbe_mayor_bn_gfx)
