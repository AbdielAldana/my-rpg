
@{{BLOCK(librery_front_16x32_bn_gfx)

@=======================================================================
@
@	librery_front_16x32_bn_gfx, 16x32@4, 
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
	.global librery_front_16x32_bn_gfxTiles		@ 256 unsigned chars
	.hidden librery_front_16x32_bn_gfxTiles
librery_front_16x32_bn_gfxTiles:
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x11111111,0x22222221
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x11111111,0x12222222
	.word 0x33333321,0x33333321,0x33333321,0x33333321,0x33333321,0x11111111,0x43332221,0x31313121
	.word 0x13333333,0x13333333,0x14333333,0x14333333,0x14444333,0x11111111,0x14444434,0x14111131
	.word 0x31213121,0x31313131,0x31313131,0x22222231,0x31313131,0x11212131,0x11313141,0x11313141
	.word 0x14144121,0x14133131,0x14133131,0x14332222,0x14111111,0x14144413,0x14133131,0x14131311
	.word 0x22222231,0x31111131,0x31111141,0x31323141,0x11111141,0x22222241,0x44444441,0x11111111
	.word 0x14133232,0x14111131,0x14144131,0x14133131,0x14133111,0x14133323,0x14444444,0x11111111

	.section .rodata
	.align	2
	.global librery_front_16x32_bn_gfxPal		@ 32 unsigned chars
	.hidden librery_front_16x32_bn_gfxPal
librery_front_16x32_bn_gfxPal:
	.hword 0x03E0,0x110B,0x4F5A,0x368F,0x260B,0x1911,0x05FA,0x479F
	.hword 0x2549,0x0000,0x0421,0x0421,0x0421,0x0421,0x0421,0x0421

@}}BLOCK(librery_front_16x32_bn_gfx)
