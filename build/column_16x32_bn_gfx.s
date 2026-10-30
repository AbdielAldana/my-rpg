
@{{BLOCK(column_16x32_bn_gfx)

@=======================================================================
@
@	column_16x32_bn_gfx, 16x32@4, 
@	+ palette 16 entries, not compressed
@	+ 8 tiles Metatiled by 2x4 not compressed
@	Total size: 32 + 256 = 288
@
@	Time-stamp: 2026-10-25, 14:41:54
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global column_16x32_bn_gfxTiles		@ 256 unsigned chars
	.hidden column_16x32_bn_gfxTiles
column_16x32_bn_gfxTiles:
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x11111000,0x22222100,0x33322210,0x33333210
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00011111,0x00123332,0x01233333,0x01233333
	.word 0x33333210,0x33333210,0x33333210,0x33333210,0x33332110,0x11111310,0x43433100,0x11111000
	.word 0x01333333,0x01333333,0x01333333,0x01333333,0x01133333,0x01411111,0x00144444,0x00011111
	.word 0x44441000,0x22221000,0x33321000,0x33331000,0x14441000,0x42221100,0x43321210,0x43331210
	.word 0x00011444,0x00014422,0x00014333,0x00014333,0x00011141,0x00114324,0x01413334,0x01413334
	.word 0x44411210,0x33221210,0x44331210,0x11111210,0x22222210,0x44444410,0x11111130,0x33333300
	.word 0x01411144,0x01414433,0x01414444,0x01411111,0x01433322,0x01444444,0x03111111,0x00333333

	.section .rodata
	.align	2
	.global column_16x32_bn_gfxPal		@ 32 unsigned chars
	.hidden column_16x32_bn_gfxPal
column_16x32_bn_gfxPal:
	.hword 0x03E0,0x110B,0x4F5A,0x368F,0x260B,0x1911,0x05FA,0x479F
	.hword 0x2549,0x0000,0x0421,0x0421,0x0421,0x0421,0x0421,0x0421

@}}BLOCK(column_16x32_bn_gfx)
