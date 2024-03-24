#include "load_tex_data.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "libsm64.h"

#include "decomp/tools/libmio0.h"
#include "decomp/tools/n64graphics.h"

#define MARIO_TEX_ROM_OFFSET 0x114750
#define MENU_TEX_ROM_OFFSET 0x108A40

#define MARIO_ATLAS_WIDTH (MARIO_NUM_USED_TEXTURES * 64)
#define MARIO_ATLAS_HEIGHT 64

#define MENU_ATLAS_WIDTH ((MENU_NUM_USED_TEXTURES-4) * 16)
#define MENU_ATLAS_HEIGHT 16 + 64

static void blt_image_to_atlas( rgba *img, int i, int w, int h, int atlasEntryWidth, int atlasWidth, int atlasYOffset, uint8_t *outTexture )
{
    for( int iy = 0; iy < h; ++iy )
    for( int ix = 0; ix < w; ++ix )
    {
        int o = (ix + atlasEntryWidth * i) + (iy + atlasYOffset) * atlasWidth;
        int q = ix + iy * w;
        outTexture[4*o + 0] = img[q].red;
        outTexture[4*o + 1] = img[q].green;
        outTexture[4*o + 2] = img[q].blue;
        outTexture[4*o + 3] = img[q].alpha;
    }
}

void load_mario_textures_from_rom( const uint8_t *rom, uint8_t *outTexture )
{
    memset( outTexture, 0, 4 * MARIO_ATLAS_WIDTH * MARIO_ATLAS_HEIGHT );

    mio0_header_t head;
    const uint8_t *in_buf = rom + MARIO_TEX_ROM_OFFSET;

    mio0_decode_header( in_buf, &head );
    uint8_t *out_buf = malloc( head.dest_size );
    mio0_decode( in_buf, out_buf, NULL );

    for( int i = 0; i < MARIO_NUM_USED_TEXTURES; ++i )
    {
        uint8_t *raw = out_buf + mario_tex_offsets[i];
        rgba *img = raw2rgba( raw, mario_tex_widths[i], mario_tex_heights[i], 16 );
        blt_image_to_atlas( img, i, mario_tex_widths[i], mario_tex_heights[i], 64, MARIO_ATLAS_WIDTH, 0, outTexture );
        free( img );
    }

    free( out_buf );
}

void load_menu_textures_from_rom( const uint8_t *rom, uint8_t *outTexture ) {
    
    memset( outTexture, 0, 4 * MENU_ATLAS_WIDTH * MENU_ATLAS_HEIGHT );

    mio0_header_t head;
    const uint8_t *in_buf = rom + MENU_TEX_ROM_OFFSET;

    mio0_decode_header( in_buf, &head );
    uint8_t *out_buf = malloc( head.dest_size );
    mio0_decode( in_buf, out_buf, NULL );

    // Place the last 4 textures (large screen transition wipes) on the next layer of the atlas
    for( int i = 0; i < MENU_NUM_USED_TEXTURES-4; ++i )
    {
        uint8_t *raw = out_buf + menu_tex_offsets[i];
        rgba *img = raw2rgba( raw, menu_tex_widths[i], menu_tex_heights[i], 16 );
        blt_image_to_atlas( img, i, menu_tex_widths[i], menu_tex_heights[i], 16, MENU_ATLAS_WIDTH, 0, outTexture );
        free( img );
    }
    for( int i = MENU_NUM_USED_TEXTURES-4; i < MENU_NUM_USED_TEXTURES; ++i )
    {
        uint8_t *raw = out_buf + menu_tex_offsets[i];
        ia *ia_img = raw2ia( raw, menu_tex_widths[i], menu_tex_heights[i], 8 );
        rgba *rgba_img = ia2rgba( ia_img, menu_tex_widths[i], menu_tex_heights[i] );
        blt_image_to_atlas( rgba_img, i-MENU_NUM_USED_TEXTURES+4, menu_tex_widths[i], menu_tex_heights[i], 64, MENU_ATLAS_WIDTH, 16, outTexture );
        free( ia_img );
        free( rgba_img );
    }

    free( out_buf );
}
