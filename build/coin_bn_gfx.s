
@{{BLOCK(coin_bn_gfx)

@=======================================================================
@
@	coin_bn_gfx, 16x16@4, 
@	+ palette 16 entries, not compressed
@	+ 4 tiles Metatiled by 2x2 not compressed
@	Total size: 32 + 128 = 160
@
@	Time-stamp: 2026-11-01, 12:43:56
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global coin_bn_gfxTiles		@ 128 unsigned chars
	.hidden coin_bn_gfxTiles
coin_bn_gfxTiles:
	.word 0x00000000,0x11B00000,0xAAC10000,0xFFFC1000,0xCCFFC100,0xFCFFFCB0,0xFCFFFA10,0xCCFFFA10
	.word 0x00000000,0x00000B11,0x00001CAA,0x0001CFFF,0x001CFFCC,0x0BCFFFFC,0x01AFFFFC,0x01AFFFCC
	.word 0xCFFFFA10,0xCFFFFA10,0xCCFFFCB0,0xCFFFC100,0xFFFC1000,0xAAC10000,0x11B00000,0x00000000
	.word 0x01AFFFCF,0x01AFFFCF,0x0BCFFFCC,0x001CFFCF,0x0001CFFF,0x00001CAA,0x00000B11,0x00000000

	.section .rodata
	.align	2
	.global coin_bn_gfxPal		@ 32 unsigned chars
	.hidden coin_bn_gfxPal
coin_bn_gfxPal:
	.hword 0x03E0,0x0C01,0x24C5,0x1863,0x1067,0x14AB,0x260B,0x368F
	.hword 0x7FFF,0x4F5A,0x3EF9,0x14C7,0x2E7C,0x4A2E,0x1936,0x479F

@}}BLOCK(coin_bn_gfx)
