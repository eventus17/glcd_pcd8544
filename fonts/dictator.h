/*
 *
 * dictator
 * dictator4
 * 
 * (c) 2011 Dana Ramond Kaikane Stoneman : http://www.fontspace.com/profile/3killgor3
 *
 * Licensed CC-BY-SA
 *
 * Converted with FontCreator
 * written by F. Maximilian Thiele
 *
 * http://www.apetech.de/fontCreator
 * me@apetech.de
 *
 * File Name           : dictator
 * Date                : 10.07.2011
 * Font size in bytes  : 2228
 * Font width          : 10
 * Font height         : 10
 * Font first char     : 32
 * Font last char      : 124
 * Font used chars     : 92
 *
 * The font data are defined as
 *
 * struct _FONT_ {
 *     uint16_t   font_Size_in_Bytes_over_all_included_Size_it_self;
 *     uint8_t    font_Width_in_Pixel_for_fixed_drawing;
 *     uint8_t    font_Height_in_Pixel_for_all_characters;
 *     unit8_t    font_First_Char;
 *     uint8_t    font_Char_Count;
 *
 *     uint8_t    font_Char_Widths[font_Last_Char - font_First_Char +1];
 *                  // for each character the separate width in pixels,
 *                  // characters < 128 have an implicit virtual right empty row
 *
 *     uint8_t    font_data[];
 *                  // bit field of all characters
 */

#include <inttypes.h>
#include <avr/pgmspace.h>

#ifndef DICTATOR_H
#define DICTATOR_H

#define DICTATOR_WIDTH 10
#define DICTATOR_HEIGHT 10

static uint8_t dictator[] __attribute__(( section(".progmem.data") )) = {
    0x08, 0xB4, // size
    0x0A, // width
    0x0A, // height
    0x20, // first char
    0x3b, // char count
    
    // char widths
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x06, 0x06, 
    0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 
    0x06, 0x02, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 
    0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06,
    
    // font data
    0x00, 0x00, // 32
    0xFF, 0xFF, 0xC3, 0xC3, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 48
    0xCC, 0xCC, 0xFC, 0xFC, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 49
    0x0C, 0x0C, 0xFC, 0xFC, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 50
    0xCC, 0xCC, 0xFC, 0xFC, 0xFC, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 51
    0x3C, 0x3C, 0x30, 0x30, 0xFC, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 52
    0xC0, 0xC0, 0xFC, 0xFC, 0x0C, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 53
    0xFC, 0xFC, 0xFC, 0xFC, 0xCC, 0xCC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 54
    0x0C, 0x0C, 0x0C, 0x0C, 0xFC, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 55
    0xFC, 0xFC, 0x30, 0x30, 0xFC, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 56
    0x3C, 0x3C, 0x3C, 0x3C, 0xFC, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 57
    0xF0, 0xF0, 0x3C, 0x3C, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 65
    0xFC, 0xFC, 0xF0, 0xF0, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 66
    0xFC, 0xFC, 0xCC, 0xCC, 0xCC, 0xCC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 67
    0xCC, 0xCC, 0xCC, 0xCC, 0xFC, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 68
    0xFC, 0xFC, 0xFC, 0xFC, 0xCC, 0xCC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 69
    0xFC, 0xFC, 0x3C, 0x3C, 0x0C, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 70
    0xFC, 0xFC, 0xFC, 0xFC, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 71
    0xFC, 0xFC, 0x30, 0x30, 0xFC, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 72
    0xFC, 0xFC, 0x00, 0x00, // 73
    0xCC, 0xCC, 0xFC, 0xFC, 0x0C, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 74
    0xFC, 0xFC, 0x3C, 0x3C, 0xCC, 0xCC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 75
    0xFC, 0xFC, 0xC0, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 76
    0xFC, 0xFC, 0x3C, 0x3C, 0xFC, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 77
    0xFC, 0xFC, 0x0C, 0x0C, 0xFC, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 78
    0xFC, 0xFC, 0xCC, 0xCC, 0xFC, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 79
    0xFC, 0xFC, 0x3C, 0x3C, 0x3C, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 80
    0xFC, 0xFC, 0xFC, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, // 81
    0xFC, 0xFC, 0x3C, 0x3C, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 82
    0xC0, 0xC0, 0xFC, 0xFC, 0x0C, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 83
    0x0C, 0x0C, 0xFC, 0xFC, 0x0C, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 84
    0xFC, 0xFC, 0xC0, 0xC0, 0xFC, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 85
    0x3C, 0x3C, 0xC0, 0xC0, 0x3C, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 86
    0xFC, 0xFC, 0xC0, 0xC0, 0xFC, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 87
    0xCC, 0xCC, 0x30, 0x30, 0xCC, 0xCC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 88
    0x0C, 0x0C, 0xF0, 0xF0, 0x0C, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 89
    0x0C, 0x0C, 0xFC, 0xFC, 0xC0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 90
    
};

#define DICTATOR4_WIDTH 10
#define DICTATOR4_HEIGHT 5

static uint8_t dictator4[] __attribute__(( section(".progmem.data") )) = {
    0x02, 0x5D, // size
    0x0A, // width
    0x05, // height
    0x20, // first char
    0x3B, // char count
    
    // char widths
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x03, 0x03, 0x03, 0x03, 
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
    0x03, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 
    
    // font data
    0x40, // 36
    0x40, // 46
    0x78, 0x48, 0x78, // 48
    0x50, 0x70, 0x40, // 49
    0x10, 0x70, 0x40, // 50
    0x50, 0x70, 0x70, // 51
    0x30, 0x20, 0x70, // 52
    0x40, 0x70, 0x10, // 53
    0x70, 0x70, 0x50, // 54
    0x10, 0x10, 0x70, // 55
    0x70, 0x20, 0x70, // 56
    0x30, 0x30, 0x70, // 57
    0x60, 0x30, 0x60, // 65
    0x70, 0x60, 0x60, // 66
    0x70, 0x50, 0x50, // 67
    0x50, 0x50, 0x70, // 68
    0x70, 0x70, 0x50, // 69
    0x70, 0x30, 0x10, // 70
    0x70, 0x70, 0x40, // 71
    0x70, 0x20, 0x70, // 72
    0x70, // 73
    0x50, 0x70, 0x10, // 74
    0x70, 0x30, 0x50, // 75
    0x70, 0x40, 0x40, // 76
    0x70, 0x30, 0x70, // 77
    0x70, 0x10, 0x70, // 78
    0x70, 0x50, 0x70, // 79
    0x70, 0x30, 0x30, // 80
    0x70, 0x70, 0x80, // 81
    0x70, 0x30, 0x40, // 82
    0x40, 0x70, 0x10, // 83
    0x10, 0x70, 0x10, // 84
    0x70, 0x40, 0x70, // 85
    0x30, 0x40, 0x30, // 86
    0x70, 0x40, 0x70, // 87
    0x50, 0x20, 0x50, // 88
    0x10, 0x60, 0x10, // 89
    0x10, 0x70, 0x40 // 90
    
};

#endif
