
@{{BLOCK(corazon_arcano_bn_gfx)

@=======================================================================
@
@	corazon_arcano_bn_gfx, 16x16@4, 
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
	.global corazon_arcano_bn_gfxTiles		@ 128 unsigned chars
	.hidden corazon_arcano_bn_gfxTiles
corazon_arcano_bn_gfxTiles:
	.word 0xE00000E0,0x00888000,0x08999800,0x89333980,0x93333398,0x33373398,0x73373398,0x33973398
	.word 0x0E00000E,0x00088800,0x00899980,0x08933398,0x89333339,0x89397333,0x89333797,0x89333377
	.word 0x33333980,0x73339800,0x7339800E,0x33980000,0x39800E00,0x98000000,0x800E0000,0x00000000
	.word 0x08933397,0x00893339,0xE0089333,0x00008933,0x00E00893,0x00000089,0x0000E008,0x00000000

	.section .rodata
	.align	2
	.global corazon_arcano_bn_gfxPal		@ 32 unsigned chars
	.hidden corazon_arcano_bn_gfxPal
corazon_arcano_bn_gfxPal:
	.hword 0x03E0,0x533E,0x2DF7,0x250F,0x0000,0x2967,0x1AAE,0x1CF5
	.hword 0x0EDE,0x310A,0x4511,0x4999,0x5ABF,0x0DFE,0x7BDB,0x6F25

@}}BLOCK(corazon_arcano_bn_gfx)
