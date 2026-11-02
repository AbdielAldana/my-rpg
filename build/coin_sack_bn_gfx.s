
@{{BLOCK(coin_sack_bn_gfx)

@=======================================================================
@
@	coin_sack_bn_gfx, 16x16@4, 
@	+ palette 16 entries, not compressed
@	+ 4 tiles Metatiled by 2x2 not compressed
@	Total size: 32 + 128 = 160
@
@	Time-stamp: 2026-11-01, 18:47:35
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global coin_sack_bn_gfxTiles		@ 128 unsigned chars
	.hidden coin_sack_bn_gfxTiles
coin_sack_bn_gfxTiles:
	.word 0x00000000,0x00000000,0x44400000,0x88840000,0x88400000,0x99000000,0x84400000,0x88440000
	.word 0x00000000,0x00000000,0x00000444,0x00004888,0x00000488,0x00090999,0x00009488,0x0004488E
	.word 0x38844000,0x38884000,0x38884000,0x88884000,0x38884000,0x88844000,0x44440000,0x00000000
	.word 0x00488833,0x0048888E,0x00488833,0x0044883E,0x0004883E,0x0004488E,0x00004444,0x00000000

	.section .rodata
	.align	2
	.global coin_sack_bn_gfxPal		@ 32 unsigned chars
	.hidden coin_sack_bn_gfxPal
coin_sack_bn_gfxPal:
	.hword 0x03E0,0x533E,0x2DF7,0x250F,0x0000,0x2967,0x1AAE,0x1CF5
	.hword 0x0EDE,0x310A,0x4511,0x4999,0x5ABF,0x0DFE,0x7BDB,0x6F25

@}}BLOCK(coin_sack_bn_gfx)
