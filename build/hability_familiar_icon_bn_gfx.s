
@{{BLOCK(hability_familiar_icon_bn_gfx)

@=======================================================================
@
@	hability_familiar_icon_bn_gfx, 16x16@4, 
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
	.global hability_familiar_icon_bn_gfxTiles		@ 128 unsigned chars
	.hidden hability_familiar_icon_bn_gfxTiles
hability_familiar_icon_bn_gfxTiles:
	.word 0x00000000,0xDDD00000,0x88DD0000,0x888D0000,0x858D0000,0x888D0000,0x188D0000,0x88DD0000
	.word 0x00000000,0x00000DDD,0x0000DD88,0x0000D888,0x0000D858,0x0000D888,0x0000D881,0x0000DD88
	.word 0xDDD00000,0xDD0D0000,0xDD000000,0xDD000000,0xD00D0000,0x0D000000,0x00000000,0x00000000
	.word 0x00000DDD,0x000000DD,0x0000D0DD,0x000000DD,0x0000000D,0x0000D000,0x0000000D,0x00000000

	.section .rodata
	.align	2
	.global hability_familiar_icon_bn_gfxPal		@ 32 unsigned chars
	.hidden hability_familiar_icon_bn_gfxPal
hability_familiar_icon_bn_gfxPal:
	.hword 0x03E0,0x0C01,0x24C5,0x1863,0x1067,0x14AB,0x260B,0x368F
	.hword 0x7FFF,0x4F5A,0x3EF9,0x14C7,0x2E7C,0x4A2E,0x0000,0x0421

@}}BLOCK(hability_familiar_icon_bn_gfx)
