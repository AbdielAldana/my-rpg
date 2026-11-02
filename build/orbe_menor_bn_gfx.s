
@{{BLOCK(orbe_menor_bn_gfx)

@=======================================================================
@
@	orbe_menor_bn_gfx, 16x16@4, 
@	+ palette 16 entries, not compressed
@	+ 4 tiles Metatiled by 2x2 not compressed
@	Total size: 32 + 128 = 160
@
@	Time-stamp: 2026-11-01, 17:41:55
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global orbe_menor_bn_gfxTiles		@ 128 unsigned chars
	.hidden orbe_menor_bn_gfxTiles
orbe_menor_bn_gfxTiles:
	.word 0x00000000,0x00000000,0x77000000,0x55770000,0xDD557000,0xDDD57000,0x4DDD5700,0x44DD5700
	.word 0x00000000,0x00000000,0x00000077,0x00007755,0x000755DD,0x00075DDD,0x0075DDD4,0x0075DD44
	.word 0x44DD5700,0x4DDD5700,0xDDD57000,0xDD557000,0x55770000,0x77000000,0x00000000,0x00000000
	.word 0x0075DD44,0x0075DDD4,0x00075DDD,0x000755DD,0x00007755,0x00000077,0x00000000,0x00000000

	.section .rodata
	.align	2
	.global orbe_menor_bn_gfxPal		@ 32 unsigned chars
	.hidden orbe_menor_bn_gfxPal
orbe_menor_bn_gfxPal:
	.hword 0x03E0,0x533E,0x2DF7,0x250F,0x0000,0x2967,0x1AAE,0x1CF5
	.hword 0x0EDE,0x310A,0x4511,0x4999,0x5ABF,0x0DFE,0x7BDB,0x6F25

@}}BLOCK(orbe_menor_bn_gfx)
