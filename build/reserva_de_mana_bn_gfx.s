
@{{BLOCK(reserva_de_mana_bn_gfx)

@=======================================================================
@
@	reserva_de_mana_bn_gfx, 16x16@4, 
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
	.global reserva_de_mana_bn_gfxTiles		@ 128 unsigned chars
	.hidden reserva_de_mana_bn_gfxTiles
reserva_de_mana_bn_gfxTiles:
	.word 0x00000000,0x33000000,0x35000000,0x35000000,0xE5000000,0xE5000000,0xE5000000,0xEE500000
	.word 0x00000000,0x00000033,0x00000053,0x00000053,0x0000005E,0x0000005E,0x0000005E,0x000005EE
	.word 0xEEE50000,0xFFFF5000,0xFFFFF500,0xFFFFF500,0xFFFFF500,0xFFFFF500,0x95555000,0x00000000
	.word 0x00005EEE,0x0005FFFF,0x009FFFFF,0x009FFFFF,0x009FFFFF,0x009FFFFF,0x00099999,0x00000000

	.section .rodata
	.align	2
	.global reserva_de_mana_bn_gfxPal		@ 32 unsigned chars
	.hidden reserva_de_mana_bn_gfxPal
reserva_de_mana_bn_gfxPal:
	.hword 0x03E0,0x533E,0x2DF7,0x250F,0x0000,0x2967,0x1AAE,0x1CF5
	.hword 0x0EDE,0x310A,0x4511,0x4999,0x5ABF,0x0DFE,0x7BDB,0x6F25

@}}BLOCK(reserva_de_mana_bn_gfx)
