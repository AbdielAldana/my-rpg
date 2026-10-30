
@{{BLOCK(piedra1_bn_gfx)

@=======================================================================
@
@	piedra1_bn_gfx, 16x16@4, 
@	+ palette 16 entries, not compressed
@	+ 4 tiles Metatiled by 2x2 not compressed
@	Total size: 32 + 128 = 160
@
@	Time-stamp: 2026-10-25, 14:41:55
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global piedra1_bn_gfxTiles		@ 128 unsigned chars
	.hidden piedra1_bn_gfxTiles
piedra1_bn_gfxTiles:
	.word 0x44444000,0x33331400,0x11333140,0x11133140,0x42213114,0x11123114,0x21123144,0x21132214
	.word 0x00044444,0x00444421,0x04222411,0x04211211,0x44211224,0x44211214,0x44442111,0x44211111
	.word 0x43331114,0x41111314,0x42211314,0x22221134,0x44221134,0x22442114,0x22111214,0x44444440
	.word 0x44211331,0x44122112,0x44122222,0x41222224,0x41244442,0x42222242,0x42222422,0x04444444

	.section .rodata
	.align	2
	.global piedra1_bn_gfxPal		@ 32 unsigned chars
	.hidden piedra1_bn_gfxPal
piedra1_bn_gfxPal:
	.hword 0x03E0,0x368F,0x260B,0x4F5A,0x110B,0x3EF9,0x14C7,0x0000
	.hword 0x0421,0x0421,0x0421,0x0421,0x0421,0x0421,0x0421,0x0421

@}}BLOCK(piedra1_bn_gfx)
