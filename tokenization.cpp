
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

#include "tokenization.hpp"

namespace // internal parts
{
    omn::unicode::UTF32String tidyString( const omn::unicode::UTF32String & string,
                                          omn::characterClass * characterClasses )
    {
        const size_t size = string.size();
        omn::unicode::UTF32String buffer((size + 4), 32);
        characterClasses[0] = characterClasses[1] = omn::characterClass::HorizontalSpace;
        size_t j = 2;
        omn::characterClass charClass;
        for (size_t i = 0; i < size; i++)
        {
            charClass = omn::unicode::classOf(string[i]);
            if (isJunk(charClass)) continue;
            if (isSeparator(charClass))
            {
                characterClasses[j] = omn::characterClass::HorizontalSpace;
                buffer[j++] = 32;
                continue;
            }
            characterClasses[j] = charClass;
            buffer[j++] = string[i];
        }
        characterClasses[j++] = omn::characterClass::HorizontalSpace;
        characterClasses[j++] = omn::characterClass::HorizontalSpace;
        buffer.resize(j);
        return buffer;
    }

}

namespace omn
{
    namespace tokenization
    {
        tokenizedString tokenize( unicode::UTF32String UTF32Text )
        {
            if (UTF32Text.empty()) return tokenizedString{};
            std::queue<unicode::UTF32String> textBuffer;
            characterClass * characterClasses = new characterClass[UTF32Text.size() + 4];
            UTF32Text = tidyString(UTF32Text, characterClasses);
            enqueueTokens(UTF32Text, characterClasses, textBuffer);
            delete[] characterClasses;
            const size_t count = textBuffer.size();
            unicode::UTF32String * tokens = new unicode::UTF32String[count];
            for (size_t i = 0; i < count; i++)
            {
                tokens[i] = textBuffer.front();
                textBuffer.pop();
            }
            tokenizedString result(tokens, (tokens + count));
            delete[] tokens;
            return result;
        }

        tokenizedString tokenize( const unicode::UTF32Character * UTF32Text, size_t textSize )
        {
            if (textSize == 0) return tokenizedString{};
            if (textSize == ((size_t)(-1)))
            {
                unicode::UTF32String buffer(UTF32Text);
                return tokenize(buffer);
            }
            else
            {
                unicode::UTF32String buffer(UTF32Text, (UTF32Text + textSize));
                return tokenize(buffer);
            }
        }
    }
}
