
@{{BLOCK(totem_de_repeticion_bn_gfx)

@=======================================================================
@
@	totem_de_repeticion_bn_gfx, 16x16@4, 
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
	.global totem_de_repeticion_bn_gfxTiles		@ 128 unsigned chars
	.hidden totem_de_repeticion_bn_gfxTiles
totem_de_repeticion_bn_gfxTiles:
	.word 0x00000000,0xEE00E000,0xCEE00000,0xBCE00000,0xBAE00000,0xAEE00000,0xEE00F000,0xE0000000
	.word 0x00000000,0x000000EE,0x00000EEA,0x00000EAB,0x00000E9B,0x0E000EE9,0x000000EE,0x000F000E
	.word 0xEE000000,0xCEE00000,0xBCE000E0,0xBAE00000,0xAEE0F000,0xEE000000,0x00000000,0x00000000
	.word 0x000000EE,0x00000EEA,0x00000EAB,0x00000E9B,0x00000EE9,0x000E00EE,0x00000000,0x00000000

	.section .rodata
	.align	2
	.global totem_de_repeticion_bn_gfxPal		@ 32 unsigned chars
	.hidden totem_de_repeticion_bn_gfxPal
totem_de_repeticion_bn_gfxPal:
	.hword 0x03E0,0x533E,0x2DF7,0x250F,0x0000,0x2967,0x1AAE,0x1CF5
	.hword 0x0EDE,0x310A,0x4511,0x4999,0x5ABF,0x0DFE,0x7BDB,0x6F25

@}}BLOCK(totem_de_repeticion_bn_gfx)
