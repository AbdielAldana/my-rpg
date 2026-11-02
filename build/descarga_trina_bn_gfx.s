
@{{BLOCK(descarga_trina_bn_gfx)

@=======================================================================
@
@	descarga_trina_bn_gfx, 16x16@4, 
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
	.global descarga_trina_bn_gfxTiles		@ 128 unsigned chars
	.hidden descarga_trina_bn_gfxTiles
descarga_trina_bn_gfxTiles:
	.word 0x00000000,0xEE00E000,0xCEF00000,0xBCE00000,0xBAE000E0,0xAEE00000,0xEEEEF000,0xEEACEE00
	.word 0x00000000,0x000000EE,0x00000EEA,0x00F00EAB,0x00000E9B,0x000E0EE9,0x00EEEEEE,0x0EEACEE0
	.word 0xEABBCE00,0xE9BBAE00,0xEE9AEE00,0x0EEEE000,0xE0000000,0x55550000,0xF5500000,0x55000000
	.word 0x0EABBCE0,0x0E9BBAE0,0x0EE9AEE0,0x00EEEE00,0x00000000,0x000FFFF5,0x0000FFFF,0x00000555

	.section .rodata
	.align	2
	.global descarga_trina_bn_gfxPal		@ 32 unsigned chars
	.hidden descarga_trina_bn_gfxPal
descarga_trina_bn_gfxPal:
	.hword 0x03E0,0x533E,0x2DF7,0x250F,0x0000,0x2967,0x1AAE,0x1CF5
	.hword 0x0EDE,0x310A,0x4511,0x4999,0x5ABF,0x0DFE,0x7BDB,0x6F25

@}}BLOCK(descarga_trina_bn_gfx)
