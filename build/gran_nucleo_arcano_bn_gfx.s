
@{{BLOCK(gran_nucleo_arcano_bn_gfx)

@=======================================================================
@
@	gran_nucleo_arcano_bn_gfx, 16x16@4, 
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
	.global gran_nucleo_arcano_bn_gfxTiles		@ 128 unsigned chars
	.hidden gran_nucleo_arcano_bn_gfxTiles
gran_nucleo_arcano_bn_gfxTiles:
	.word 0x00000000,0x0000CC00,0x000ABBC0,0x330A9BC0,0x1130AA00,0x88130000,0x88813000,0x68883000
	.word 0x00000000,0x00000000,0x00000000,0x00000033,0x00000381,0x00003888,0x00038888,0x00038886
	.word 0x68883000,0x88883000,0x88830000,0xDD300000,0x33000000,0x00000000,0x00000000,0x00000000
	.word 0x00038886,0x0003D888,0x00003D88,0x00CC03DD,0x0ABBC033,0x0A9BC000,0x00AA0000,0x00000000

	.section .rodata
	.align	2
	.global gran_nucleo_arcano_bn_gfxPal		@ 32 unsigned chars
	.hidden gran_nucleo_arcano_bn_gfxPal
gran_nucleo_arcano_bn_gfxPal:
	.hword 0x03E0,0x533E,0x2DF7,0x250F,0x0000,0x2967,0x1AAE,0x1CF5
	.hword 0x0EDE,0x310A,0x4511,0x4999,0x5ABF,0x0DFE,0x7BDB,0x6F25

@}}BLOCK(gran_nucleo_arcano_bn_gfx)
