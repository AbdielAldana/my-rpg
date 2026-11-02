
@{{BLOCK(cruz_divina_bn_gfx)

@=======================================================================
@
@	cruz_divina_bn_gfx, 16x16@4, 
@	+ palette 16 entries, not compressed
@	+ 4 tiles Metatiled by 2x2 not compressed
@	Total size: 32 + 128 = 160
@
@	Time-stamp: 2026-11-01, 21:58:37
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global cruz_divina_bn_gfxTiles		@ 128 unsigned chars
	.hidden cruz_divina_bn_gfxTiles
cruz_divina_bn_gfxTiles:
	.word 0x00000000,0xF0000000,0xFF000000,0xF9000000,0x90000000,0x30000000,0xF000FF00,0xFF7FFFF0
	.word 0x00000000,0x0000000F,0x000000FF,0x0000009F,0x00000009,0x00000003,0x00FF000F,0x0FFFF7FF
	.word 0xF939FF90,0x90009900,0x30000000,0xF0000000,0xFF000000,0xF9000000,0x90000000,0x00000000
	.word 0x09FF939F,0x00990009,0x00000003,0x0000000F,0x000000FF,0x0000009F,0x00000009,0x00000000

	.section .rodata
	.align	2
	.global cruz_divina_bn_gfxPal		@ 32 unsigned chars
	.hidden cruz_divina_bn_gfxPal
cruz_divina_bn_gfxPal:
	.hword 0x03E0,0x533E,0x2DF7,0x250F,0x0000,0x2967,0x1AAE,0x1CF5
	.hword 0x0EDE,0x310A,0x4511,0x4999,0x5ABF,0x0DFE,0x7BDB,0x6F25

@}}BLOCK(cruz_divina_bn_gfx)
