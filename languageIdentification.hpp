
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
#ifndef _OMN_LANGUAGEIDENTIFICATION_DEFINED
#define _OMN_LANGUAGEIDENTIFICATION_DEFINED

#include "globalUtilities.hpp"
#include "ISO639.hpp"
#include "characterClass.hpp"
#include "map.hpp"
#include "vector.hpp"
#include <algorithm>

namespace // internal parts
{
    constexpr double roundedScore( const double value )
    {
        return (((((int32_t)(value * 1000.0) % 10) >= 5) + ((uint32_t)(value * 100.0))) / 100.0);
    }
}

namespace omn
{
    namespace languageIdentification
    {
        inline double minimumAcceptableConfidence = 0.1;

        using score = std::pair<ISO6392LanguageCode, double>;
        using scores = vector<score>;
        using scoresMap = map<ISO6392LanguageCode, double>;

        class identification
        {
            protected:

            static inline bool isActualWord( const unicode::UTF32String & token )
            {
                return ((unicode::classOf(token[0]) & 0b00000000000100000000) &&
                        (unicode::classOf(token[token.size() - 1]) & 0b10000000000000100000));
            }

            static inline bool isPartOfLanguage( const unicode::UTF32String & token )
            {
                return ((unicode::classOf(token[0]) & 0b10000000000000100000) &&
                        (unicode::classOf(token[token.size() - 1]) & 0b10000000000000100000));
            }

            static constexpr bool descendingScore( const score & first, const score & last )
            {
                return (first.second > last.second);
            }

            static constexpr double roundedScore( const double value )
            {
                return (((((int32_t)(value * 1000.0) % 10) >= 5) + ((uint32_t)(value * 100.0))) / 100.0);
            }

            static inline void improveNonLanguageScore( scoresMap & byLanguage,
                                                        const size_t nonActualWordsCount )
            {
                if ((byLanguage.size() == 1) && (byLanguage.count(ISO6392LanguageCode::zxx)))
                    byLanguage[ISO6392LanguageCode::zxx] += nonActualWordsCount;
            }

            static inline void removeUselessScores( scoresMap & byLanguage )
            {
                byLanguage.erase(ISO6392LanguageCode::mul);
                byLanguage.erase(ISO6392LanguageCode::mis);
                byLanguage.erase(ISO6392LanguageCode::und);
            }

            public:

            identification() = delete;
        };
    }
}

#endif // _OMN_LANGUAGEIDENTIFICATION_DEFINED
