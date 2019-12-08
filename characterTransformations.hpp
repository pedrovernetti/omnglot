
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
#ifndef _OMN_CHARACTERTRANSFORMATIONS_INCLUDED
#define _OMN_CHARACTERTRANSFORMATIONS_INCLUDED

#include "globalUtilities.hpp"
#include "characterClass.hpp"
#include <algorithm>

namespace // internal parts
{
	inline bool isLetter( const omn::characterClass classOf )
	{
		return (classOf & 0b00000000000100000000);
	}
	
	inline bool isDiacritic( const omn::characterClass classOf )
	{
		return (classOf & 0b00000010000000000000);
	}
}

namespace omn
{

	unicode::UTF32Character casefoldCharacter( const unicode::UTF32Character codepoint,
											   const characterClass classOf );

	inline unicode::UTF32Character casefoldCharacter( const unicode::UTF32Character codepoint )
	{
		return casefoldCharacter(codepoint, omn::unicode::classOf(codepoint));
	}
	
	unicode::UTF32Character lowercaseCharacter( const unicode::UTF32Character codepoint,
												const characterClass classOf );
	
	inline unicode::UTF32Character lowercaseCharacter( const unicode::UTF32Character codepoint )
	{
		return lowercaseCharacter(codepoint, omn::unicode::classOf(codepoint));
	}
	
	unicode::UTF32Character uppercaseCharacter( const unicode::UTF32Character codepoint,
												const characterClass classOf );
													 
	inline unicode::UTF32Character uppercaseCharacter( const unicode::UTF32Character codepoint )
	{
		return uppercaseCharacter(codepoint, omn::unicode::classOf(codepoint));
	}
	
	unicode::UTF32Character titlecaseCharacter( const unicode::UTF32Character codepoint,
												const characterClass classOf );
													 
	inline unicode::UTF32Character titlecaseCharacter( const unicode::UTF32Character codepoint )
	{
		return titlecaseCharacter(codepoint, omn::unicode::classOf(codepoint));
	}
		
	unicode::UTF32Character undiacriticizedCharacter( const unicode::UTF32Character codepoint,
													  const characterClass classOf );
	
	inline unicode::UTF32Character undiacriticizedCharacter( const unicode::UTF32Character codepoint )
	{
		return undiacriticizedCharacter(codepoint, omn::unicode::classOf(codepoint));
	}
	
	unicode::UTF32String casefold( const unicode::UTF32String & string );
	
	unicode::UTF32String lowercase( const unicode::UTF32String & string,
									const bool mayContainGreekLetters = true  );
	
	unicode::UTF32String uppercase( const unicode::UTF32String & string );
	
	unicode::UTF32String titlecase( const unicode::UTF32String & string );
	
	unicode::UTF32String altercase( const unicode::UTF32String & string, 
								    const bool startWithUppercase = false );
	
	unicode::UTF32String undiacriticized( const unicode::UTF32String & string );
}

#endif // _OMN_CHARACTERTRANSFORMATIONS_INCLUDED
