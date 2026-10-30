
@{{BLOCK(key_bn_gfx)

@=======================================================================
@
@	key_bn_gfx, 16x16@4, 
@	+ palette 16 entries, not compressed
@	+ 4 tiles Metatiled by 2x2 not compressed
@	Total size: 32 + 128 = 160
@
@	Time-stamp: 2026-10-25, 14:41:54
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global key_bn_gfxTiles		@ 128 unsigned chars
	.hidden key_bn_gfxTiles
key_bn_gfxTiles:
	.word 0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x70000000,0x87777000
	.word 0x00000000,0x00770000,0x00887000,0x07808700,0x08000870,0x00007887,0x00008088,0x00000008
	.word 0x88888700,0x80000870,0x80000870,0x70000870,0x70000870,0x87778800,0x08888000,0x00000000
	.word 0x00000000,0x00000008,0x00000008,0x00000008,0x00000008,0x00000000,0x00000000,0x00000000

	.section .rodata
	.align	2
	.global key_bn_gfxPal		@ 32 unsigned chars
	.hidden key_bn_gfxPal
key_bn_gfxPal:
	.hword 0x03E0,0x110B,0x4F5A,0x368F,0x260B,0x1911,0x05FA,0x479F
	.hword 0x2549,0x0000,0x0421,0x0421,0x0421,0x0421,0x0421,0x0421

@}}BLOCK(key_bn_gfx)
