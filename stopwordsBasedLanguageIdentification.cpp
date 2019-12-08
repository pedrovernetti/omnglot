
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

#include "stopwordsBasedLanguageIdentification.hpp"

namespace omn
{
    namespace languageIdentification
    {
        stopwords::index stopwordsBased::StopwordsIndex{};

        scores stopwordsBased::actuallyIdentify( const tokenization::tokenizedString & tokens,
                                                 const stopwords::index & stopwordsIndex,
                                                 const bool includeNonLinguisticScore )
        {
            if (tokens.empty()) return scores{};
            scoresMap byLanguage;
            size_t total = 0, nonActualWordsCount = 0;
            for (const auto & token : tokens)
            {
                if (identification::isPartOfLanguage(token))
                {
                    total += stopwordsIndex.contains(token);
                    if (!identification::isActualWord(token)) nonActualWordsCount++;
                    for (const auto & language : stopwordsIndex.languagesOf(token))
                        byLanguage[language] += 1;
                }
                else if (includeNonLinguisticScore) byLanguage[ISO6392LanguageCode::zxx] += 1;
            }
            if (includeNonLinguisticScore)
            {
                total += byLanguage[ISO6392LanguageCode::zxx];
                identification::improveNonLanguageScore(byLanguage, nonActualWordsCount);
            }
            if (!total) return scores{};
            identification::removeUselessScores(byLanguage);
            scores results;
            results.reserve(byLanguage.size());
            double confidence;
            for (const auto & score : byLanguage)
            {
                confidence = score.second / total;
                if (confidence < minimumAcceptableConfidence) continue;
                results.push_back(std::make_pair(score.first, identification::roundedScore(confidence)));
            }
            std::sort(results.begin(), results.end(), identification::descendingScore);
            return results;
        }
    }
}
