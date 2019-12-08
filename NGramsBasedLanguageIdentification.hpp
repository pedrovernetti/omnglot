
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
#ifndef _OMN_NGRAMSBASEDLANGUAGEIDENTIFICATION_INCLUDED
#define _OMN_NGRAMSBASEDLANGUAGEIDENTIFICATION_INCLUDED

#include "globalUtilities.hpp"
#include "languageIdentification.hpp"
#include "letterNGrams.hpp"
#include "unorderedMap.hpp"
#include "set.hpp"
#include "tokenization.hpp"
#include <algorithm>

namespace omn
{
    namespace languageIdentification
    {
        class NGramsBased : public identification
        {
            protected:

            static unorderedMap<letterNGrams::letterNGram<3>, set<ISO6392LanguageCode>> NGramsIndex;
            static const set<ISO6392LanguageCode> NoLanguage;

            static void initializeNGramsIndex();

            static const set<ISO6392LanguageCode> & languagesOf( const unicode::UTF32String & string,
                                                                 const size_t position );

            static scores actuallyIdentify( const tokenization::tokenizedString & tokens,
                                            const bool includeNonLinguisticScore );

            public:

            NGramsBased() = delete;

            static inline scores identify ( const tokenization::tokenizedString & topWords,
                                            const bool includeNonLinguisticScore = true )
            {
                if (topWords.empty()) return scores{};
                if (NGramsBased::NGramsIndex.size() <= 1) NGramsBased::initializeNGramsIndex();
                return NGramsBased::actuallyIdentify(topWords, includeNonLinguisticScore);
            }
        };
    }
}

#endif // _OMN_NGRAMSBASEDLANGUAGEIDENTIFICATION_INCLUDED
