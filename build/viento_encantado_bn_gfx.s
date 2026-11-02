
@{{BLOCK(viento_encantado_bn_gfx)

@=======================================================================
@
@	viento_encantado_bn_gfx, 16x16@4, 
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
	.global viento_encantado_bn_gfxTiles		@ 128 unsigned chars
	.hidden viento_encantado_bn_gfxTiles
viento_encantado_bn_gfxTiles:
	.word 0x00000000,0x00000000,0x00000000,0x000D0000,0x55DD0000,0xEEEEE000,0xFFFF00F0,0xD55E00E0
	.word 0x00000000,0x00000000,0x000EE000,0x000E5500,0x000FE555,0x000FFEEE,0x0000FFFF,0x0000E55D
	.word 0x55EE00E0,0xEEF00000,0xFFF00000,0xDDE00F00,0xEE00E000,0xF0000000,0xD0000000,0x00000000
	.word 0x00F0EED5,0x00E0FFEE,0x00000DFF,0x00000DDD,0x000E00FF,0x000FE00F,0x0000F00F,0x00000000

	.section .rodata
	.align	2
	.global viento_encantado_bn_gfxPal		@ 32 unsigned chars
	.hidden viento_encantado_bn_gfxPal
viento_encantado_bn_gfxPal:
	.hword 0x03E0,0x533E,0x2DF7,0x250F,0x0000,0x2967,0x1AAE,0x1CF5
	.hword 0x0EDE,0x310A,0x4511,0x4999,0x5ABF,0x0DFE,0x7BDB,0x6F25

@}}BLOCK(viento_encantado_bn_gfx)
