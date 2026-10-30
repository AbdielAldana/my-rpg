
@{{BLOCK(door_special_bn_gfx)

@=======================================================================
@
@	door_special_bn_gfx, 16x32@4, 
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
	.global door_special_bn_gfxTiles		@ 256 unsigned chars
	.hidden door_special_bn_gfxTiles
door_special_bn_gfxTiles:
	.word 0x00000000,0x00000000,0x00000044,0x00004444,0x04444444,0x44444444,0x31444444,0x11134444
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x44444444,0x11321132,0x11321132
	.word 0x11113444,0x44111344,0x44411224,0x44442134,0x44442134,0x44444134,0x44444134,0x44444224
	.word 0x12644444,0x12266444,0x11226444,0x11226644,0x11122664,0x11122664,0x11122664,0x11122664
	.word 0x44444134,0x44444134,0x44444134,0x44442134,0x44442134,0x44411224,0x44111344,0x11113444
	.word 0x11122664,0x11122664,0x11122664,0x11122664,0x11226644,0x11226444,0x12266444,0x12644444
	.word 0x11134444,0x31444444,0x44444444,0x04444444,0x00004444,0x00000044,0x00000000,0x00000000
	.word 0x11321132,0x11321132,0x44444444,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000

	.section .rodata
	.align	2
	.global door_special_bn_gfxPal		@ 32 unsigned chars
	.hidden door_special_bn_gfxPal
door_special_bn_gfxPal:
	.hword 0x03E0,0x368F,0x260B,0x4F5A,0x110B,0x3EF9,0x14C7,0x0000
	.hword 0x0421,0x0421,0x0421,0x0421,0x0421,0x0421,0x0421,0x0421

@}}BLOCK(door_special_bn_gfx)
