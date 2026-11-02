
@{{BLOCK(baston_pesado_bn_gfx)

@=======================================================================
@
@	baston_pesado_bn_gfx, 16x16@4, 
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
	.global baston_pesado_bn_gfxTiles		@ 128 unsigned chars
	.hidden baston_pesado_bn_gfxTiles
baston_pesado_bn_gfxTiles:
	.word 0x00000000,0xDD000000,0x88D00000,0x88D00000,0x28D00000,0x27330000,0xE7330000,0x73300000
	.word 0x00000000,0x000000DD,0x00000D88,0x00000D82,0x00000D88,0x00003372,0x0000337E,0x00000337
	.word 0x33000000,0x23000000,0x22000000,0x22000000,0x22000000,0x22000000,0x22000000,0x20000000
	.word 0x00000033,0x00000032,0x00000022,0x00000022,0x00000023,0x00000023,0x00000022,0x00000002

	.section .rodata
	.align	2
	.global baston_pesado_bn_gfxPal		@ 32 unsigned chars
	.hidden baston_pesado_bn_gfxPal
baston_pesado_bn_gfxPal:
	.hword 0x03E0,0x533E,0x2DF7,0x250F,0x0000,0x2967,0x1AAE,0x1CF5
	.hword 0x0EDE,0x310A,0x4511,0x4999,0x5ABF,0x0DFE,0x7BDB,0x6F25

@}}BLOCK(baston_pesado_bn_gfx)
