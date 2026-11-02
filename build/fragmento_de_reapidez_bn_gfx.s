
@{{BLOCK(fragmento_de_reapidez_bn_gfx)

@=======================================================================
@
@	fragmento_de_reapidez_bn_gfx, 16x16@4, 
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
	.global fragmento_de_reapidez_bn_gfxTiles		@ 128 unsigned chars
	.hidden fragmento_de_reapidez_bn_gfxTiles
fragmento_de_reapidez_bn_gfxTiles:
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0xF0000000,0x00000000
	.word 0x00000000,0x00000000,0x000888E0,0x008FFFFE,0x008FEFFE,0x00EFEFFF,0x00FFFFF0,0x000FF0E0
	.word 0x00000000,0x00F00000,0xE0000000,0x00800000,0x0E00F000,0x00000000,0x0000E000,0x00000000
	.word 0x0000080F,0x00000F00,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000

	.section .rodata
	.align	2
	.global fragmento_de_reapidez_bn_gfxPal		@ 32 unsigned chars
	.hidden fragmento_de_reapidez_bn_gfxPal
fragmento_de_reapidez_bn_gfxPal:
	.hword 0x03E0,0x533E,0x2DF7,0x250F,0x0000,0x2967,0x1AAE,0x1CF5
	.hword 0x0EDE,0x310A,0x4511,0x4999,0x5ABF,0x0DFE,0x7BDB,0x6F25

@}}BLOCK(fragmento_de_reapidez_bn_gfx)
