
@{{BLOCK(hability_viewallmap_icon_bn_gfx)

@=======================================================================
@
@	hability_viewallmap_icon_bn_gfx, 16x16@4, 
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
	.global hability_viewallmap_icon_bn_gfxTiles		@ 128 unsigned chars
	.hidden hability_viewallmap_icon_bn_gfxTiles
hability_viewallmap_icon_bn_gfxTiles:
	.word 0x00000000,0x00000000,0x00000000,0x44440000,0xAAAAB000,0x5AAAAB00,0xAAAAAB00,0xAAAAAB00
	.word 0x00000000,0x00000000,0x00BB0000,0x00B94444,0x00B9AAAA,0x00B95AAA,0x00BAA5A5,0x00BAAA5A
	.word 0xAAAAAB00,0x5AAA9B00,0xAAA99B00,0xA9999B00,0x99999B00,0xB44B9B00,0x0000BB00,0x00000000
	.word 0x00BAA5A5,0x00BA5AAA,0x00BAAAAA,0x004AAAAA,0x0004AAAA,0x00004BBB,0x00000000,0x00000000

	.section .rodata
	.align	2
	.global hability_viewallmap_icon_bn_gfxPal		@ 32 unsigned chars
	.hidden hability_viewallmap_icon_bn_gfxPal
hability_viewallmap_icon_bn_gfxPal:
	.hword 0x03E0,0x0C01,0x24C5,0x1863,0x1067,0x14AB,0x260B,0x368F
	.hword 0x7FFF,0x4F5A,0x3EF9,0x14C7,0x2E7C,0x4A2E,0x0000,0x0421

@}}BLOCK(hability_viewallmap_icon_bn_gfx)
