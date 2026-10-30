
@{{BLOCK(box_16x16_bn_gfx)

@=======================================================================
@
@	box_16x16_bn_gfx, 16x16@4, 
@	+ palette 16 entries, not compressed
@	+ 4 tiles Metatiled by 2x2 not compressed
@	Total size: 32 + 128 = 160
@
@	Time-stamp: 2026-10-25, 14:41:54
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global box_16x16_bn_gfxTiles		@ 128 unsigned chars
	.hidden box_16x16_bn_gfxTiles
box_16x16_bn_gfxTiles:
	.word 0x11111100,0x22222210,0x44444210,0x33334210,0x44444210,0x33334210,0x44444210,0x33334210
	.word 0x00111111,0x01333232,0x01344444,0x01343333,0x01344444,0x01344433,0x01344444,0x01344444
	.word 0x22222210,0x11111110,0x33333310,0x44434110,0x43333410,0x44341110,0x43334110,0x11111100
	.word 0x01333233,0x01111111,0x01114433,0x01111444,0x01114444,0x01111114,0x01111444,0x00111111

	.section .rodata
	.align	2
	.global box_16x16_bn_gfxPal		@ 32 unsigned chars
	.hidden box_16x16_bn_gfxPal
box_16x16_bn_gfxPal:
	.hword 0x03E0,0x110B,0x4F5A,0x368F,0x260B,0x1911,0x05FA,0x479F
	.hword 0x2549,0x0000,0x0421,0x0421,0x0421,0x0421,0x0421,0x0421

@}}BLOCK(box_16x16_bn_gfx)
