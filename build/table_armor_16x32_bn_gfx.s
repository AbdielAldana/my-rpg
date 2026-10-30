
@{{BLOCK(table_armor_16x32_bn_gfx)

@=======================================================================
@
@	table_armor_16x32_bn_gfx, 32x16@4, 
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
	.global table_armor_16x32_bn_gfxTiles		@ 256 unsigned chars
	.hidden table_armor_16x32_bn_gfxTiles
table_armor_16x32_bn_gfxTiles:
	.word 0x00000000,0x00000000,0x44444400,0x41333340,0x14211340,0x41444344,0x41414144,0x44144244
	.word 0x04444000,0x42133440,0x43444134,0x24342443,0x24342224,0x44434444,0x11434111,0x44443444
	.word 0x10004000,0x00043400,0x44441444,0x41441441,0x14222214,0x44443444,0x11143411,0x44443444
	.word 0x00000040,0x00000434,0x00444414,0x04114414,0x04242222,0x44244434,0x44241434,0x44244434
	.word 0x14244144,0x24242234,0x44244424,0x44241424,0x42411424,0x42411424,0x24111444,0x41000000
	.word 0x11243411,0x22224342,0x44444344,0x11111434,0x11111434,0x11111143,0x11111143,0x00000014
	.word 0x11143411,0x22243422,0x44441444,0x11143411,0x11143411,0x11141411,0x11124211,0x00012100
	.word 0x44241434,0x42222414,0x42444414,0x42411434,0x42411434,0x42411414,0x44411242,0x00000121

	.section .rodata
	.align	2
	.global table_armor_16x32_bn_gfxPal		@ 32 unsigned chars
	.hidden table_armor_16x32_bn_gfxPal
table_armor_16x32_bn_gfxPal:
	.hword 0x03E0,0x368F,0x260B,0x4F5A,0x110B,0x3EF9,0x14C7,0x0000
	.hword 0x0421,0x0421,0x0421,0x0421,0x0421,0x0421,0x0421,0x0421

@}}BLOCK(table_armor_16x32_bn_gfx)
