
@{{BLOCK(axe_floor_16x16_bn_gfx)

@=======================================================================
@
@	axe_floor_16x16_bn_gfx, 16x16@4, 
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
	.global axe_floor_16x16_bn_gfxTiles		@ 128 unsigned chars
	.hidden axe_floor_16x16_bn_gfxTiles
axe_floor_16x16_bn_gfxTiles:
	.word 0x00000000,0x00000000,0x00004400,0x00441340,0x44132240,0x13244400,0x24400000,0x40000000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000044,0x00044411,0x00422244
	.word 0x40000000,0x14000000,0x43400000,0x44444400,0x44400000,0x00000000,0x00000000,0x00000000
	.word 0x00044422,0x00004211,0x00004111,0x04444444,0x00000444,0x00000000,0x00000000,0x00000000

	.section .rodata
	.align	2
	.global axe_floor_16x16_bn_gfxPal		@ 32 unsigned chars
	.hidden axe_floor_16x16_bn_gfxPal
axe_floor_16x16_bn_gfxPal:
	.hword 0x03E0,0x368F,0x260B,0x4F5A,0x110B,0x3EF9,0x14C7,0x0000
	.hword 0x0421,0x0421,0x0421,0x0421,0x0421,0x0421,0x0421,0x0421

@}}BLOCK(axe_floor_16x16_bn_gfx)
