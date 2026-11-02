
@{{BLOCK(baston_liviano_bn_gfx)

@=======================================================================
@
@	baston_liviano_bn_gfx, 16x16@4, 
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
	.global baston_liviano_bn_gfxTiles		@ 128 unsigned chars
	.hidden baston_liviano_bn_gfxTiles
baston_liviano_bn_gfxTiles:
	.word 0x00000000,0xC0000000,0xEC000000,0xEF000000,0xFB300000,0xCB300000,0xB3000000,0x30000000
	.word 0x00000000,0x0000000F,0x000000FE,0x0000005E,0x000003B5,0x000003BC,0x0000003B,0x00000003
	.word 0x20000000,0x20000000,0x20000000,0x20000000,0x20000000,0x20000000,0x20000000,0x00000000
	.word 0x00000002,0x00000002,0x00000002,0x00000002,0x00000002,0x00000002,0x00000002,0x00000000

	.section .rodata
	.align	2
	.global baston_liviano_bn_gfxPal		@ 32 unsigned chars
	.hidden baston_liviano_bn_gfxPal
baston_liviano_bn_gfxPal:
	.hword 0x03E0,0x533E,0x2DF7,0x250F,0x0000,0x2967,0x1AAE,0x1CF5
	.hword 0x0EDE,0x310A,0x4511,0x4999,0x5ABF,0x0DFE,0x7BDB,0x6F25

@}}BLOCK(baston_liviano_bn_gfx)
