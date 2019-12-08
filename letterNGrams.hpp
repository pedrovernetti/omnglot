
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
#ifndef _OMN_LETTERNGRAM_INCLUDED
#define _OMN_LETTERNGRAM_INCLUDED

#include "globalUtilities.hpp"
#include "charEncoding.hpp"
#include "characterTransformations.hpp"
#include "vector.hpp"
#include "bag.hpp"
#include "array.hpp"

namespace omn
{
	namespace letterNGrams
	{
		template <size_t N>
		using letterNGram = array<unicode::UTF32Character, N>;
		
		using letterUnigram = letterNGram<1>;
		using letterBigram = letterNGram<2>;
		using letterTrigram = letterNGram<3>;
		using letterQuadrigram = letterNGram<4>;

		template <size_t N>
		unicode::UTF32String preExtrationString( const unicode::UTF32String & string )
		{
			const size_t N_ = N ? 1 : 0;
			unicode::UTF32String result((string.size() + (N_ * 2)), 0);
			const size_t size = string.size();
			size_t i = N_, j = 0;
			while (unicode::classOf(string[j]) & 0b00000000000000000100) j++;
			bool previousIsWhitespace = false;
			for (characterClass classOf; j < size; j++)
			{
				classOf = unicode::classOf(string[j]);
				if (classOf & 0b00000000000000000100)
				{
					if (!previousIsWhitespace)result[i++] = 0;
					previousIsWhitespace = true;
				}
				else
				{
					previousIsWhitespace = false;
					if (classOf & 0b10000000000000000000) result[i++] = string[j];
				}
			}
			result.resize(i + N_ - ((result[i - 1] == 0) && (i > N_)));
			return casefold(result);
		}
		
		template <size_t N>
		unicode::UTF32String preExtrationToken( const unicode::UTF32String & token )
		{
			const size_t N_ = N ? 1 : 0;
			unicode::UTF32String result((token.size() + (N_ * 2)), 0);
			const size_t size = token.size();
			size_t i = N_, j = 0;
			for (; j < size; j++)
			{
				if (unicode::classOf(token[j]) & 0b10000000000000000000) 
					result[i++] = token[j];
			}
			result.resize(i + N_);
			return casefold(result);
		}
		
		template <size_t N>
		inline size_t count( const unicode::UTF32String & token )
		{
			return ((N > (token.size() + 3)) ? 0 : ((token.size() + 3) - N));
		}
		
		template <size_t N>
		size_t count( const vector<unicode::UTF32String> & tokens )
		{
			size_t total = 0;
			for (const auto & token : tokens) 
				total += ((N > (token.size() + 3)) ? 0 : ((token.size() + 3) - N));
			return total;
		}
		
		template <size_t N>
		size_t count( const bag<unicode::UTF32String> & tokens )
		{
			size_t total = 0;
			for (const auto & token : tokens) 
			{
				if (N < (token.first.size() + 3)) 
					total += (token.second * ((token.first.size() + 3) - N));
			}
			return total;
		}
		
		template <size_t N>
		vector<letterNGram<N>> extract( const vector<unicode::UTF32String> & tokens )
		{
			if ((!N) || (tokens.empty())) return vector<letterNGram<N>>{};
			vector<letterNGram<N>> result;
			unicode::UTF32String paddedBuffer;
			letterNGram<N> NGramBuffer;
			size_t totalNGrams = (N > 1) ? tokens.size() : 0;
			for (size_t i = 0, size = tokens.size(); i < size; i++) totalNGrams += tokens[i].size();
			result.reserve(totalNGrams);
			for (size_t i = 0, j, k, size = tokens.size(), jsize, ksize; i < size; i++)
			{
				paddedBuffer = (N > 1) ? preExtrationToken<1>(tokens[i]) : preExtrationToken<0>(tokens[i]);
				jsize = (paddedBuffer.size() - (N - 1));
				if (jsize < N) continue;
				for (j = 0; j < jsize; j++)
				{
					for (k = j, ksize = j + N; k < ksize; k++) NGramBuffer[k - j] = paddedBuffer[k];
					result.push_back(NGramBuffer);
				}
			}
			result.shrink_to_fit();
			return result;
		}

		template <size_t N>
		bag<letterNGram<N>> extractToBag( const vector<unicode::UTF32String> & tokens )
		{
			if ((!N) || (tokens.empty())) return vector<letterNGram<N>>{};
			bag<letterNGram<N>> result;
			unicode::UTF32String paddedBuffer;
			letterNGram<N> NGramBuffer;
			size_t totalNGrams = (N > 1) ? tokens.size() : 0;
			for (size_t i = 0, size = tokens.size(); i < size; i++) totalNGrams += tokens[i].size();
			result.reserve(totalNGrams);
			for (size_t i = 0, j, k, size = tokens.size(), jsize, ksize; i < size; i++)
			{
				paddedBuffer = 
					(N > 1) ? preExtrationToken<1>(tokens[i]) : preExtrationToken<0>(tokens[i]);
				jsize = (paddedBuffer.size() - (N - 1));
				if (jsize < N) continue;
				for (j = 0; j < jsize; j++)
				{
					for (k = j, ksize = j + N; k < ksize; k++) NGramBuffer[k - j] = paddedBuffer[k];
					result.insert(NGramBuffer);
				}
			}
			return result;
		}
	}
	// list, bag ;; string, text, bag
}

namespace std
{
	template <size_t N> 
	ostream & operator << ( ostream & os, const omn::letterNGrams::letterNGram<N> & NGram )
	{
		for (size_t i = 0; i < N; i++) os << ((NGram[i]) ? omn::unicode::UTF8::encode(NGram[i]) : "_");
		return os;
	}
}

#endif // _OMN_LETTERNGRAM_INCLUDED
