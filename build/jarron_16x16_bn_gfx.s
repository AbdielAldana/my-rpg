
@{{BLOCK(jarron_16x16_bn_gfx)

@=======================================================================
@
@	jarron_16x16_bn_gfx, 16x16@4, 
@	+ palette 16 entries, not compressed
@	+ 4 tiles Metatiled by 2x2 not compressed
@	Total size: 32 + 128 = 160
@
@	Time-stamp: 2026-10-29, 10:31:11
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global jarron_16x16_bn_gfxTiles		@ 128 unsigned chars
	.hidden jarron_16x16_bn_gfxTiles
jarron_16x16_bn_gfxTiles:
	.word 0x44400000,0x33340000,0x22134000,0x44213400,0x44423440,0x44423440,0x44423434,0x44134234
	.word 0x00000444,0x00004333,0x00043122,0x00431244,0x04412444,0x04412444,0x42412444,0x42241144
	.word 0x13342134,0x44421334,0x22213214,0x11112240,0x12111140,0x21122400,0x22244000,0x44400000
	.word 0x42224113,0x42222444,0x44222222,0x44222111,0x04422221,0x04442222,0x00444442,0x00044444

	.section .rodata
	.align	2
	.global jarron_16x16_bn_gfxPal		@ 32 unsigned chars
	.hidden jarron_16x16_bn_gfxPal
jarron_16x16_bn_gfxPal:
	.hword 0x03E0,0x368F,0x260B,0x4F5A,0x110B,0x3EF9,0x14C7,0x0000
	.hword 0x0421,0x0421,0x0421,0x0421,0x0421,0x0421,0x0421,0x0421

@}}BLOCK(jarron_16x16_bn_gfx)
