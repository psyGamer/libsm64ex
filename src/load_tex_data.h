#pragma once

#include <stdint.h>

enum MarioTextures
{
    mario_texture_metal = 0,
    mario_texture_yellow_button,
    mario_texture_m_logo,
    mario_texture_hair_sideburn,
    mario_texture_mustache,
    mario_texture_eyes_front,
    mario_texture_eyes_half_closed,
    mario_texture_eyes_closed,
    mario_texture_eyes_dead,
    mario_texture_wings_half_1,
    mario_texture_wings_half_2,
    mario_texture_metal_wings_half_1 = -99,
    mario_texture_metal_wings_half_2,
    mario_texture_eyes_closed_unused1,
    mario_texture_eyes_closed_unused2,
    mario_texture_eyes_right,
    mario_texture_eyes_left,
    mario_texture_eyes_up,
    mario_texture_eyes_down
};

#define MARIO_NUM_USED_TEXTURES 11
#define MENU_NUM_USED_TEXTURES 45

static const int mario_tex_offsets[MARIO_NUM_USED_TEXTURES] = { 144, 4240, 6288, 8336, 10384, 12432, 14480, 16528, 30864, 32912, 37008 };
static const int mario_tex_widths [MARIO_NUM_USED_TEXTURES] = { 64, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32 };
static const int mario_tex_heights[MARIO_NUM_USED_TEXTURES] = { 32, 32, 32, 32, 32, 32, 32, 32, 32, 64, 64 };

static const int menu_tex_offsets[MENU_NUM_USED_TEXTURES] = { 0x0, 0x200, 0x400, 0x600, 0x800, 0xA00, 0xC00, 0xE00, 0x1000, 0x1200, 0x1400, 0x1600, 0x1800, 0x1A00, 0x1C00, 0x1E00, 0x2000, 0x2200, 0x2400, 0x2600, 0x2800, 0x2A00, 0x2C00, 0x2E00, 0x3000, 0x3200, 0x3400, 0x3600, 0x3800, 0x3A00, 0x3C00, 0x3E00, 0x4000, 0x4200, 0x4400, 0x4600, 0x4800, 0x7200, 0x7400, 0x7600, 0x7680, 0x122B8, 0x12AB8, 0x132B8, 0x142B8 };
static const int menu_tex_widths [MENU_NUM_USED_TEXTURES] = { 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 8, 8, 32, 32, 64, 32 };
static const int menu_tex_heights[MENU_NUM_USED_TEXTURES] = { 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 8, 8, 64, 64, 64, 64 };

extern void load_mario_textures_from_rom( const uint8_t *rom, uint8_t *outTexture );
extern void load_menu_textures_from_rom( const uint8_t *rom, uint8_t *outTexture );
