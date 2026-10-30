
@{{BLOCK(map_current_bn_gfx)

@=======================================================================
@
@	map_current_bn_gfx, 8x8@4, 
@	+ palette 16 entries, not compressed
@	+ 1 tiles not compressed
@	Total size: 32 + 32 = 64
@
@	Time-stamp: 2026-10-25, 14:41:54
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global map_current_bn_gfxTiles		@ 32 unsigned chars
	.hidden map_current_bn_gfxTiles
map_current_bn_gfxTiles:
	.word 0x11111111,0x13333331,0x13333331,0x13322331,0x13322331,0x13333331,0x13333331,0x11111111

	.section .rodata
	.align	2
	.global map_current_bn_gfxPal		@ 32 unsigned chars
	.hidden map_current_bn_gfxPal
map_current_bn_gfxPal:
	.hword 0x03E0,0x479F,0x2E7C,0x1911,0x05FA,0x3DCA,0x3167,0x1936
	.hword 0x70AF,0x0000,0x0421,0x0421,0x0421,0x0421,0x0421,0x0421

@}}BLOCK(map_current_bn_gfx)
