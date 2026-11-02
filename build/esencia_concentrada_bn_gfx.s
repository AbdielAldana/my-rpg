
@{{BLOCK(esencia_concentrada_bn_gfx)

@=======================================================================
@
@	esencia_concentrada_bn_gfx, 16x16@4, 
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
	.global esencia_concentrada_bn_gfxTiles		@ 128 unsigned chars
	.hidden esencia_concentrada_bn_gfxTiles
esencia_concentrada_bn_gfxTiles:
	.word 0x00000000,0x00000000,0x00000000,0xFF000000,0xEEF00000,0xCEEF0000,0xABEEF000,0x9ACEF000
	.word 0x00000000,0x00000000,0x00000000,0x000000FF,0x00000FEE,0x0000FEEC,0x000FEEBA,0x000FECA9
	.word 0x9ACEF000,0xABEEF000,0xCEEF0000,0xEEF00000,0xFF000000,0x00000000,0x00000000,0x00000000
	.word 0x000FECA9,0x000FEEBA,0x0000FEEC,0x00000FEE,0x000000FF,0x00000000,0x00000000,0x00000000

	.section .rodata
	.align	2
	.global esencia_concentrada_bn_gfxPal		@ 32 unsigned chars
	.hidden esencia_concentrada_bn_gfxPal
esencia_concentrada_bn_gfxPal:
	.hword 0x03E0,0x533E,0x2DF7,0x250F,0x0000,0x2967,0x1AAE,0x1CF5
	.hword 0x0EDE,0x310A,0x4511,0x4999,0x5ABF,0x0DFE,0x7BDB,0x6F25

@}}BLOCK(esencia_concentrada_bn_gfx)
