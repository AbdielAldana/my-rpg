
@{{BLOCK(hability_bomb_icon_bn_gfx)

@=======================================================================
@
@	hability_bomb_icon_bn_gfx, 16x16@4, 
@	+ palette 16 entries, not compressed
@	+ 4 tiles Metatiled by 2x2 not compressed
@	Total size: 32 + 128 = 160
@
@	Time-stamp: 2026-10-26, 14:47:57
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global hability_bomb_icon_bn_gfxTiles		@ 128 unsigned chars
	.hidden hability_bomb_icon_bn_gfxTiles
hability_bomb_icon_bn_gfxTiles:
	.word 0x00000000,0x00000000,0xC0C00000,0xC000C000,0x50000000,0x20000000,0x22200000,0x28220000
	.word 0x00000000,0x00000000,0x00000C00,0x000C000C,0x00000005,0x00000002,0x00000222,0x00003222
	.word 0x22822000,0x22222000,0x22222000,0x22223000,0x22223000,0x33330000,0x33300000,0x00000000
	.word 0x00032222,0x00032222,0x00033222,0x00033322,0x00033332,0x00003333,0x00000333,0x00000000

	.section .rodata
	.align	2
	.global hability_bomb_icon_bn_gfxPal		@ 32 unsigned chars
	.hidden hability_bomb_icon_bn_gfxPal
hability_bomb_icon_bn_gfxPal:
	.hword 0x03E0,0x0C01,0x24C5,0x1863,0x1067,0x14AB,0x260B,0x368F
	.hword 0x7FFF,0x4F5A,0x3EF9,0x14C7,0x2E7C,0x4A2E,0x0000,0x0421

@}}BLOCK(hability_bomb_icon_bn_gfx)
