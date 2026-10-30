
@{{BLOCK(stairs_bn_gfx)

@=======================================================================
@
@	stairs_bn_gfx, 16x16@4, 
@	+ palette 16 entries, not compressed
@	+ 4 tiles Metatiled by 2x2 not compressed
@	Total size: 32 + 128 = 160
@
@	Time-stamp: 2026-10-25, 14:41:55
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global stairs_bn_gfxTiles		@ 128 unsigned chars
	.hidden stairs_bn_gfxTiles
stairs_bn_gfxTiles:
	.word 0x00001000,0x11123100,0x33333100,0x22223200,0x11123200,0x33333400,0x44443400,0x11143400
	.word 0x00010000,0x00132111,0x00133333,0x00232222,0x00232111,0x00433333,0x00434444,0x00434211
	.word 0x33333400,0x44443400,0x11143400,0x33333410,0x44443421,0x22243421,0x22224210,0x22222100
	.word 0x00433333,0x00414444,0x00414221,0x01411111,0x12414444,0x12414222,0x01242222,0x00122222

	.section .rodata
	.align	2
	.global stairs_bn_gfxPal		@ 32 unsigned chars
	.hidden stairs_bn_gfxPal
stairs_bn_gfxPal:
	.hword 0x03E0,0x368F,0x260B,0x4F5A,0x110B,0x3EF9,0x14C7,0x0000
	.hword 0x0421,0x0421,0x0421,0x0421,0x0421,0x0421,0x0421,0x0421

@}}BLOCK(stairs_bn_gfx)
