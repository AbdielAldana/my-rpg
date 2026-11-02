
@{{BLOCK(nucleo_denso_bn_gfx)

@=======================================================================
@
@	nucleo_denso_bn_gfx, 16x16@4, 
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
	.global nucleo_denso_bn_gfxTiles		@ 128 unsigned chars
	.hidden nucleo_denso_bn_gfxTiles
nucleo_denso_bn_gfxTiles:
	.word 0x00000000,0x00000000,0xAAAA0000,0xAAAA9000,0xEEA99900,0x8EE99900,0x3DEE9900,0x338E9900
	.word 0x00000000,0x00000000,0x0000CCAC,0x000CAAAA,0x00CAAAEE,0x00CAAEE8,0x00CAEED3,0x00AAE833
	.word 0x338E9900,0x3DEE9900,0x8EE99400,0xEE999400,0x99994000,0x99440000,0x00000000,0x00000000
	.word 0x00CAE833,0x00AAEED3,0x00AAAEE8,0x00AA99EE,0x00099999,0x00009999,0x00000000,0x00000000

	.section .rodata
	.align	2
	.global nucleo_denso_bn_gfxPal		@ 32 unsigned chars
	.hidden nucleo_denso_bn_gfxPal
nucleo_denso_bn_gfxPal:
	.hword 0x03E0,0x533E,0x2DF7,0x250F,0x0000,0x2967,0x1AAE,0x1CF5
	.hword 0x0EDE,0x310A,0x4511,0x4999,0x5ABF,0x0DFE,0x7BDB,0x6F25

@}}BLOCK(nucleo_denso_bn_gfx)
