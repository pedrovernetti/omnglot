
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
#ifndef _OMN_TOKENIZATION_INCLUDED
#define _OMN_TOKENIZATION_INCLUDED

#include "globalUtilities.hpp"
#include "characterClass.hpp"
#include "vector.hpp"
#include <queue>
#include <algorithm>

namespace // internal parts
{
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
        return false;
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
}

namespace omn
{
    namespace tokenization
    {
        using tokenizedString = vector<unicode::UTF32String>;
        using tokenizationFunction = tokenizedString (*)(unicode::UTF32String);

        tokenizedString tokenize( unicode::UTF32String UTF32Text );

        tokenizedString tokenize( const unicode::UTF32Character * UTF32Text,
                                  size_t textSize = ((size_t)(-1)) );
    }
}

#endif // _OMN_TOKENIZATION_INCLUDED
