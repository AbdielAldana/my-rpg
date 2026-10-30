
@{{BLOCK(cartel_16x16_bn_gfx)

@=======================================================================
@
@	cartel_16x16_bn_gfx, 16x16@4, 
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
	.global cartel_16x16_bn_gfxTiles		@ 128 unsigned chars
	.hidden cartel_16x16_bn_gfxTiles
cartel_16x16_bn_gfxTiles:
	.word 0x40000000,0x14444400,0x33333340,0x13333340,0x22222340,0x22232340,0x23232140,0x23322340
	.word 0x00000004,0x00444441,0x04333333,0x04111111,0x04222222,0x04122322,0x04223333,0x04222322
	.word 0x22222140,0x21111140,0x44444400,0x44000000,0x24111000,0x24221100,0x42111000,0x20000000
	.word 0x04122222,0x04111212,0x00444444,0x00000044,0x00011144,0x00112242,0x00011124,0x00000002

	.section .rodata
	.align	2
	.global cartel_16x16_bn_gfxPal		@ 32 unsigned chars
	.hidden cartel_16x16_bn_gfxPal
cartel_16x16_bn_gfxPal:
	.hword 0x03E0,0x368F,0x260B,0x4F5A,0x110B,0x3EF9,0x14C7,0x0000
	.hword 0x0421,0x0421,0x0421,0x0421,0x0421,0x0421,0x0421,0x0421

@}}BLOCK(cartel_16x16_bn_gfx)
