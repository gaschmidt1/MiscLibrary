
#include "Ascii.h"


const uint8_t ascii_table9x16[12][18] = {
    {0xFC, 0xFE, 0xFF, 0x03, 0x03, 0x03, 0xFF, 0xFE, 0xFC, 0x3F, 0x7F, 0xFF, 0xC0, 0xC0, 0xC0, 0xFF, 0x7F, 0x3F}, ////'0'
    {0x00, 0x0C, 0x0E, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0x00}, ////'1'
    {0x0C, 0x0E, 0x0F, 0x03, 0x03, 0x83, 0xFF, 0xFE, 0x7C, 0xF0, 0xF8, 0xFC, 0xCE, 0xC7, 0xC3, 0xE1, 0xE0, 0xE0}, ////'2'
    {0x0C, 0x0E, 0x0F, 0xC3, 0xC3, 0xC3, 0xFF, 0x7E, 0x3C, 0x60, 0x60, 0xE0, 0xC0, 0xC0, 0xC0, 0xFF, 0x7F, 0x3E}, ////'3'
    {0x00, 0x80, 0xE0, 0xF8, 0x7E, 0x1F, 0xFF, 0xFF, 0xFF, 0x06, 0x07, 0x07, 0x07, 0x06, 0x06, 0xFF, 0xFF, 0xFF}, ////'4'
    {0x7F, 0x7F, 0x7F, 0x63, 0x63, 0x63, 0xE7, 0xC7, 0x87, 0x30, 0x70, 0xF0, 0xC0, 0xC0, 0xC0, 0xFF, 0x7F, 0x3F}, ////'5'
    {0xFC, 0xFE, 0xFF, 0xC3, 0xC3, 0xC3, 0xCF, 0x8E, 0x0C, 0x3F, 0x7F, 0xFF, 0xC0, 0xC0, 0xC0, 0xFF, 0x7F, 0x3F}, ////'6'
    {0x07, 0x07, 0x07, 0x03, 0xC3, 0xF3, 0xFF, 0x3F, 0x0F, 0x00, 0xF0, 0xFC, 0xFF, 0x0F, 0x03, 0x00, 0x00, 0x00}, ////'7'
    {0x3C, 0xFE, 0xFF, 0xC3, 0xC3, 0xC3, 0xFF, 0xFE, 0x3C, 0x3F, 0x7F, 0xFF, 0xC0, 0xC0, 0xC0, 0xFF, 0x7F, 0x3F}, ////'8'
    {0xFC, 0xFE, 0xFF, 0x03, 0x03, 0x03, 0xFF, 0xFE, 0xFC, 0x30, 0x71, 0xF3, 0xC3, 0xC3, 0xC3, 0xFF, 0x7F, 0x3F}, ////'9'
    {0x00, 0x70, 0x70, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x0E, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00}, ////':'
    {0x00, 0x70, 0x50, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x0A, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00}, ////' '
};

const uint8_t ascii_table5x7[97][5] = {
    {0x00, 0x00, 0x00, 0x00, 0x00}, //// space
    {0x00, 0x00, 0x5F, 0x00, 0x00}, //// !
    {0x00, 0x07, 0x00, 0x07, 0x00}, //// #
    {0x14, 0x7F, 0x14, 0x7F, 0x14}, //// "
    {0x24, 0x2A, 0x7F, 0x2A, 0x12}, //// $
    {0x23, 0x13, 0x08, 0x64, 0x62}, //// %
    {0x36, 0x49, 0x55, 0x22, 0x50}, //// &
    {0x00, 0x05, 0x03, 0x00, 0x00}, //// '
    {0x00, 0x1C, 0x22, 0x41, 0x00}, //// (
    {0x00, 0x41, 0x22, 0x1C, 0x00}, //// )
    {0x08, 0x2A, 0x1C, 0x2A, 0x08}, //// *
    {0x08, 0x08, 0x3E, 0x08, 0x08}, //// +
    {0x00, 0x50, 0x30, 0x00, 0x00}, //// ,
    {0x08, 0x08, 0x08, 0x08, 0x08}, //// -
    {0x00, 0x30, 0x30, 0x00, 0x00}, //// .
    {0x20, 0x10, 0x08, 0x04, 0x02}, //// /
    {0x3E, 0x51, 0x49, 0x45, 0x3E}, //// 0
    {0x00, 0x42, 0x7F, 0x40, 0x00}, //// 1
    {0x42, 0x61, 0x51, 0x49, 0x46}, //// 2
    {0x21, 0x41, 0x45, 0x4B, 0x31}, //// 3
    {0x18, 0x14, 0x12, 0x7F, 0x10}, //// 4
    {0x27, 0x45, 0x45, 0x45, 0x39}, //// 5
    {0x3C, 0x4A, 0x49, 0x49, 0x30}, //// 6
    {0x01, 0x71, 0x09, 0x05, 0x03}, //// 7
    {0x36, 0x49, 0x49, 0x49, 0x36}, //// 8
    {0x06, 0x49, 0x49, 0x29, 0x1E}, //// 9
    {0x00, 0x36, 0x36, 0x00, 0x00}, //// :
    {0x00, 0x56, 0x36, 0x00, 0x00}, //// ,
    {0x00, 0x08, 0x14, 0x22, 0x41}, //// <
    {0x14, 0x14, 0x14, 0x14, 0x14}, //// =
    {0x41, 0x22, 0x14, 0x08, 0x00}, //// >
    {0x02, 0x01, 0x51, 0x09, 0x06}, //// ?
    {0x32, 0x49, 0x79, 0x41, 0x3E}, //// @
    {0x7E, 0x11, 0x11, 0x11, 0x7E}, //// A
    {0x7F, 0x49, 0x49, 0x49, 0x36}, //// B
    {0x3E, 0x41, 0x41, 0x41, 0x22}, //// C
    {0x7F, 0x41, 0x41, 0x22, 0x1C}, //// D
    {0x7F, 0x49, 0x49, 0x49, 0x41}, //// E
    {0x7F, 0x09, 0x09, 0x01, 0x01}, //// F
    {0x3E, 0x41, 0x41, 0x51, 0x32}, //// G
    {0x7F, 0x08, 0x08, 0x08, 0x7F}, //// H
    {0x00, 0x41, 0x7F, 0x41, 0x00}, //// I
    {0x20, 0x40, 0x41, 0x3F, 0x01}, //// J
    {0x7F, 0x08, 0x14, 0x22, 0x41}, //// K
    {0x7F, 0x40, 0x40, 0x40, 0x40}, //// L
    {0x7F, 0x02, 0x04, 0x02, 0x7F}, //// M
    {0x7F, 0x04, 0x08, 0x10, 0x7F}, //// N
    {0x3E, 0x41, 0x41, 0x41, 0x3E}, //// O
    {0x7F, 0x09, 0x09, 0x09, 0x06}, //// P
    {0x3E, 0x41, 0x51, 0x21, 0x5E}, //// Q
    {0x7F, 0x09, 0x19, 0x29, 0x46}, //// R
    {0x46, 0x49, 0x49, 0x49, 0x31}, //// S
    {0x01, 0x01, 0x7F, 0x01, 0x01}, //// T
    {0x3F, 0x40, 0x40, 0x40, 0x3F}, //// U
    {0x1F, 0x20, 0x40, 0x20, 0x1F}, //// V
    {0x7F, 0x20, 0x18, 0x20, 0x7F}, //// W
    {0x63, 0x14, 0x08, 0x14, 0x63}, //// X
    {0x03, 0x04, 0x78, 0x04, 0x03}, //// Y
    {0x61, 0x51, 0x49, 0x45, 0x43}, //// Z
    {0x00, 0x00, 0x7F, 0x41, 0x41}, //// '['
    {0x02, 0x04, 0x08, 0x10, 0x20}, //// '\'
    {0x41, 0x41, 0x7F, 0x00, 0x00}, //// ']'
    {0x04, 0x02, 0x01, 0x02, 0x04}, //// '^'
    {0x40, 0x40, 0x40, 0x40, 0x40}, //// '_'
    {0x00, 0x01, 0x02, 0x04, 0x00}, //// '`'
    {0x20, 0x54, 0x54, 0x54, 0x78}, //// a
    {0x7F, 0x48, 0x44, 0x44, 0x38}, //// b
    {0x38, 0x44, 0x44, 0x44, 0x20}, //// c
    {0x38, 0x44, 0x44, 0x48, 0x7F}, //// d
    {0x38, 0x54, 0x54, 0x54, 0x18}, //// e
    {0x08, 0x7E, 0x09, 0x01, 0x02}, //// f
    {0x08, 0x14, 0x54, 0x54, 0x3C}, //// g
    {0x7F, 0x08, 0x04, 0x04, 0x78}, //// h
    {0x40, 0x44, 0x7D, 0x40, 0x00}, //// i
    {0x20, 0x40, 0x44, 0x3D, 0x00}, //// j
    {0x00, 0x7F, 0x10, 0x28, 0x44}, //// k
    {0x00, 0x41, 0x7F, 0x40, 0x00}, //// l
    {0x7C, 0x04, 0x18, 0x04, 0x78}, //// m
    {0x7C, 0x08, 0x04, 0x04, 0x78}, //// n
    {0x38, 0x44, 0x44, 0x44, 0x38}, //// o
    {0x7C, 0x14, 0x14, 0x14, 0x08}, //// p
    {0x08, 0x14, 0x14, 0x18, 0x7C}, //// q
    {0x7C, 0x08, 0x04, 0x04, 0x08}, //// r
    {0x48, 0x54, 0x54, 0x54, 0x20}, //// s
    {0x04, 0x3F, 0x44, 0x40, 0x20}, //// t
    {0x3C, 0x40, 0x40, 0x20, 0x7C}, //// u
    {0x1C, 0x20, 0x40, 0x20, 0x1C}, //// v
    {0x3C, 0x40, 0x30, 0x40, 0x3C}, //// w
    {0x44, 0x28, 0x10, 0x28, 0x44}, //// x
    {0x0C, 0x50, 0x50, 0x50, 0x3C}, //// y
    {0x44, 0x64, 0x54, 0x4C, 0x44}, //// z
    {0x00, 0x08, 0x36, 0x41, 0x00}, //// '{'
    {0x00, 0x00, 0x7F, 0x00, 0x00}, //// '|'
    {0x00, 0x41, 0x36, 0x08, 0x00}, //// '}'
    {0x08, 0x08, 0x2A, 0x1C, 0x08}, //// '->'
    {0x08, 0x1C, 0x2A, 0x08, 0x08}, //// '<-'
    {0x38, 0x44, 0x4C, 0x44, 0x20}, //// '�'
};

const uint8_t ascii_table4x6[95][4] = {
    {0x00, 0x00, 0x00, 0x00}, // Code for char
    {0x00, 0x00, 0x2E, 0x00}, // Code for char !
    {0x00, 0x06, 0x00, 0x06}, // Code for char "
    {0x00, 0x3E, 0x14, 0x3E}, // Code for char #
    {0x00, 0x28, 0x7E, 0x14}, // Code for char $
    {0x00, 0x12, 0x08, 0x24}, // Code for char %
    {0x00, 0x34, 0x2A, 0x3C}, // Code for char &
    {0x00, 0x06, 0x02, 0x00}, // Code for char '
    {0x00, 0x1C, 0x22, 0x00}, // Code for char (
    {0x00, 0x22, 0x1C, 0x00}, // Code for char )
    {0x00, 0x2A, 0x1C, 0x2A}, // Code for char *
    {0x00, 0x08, 0x1C, 0x08}, // Code for char +
    {0x00, 0x60, 0x20, 0x00}, // Code for char ,
    {0x00, 0x08, 0x08, 0x08}, // Code for char -
    {0x00, 0x00, 0x20, 0x00}, // Code for char .
    {0x00, 0x30, 0x08, 0x06}, // Code for char /
    {0x3C, 0x42, 0x42, 0x3C}, // Code for char 0
    {0x00, 0x44, 0x7E, 0x40}, // Code for char 1
    {0x62, 0x52, 0x4A, 0x44}, // Code for char 2
    {0x42, 0x42, 0x4A, 0x34}, // Code for char 3
    {0x0E, 0x08, 0x08, 0x7E}, // Code for char 4
    {0x4E, 0x4A, 0x4A, 0x32}, // Code for char 5
    {0x3C, 0x4A, 0x4A, 0x32}, // Code for char 6
    {0x02, 0x72, 0x1A, 0x0E}, // Code for char 7
    {0x34, 0x4A, 0x4A, 0x34}, // Code for char 8
    {0x44, 0x4A, 0x4A, 0x3C}, // Code for char 9
    {0x00, 0x00, 0x28, 0x00}, // Code for char :
    {0x00, 0x60, 0x28, 0x00}, // Code for char ;
    {0x00, 0x18, 0x24, 0x42}, // Code for char <
    {0x28, 0x28, 0x28, 0x28}, // Code for char =
    {0x42, 0x24, 0x18, 0x00}, // Code for char >
    {0x00, 0x02, 0x2A, 0x04}, // Code for char ?
    {0x00, 0x3E, 0x22, 0x2E}, // Code for char @
    {0x7C, 0x0A, 0x0A, 0x7C}, // Code for char A
    {0x7E, 0x4A, 0x4A, 0x34}, // Code for char B
    {0x3C, 0x42, 0x42, 0x42}, // Code for char C
    {0x7E, 0x42, 0x42, 0x3C}, // Code for char D
    {0x7E, 0x4A, 0x4A, 0x42}, // Code for char E
    {0x7E, 0x0A, 0x0A, 0x02}, // Code for char F
    {0x3C, 0x42, 0x4A, 0x3A}, // Code for char G
    {0x7E, 0x08, 0x08, 0x7E}, // Code for char H
    {0x00, 0x42, 0x7E, 0x42}, // Code for char I
    {0x20, 0x40, 0x40, 0x3E}, // Code for char J
    {0x7E, 0x08, 0x08, 0x76}, // Code for char K
    {0x7E, 0x40, 0x40, 0x40}, // Code for char L
    {0x7E, 0x0C, 0x0C, 0x7E}, // Code for char M
    {0x7E, 0x04, 0x08, 0x7E}, // Code for char N
    {0x3C, 0x42, 0x42, 0x3C}, // Code for char O
    {0x7E, 0x0A, 0x0A, 0x04}, // Code for char P
    {0x1C, 0x22, 0x22, 0x5C}, // Code for char Q
    {0x7E, 0x0A, 0x0A, 0x74}, // Code for char R
    {0x4E, 0x4A, 0x4A, 0x3A}, // Code for char S
    {0x00, 0x02, 0x7E, 0x02}, // Code for char T
    {0x7E, 0x40, 0x40, 0x7E}, // Code for char U
    {0x3E, 0x40, 0x40, 0x3E}, // Code for char V
    {0x7E, 0x20, 0x20, 0x7E}, // Code for char W
    {0x76, 0x08, 0x08, 0x76}, // Code for char X
    {0x06, 0x48, 0x38, 0x06}, // Code for char Y
    {0x62, 0x52, 0x4A, 0x46}, // Code for char Z
    {0x00, 0x7E, 0x42, 0x00}, // Code for char [
    {0x00, 0x06, 0x08, 0x30}, // Code for char BackSlash
    {0x00, 0x42, 0x7E, 0x00}, // Code for char ]
    {0x00, 0x04, 0x02, 0x04}, // Code for char ^
    {0x40, 0x40, 0x40, 0x40}, // Code for char _
    {0x00, 0x02, 0x06, 0x00}, // Code for char `
    {0x00, 0x30, 0x28, 0x38}, // Code for char a
    {0x00, 0x3E, 0x28, 0x10}, // Code for char b
    {0x00, 0x10, 0x28, 0x28}, // Code for char c
    {0x00, 0x10, 0x28, 0x3E}, // Code for char d
    {0x00, 0x18, 0x38, 0x28}, // Code for char e
    {0x00, 0x08, 0x3C, 0x0A}, // Code for char f
    {0x00, 0x58, 0x48, 0x78}, // Code for char g
    {0x00, 0x3E, 0x08, 0x30}, // Code for char h
    {0x00, 0x00, 0x3A, 0x00}, // Code for char i
    {0x00, 0x40, 0x7A, 0x00}, // Code for char j
    {0x00, 0x3E, 0x10, 0x28}, // Code for char k
    {0x00, 0x00, 0x3E, 0x00}, // Code for char l
    {0x00, 0x38, 0x18, 0x38}, // Code for char m
    {0x00, 0x38, 0x08, 0x30}, // Code for char n
    {0x00, 0x10, 0x28, 0x10}, // Code for char o
    {0x00, 0x78, 0x28, 0x10}, // Code for char p
    {0x00, 0x10, 0x28, 0x78}, // Code for char q
    {0x00, 0x38, 0x08, 0x00}, // Code for char r
    {0x00, 0x20, 0x38, 0x08}, // Code for char s
    {0x00, 0x08, 0x3C, 0x28}, // Code for char t
    {0x00, 0x38, 0x20, 0x38}, // Code for char u
    {0x00, 0x18, 0x20, 0x18}, // Code for char v
    {0x00, 0x38, 0x30, 0x38}, // Code for char w
    {0x00, 0x28, 0x10, 0x28}, // Code for char x
    {0x00, 0x58, 0x20, 0x18}, // Code for char y
    {0x00, 0x08, 0x38, 0x20}, // Code for char z
    {0x00, 0x08, 0x3E, 0x22}, // Code for char {
    {0x00, 0x00, 0x3E, 0x00}, // Code for char |
    {0x00, 0x22, 0x3E, 0x08}, // Code for char }
    {0x04, 0x02, 0x04, 0x02} // Code for char ~
};

//#define SizeOffLogoClk 180
const uint8_t LogoClk[SizeOffLogoClk] = 
{
    //comlink

    0xE0, 0xF8, 0xFC, 0xFE, 0xFE, 0x7F, 0x3F, 0x1F, 0x1F, 0x3F, 0x3E, 0x1E, 0x0C, 0x00, 0x80, 0xC0,
    0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0x80, 0x00, 0x00, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0,
    0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0xC0, 0x00, 0xFE, 0xFE,
    0xFE, 0xFE, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE4, 0xEE, 0xFF, 0xEE, 0xE4, 0x00,
    0xE0, 0xE0, 0xE0, 0xE0, 0xE0, 0x80, 0xC0, 0xE0, 0xE0, 0xE0, 0xC0, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x80, 0xC0, 0xE0, 0xE0, 0xE0, 0xE0, 0x60, 0x20,

    0x0F, 0x3F, 0x7F, 0x7F, 0xFF, 0xFC, 0xF8, 0xF8, 0xF8, 0xF8, 0xFC, 0x70, 0x40, 0x0E, 0x3F, 0x7F,
    0xFF, 0xFF, 0xFB, 0xF1, 0xFB, 0xFF, 0xFF, 0x7F, 0x3F, 0x0E, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x01, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0xF8, 0xF8, 0xF8, 0xF8, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x3F, 0x7F, 0xFF, 0xFF, 0xF1, 0xE0, 0xC0, 0x80
};
    // vic
    //    0x30, 0xF0, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0xF0, 0x30, 0x00, 0xF0, 0x0F, 0x0F, 0x0F, 0x0F, 0xF0,
    //    0x00, 0x80, 0xC0, 0xE0, 0x70, 0x30, 0x30, 0x70, 0xE0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    //    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    //    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    //    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    //    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    //    0x00, 0x01, 0x1F, 0xFF, 0xF8, 0xFF, 0x1F, 0x01, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    //    0x00, 0x1F, 0x3F, 0x7F, 0xE0, 0xC0, 0xC0, 0xE0, 0x70, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    //    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    //    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    //    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    //    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

    //rosseti
//        0xFF, 0x01, 0xFD, 0xFD, 0xFD, 0x0D, 0x05, 0x65, 0x65, 0x65, 0x65, 0x0D, 0x1D, 0x7D, 0x1D, 0x8D,
//        0xC5, 0xE5, 0xE5, 0xC5, 0x0D, 0x1D, 0xFD, 0xFD, 0x9D, 0x0D, 0x45, 0x65, 0xC5, 0xCD, 0xDD, 0xFD,
//        0xFD, 0x9D, 0x0D, 0x45, 0x65, 0xC5, 0xCD, 0xDD, 0xFD, 0x1D, 0x05, 0x05, 0x65, 0x65, 0x65, 0xE5,
//        0xFD, 0xE5, 0xE5, 0x05, 0x05, 0x05, 0xE5, 0xE5, 0xFD, 0xE5, 0xE5, 0x05, 0x05, 0x05, 0xE5, 0xE5,
//        0xFD, 0x05, 0x05, 0x85, 0xFD, 0xFD, 0x01, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//
//        0xFF, 0x80, 0xBF, 0xAF, 0xA1, 0xA0, 0xBE, 0xBE, 0xB0, 0xA0, 0xA6, 0xAE, 0xBF, 0xBC, 0xB0, 0xB3,
//        0xA7, 0xA7, 0xB3, 0xB1, 0xB8, 0xBE, 0xBF, 0xBB, 0xB3, 0xA3, 0xA6, 0xA2, 0xA0, 0xB1, 0xBF, 0xBF,
//        0xBB, 0xB3, 0xA3, 0xA6, 0xA2, 0xA0, 0xB1, 0xBF, 0xA3, 0xA0, 0xA0, 0xA2, 0xA2, 0xA2, 0xA2, 0xBF,
//        0xBF, 0xBF, 0xA3, 0xA0, 0xA0, 0xBF, 0xBF, 0xBF, 0xBF, 0xBF, 0xA3, 0xA0, 0xA0, 0xBF, 0xBF, 0xBF,
//        0xA3, 0xA0, 0xA0, 0xBF, 0xBF, 0xBF, 0x80, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
//};
//#define SizeOffLogoSebras 142
//u8r LogoSebras[SizeOffLogoSebras] = {
//    //sebras
//    0x18, 0x3C, 0x7E, 0xFF, 0xFF, 0xFF, 0xEA, 0x55, 0xAA, 0xD5, 0xCA, 0x85, 0x02, 0x00, 0x00, 0x00,
//    0x00, 0x30, 0xCC, 0x02, 0x31, 0x49, 0x91, 0x12, 0x0C, 0xE0, 0x1F, 0x01, 0x71, 0x59, 0x49, 0xCF,
//    0x00, 0xFF, 0xFF, 0xFF, 0xC7, 0xC7, 0xEF, 0x7E, 0x3C, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xC7, 0xC7,
//    0xEF, 0x7E, 0x3C, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xE0, 0xFC, 0xFF, 0xFF, 0xFE, 0x00, 0x00, 0x00,
//    0x30, 0xFC, 0xFE, 0xEF, 0xC7, 0x9F, 0x1E,
//    0x00, 0x40, 0xA0, 0x50, 0xA9, 0x55, 0xAA, 0x57, 0xBF, 0xFF, 0xFF, 0x7F, 0x3F, 0x1E, 0x0C, 0x00,
//    0x30, 0x48, 0x88, 0x91, 0x8E, 0x80, 0x41, 0x3E, 0x00, 0xFF, 0x80, 0x80, 0x9E, 0x92, 0xF2, 0x03,
//    0xFC, 0xFF, 0xFF, 0xE1, 0xE1, 0xF3, 0xFF, 0xFF, 0x3E, 0x00, 0xFC, 0xFF, 0xFF, 0xC1, 0x01, 0x03,
//    0xFF, 0xFF, 0xFE, 0xC0, 0xF8, 0xFC, 0x3F, 0x1F, 0x19, 0x18, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x30,
//    0x78, 0xF8, 0xE1, 0xF3, 0xFF, 0x7F, 0x3E
//};




