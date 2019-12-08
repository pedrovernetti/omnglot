
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright (c) 2019 Pedro Vernetti G.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the "Software"), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons
 * to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#pragma once
#ifndef _OMN_CHARENCODING_INCLUDED
#define _OMN_CHARENCODING_INCLUDED

#include "globalUtilities.hpp"

namespace // internal parts
{
    constexpr byte isASCIIPunctuation[16] =
    {
        0b00000000, 0b00000000, 0b00000000, 0b00000000,
        0b01100001, 0b11001111, 0b00000000, 0b00111011,
        0b00000000, 0b00000000, 0b00000000, 0b00010100,
        0b00000000, 0b00000000, 0b00000000, 0b00010100,
    };

    constexpr byte isASCIISymbol[16] =
    {
        0b00000000, 0b00000000, 0b00000000, 0b00000000,
        0b00011110, 0b00110000, 0b00000000, 0b00001110,
        0b10000000, 0b00000000, 0b00000000, 0b00001011,
        0b10000000, 0b00000000, 0b00000000, 0b00001010
    };

    constexpr uint16_t ISO88597ToUnicodeConversionTable[30] =
    {
        160, 8216, 8217, 163, 8364, 8367, 166, 167, 168, 169, 890,  171, 172, 173, 26, 8213,
        176, 177, 178, 179, 900, 901, 902, 183, 904, 905, 906, 187, 908, 189
    };

    constexpr uint16_t CP1250ToUnicodeConversionTable[128] =
    {
        8364, 26, 8218, 26, 8222, 8230, 8224, 8225, 26, 8240, 352, 8249, 346, 356, 381, 377,
        26, 8216, 8217, 8220, 8221, 8226, 8211, 8212, 26, 8482, 353, 8250, 347, 357, 382, 378,
        160, 711, 728, 321, 164, 260, 166, 167, 168, 169, 350, 171, 172, 173, 174, 379,
        176, 177, 731, 322, 180, 181, 182, 183, 184, 261, 351, 187, 317, 733, 318, 380,
        340, 193, 194, 258, 196, 313, 262, 199, 268, 201, 280, 203, 282, 205, 206, 270,
        272, 323, 327, 211, 212, 336, 214, 215, 344, 366, 218, 368, 220, 221, 354, 223,
        341, 225, 226, 259, 228, 314, 263, 231, 269, 233, 281, 235, 283, 237, 238, 271,
        273, 324, 328, 243, 244, 337, 246, 247, 345, 367, 250, 369, 252, 253, 355, 729
    };

    constexpr uint16_t CP1251ToUnicodeConversionTable[64] =
    {
        1026, 1027, 8218, 402, 8222, 8230, 8224, 8225, 8364, 8240, 1033, 8249, 1034, 1036, 1035, 1039,
        1106, 8216, 8217, 8220, 8221, 8226, 8211, 8212, 26, 8482, 1113, 8250, 1114, 1116, 1115, 1119,
        160, 1038, 1118, 1032, 164, 1168, 166, 167, 1025, 169, 1028, 171, 172, 173, 174, 1031,
        176, 177, 1030, 1110, 1169, 181, 182, 183, 1105, 8470, 1108, 187, 1112, 1029, 1109, 1111
    };

    constexpr uint16_t CP1252ToUnicodeConversionTable[32] =
    {
        8364, 26, 8218, 402, 8222, 8230, 8224, 8225, 710, 8240, 352, 8249, 338, 26, 381, 26,
        26, 8216, 8217, 8220, 8221, 8226, 8211, 8212, 732, 8482, 353, 8250, 339, 26, 382, 376
    };

    constexpr uint16_t CP1253ToUnicodeConversionTable[64] =
    {
        8364, 26, 8218, 402, 8222, 8230, 8224, 8225, 26, 8240, 26, 8249, 26, 26, 26, 26,
        26, 8216, 8217, 8220, 8221, 8226, 8211, 8212, 26, 8482, 26, 8250, 26, 26, 26, 26,
        160, 901, 902, 163, 164, 165, 166, 167, 168, 169, 26, 171, 172, 173, 174, 8213,
        176, 177, 178, 179, 900, 181, 182, 183, 904, 905, 906, 187, 908, 189, 910, 911
    };

    constexpr uint16_t CP1255ToUnicodeConversionTable[64] =
    {
        8364, 26, 8218, 402, 8222, 8230, 8224, 8225, 710, 8240, 26, 8249, 26, 26, 26, 26,
        26, 8216, 8217, 8220, 8221, 8226, 8211, 8212, 732, 8482, 26, 8250, 26, 26, 26, 26,
        160, 161, 162, 163, 8362, 165, 166, 167, 168, 169, 215, 171, 172, 173, 174, 175,
        176, 177, 178, 179, 900, 181, 182, 183, 184, 185, 247, 187, 188, 189, 190, 191
    };

    constexpr uint16_t CP1256ToUnicodeConversionTable[128] =
    {
        8364, 1662, 8218, 402,  8222, 8230, 8224, 8225, 710,  8240, 1657, 8249, 338,  1670, 1688, 1672,
        1711, 8216, 8217, 8220, 8221, 8226, 8211, 8212, 1705, 8482, 1681, 8250, 339,  8204, 8205, 1722,
        160,  1548, 162,  163,  164,  165,  166,  167,  168,  169,  1726, 171,  172,  173,  174,  175,
        176,  177,  178,  179,  180,  181,  182,  183,  184,  185,  1563, 187,  188,  189,  190,  1567,
        1729, 1569, 1570, 1571, 1572, 1573, 1574, 1575, 1576, 1577, 1578, 1579, 1580, 1581, 1582, 1583,
        1584, 1585, 1586, 1587, 1588, 1589, 1590, 215,  1591, 1592, 1593, 1594, 1600, 1601, 1602, 1603,
        224,  1604, 226,  1605, 1606, 1607, 1608, 231,  232,  233,  234,  235,  1609, 1610, 238,  239,
        1611, 1612, 1613, 1614, 244,  1615, 1616, 247,  1617, 249,  1618, 251,  252,  8206, 8207, 1746
    };

    constexpr uint16_t CP1257ToUnicodeConversionTable[128] =
    {
        8364, 26, 8218, 26, 8222, 8230, 8224, 8225, 26, 8240, 26, 8249, 26, 168, 711, 184,
        26, 8216, 8217, 8220, 8221, 8226, 8211, 8212, 26, 8482, 26, 8250, 26, 175, 731, 26,
        160, 26,  162, 163, 164, 26,  166, 167, 216, 169, 342, 171, 172, 173, 174, 198,
        176, 177, 178, 179, 900, 181, 182, 183, 248, 185, 343, 187, 188, 189, 190, 230,
        260, 302, 256, 262, 196, 197, 280, 274, 268, 201, 377, 278, 290, 310, 298, 315,
        352, 323, 325, 211, 332, 213, 214, 215, 370, 321, 346, 362, 220, 379, 381, 223,
        261, 303, 257, 263, 228, 229, 281, 275, 269, 233, 378, 279, 291, 311, 299, 316,
        353, 324, 326, 243, 333, 245, 246, 247, 371, 322, 347, 363, 252, 380, 382, 729
    };

    constexpr uint16_t CP1258ToUnicodeConversionTable[128] =
    {
        8364, 26, 8218, 402, 8222, 8230, 8224, 8225, 710, 8240, 26, 8249, 338, 26, 26, 26,
        26, 8216, 8217, 8220, 8221, 8226, 8211, 8212, 732, 8482, 26, 8250, 339, 26, 26, 376,
        160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175,
        176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
        192, 193, 194, 258, 196, 197, 198, 199, 200, 201, 202, 203, 768, 205, 206, 207,
        272, 209, 777, 211, 212, 416, 214, 215, 216, 217, 218, 219, 220, 431, 771, 223,
        224, 225, 226, 259, 228, 229, 230, 231, 232, 233, 234, 235, 769, 237, 238, 239,
        273, 241, 803, 243, 244, 417, 246, 247, 248, 249, 250, 251, 252, 432, 8363, 255,
    };

    constexpr uint16_t EBCDICToUnicodeConversionTable[256] =
    {
        0,   1,   2,   3,   26,  9,   10,  127, 26,  26,  26,  11,  12,  13,  14,  15,
        16,  17,  18,  19,  26,  10,  8,   26,  24,  25,  26,  145, 28,  29,  30,  31,
        26,  152, 28,  818, 26,  10,  23,  27,  26,  26,  26,  26,  26,  5,   6,   7,
        26,  26,  22,  133, 26,  26,  8,   4,   26,  26,  12,  146, 20,  21,  0,   26,
        32,  26,  26,  26,  26,  26,  26,  26,  26,  26,  162, 46,  60,  40,  43,  124,
        38,  26,  26,  26,  26,  26,  26,  26,  26,  26,  33,  36,  42,  41,  59,  172,
        45,  47,  26,  26,  26,  26,  26,  26,  26,  26,  166, 44,  37,  95,  62,  63,
        26,  26,  26,  26,  26,  26,  26,  26,  26,  96,  58,  35,  64,  39,  61,  34,
        26,  97,  98,  99,  100, 101, 102, 103, 104, 105, 26,  26,  26,  26,  26,  177,
        26,  106, 107, 108, 109, 110, 111, 112, 113, 114, 26,  26,  26,  26,  26,  26,
        26,  126, 115, 116, 117, 118, 119, 120, 121, 122, 26,  26,  26,  26,  26,  26,
        94,  26,  26,  26,  26,  26,  26,  26,  26,  26,  91,  93,  26,  26,  26,  26,
        123, 65,  66,  67,  68,  69,  70,  71,  72,  73,  26,  26,  26,  26,  26,  26,
        125, 74,  75,  76,  77,  78,  79,  80,  81,  82,  26,  26,  26,  26,  26,  26,
        92,  26,  83,  84,  85,  86,  87,  88,  89,  90,  26,  26,  26,  26,  26,  26,
        48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  26,  26,  26,  26,  26,  159
    };

    constexpr uint32_t codepointFrom2UTF8Bytes( const byte * bytes, const size_t position )
    {
        return (((bytes[position] & 0x1F) << 6)      |
                ((bytes[position + 1]) & 0x3F));
    }

    constexpr uint32_t codepointFrom3UTF8Bytes( const byte * bytes, const size_t position )
    {
        return (((bytes[position] & 0xF) << 12)      |
                ((bytes[position + 1] & 0x3F) <<  6) |
                (bytes[position + 2] & 0x3F));
    }

    constexpr uint32_t codepointFrom4UTF8Bytes( const byte * bytes, const size_t position )
    {
        return (((bytes[position] & 0x7) << 18)      |
                ((bytes[position + 1] & 0x3F) << 12) |
                ((bytes[position + 2] & 0x3F) <<  6) |
                (bytes[position + 3] & 0x3F));
    }

    constexpr void codepointTo2UTF8Bytes( const uint32_t codepoint,
                                          byte * string,
                                          size_t position )
    {
        string[position++] = (((codepoint >> 6) & 0x1F)  | 0xC0);
        string[position] =   ((codepoint & 0x3F)         | 0x80);
    }

    constexpr void codepointTo3UTF8Bytes( const uint32_t codepoint,
                                          byte * string,
                                          size_t position )
    {
        string[position++] = (((codepoint >> 12) & 0xF)  | 0xE0);
        string[position++] = (((codepoint >> 6) & 0x3F)  | 0x80);
        string[position] =   ((codepoint & 0x3F)         | 0x80);
    }

    constexpr void codepointTo4UTF8Bytes( const uint32_t codepoint,
                                          byte * string,
                                          size_t position )
    {
        string[position++] = (((codepoint >> 18) & 0x7)  | 0xF0);
        string[position++] = (((codepoint >> 12) & 0x3F) | 0x80);
        string[position++] = (((codepoint >> 6) & 0x3F)  | 0x80);
        string[position] =   ((codepoint & 0x3F)         | 0x80);
    }

    constexpr bool isNonCharacter( const omn::unicode::UTF32Character codepoint )
    {
        return (((codepoint & 65535) > 65533) || ((codepoint >= 64976) && (codepoint <= 65007)));
    }
}

namespace omn
{
    namespace unicode
    {
        constexpr UTF32Character nullCharacter = 0;
        constexpr UTF32Character NUL = 0;
        constexpr UTF32Character backspace = 8;
        constexpr UTF32Character BS = 8;
        constexpr UTF32Character horizontalTab = 9;
        constexpr UTF32Character HT = 9;
        constexpr UTF32Character lineFeed = 10;
        constexpr UTF32Character LF = 10;
        constexpr UTF32Character carriageReturn = 13;
        constexpr UTF32Character CR = 13;
        constexpr UTF32Character substituteCharacter = 26;
        constexpr UTF32Character SUB = 26;
        constexpr UTF32Character escapeCharacter = 27;
        constexpr UTF32Character ESC = 27;
        constexpr UTF32Character space = 32;
        constexpr UTF32Character SP = 32;
        constexpr UTF32Character deleteCharacter = 127;
        constexpr UTF32Character DEL = 127;
        constexpr UTF32Character byteOrderMark = 65279;
        constexpr UTF32Character BOM = 65279;
        constexpr UTF32Character replacementCharacter = 65533;

        constexpr UTF32Character fromASCII( const char character )
        {
            return ((character & 128) ? 26 : character);
        }

        constexpr UTF32Character fromISO88591( const byte character )
        {
            return character;
        }

        UTF32Character fromISO88592( const byte character );

        UTF32Character fromISO88593( const byte character );

        UTF32Character fromISO88594( const byte character );

        UTF32Character fromISO88595( const byte character );

        UTF32Character fromISO88596( const byte character );

        constexpr UTF32Character fromISO88597( const byte character )
        {
            if (character < 160) return character;
            if (character > 190) return ((character == 255) ? 26 : (character + 720));
            return ISO88597ToUnicodeConversionTable[character - 160];
        }

        UTF32Character fromISO88598( const byte character );

        UTF32Character fromISO88599( const byte character );

        UTF32Character fromISO885910( const byte character );

        UTF32Character fromISO885911( const byte character );

        UTF32Character fromISO885913( const byte character );

        UTF32Character fromISO885914( const byte character );

        UTF32Character fromISO885915( const byte character );

        UTF32Character fromISO885916( const byte character );

        constexpr UTF32Character fromWindows1250( const byte character )
        {
            if (character < 128) return character;
            return CP1250ToUnicodeConversionTable[character - 128];
        }

        constexpr UTF32Character fromWindows1251( const byte character )
        {
            if (character < 128) return character;
            if (character > 191) return (character + 848);
            return CP1251ToUnicodeConversionTable[character - 128];
        }

        constexpr UTF32Character fromWindows1252( const byte character )
        {
            if ((character < 128) || (character > 159)) return character;
            return CP1252ToUnicodeConversionTable[character - 128];
        }

        constexpr UTF32Character fromWindows1253( const byte character )
        {
            if (character < 128) return character;
            if (character > 189) return ((character == 255) ? 26 : (character + 720));
            return CP1253ToUnicodeConversionTable[character - 128];
        }

        UTF32Character fromWindows1254( const byte character );

        UTF32Character fromWindows1255( const byte character );

        constexpr UTF32Character fromWindows1256( const byte character )
        {
            if (character < 128) return character;
            return CP1256ToUnicodeConversionTable[character - 128];
        }

        constexpr UTF32Character fromWindows1257( const byte character )
        {
            if (character < 128) return character;
            return CP1257ToUnicodeConversionTable[character - 128];
        }

        constexpr UTF32Character fromWindows1258( const byte character )
        {
            if (character < 128) return character;
            return CP1258ToUnicodeConversionTable[character - 128];
        }

        constexpr UTF32Character fromUCS2( const uint16_t character )
        {
            return character;
        }

        constexpr UTF32Character fromUCS4( const uint32_t character )
        {
            return character;
        }

        constexpr UTF32Character fromEBCDIC( const byte character )
        {
            return EBCDICToUnicodeConversionTable[character];
        }

        namespace planes
        {
            enum plane : byte
            {
                BMP    = 0,
                SMP    = 1,
                SIP    = 2,
                TIP    = 3,
                // Unassigned Planes (4 to 13)
                SSP    = 14,
                SPUA_A = 15,
                SPUA_B = 16,
                
                // Aliases
                BasicMultilingualPlane = BMP,
                SupplementaryMultilingualPlane = SMP,
                SupplementaryIdeographicPlane = SIP,
                TertiaryIdeographicPlane = TIP,
                SupplementaryPrivateUseAreaA = SPUA_A,
                SupplementaryPrivateUseAreaB = SPUA_B
            };
            
            constexpr uint16_t planeOf( const UTF32Character codepoint )
            {
                return (codepoint >> 16);
            }

            constexpr bool belongsToBMP( const UTF32Character codepoint )
            {
                return (codepoint < 0x10000);
            }

            constexpr bool belongsToSMP( const UTF32Character codepoint )
            {
                return ((codepoint >> 16) == 1);
            }

            constexpr bool belongsToSIP( const UTF32Character codepoint )
            {
                return ((codepoint >> 16) == 2);
            }

            constexpr bool belongsToUnassignedPlanes( const UTF32Character codepoint )
            {
                return ((codepoint >= 0x30000) && (codepoint <= 0xDFFFF));
            }

            constexpr bool belongsToSSP( const UTF32Character codepoint )
            {
                return ((codepoint >> 16) == 14);
            }

            constexpr bool belongsToPrivateUsePlanes( const UTF32Character codepoint )
            {
                return ((codepoint >= 0xF0000) && (codepoint <= 0x10FFFF));
            }

            constexpr bool belongsToNoValidPlane( const UTF32Character codepoint )
            {
                return (codepoint > 0x10FFFF);
            }
        }
        
        namespace UTF16
        {
        }

        namespace UTF8
        {
            constexpr bool isOutsideEncodingRange( const UTF32Character codepoint )
            {
                return (codepoint > 2097151);
            }

            constexpr byte bytesNeededToEncode( const UTF32Character codepoint )
            {
                if (codepoint < 128) return 1;
                if (codepoint < 2048) return 2;
                if (codepoint < 65536) return 3;
                if (codepoint < 2097152) return 4;
                if (codepoint < 67108864) return 5;
                return 6;
            }

            constexpr bool isLeadingByte( const byte character )
            {
                return ((character >= 192) && (character <= 247));
            }

            constexpr bool isContinuationByte( const byte character )
            {
                return ((character & 0xC0) == 0x80);
            }

            constexpr byte sequenceSize( const byte leadingByte )
            {
                if (leadingByte >= 224) return ((leadingByte >> 4) - 11);
                if (leadingByte >= 192) return 2;
                return 1;
            }

            UTF32Character decode2Bytes( const byte * string,
                                         const size_t position,
                                         const size_t stringSize );

            UTF32Character decode3Bytes( const byte * string,
                                         const size_t position,
                                         const size_t stringSize );

            UTF32Character decode4Bytes( const byte * string,
                                         const size_t position,
                                         const size_t stringSize );

            UTF32Character decode( const byte * string,
                                   const size_t position,
                                   const size_t stringSize );

            inline UTF32Character decode( const UTF8String & string,
                                          const size_t position )
            {
                return decode((const byte *)(string.data()), position, string.size());
            }

            UTF32String decode( const UTF8Character * string,
                                size_t stringSize = ((size_t)(-1)) );

            inline UTF32String decode( const UTF8String & string )
            {
                return decode(string.data(), string.size());
            }

            bool encodeAs2Bytes( const UTF32Character character,
                                 byte * string,
                                 const size_t position,
                                 const size_t stringSize );

            bool encodeAs3Bytes( const UTF32Character character,
                                 byte * string,
                                 const size_t position,
                                 const size_t stringSize );

            bool encodeAs4Bytes( const UTF32Character character,
                                 byte * string,
                                 const size_t position,
                                 const size_t stringSize );

            byte encode( const UTF32Character character,
                         byte * string,
                         const size_t position,
                         const size_t stringSize );

            UTF8String encode( const UTF32Character character );

            UTF8String encode( const UTF32Character * string,
                               size_t stringSize = ((size_t)(-1)) );

            inline UTF8String encode( const UTF32String string )
            {
                return encode(string.data(), string.size());
            }

            bool isValid( const byte * string,
                          const size_t position,
                          const size_t stringSize );

            inline bool isValid( const UTF8String string, const size_t position )
            {
                return isValid((const byte *)(string.data()), string.size(), position);
            }

            bool isValid( const byte * string, const size_t stringSize );

            inline bool isValid( const UTF8String string )
            {
                return isValid((const byte *)(string.data()), string.size());
            }

            void replaceInvalidBytes( byte * string, const size_t stringSize );

            inline void replaceInvalidBytes( UTF8String & string )
            {
                replaceInvalidBytes(const_cast<byte *>((const byte *)(string.data())),
                                    string.size());
            }
        }
    }
}

namespace std
{
    inline ostream & operator << ( ostream & os, const omn::unicode::UTF32Character character )
    {
        os << omn::unicode::UTF8::encode(character);
        return os;
    }

    inline ostream & operator << ( ostream & os, const omn::unicode::UTF32Character * string )
    {
        os << omn::unicode::UTF8::encode(string);
        return os;
    }

    inline ostream & operator << ( ostream & os, const omn::unicode::UTF32String & string )
    {
        os << omn::unicode::UTF8::encode(string);
        return os;
    }
}

#endif // _OMN_CHARENCODING_INCLUDED
