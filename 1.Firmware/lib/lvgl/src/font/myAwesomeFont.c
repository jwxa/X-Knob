/*******************************************************************************
 * Size: 14 px
 * Bpp: 4
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "../../lvgl.h"
#endif

#ifndef LV_FONT_MYAWESOMEFONT
#define LV_FONT_MYAWESOMEFONT 1
#endif

#if LV_FONT_MYAWESOMEFONT

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+F78A "" */
    0x0, 0x0, 0x1, 0x30, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x2e, 0xfc, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x9d, 0x3f, 0x40, 0x0,
    0x0, 0x16, 0x40, 0x0, 0x0, 0x6f, 0xcf, 0x10,
    0x0, 0x0, 0xcf, 0xf4, 0x0, 0x0, 0x6, 0xdc,
    0x0, 0x0, 0x0, 0xef, 0xf6, 0x0, 0x0, 0x0,
    0x3f, 0x40, 0x0, 0x2, 0x6e, 0xc1, 0x0, 0x0,
    0x0, 0xd, 0xfe, 0xa1, 0x8b, 0x0, 0x0, 0x29,
    0x70, 0x0, 0x6f, 0x86, 0xdb, 0x10, 0x0, 0x0,
    0xdf, 0xf5, 0x21, 0xc9, 0x0, 0x3f, 0x20, 0x0,
    0x0, 0xef, 0xf6, 0x95, 0xc8, 0x0, 0x2f, 0x20,
    0x0, 0x0, 0x4b, 0x90, 0x0, 0x7f, 0x64, 0xcf,
    0x81, 0x2, 0x0, 0x0, 0x0, 0x0, 0x8, 0xff,
    0xc6, 0xee, 0xdf, 0xd1, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0xa, 0xf3, 0xe6, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x4, 0xf9, 0xf5, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x8c, 0x80
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 280, .box_w = 18, .box_h = 15, .ofs_x = 0, .ofs_y = -2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 63370, .range_length = 1, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 4,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t myAwesomeFont = {
#else
lv_font_t myAwesomeFont = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 15,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if LV_FONT_MYAWESOMEFONT*/

