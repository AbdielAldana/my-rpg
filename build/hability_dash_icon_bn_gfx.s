
@{{BLOCK(hability_dash_icon_bn_gfx)

@=======================================================================
@
@	hability_dash_icon_bn_gfx, 16x16@4, 
@	+ palette 16 entries, not compressed
@	+ 4 tiles Metatiled by 2x2 not compressed
@	Total size: 32 + 128 = 160
@
@	Time-stamp: 2026-10-25, 18:17:29
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global hability_dash_icon_bn_gfxTiles		@ 128 unsigned chars
	.hidden hability_dash_icon_bn_gfxTiles
hability_dash_icon_bn_gfxTiles:
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0xB0000000,0xCBB00000,0xCCCBB000
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00BB000B,0x00BCCCCC,0x00BCDDDD
	.word 0xDDDDDB00,0x99999B00,0xBBBBB000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000
	.word 0x00BDDDDD,0x00B99999,0x000BBBBB,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000

	.section .rodata
	.align	2
	.global hability_dash_icon_bn_gfxPal		@ 32 unsigned chars
	.hidden hability_dash_icon_bn_gfxPal
hability_dash_icon_bn_gfxPal:
	.hword 0x03E0,0x0C01,0x24C5,0x1863,0x1067,0x14AB,0x260B,0x368F
	.hword 0x7FFF,0x4F5A,0x3EF9,0x14C7,0x2E7C,0x4A2E,0x0000,0x0421

@}}BLOCK(hability_dash_icon_bn_gfx)
