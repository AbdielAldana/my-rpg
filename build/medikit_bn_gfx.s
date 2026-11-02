
@{{BLOCK(medikit_bn_gfx)

@=======================================================================
@
@	medikit_bn_gfx, 16x16@4, 
@	+ palette 16 entries, not compressed
@	+ 4 tiles Metatiled by 2x2 not compressed
@	Total size: 32 + 128 = 160
@
@	Time-stamp: 2026-11-01, 12:43:56
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global medikit_bn_gfxTiles		@ 128 unsigned chars
	.hidden medikit_bn_gfxTiles
medikit_bn_gfxTiles:
	.word 0x00000000,0x00000000,0x00000000,0xBB000000,0x00B00000,0xBBBB0000,0xE888B000,0xE8888B00
	.word 0x00000000,0x00000000,0x00000000,0x000000BB,0x00000100,0x0000BBBB,0x000B8885,0x001A8885
	.word 0xEEEEEB00,0xE5555B00,0xE8888B00,0xE8888B00,0x5AAAAB00,0x11111100,0x00000000,0x00000000
	.word 0x001EEEEE,0x00155555,0x001A8885,0x001A8885,0x001AAAA5,0x00111111,0x00000000,0x00000000

	.section .rodata
	.align	2
	.global medikit_bn_gfxPal		@ 32 unsigned chars
	.hidden medikit_bn_gfxPal
medikit_bn_gfxPal:
	.hword 0x03E0,0x0C01,0x24C5,0x1863,0x1067,0x14AB,0x260B,0x368F
	.hword 0x7FFF,0x4F5A,0x3EF9,0x14C7,0x2E7C,0x4A2E,0x1936,0x479F

@}}BLOCK(medikit_bn_gfx)
