
@{{BLOCK(cristal_de_cadencia_bn_gfx)

@=======================================================================
@
@	cristal_de_cadencia_bn_gfx, 16x16@4, 
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
	.global cristal_de_cadencia_bn_gfxTiles		@ 128 unsigned chars
	.hidden cristal_de_cadencia_bn_gfxTiles
cristal_de_cadencia_bn_gfxTiles:
	.word 0x00000000,0x000B0000,0x9000B000,0xF9000B00,0xFF900000,0xFEF90000,0xFFE90000,0xEFFF90B0
	.word 0x00000000,0x0000B000,0x000B0009,0x00B0009E,0x000009FF,0x00009FEF,0x00009FFE,0x0B09FEFF
	.word 0xFFFF90B0,0xFFE90000,0xEFF90000,0xFE900000,0xF9000B00,0x9000B000,0x000B0000,0x00000000
	.word 0x0B09FFFF,0x00009FFE,0x00009EFF,0x000009FF,0x00B0009E,0x000B0009,0x0000B000,0x00000000

	.section .rodata
	.align	2
	.global cristal_de_cadencia_bn_gfxPal		@ 32 unsigned chars
	.hidden cristal_de_cadencia_bn_gfxPal
cristal_de_cadencia_bn_gfxPal:
	.hword 0x03E0,0x533E,0x2DF7,0x250F,0x0000,0x2967,0x1AAE,0x1CF5
	.hword 0x0EDE,0x310A,0x4511,0x4999,0x5ABF,0x0DFE,0x7BDB,0x6F25

@}}BLOCK(cristal_de_cadencia_bn_gfx)
