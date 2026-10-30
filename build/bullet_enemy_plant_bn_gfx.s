
@{{BLOCK(bullet_enemy_plant_bn_gfx)

@=======================================================================
@
@	bullet_enemy_plant_bn_gfx, 8x8@4, 
@	+ palette 16 entries, not compressed
@	+ 1 tiles not compressed
@	Total size: 32 + 32 = 64
@
@	Time-stamp: 2026-10-26, 09:05:52
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global bullet_enemy_plant_bn_gfxTiles		@ 32 unsigned chars
	.hidden bullet_enemy_plant_bn_gfxTiles
bullet_enemy_plant_bn_gfxTiles:
	.word 0x00000000,0x00555500,0x05CC4650,0x05C44450,0x05444C50,0x0564CC50,0x00555500,0x00000000

	.section .rodata
	.align	2
	.global bullet_enemy_plant_bn_gfxPal		@ 32 unsigned chars
	.hidden bullet_enemy_plant_bn_gfxPal
bullet_enemy_plant_bn_gfxPal:
	.hword 0x03E0,0x0C01,0x24C5,0x1863,0x1067,0x14AB,0x260B,0x368F
	.hword 0x7FFF,0x4F5A,0x3EF9,0x14C7,0x2E7C,0x4A2E,0x0000,0x0421

@}}BLOCK(bullet_enemy_plant_bn_gfx)
