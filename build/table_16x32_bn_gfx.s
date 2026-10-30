
@{{BLOCK(table_16x32_bn_gfx)

@=======================================================================
@
@	table_16x32_bn_gfx, 32x16@4, 
@	+ palette 16 entries, not compressed
@	+ 8 tiles Metatiled by 4x2 not compressed
@	Total size: 32 + 256 = 288
@
@	Time-stamp: 2026-10-29, 10:31:11
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global table_16x32_bn_gfxTiles		@ 256 unsigned chars
	.hidden table_16x32_bn_gfxTiles
table_16x32_bn_gfxTiles:
	.word 0x44444600,0x33333160,0x33333140,0x33333140,0x31122240,0x33333140,0x33333140,0x33333140
	.word 0x44444444,0x33333333,0x33333333,0x33333333,0x33333113,0x33333333,0x33333333,0x33333333
	.word 0x44444444,0x33333333,0x33333333,0x33333333,0x33333333,0x33333333,0x33333333,0x33333333
	.word 0x00444444,0x06133333,0x04133333,0x04133333,0x04211313,0x04133333,0x04133333,0x04133333
	.word 0x31311240,0x33333140,0x33333240,0x11112240,0x44444410,0x24224100,0x11434000,0x11141000
	.word 0x33333333,0x33333333,0x33333333,0x11111111,0x44444444,0x22222222,0x11111111,0x11111111
	.word 0x13333333,0x33333333,0x33333333,0x11111111,0x44444444,0x22222222,0x11111111,0x11111111
	.word 0x04222133,0x04133333,0x04233333,0x04222111,0x01444444,0x00142242,0x00063411,0x00024111

	.section .rodata
	.align	2
	.global table_16x32_bn_gfxPal		@ 32 unsigned chars
	.hidden table_16x32_bn_gfxPal
table_16x32_bn_gfxPal:
	.hword 0x03E0,0x368F,0x260B,0x4F5A,0x110B,0x3EF9,0x14C7,0x0000
	.hword 0x0421,0x0421,0x0421,0x0421,0x0421,0x0421,0x0421,0x0421

@}}BLOCK(table_16x32_bn_gfx)
