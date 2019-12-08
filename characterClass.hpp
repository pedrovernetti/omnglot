
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
#ifndef _OMN_CHARACTERCLASS_INCLUDED
#define _OMN_CHARACTERCLASS_INCLUDED

#include "globalUtilities.hpp"

namespace omn
{
    enum characterClass : uint32_t
    {
		Unassigned				= 0b00000000000000000000,
		Control					= 0b00000000000000000001,
		  HorizontalTab		    = 0b00000000000000001101,
		  ControlAndNewline		= 0b00000000000000010101,
		  ControlAndFormat		= 0b00000000000000000011,
		Format					= 0b00000000000000000010,
		Whitespace				= 0b00000000000000000100,
		  HorizontalSpace		= 0b00000000000000001100,
		  Newline				= 0b00000000000000010100,	
		Punctuation				= 0b00000000000000100000, // Po~ | Pc | Pd | Pe | Pf | Pi | Ps
		PartOfWord				= 0b10000000000000000000,
		  PartOfWordPunctuation = 0b10000000000000100000,
		  Number				= 0b10000000000001000000, // No | Nd | Nl
		    Digit				= 0b10000000000011000000,
		    LetterNumber		= 0b10000000000101000000, // Nl
			  LowercaseNumber	= 0b10000000001101000000, // Nl~
			  UppercaseNumber	= 0b10000000110101000000, // Nl~
		  Letter				= 0b10000000000100000000, // Lo | Ll | Lt | Lu | Nl
			LowercaseLetter		= 0b10000000001100000000, // Ll
			TitlecaseLetter		= 0b10000000010100000000, // Lt
			  UppercaseLetter 	= 0b10000000110100000000, // Lu
		  Modifier				= 0b10000001000000000000, // Mc | Me | Mn | Lm | Sk
		    NonSpacingModifier	= 0b10000011000000000000, // Me | Mn 
		    SpacingModifier		= 0b10000101000000000000, // Mc | Lm | Sk~
			  ModifierLetter  	= 0b10000101000100000000, // Lm
		Symbol					= 0b00001000000000000000, // So | Sc | Sm | Po~ | Sk~
		  MathSymbol			= 0b00011000000000000000, // Sm
		  LetterAsSymbol		= 0b00001000000100000000, // Lo~ | Ll~ | Lu~ | So~
			LowercaseSymbol 	= 0b00001000001100000000, // Lo~ | Ll~ | So~
			UppercaseSymbol 	= 0b00001000110100000000, // Lo~ | Lu~ | So~
		Private					= 0b00100000000000000000,
		Surrogate				= 0b01000000000000000000
    };

    namespace unicode
    {
        characterClass classOf( const UTF32Character codepoint );
        
		UTF8String nameOfTheClassOf( const UTF32Character codepoint );
        
        constexpr bool isControlCharacter( const UTF32Character codepoint )
        {
			return ((codepoint < 32) || ((codepoint > 126) && (codepoint < 160)));
		}
        
        bool isNonGraphicControlCharacter( const UTF32Character codepoint );
        
        inline bool isFormatCharacter( const UTF32Character codepoint )
        {
            return (classOf(codepoint) & characterClass::Format);
		}
        
        inline bool isWhitespace( const UTF32Character codepoint )
        {
            return (classOf(codepoint) & characterClass::Whitespace);
		}
        
        inline bool isHorizontalWhitespace( const UTF32Character codepoint )
        {
            return (classOf(codepoint) & 0b00000000000000001000);
		}
        
        inline bool isPartOfWord( const UTF32Character codepoint )
        {
            return (classOf(codepoint) & 0b10000000000000000000);
        }
        
        inline bool isLineBreak( const UTF32Character codepoint )
        {
            return (classOf(codepoint) & 0b00000000000000010000);
		}
        
		bool isDigit( const UTF32Character codepoint );
		
		constexpr bool isHexadecimalDigit( const UTF32Character codepoint )
		{
			return (((codepoint >= 48) && (codepoint <= 57)) ||
					((codepoint >= 65) && (codepoint <= 70)) ||
					((codepoint >= 97) && (codepoint <= 102)));
		}
		
        inline bool isTitlecase( const UTF32Character codepoint )
        {
            return (classOf(codepoint) & 0b00000000010000000000);
        }
        
        inline bool isUppercase( const UTF32Character codepoint )
        {
            return (classOf(codepoint) & 0b00000000100000000000);
        }
        
		inline bool isLowercase( const UTF32Character codepoint )
        {
            return (classOf(codepoint) & 0b00000000001000000000);
        }
        
        inline bool isLetter( const UTF32Character codepoint )
        {
            return (classOf(codepoint) & 0b00000000000100000000);
        }
        
        inline bool isPunctuation( const UTF32Character codepoint )
        {
            return (classOf(codepoint) & characterClass::Punctuation);
		}
        
        inline bool isNonSpacingModifier( const UTF32Character codepoint )
        {
            return (classOf(codepoint) & 0b00000010000000000000);
        }
        
        inline bool isSymbol( const UTF32Character codepoint )
        {
            return (classOf(codepoint) & characterClass::Symbol);
		}
        
        inline bool isGraphicCharacter( const UTF32Character codepoint )
        {
            return (classOf(codepoint) & 0b10011111111111111100);
        }
        
        constexpr bool isSurrogate( const UTF32Character codepoint )
        {
            return ((codepoint >= 983040) && (codepoint <= 1048573));
        }
        
        constexpr bool isControlPicture( const UTF32Character codepoint )
        {
            if ((codepoint >= 9216) && (codepoint <= 9254)) return true; 
            return false;
        }
        
        constexpr bool isTagCharacter( const UTF32Character codepoint )
        {
            return ((codepoint >= 917536) && (codepoint <= 917630));
        }
        
        inline bool isUnassigned( const UTF32Character codepoint )
        {
            return (!classOf(codepoint));
        }
        
        constexpr bool isPrivateCharacter( const UTF32Character codepoint )
        {
            return (((codepoint >= 983040) && (codepoint <= 1048573)) ||
                    ((codepoint >= 57344) && (codepoint <= 63743)));
        }
        
        constexpr bool isNonCharacter( const UTF32Character codepoint )
        {
			return (((codepoint & 65535) > 65533) || ((codepoint >= 64976) && (codepoint <= 65007)));
		}
    }
}

namespace std
{
	ostream & operator << ( ostream & os, const omn::characterClass classOf );
}

#endif // _OMN_CHARACTERCLASS_INCLUDED
