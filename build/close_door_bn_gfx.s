
@{{BLOCK(close_door_bn_gfx)

@=======================================================================
@
@	close_door_bn_gfx, 16x32@4, 
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
	.global close_door_bn_gfxTiles		@ 256 unsigned chars
	.hidden close_door_bn_gfxTiles
close_door_bn_gfxTiles:
	.word 0x00000000,0x00000000,0x64444444,0x44446644,0x55334553,0x33334533,0x53334333,0x44444444
	.word 0x00000000,0x00000000,0x22211166,0x66666644,0x33335555,0x33333355,0x33555555,0x44444444
	.word 0x44463433,0x44463635,0x44443335,0x44446355,0x44446355,0x44446355,0x44446355,0x34444355
	.word 0x24444444,0x42144444,0x44414444,0x64444444,0x64444444,0x64444444,0x64465653,0x64465533
	.word 0x44444355,0x44444355,0x44446355,0x44446355,0x44446355,0x44443335,0x44443435,0x44443433
	.word 0x44465633,0x44444444,0x44444444,0x44444444,0x64444444,0x64444444,0x62214444,0x24444444
	.word 0x44446644,0x55336333,0x33334533,0x53334553,0x44444444,0x44444444,0x00000000,0x00000000
	.word 0x64444444,0x33335555,0x33333355,0x33555555,0x22666444,0x66221664,0x00000000,0x00000000

	.section .rodata
	.align	2
	.global close_door_bn_gfxPal		@ 32 unsigned chars
	.hidden close_door_bn_gfxPal
close_door_bn_gfxPal:
	.hword 0x03E0,0x368F,0x260B,0x4F5A,0x110B,0x3EF9,0x14C7,0x0000
	.hword 0x0421,0x0421,0x0421,0x0421,0x0421,0x0421,0x0421,0x0421

@}}BLOCK(close_door_bn_gfx)
