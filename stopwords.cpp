
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

#include "stopwords.hpp"

namespace omn
{
	namespace stopwords
	{
		void index::insertAllByLanguage( ISO6392LanguageCode language )
		{
			if (language == ISO6392LanguageCode::mul)
			{
				const size_t totalLanguages = ISO6392LanguageCode::zza + 1;
				const unicode::UTF32Character * const * stopwordsList;
				size_t count;
				for (uint16_t i = 0; i < totalLanguages; i++)
				{
					if (!(count = countPerLanguage[i])) continue;
					stopwordsList = all[i];
					this->insertAll(stopwordsList, count, (ISO6392LanguageCode)(i));
				}
			}
			else
			{
				const unicode::UTF32Character * const * stopwordsList = all[language];
				const size_t count = countPerLanguage[language];
				this->insertAll(stopwordsList, count, language);
			}
		}
		
        index::index() :
			Entries()
        {
		}
			
		index::index( ISO6392LanguageCode language ) :
			Entries()
		{
			this->insertAllByLanguage(language);
		}
			
		index::index( const unicode::UTF32Character * const * stopwordsList, 
					  const size_t count,
				      ISO6392LanguageCode language ) :
			Entries()
		{
			this->insertAll(stopwordsList, count, language);
		}

		tokenization::tokenizedString listByLanguage( const ISO6392LanguageCode language )
		{
			const size_t total = countPerLanguage[language];
			if (!total) return tokenization::tokenizedString{};
			const unicode::UTF32Character * const * UTF32ConstList = all[language];
			return (tokenization::tokenizedString(UTF32ConstList, (UTF32ConstList + total)));
		}
	}
}
