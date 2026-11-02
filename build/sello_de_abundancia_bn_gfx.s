
@{{BLOCK(sello_de_abundancia_bn_gfx)

@=======================================================================
@
@	sello_de_abundancia_bn_gfx, 16x16@4, 
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
	.global sello_de_abundancia_bn_gfxTiles		@ 128 unsigned chars
	.hidden sello_de_abundancia_bn_gfxTiles
sello_de_abundancia_bn_gfxTiles:
	.word 0x00000000,0x73444000,0x83384000,0x83384000,0x83383000,0x83383000,0x833D3000,0x88DD7000
	.word 0x00000000,0x00044437,0x0004D338,0x0004D33D,0x0003D33D,0x0003D33D,0x0003833D,0x0007888D
	.word 0x83337000,0x88887000,0x83383000,0xD3383000,0xD3384000,0xDDD84000,0x73444000,0x00000000
	.word 0x00073338,0x0007DDD8,0x0003D338,0x00038338,0x00048338,0x00048888,0x00044437,0x00000000

	.section .rodata
	.align	2
	.global sello_de_abundancia_bn_gfxPal		@ 32 unsigned chars
	.hidden sello_de_abundancia_bn_gfxPal
sello_de_abundancia_bn_gfxPal:
	.hword 0x03E0,0x533E,0x2DF7,0x250F,0x0000,0x2967,0x1AAE,0x1CF5
	.hword 0x0EDE,0x310A,0x4511,0x4999,0x5ABF,0x0DFE,0x7BDB,0x6F25

@}}BLOCK(sello_de_abundancia_bn_gfx)
