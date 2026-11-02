
@{{BLOCK(canalizador_rapido_bn_gfx)

@=======================================================================
@
@	canalizador_rapido_bn_gfx, 16x16@4, 
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
	.global canalizador_rapido_bn_gfxTiles		@ 128 unsigned chars
	.hidden canalizador_rapido_bn_gfxTiles
canalizador_rapido_bn_gfxTiles:
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x20000000,0x20200000
	.word 0x00000000,0x0EBB0000,0x0BB30000,0x0B3000CA,0x0000CAAA,0x000AA332,0x00CA3333,0x00AA9333
	.word 0x32200000,0x33200000,0x33200000,0x93320000,0x09332000,0x00933200,0x00093320,0x00009300
	.word 0x00000933,0x00000093,0x00000009,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000

	.section .rodata
	.align	2
	.global canalizador_rapido_bn_gfxPal		@ 32 unsigned chars
	.hidden canalizador_rapido_bn_gfxPal
canalizador_rapido_bn_gfxPal:
	.hword 0x03E0,0x533E,0x2DF7,0x250F,0x0000,0x2967,0x1AAE,0x1CF5
	.hword 0x0EDE,0x310A,0x4511,0x4999,0x5ABF,0x0DFE,0x7BDB,0x6F25

@}}BLOCK(canalizador_rapido_bn_gfx)
