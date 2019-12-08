
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright 2019 Pedro Vernetti G.
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
#ifndef _OMN_TOKENIZATION_INCLUDED
#define _OMN_TOKENIZATION_INCLUDED

#include "globalUtilities.hpp"
#include "characterClass.hpp"
#include "vector.hpp"
#include <queue>
#include <algorithm>

namespace // internal parts
{
    /*inline bool notASpecialCase(  )

    inline bool isBetweenLetters( const omn::unicode::UTF32String & string,
                                  const omn::characterClass * characterClasses,
                                  const size_t position )
    {
    }

    inline bool isBetweenPartsOfWord( const omn::unicode::UTF32String & string,
                                      const omn::characterClass * characterClasses,
                                      const size_t position )
    {
    }

    inline bool isBeforeNumeral( const omn::unicode::UTF32String & string,
                                 const omn::characterClass * characterClasses,
                                 const size_t position )
    {
        if (characterClasses[position + 1] != omn::characterClass::Digit) return false;
        return (isSeparator(characterClasses[position - 1]) ||
                (isStandalone(characterClasses[position - 1]) &&
                (string[position] != string[position - 1])));
    }

    constexpr bool (* specialCaseCheckings[])
        (const omn::unicode::UTF32String &, const omn::characterClass *, const size_t) =
    {
        nullptr, isBetweenLetters, isBetweenPartsOfWord, isBeforeNumeral
    };

    enum specialCaseType : byte
    {
        NON = 0, // not a especial case
        BLE = 1, // Between Letters
        BPW    = 2, // Between Parts-of-Word
        BNU = 3  // Before Numerals

    };

    constexpr const unicode::UTF32Character goesBetweenLetters[] =
    {
        0x002D, 0x005F, 0x058A, 0x05BE, 0x1400, 0x1806, 0x2010, 0x2011, 0x203F, 0x2040,
        0x2054, 0x2E17, 0x2E40, 0x30A0, 0xFE33, 0xFE34, 0xFE4D, 0xFE4E, 0xFE4F, 0xFE63,
        0xFF0D, 0xFF3F
    };

    constexpr const unicode::UTF32Character specialBeginningsOfNumeral[] =
    {
        0x002B, 0x002D, 0x00B1, 0x207A, 0x207B, 0xFE63, 0xFF0D,
    };*/

    constexpr bool isJunk( omn::characterClass charClass )
    {
        return ((!charClass) || (charClass & 0b01100000000000000000) || (charClass == 0b00000000000000000001));
    }

    constexpr bool isSeparator( omn::characterClass charClass )
    {
        return (charClass & 0b00000000000000000100);
    }

    constexpr bool isStandalone( const omn::characterClass charClass )
    {
        return (charClass & 0b00001000000000100011);
    }

    constexpr bool isPartOfWord( omn::characterClass charClass )
    {
        return (charClass & 0b10000000000000000000);
    }

    omn::unicode::UTF32String tidyString( const omn::unicode::UTF32String & string,
                                            omn::characterClass * characterClasses );

    inline void enqueueToken( const omn::unicode::UTF32String & UTF32Text,
                              const size_t i,
                              size_t & wordSize,
                              std::queue<omn::unicode::UTF32String> & textBuffer )
    {
        textBuffer.push(UTF32Text.substr((i - wordSize), wordSize));
        wordSize = 0;
    }

    inline bool isSpecialPartOfWord( const omn::unicode::UTF32String & UTF32Text,
                                     const omn::characterClass * characterClasses,
                                     const size_t i )
    {
         //if (std::binary_search(simpleSpecialCases, simpleSpecialCases + , UTF32Text[i]))
            return false;//((characterClasses[i - 1]
            //std::binary_search(a, (a+1000000), a[250000]);
    }

    void enqueueTokens( const omn::unicode::UTF32String & UTF32Text,
                        const omn::characterClass * characterClasses,
                        std::queue<omn::unicode::UTF32String> & textBuffer )
    {
        const size_t textSize = UTF32Text.size() - 1;
        for (size_t i = 1, wordSize = 0; i < textSize; i++)
        {
            if (isSeparator(characterClasses[i]) && (wordSize))
                enqueueToken(UTF32Text, i, wordSize, textBuffer);
            else if (isStandalone(characterClasses[i]))
            {
                if (wordSize > 0) enqueueToken(UTF32Text, i, wordSize, textBuffer);
                if (isSpecialPartOfWord(UTF32Text, characterClasses, i)) wordSize++;
                else enqueueToken(UTF32Text, (i + 1), (wordSize = 1), textBuffer);
            }
            else if (isPartOfWord(characterClasses[i]))
                wordSize++;
        }
    }

    //void tokenizeWhitespace

    //void enqueueTokensByDictionary
}

namespace omn
{
    namespace tokenization
    {
        using tokenizedString = vector<unicode::UTF32String>;
        using tokenizationFunction = tokenizedString (*)(unicode::UTF32String);

        //tokenizedString split( const uint32_t * UTF32Text, size_t textSize,

        tokenizedString tokenize( unicode::UTF32String UTF32Text );

        tokenizedString tokenize( const unicode::UTF32Character * UTF32Text,
                                  size_t textSize = ((size_t)(-1)) );
    }
}

#endif // _OMN_TOKENIZATION_INCLUDED
