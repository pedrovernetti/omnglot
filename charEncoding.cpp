
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

#include "charEncoding.hpp"

namespace omn
{
    namespace unicode
    {
        UTF32Character fromISO88596( const byte character )
        {
            if (character < 161) return character;
            if (character > 192)
            {
                if ((character < 219) || ((character > 223) && (character < 243)))
                    return (character + 1376);
            }
            else
            {
                if ((character == 164) || (character == 173)) return character;
                if (character == 172) return 1548;
                if (character == 187) return 1563;
                if (character == 191) return 1567;
            }
            return 26;
        }

        UTF32Character fromISO88598( const byte character )
        {
            if (character == 161) return 26;
            if (character < 170) return character;
            if (character < 191) return CP1255ToUnicodeConversionTable[character - 128];
            if (character < 223) return 26;
            if (character == 223) return 8215;
            if (character < 251) return (character + 1264);
            if ((character == 253) || (character == 254)) return (character + 7953);
            return 26;
        }

        UTF32Character fromISO88599( const byte character )
        {
            if (character > 207)
            {
                if (character > 239)
                {
                    if (character == 222) return 304;
                    if (character == 223) return 350;
                    if (character == 240) return 287;
                }
                else if ((character & 240) == 208)
                {
                    if (character == 190) return 305;
                    if (character == 191) return 351;
                    if (character == 208) return 288;
                }
            }
            return character;
        }

        namespace UTF8
        {
            UTF32Character decode2Bytes( const byte * string,
                                         const size_t position,
                                         const size_t stringSize )
            {
                if ((position + 1) >= stringSize)
                    return ((position < stringSize) ? string[position] : 0);
                return codepointFrom2UTF8Bytes(string, position);
            }

            UTF32Character decode3Bytes( const byte * string,
                                         const size_t position,
                                         const size_t stringSize )
            {
                if ((position + 2) >= stringSize)
                    return ((position < stringSize) ? string[position] : 0);
                return codepointFrom3UTF8Bytes(string, position);
            }

            UTF32Character decode4Bytes( const byte * string,
                                         const size_t position,
                                         const size_t stringSize )
            {
                if ((position + 3) >= stringSize)
                    return ((position < stringSize) ? string[position] : 0);
                return codepointFrom4UTF8Bytes(string, position);
            }

            UTF32Character decode( const byte * string,
                                   const size_t position,
                                   const size_t stringSize )
            {
                if (position >= stringSize) return 0;
                const byte character = string[position];
                if (character & 128)
                {
                    if (character > 193)
                    {
                        if ((character < 224) && (stringSize > (position + 1)))
                            return codepointFrom2UTF8Bytes(string, position);
                        if ((character < 240) && (stringSize > (position + 2)))
                            return codepointFrom3UTF8Bytes(string, position);
                        if ((character < 245) && (stringSize > (position + 3)))
                            return codepointFrom4UTF8Bytes(string, position);
                    }
                    return 26;
                }
                return character;
            }

            UTF32String decode( const UTF8Character * string, size_t stringSize )
            {
                UTF32String decodedString(stringSize, U'\0');
                size_t i, j;
                byte character;
                for (i = 0, j = 0; j < stringSize; j++)
                {
                    character = string[j];
                    if (character & 128)
                    {
                        if (character > 193)
                        {
                            if ((character < 224) && (stringSize > (j + 1)))
                            {
                                decodedString[i++] = codepointFrom2UTF8Bytes((const byte *)(string), j);
                                j += 1;
                            }
                            else if ((character < 240) && (stringSize > (j + 2)))
                            {
                                decodedString[i++] = codepointFrom3UTF8Bytes((const byte *)(string), j);
                                j += 2;
                            }
                            else if ((character < 245) && (stringSize > (j + 3)))
                            {
                                decodedString[i++] = codepointFrom4UTF8Bytes((const byte *)(string), j);
                                j += 3;
                            }
                        }
                    }
                    else decodedString[i++] = character;
                }
                decodedString.resize(i);
                return decodedString;
            }

            bool encodeAs2Bytes( const UTF32Character character,
                                 byte * string,
                                 const size_t position,
                                 const size_t stringSize )
            {
                if ((position + 1) >= stringSize) return 0;
                codepointTo2UTF8Bytes(character, string, position);
                return (character > 0x7F);
            }

            bool encodeAs3Bytes( const UTF32Character character,
                                 byte * string,
                                 const size_t position,
                                 const size_t stringSize )
            {
                if ((position + 2) >= stringSize) return 0;
                codepointTo3UTF8Bytes(character, string, position);
                return (character > 0x7FF);
            }

            bool encodeAs4Bytes( const UTF32Character character,
                                 byte * string,
                                 const size_t position,
                                 const size_t stringSize )
            {
                if ((position + 3) >= stringSize) return 0;
                codepointTo4UTF8Bytes(character, string, position);
                return (character > 0xFFFF);
            }

            byte encode( const UTF32Character character,
                         byte * string,
                         const size_t position,
                         const size_t stringSize )
            {
                if (position >= stringSize) return 0;
                if (character <= 0x7F)
                {
                    string[position] = character;
                    return 1;
                }
                if (character <= 0x7FF)
                {
                    codepointTo2UTF8Bytes(character, string, position);
                    return 2;
                }
                if (character <= 0xFFFF)
                {
                    codepointTo3UTF8Bytes(character, string, position);
                    return 3;
                }
                else
                {
                    codepointTo4UTF8Bytes(character, string, position);
                    return 4;
                }
            }

            UTF8String encode( const UTF32Character character )
            {
                byte buffer[5] = {0, 0, 0, 0, 0};
                if (character <= 0x7F) buffer[0] = character;
                else if (character <= 0x7FF) codepointTo2UTF8Bytes(character, buffer, 0);
                else if (character <= 0xFFFF) codepointTo3UTF8Bytes(character, buffer, 0);
                else codepointTo4UTF8Bytes(character, buffer, 0);
                return UTF8String((UTF8Character *)(buffer));
            }

            UTF8String encode( const UTF32Character * string, size_t stringSize )
            {
                if (stringSize == ((size_t)(-1)))
                    for (stringSize = 0; string[stringSize]; stringSize++);
                byte * encodedString = new byte[stringSize * 4]{};
                size_t i, j;
                UTF32Character character;
                for (i = 0, j = 0; i < stringSize; i++, j++)
                {
                    character = string[i];
                    if (character <= 0x7F)
                        encodedString[j] = character;
                    else if (character <= 0x7FF)
                    {
                        codepointTo2UTF8Bytes(character, encodedString, j);
                        j += 1;
                    }
                    else if (character <= 0xFFFF)
                    {
                        codepointTo3UTF8Bytes(character, encodedString, j);
                        j += 2;
                    }
                    else
                    {
                        codepointTo4UTF8Bytes(character, encodedString, j);
                        j += 3;
                    }
                }
                return UTF8String((UTF8Character *)(encodedString));
            }

            bool isValid( const byte * string,
                          const size_t position,
                          const size_t stringSize )
            {
                if (position >= stringSize) return false;
                const byte value = string[position];
                if ((value > 0xF4) || (value == 0xC0) || (value == 0xC1)) return false;
                if (isContinuationByte(value))
                {
                    for (size_t i = position, j = 0; (j < 4); i--, j++)
                    {
                        if ((!isContinuationByte(string[i])) &&
                            (sequenceSize(string[i]) > j))
                            return true;
                    }
                    return false;
                }
                const byte size = sequenceSize(value);
                if ((position + size) > stringSize) return false;
                if ((size >= 2) && (!isContinuationByte(string[position + 1]))) return false;
                if ((size >= 3) && (!isContinuationByte(string[position + 2]))) return false;
                if (size >= 4)
                {
                    if (!isContinuationByte(string[position + 3])) return false;
                    if (decode(string, position, stringSize) > 0x10FFFF) return false;
                }
                return true;
            }

            bool isValid( const byte * string, const size_t stringSize )
            {
                byte character, expectedContinuationBytes = 0;
                for (size_t i = 0; i < stringSize; i++)
                {
                    character = string[i];
                    if ((character > 0xF4) || (character == 0xC0) || (character == 0xC1))
                        return false;
                    if (expectedContinuationBytes)
                    {
                        if ((character & 0xC0) != 0x80) return false;
                        expectedContinuationBytes--;
                    }
                    else
                    {
                        if ((character & 0xC0) == 0x80) return false;
                        else expectedContinuationBytes = sequenceSize(character) - 1;
                    }
                    if ((string[i] == 0) && (i < (stringSize - 1))) return false;
                    if (expectedContinuationBytes)
                        if (isNonCharacter(decode(string, i, stringSize))) return false;
                }
                if (expectedContinuationBytes) return false;
                return true;
            }

            void replaceInvalidBytes( byte * string, const size_t stringSize = ((size_t)(-1)) )
            {
                bool stopAtNUL = (stringSize == ((size_t)(-1))), brokenSequence = false;
                byte character, expectedContinuationBytes = 0;
                for (size_t i = 0, j; i < stringSize; i++)
                {
                    character = string[i];
                    if (stopAtNUL && (!character)) break;
                    if ((character > 0xF4) || (character == 0xC0) || (character == 0xC1))
                        string[i] = 26;
                    else if ((character & 0xC0) == 0x80)
                    {
                        if (!expectedContinuationBytes) string[i] = 26;
                        else expectedContinuationBytes--;
                    }
                    else if (character > 193)
                    {
                        expectedContinuationBytes = (sequenceSize(character) - 1);
                        if (!expectedContinuationBytes) continue;
                        for (brokenSequence = false, j = 1; j <= expectedContinuationBytes; j++)
                            brokenSequence |= ((string[i + j] & 0xC0) != 0x80);
                        if (brokenSequence)
                        {
                            string[i] = 26;
                            expectedContinuationBytes = 0;
                        }
                    }
                }
            }
        }
    }
}
