
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

#include "characterClass.hpp"

namespace // internal parts
{
    enum internalCharacterClass : byte
    {
        // Class    // External Class
        XXX    = 0,    // Unassigned
        CTR,          // Control
        TAB,        //   HorizontalTab
        CNL,          //   ControlAndNewline
        CFM,        //   ControlAndFormat
        FMT,          // Format
        SPC,          // Whitespace
        HSP,          //   HorizontalSpace
        NWL,        //   Newline
        PUN,          // Punctuation
        POW,        // PartOfWord
        PWP,        //   PartOfWordPunctuation
        NUM,          //   Number
        DIG,         //     Digit
        LTN,        //     LetterNumber
        LON,        //       LowercaseNumber
        UPN,        //       UppercaseNumber
        LTR,         //   Letter
        LOW,         //     LowercaseLetter
        TIT,         //     TitlecaseLetter
        UPP,         //       UppercaseLetter
        MOD,         //   Modifier
        NMO,         //     NonSpacingModifier
        SMO,         //     SpacingModifier
        LMO,        //       ModifierLetter
        SYM,         // Symbol
        MAT,         //   MathSymbol
        SYL,        //   LetterAsSymbol
        SYW,        //     LowercaseSymbol
        SYU,        //     UppercaseSymbol
        PRI,         // Private
        SUR,         // Surrogate
        BOM         // ByteOrderMark
    };

    const omn::characterClass externalClassTable[33] =
    {
        omn::characterClass::Unassigned,          omn::characterClass::Control,
        omn::characterClass::HorizontalTab,         omn::characterClass::ControlAndNewline,
        omn::characterClass::ControlAndFormat,     omn::characterClass::Format,
        omn::characterClass::Whitespace,         omn::characterClass::HorizontalSpace,
        omn::characterClass::Newline,             omn::characterClass::Punctuation,
        omn::characterClass::PartOfWord,         omn::characterClass::PartOfWordPunctuation,
        omn::characterClass::Number,             omn::characterClass::Digit,
        omn::characterClass::LetterNumber,          omn::characterClass::LowercaseNumber,
        omn::characterClass::UppercaseNumber,     omn::characterClass::Letter,
        omn::characterClass::LowercaseLetter,     omn::characterClass::TitlecaseLetter,
        omn::characterClass::UppercaseLetter,     omn::characterClass::Modifier,
        omn::characterClass::NonSpacingModifier, omn::characterClass::SpacingModifier,
        omn::characterClass::ModifierLetter,     omn::characterClass::Symbol,
        omn::characterClass::MathSymbol,         omn::characterClass::LetterAsSymbol,
        omn::characterClass::LowercaseSymbol,     omn::characterClass::UppercaseSymbol,
        omn::characterClass::Private,             omn::characterClass::Surrogate,
        omn::characterClass::ControlAndFormat
    };

    constexpr const omn::unicode::UTF8Character * characterClassNamesTable[32] =
    {
        u8"unassigned", u8"control code", u8"control / horizontal space", u8"control / newline",
        u8"control / format", u8"format", u8"whitespace", u8"horizontal space", u8"newline",
        u8"punctuation", u8"part-of-word", u8"punctuation / part-of-word", u8"number", u8"digit",
        u8"letter-number", u8"lowercase letter-number", u8"uppercase letter-number", u8"letter",
        u8"lowercase letter", u8"titlecase letter", u8"uppercase letter", u8"modifier",
        u8"non-spacing modifier", u8"spacing modifier", u8"modifier-letter", u8"symbol",
        u8"mathematical symbol", u8"letter as a symbol", u8"lowercase letter as a symbol",
        u8"uppercase letter as a symbol", u8"private", u8"surrogate"
    };

    const internalCharacterClass plane0CharacterClass[65536] = // TODO: modifiers, latest 2 unicode changelogs
    {
        // Macro to fill 1 line (16 entries) (_0 to _F) with the same value
        #define x16(C) C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C
        // Macro to fill 4 lines (64 entries) with the same value
        #define x64(C) x16(C), x16(C), x16(C), x16(C)
        // Macro to fill 32 lines (512 entries) with the same value
        #define x512(C) x64(C), x64(C), x64(C), x64(C), x64(C), x64(C), x64(C), x64(C)

        // Basic Latin (ASCII)
        CTR, CTR, CTR, CTR, CTR, CTR, CTR, CTR, CTR, TAB, CNL, CNL, CNL, CNL, CTR, CTR,
        CTR, CTR, CTR, CTR, CTR, CTR, CTR, CTR, CTR, CTR, CTR, CTR, CTR, CTR, CTR, CTR,
        HSP, PUN, PUN, SYM, SYM, MAT, SYM, PUN, PUN, PUN, PUN, MAT, PUN, PUN, PUN, PUN,
        DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, PUN, PUN, MAT, MAT, MAT, PUN,
        SYM, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP,
        UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, PUN, SYM, PUN, SYM, SYM,
        SYM, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, PUN, MAT, PUN, MAT, CTR,
        // Latin-1 Supplement
        CTR, CTR, CFM, CFM, CTR, CNL, CTR, CTR, CFM, CFM, CFM, CFM, CFM, CTR, CTR, CTR,
        CTR, CTR, CTR, CTR, CTR, CTR, CTR, CTR, CTR, CTR, CTR, CTR, CTR, CTR, CTR, CTR,
        HSP, PUN, SYM, SYM, SYM, SYM, SYM, PUN, SYM, SYM, SYL, PUN, MAT, FMT, SYM, SYM,
        SYM, MAT, NUM, NUM, SYM, SYW, PUN, PUN, SYM, NUM, SYL, PUN, NUM, NUM, NUM, PUN,
        UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP,
        UPP, UPP, UPP, UPP, UPP, UPP, UPP, MAT, UPP, UPP, UPP, UPP, UPP, UPP, UPP, LOW,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, MAT, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
        // Latin Extended-A
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP,
        LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, UPP, LOW, UPP, LOW, UPP, LOW, LOW,
        // Latin Extended-B
        LOW, UPP, UPP, LOW, UPP, LOW, UPP, UPP, LOW, UPP, UPP, UPP, LOW, LOW, UPP, LOW,
        UPP, UPP, LOW, UPP, UPP, LOW, UPP, UPP, UPP, LOW, LOW, LOW, UPP, UPP, LOW, UPP,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, UPP, LOW, UPP, LOW, LOW, UPP, LOW, UPP, UPP,
        LOW, UPP, UPP, UPP, LOW, UPP, LOW, UPP, UPP, LOW, LOW, LOW, UPP, LOW, LOW, LOW,
        LOW, LOW, LOW, LOW, UPP, TIT, LOW, UPP, TIT, LOW, UPP, TIT, LOW, UPP, LOW, UPP,
        LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        LOW, UPP, TIT, LOW, UPP, LOW, UPP, UPP, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, LOW, LOW, LOW, LOW, LOW, LOW, UPP, UPP, LOW, UPP, UPP, LOW,
        UPP, UPP, LOW, UPP, UPP, UPP, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        // IPA Extensions
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
        // Spacing Modifier Letters
        LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO,
        LMO, LMO, SMO, SMO, SMO, SMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO,
        LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, SYM, SYM, SYM, SYM, SYM, SYM, LMO, LMO,
        LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO,
        LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO,
        // Combining Diacritical Marks
        NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO,
        NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO,
        NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO,
        NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO,
        NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO,
        NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO,
        NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO,
        // Greek and Coptic
        UPP, LOW, UPP, LOW, SMO, SMO, UPP, LOW, XXX, XXX, LMO, LOW, LOW, LOW, PUN, UPP,
        XXX, XXX, XXX, XXX, SYM, SYM, UPP, PUN, UPP, UPP, UPP, XXX, UPP, XXX, UPP, UPP,
        LOW, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP,
        UPP, UPP, XXX, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, LOW, LOW, LOW, LOW,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, UPP,
        LOW, LOW, UPP, UPP, UPP, LOW, LOW, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        LOW, LOW, LOW, LOW, UPP, LOW, LOW, UPP, LOW, UPP, UPP, LOW, SYW, UPP, UPP, UPP,
        // Cyrillic
        UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP,
        UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP,
        UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, SYM, NMO, NMO, NMO, NMO, NMO, NMO, NMO, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        // Cyrillic Supplement
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        // Armenian
        XXX, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP,
        UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP,
        UPP, UPP, UPP, UPP, UPP, UPP, UPP, XXX, XXX, LMO, PUN, PUN, PUN, PUN, PUN, PUN,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, PUN, PUN, XXX, XXX, SYM, SYM, SYM,
        // Hebrew
        XXX, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO,
        NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO,
        NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, PUN, NMO,
        PUN, NMO, NMO, PUN, NMO, NMO, PUN, NMO, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, LTR,
        LTR, LTR, LTR, PUN, PUN, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Arabic
        FMT, FMT, FMT, FMT, FMT, FMT, MAT, MAT, MAT, MAT, MAT, SYM, PUN, PUN, SYM, SYM,
        NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, PUN, FMT, XXX, PUN, PUN,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, NMO, NMO, NMO, NMO, NMO,
        NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO,
        DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, MAT, PUN, PUN, PUN, LTR, LTR,
        NMO, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, PUN, LTR, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, SYM, NMO,
        NMO, NMO, NMO, NMO, NMO, LMO, LMO, NMO, NMO, SYM, NMO, NMO, NMO, NMO, LTR, LTR,
        DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, LTR, LTR, LTR, SYM, SYM, LTR,
        // Syriac
        PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, XXX, FMT,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO,
        NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, XXX, XXX, LTR, LTR, LTR,
        // Arabic Supplement
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        // Thaana
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO,
        NMO, NMO, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // NKo
        DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, NMO, NMO, NMO, NMO, NMO,
        NMO, NMO, NMO, NMO, LMO, LMO, SYM, SYM, PUN, PUN, LMO, XXX, XXX, NMO, SYM, SYM,
        // Samaritan
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, NMO, NMO, NMO, NMO, LMO, NMO, NMO, NMO, NMO, NMO,
        NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, XXX, XXX,
        PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, XXX,
        // Mandaic
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, NMO, NMO, NMO, XXX, XXX, PUN, XXX,
        // Syriac Supplement
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX,
        // Unallocated Range
        x16(XXX), x16(XXX), x16(XXX),
        // Arabic Extended-A
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO,
        NMO, NMO, FMT, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO,
        NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO,
        // Devanagari
        NMO, NMO, NMO, SMO, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, NMO, SMO, NMO, LTR, SMO, SMO,
        SMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, SMO, SMO, SMO, SMO, NMO, SMO, SMO,
        LTR, NMO, NMO, NMO, NMO, NMO, NMO, NMO, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, NMO, NMO, PUN, PUN, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG,
        PUN, LMO, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        // Bengali
        LTR, NMO, NMO, NMO, XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, LTR,
        LTR, XXX, XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, XXX, LTR, XXX, XXX, XXX, LTR, LTR, LTR, LTR, XXX, XXX, NMO, LTR, SMO, SMO,
        SMO, NMO, NMO, NMO, NMO, XXX, XXX, SMO, SMO, XXX, XXX, SMO, SMO, NMO, LTR, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, SMO, XXX, XXX, XXX, XXX, LTR, LTR, XXX, LTR,
        LTR, LTR, NMO, NMO, XXX, XXX, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG,
        LTR, LTR, SYM, SYM, NUM, NUM, NUM, NUM, NUM, NUM, SYM, SYM, LTR, PUN, NMO, XXX,
        // Gurmukhi
        XXX, NMO, NMO, SMO, XXX, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, LTR,
        LTR, XXX, XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, XXX, LTR, LTR, XXX, LTR, LTR, XXX, LTR, LTR, XXX, XXX, NMO, XXX, SMO, SMO,
        SMO, NMO, NMO, XXX, XXX, XXX, XXX, NMO, NMO, XXX, XXX, NMO, NMO, NMO, XXX, XXX,
        XXX, NMO, XXX, XXX, XXX, XXX, XXX, XXX, XXX, LTR, LTR, LTR, LTR, XXX, LTR, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG,
        NMO, NMO, LTR, LTR, LTR, NMO, PUN, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Gujarati
        XXX, NMO, NMO, SMO, XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, LTR,
        LTR, LTR, XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, XXX, LTR, LTR, XXX, LTR, LTR, LTR, LTR, LTR, XXX, XXX, NMO, LTR, SMO, SMO,
        SMO, NMO, NMO, NMO, NMO, NMO, XXX, NMO, NMO, SMO, NMO, SMO, SMO, NMO, XXX, XXX,
        LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        LTR, LTR, NMO, NMO, XXX, XXX, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG,
        PUN, SYM, XXX, XXX, XXX, XXX, XXX, XXX, XXX, LTR, NMO, NMO, NMO, NMO, NMO, NMO,
        // Oriya
        XXX, NMO, SMO, SMO, XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, LTR,
        LTR, XXX, XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, XXX, LTR, LTR, XXX, LTR, LTR, LTR, LTR, LTR, XXX, XXX, NMO, LTR, SMO, NMO,
        SMO, NMO, NMO, NMO, NMO, XXX, XXX, SMO, SMO, XXX, XXX, SMO, SMO, NMO, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, NMO, SMO, XXX, XXX, XXX, XXX, LTR, LTR, XXX, LTR,
        LTR, LTR, NMO, NMO, XXX, XXX, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG,
        SYM, LTR, NUM, NUM, NUM, NUM, NUM, NUM, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Tamil
        XXX, XXX, NMO, LTR, XXX, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, LTR, LTR,
        LTR, XXX, LTR, LTR, LTR, LTR, XXX, XXX, XXX, LTR, LTR, XXX, LTR, XXX, LTR, LTR,
        XXX, XXX, XXX, LTR, LTR, XXX, XXX, XXX, LTR, LTR, LTR, XXX, XXX, XXX, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, SMO, SMO,
        SMO, SMO, SMO, XXX, XXX, XXX, SMO, SMO, SMO, XXX, SMO, SMO, SMO, NMO, XXX, XXX,
        LTR, XXX, XXX, XXX, XXX, XXX, XXX, SMO, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG,
        NUM, NUM, NUM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, XXX, XXX, XXX, XXX, XXX,
        // Telugu
        NMO, SMO, SMO, SMO, NMO, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, LTR, LTR,
        LTR, XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, LTR, SMO, SMO,
        NMO, SMO, SMO, SMO, SMO, XXX, NMO, NMO, NMO, XXX, SMO, SMO, SMO, SMO, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, SMO, NMO, XXX, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX,
        LTR, LTR, NMO, NMO, XXX, XXX, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, PUN, NUM, NUM, NUM, NUM, NUM, NUM, NUM, SYM,
        // Kannada
        SMO, NMO, SMO, SMO, PUN, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, LTR, LTR,
        LTR, XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, XXX, LTR, LTR, LTR, LTR, LTR, XXX, XXX, NMO, LTR, SMO, SMO,
        SMO, SMO, SMO, SMO, SMO, XXX, SMO, SMO, SMO, XXX, SMO, SMO, SMO, SMO, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, SMO, SMO, XXX, XXX, XXX, XXX, XXX, XXX, XXX, LTR, XXX,
        LTR, LTR, NMO, NMO, XXX, XXX, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG,
        XXX, LTR, LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Malayalam
        NMO, NMO, SMO, SMO, XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, LTR, LTR,
        LTR, XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, NMO, NMO, LTR, SMO, SMO,
        SMO, SMO, SMO, SMO, SMO, XXX, SMO, SMO, SMO, XXX, SMO, SMO, SMO, NMO, NMO, SYM,
        XXX, XXX, XXX, XXX, LTR, LTR, LTR, SMO, NUM, NUM, NUM, NUM, NUM, NUM, NUM, LTR,
        LTR, LTR, NMO, NMO, XXX, XXX, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG,
        NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, SYM, LTR, LTR, LTR, LTR, LTR, LTR,
        // Sinhala
        XXX, XXX, SMO, SMO, XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, LTR, XXX, XXX,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, NMO, XXX, XXX, XXX, XXX, SMO,
        SMO, SMO, NMO, NMO, NMO, XXX, NMO, XXX, SMO, SMO, SMO, SMO, SMO, SMO, SMO, SMO,
        XXX, XXX, XXX, XXX, XXX, XXX, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG,
        XXX, XXX, SMO, SMO, PUN, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Thai
        XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, NMO, LTR, LTR, NMO, NMO, NMO, NMO, NMO, NMO, NMO, XXX, XXX, XXX, XXX, SYM,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, PUN,
        DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, PUN, PUN, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Lao
        XXX, LTR, LTR, XXX, LTR, XXX, LTR, LTR, LTR, LTR, LTR, XXX, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, XXX, LTR, XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, NMO, LTR, LTR, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, LTR, XXX, XXX,
        LTR, LTR, LTR, LTR, LTR, XXX, LTR, XXX, NMO, NMO, NMO, NMO, NMO, NMO, XXX, XXX,
        DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, XXX, XXX, LTR, LTR, LTR, LTR,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Tibetan
        LTR, SYM, SYM, SYM, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN,
        PUN, PUN, PUN, SYM, PUN, SYM, SYM, SYM, NMO, NMO, SYM, SYM, SYM, SYM, SYM, SYM,
        DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, NUM, NUM, NUM, NUM, NUM, NUM,
        NUM, NUM, NUM, NUM, SYM, NMO, SYM, NMO, SYM, NMO, PUN, PUN, PUN, PUN, SMO, SMO,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX,
        XXX, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, SMO,
        NMO, NMO, NMO, NMO, NMO, PUN, NMO, NMO, LTR, LTR, LTR, LTR, LTR, NMO, NMO, NMO,
        NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, XXX, NMO, NMO, NMO, NMO, NMO, NMO, NMO,
        NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO,
        NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, XXX, SYM, SYM,
        SYM, SYM, SYM, SYM, SYM, SYM, NMO, SYM, SYM, SYM, SYM, SYM, SYM, XXX, SYM, SYM,
        PUN, PUN, PUN, PUN, PUN, SYM, SYM, SYM, SYM, PUN, PUN, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Myanmar
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, NMO, SMO, NMO, NMO, NMO,
        NMO, SMO, NMO, NMO, NMO, NMO, NMO, NMO, SMO, NMO, NMO, NMO, SMO, NMO, NMO, LTR,
        DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, PUN, PUN, PUN, PUN, PUN, PUN,
        LTR, LTR, LTR, LTR, LTR, LTR, SMO, SMO, NMO, NMO, LTR, LTR, LTR, LTR, NMO, NMO,
        NMO, LTR, SMO, SMO, SMO, LTR, LTR, SMO, SMO, SMO, SMO, SMO, SMO, SMO, LTR, LTR,
        LTR, NMO, NMO, NMO, NMO, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, NMO, SMO, SMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, LTR, SMO,
        DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, SMO, SMO, SMO, NMO, SYM, SYM,
        // Georgian
        UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP,
        UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP,
        UPP, UPP, UPP, UPP, UPP, UPP, XXX, UPP, XXX, XXX, XXX, XXX, XXX, UPP, XXX, XXX,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, PUN, LMO, LOW, LOW, LOW,
        // Hangul Jamo
        x64(LTR), x64(LTR), x64(LTR), x64(LTR),
        // Ethiopic
        x64(LTR),
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, LTR, LTR, LTR, LTR, XXX, XXX,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, LTR, XXX, LTR, LTR, LTR, LTR, XXX, XXX,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, LTR, LTR, LTR, LTR, XXX, XXX,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, XXX, LTR, LTR, LTR, LTR, XXX, XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX,
        LTR, XXX, LTR, LTR, LTR, LTR, XXX, XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        x16(LTR), x16(LTR), x16(LTR),
        LTR, XXX, LTR, LTR, LTR, LTR, XXX, XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        x16(LTR), x16(LTR), x16(LTR),
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, NMO, NMO, NMO,
        PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, NUM, NUM, NUM, NUM, NUM, NUM, NUM,
        NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, XXX, XXX, XXX,
        // Ethiopic Supplement
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, XXX, XXX, XXX, XXX, XXX, XXX,
        // Cherokee
        x64(UPP), x16(UPP),
        UPP, UPP, UPP, UPP, UPP, UPP, XXX, XXX, LOW, LOW, LOW, LOW, LOW, LOW, XXX, XXX,
        // Unified Canadian Aboriginal Syllabics
        PUN, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        x512(LTR), x64(LTR), x16(LTR),
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, SYM, PUN, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        // Ogham
        HSP, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, PUN, PUN, XXX, XXX, XXX,
        // Runic
        x64(LTR),
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, PUN, PUN, PUN, LTN, LTN,
        LTN, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Tagalog
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, LTR, LTR,
        LTR, LTR, NMO, NMO, NMO, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Hanunoo
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, NMO, NMO, NMO, PUN, PUN, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Buhid
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, NMO, NMO, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Tagbanwa
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, LTR, LTR,
        LTR, XXX, NMO, NMO, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Khmer
        x16(LTR), x16(LTR), x16(LTR),
        LTR, LTR, LTR, LTR, NMO, NMO, SMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, SMO, SMO,
        SMO, SMO, SMO, SMO, SMO, SMO, NMO, SMO, SMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO,
        NMO, NMO, NMO, NMO, PUN, PUN, PUN, LTR, PUN, PUN, PUN, SYM, LTR, NMO, XXX, XXX,
        DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, XXX, XXX, XXX, XXX, XXX, XXX,
        NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, XXX, XXX, XXX, XXX, XXX, XXX,
        // Mongolian
        PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, NMO, NMO, NMO, NMO, XXX,
        DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, XXX, XXX, XXX, XXX, XXX, XXX,
        x64(LTR),
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        LTR, LTR, LTR, LTR, LTR, NMO, NMO, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, NMO, LTR, XXX, XXX, XXX, XXX, XXX,
        // Unified Canadian Aboriginal Syllabics Extended
        x64(LTR),
        LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Limbu
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX,
        NMO, NMO, NMO, SMO, SMO, SMO, SMO, NMO, NMO, SMO, NMO, SMO, XXX, XXX, XXX, XXX,
        SMO, SMO, NMO, NMO, SMO, SMO, SMO, NMO, SMO, NMO, NMO, NMO, XXX, XXX, XXX, XXX,
        SYM, XXX, XXX, XXX, PUN, PUN, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG,
        // Tai Le
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX,
        LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // New Tai Lue
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX, XXX,
        DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, NUM, SYM, SYM, XXX, XXX, XXX,
        // Khmer Symbols
        x16(SYM), x16(SYM),
        // Buginese
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, NMO, NMO, SMO, SMO, NMO, XXX, XXX, PUN, PUN,
        // Tai Tham
        x16(SYM), x16(SYM), x16(SYM),
        LTR, LTR, LTR, LTR, LTR, SMO, NMO, SMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, XXX,
        NMO, SMO, NMO, SMO, SMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, SMO, SMO, SMO,
        SMO, SMO, SMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, XXX, XXX, NMO,
        DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, XXX, XXX, XXX, XXX, XXX, XXX,
        DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, XXX, XXX, XXX, XXX, XXX, XXX,
        SYM, SYM, SYM, PUN, PUN, PUN, PUN, LTR, PUN, PUN, PUN, PUN, PUN, PUN, XXX, XXX,
        // Combining Diacritical Marks Extended
        NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, XXX,
        x64(XXX),
        // Balinese
        NMO, NMO, NMO, NMO, SMO, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, NMO, SMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, SMO, SMO,
        SMO, SMO, NMO, SMO, SMO, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX,
        DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, PUN, PUN, PUN, PUN, PUN, PUN,
        PUN, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, NMO, NMO, NMO, NMO, NMO,
        NMO, NMO, NMO, NMO, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, XXX, XXX, XXX,
        // Sundanese
        NMO, NMO, SMO, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, NMO, NMO, NMO, NMO, NMO, SMO, SMO, NMO, NMO, SMO, NMO, NMO, NMO, LTR, LTR,
        DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, LTR, LTR, LTR, LTR, LTR, LTR,
        // Batak
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, NMO, SMO, NMO, SMO, SMO, SMO, SMO, NMO, NMO, NMO,
        NMO, NMO, SMO, SMO, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, PUN, PUN, PUN, PUN,
        // Lepcha
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, SMO, SMO, SMO, SMO, SMO, SMO, SMO, SMO, NMO, NMO, NMO, NMO,
        NMO, NMO, NMO, NMO, SMO, SMO, NMO, NMO, XXX, XXX, XXX, PUN, PUN, PUN, PUN, PUN,
        DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, XXX, XXX, XXX, LTR, LTR, LTR,
        // Ol Chiki
        DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LMO, LMO, LMO, LMO, LMO, LTR, PUN, PUN,
        // Cyrillic Extended-C
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Georgian Extended
        x16(UPP), x16(UPP),
        UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, XXX, XXX, UPP, UPP, UPP,
        // Sundanese Supplement
        PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Vedic Extensions
        NMO, NMO, NMO, PUN, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO,
        NMO, SMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, LTR, LTR, LTR, LTR, NMO, LTR, LTR,
        LTR, LTR, LTR, LTR, NMO, LTR, LTR, SMO, NMO, NMO, LTR, XXX, XXX, XXX, XXX, XXX,
        // Phonetic Extensions
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LMO, LMO, LMO, LMO,
        x16(LMO), x16(LMO), x16(LMO),
        LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LOW, LOW, LOW, LOW, LOW,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LMO, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
        // Phonetic Extensions Supplement
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LMO, LMO, LMO, LMO, LMO,
        LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO,
        LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO, LMO,
        // Combining Diacritical Marks Supplement
        x16(NMO), x16(NMO), x16(NMO),
        NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, XXX, NMO, NMO, NMO, NMO, NMO,
        // Latin Extended Additional
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        // Greek Extended
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP,
        LOW, LOW, LOW, LOW, LOW, LOW, XXX, XXX, UPP, UPP, UPP, UPP, UPP, UPP, XXX, XXX,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP,
        LOW, LOW, LOW, LOW, LOW, LOW, XXX, XXX, UPP, UPP, UPP, UPP, UPP, UPP, XXX, XXX,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, XXX, UPP, XXX, UPP, XXX, UPP, XXX, UPP,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, XXX, XXX,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP,
        LOW, LOW, LOW, LOW, LOW, XXX, LOW, LOW, UPP, UPP, UPP, UPP, UPP, SYM, SYM, SYM,
        SYM, SYM, LOW, LOW, LOW, XXX, LOW, LOW, UPP, UPP, UPP, UPP, UPP, SYM, SYM, SYM,
        LOW, LOW, LOW, LOW, XXX, XXX, LOW, LOW, UPP, UPP, UPP, UPP, XXX, SYM, SYM, SYM,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP,
        XXX, XXX, LOW, LOW, LOW, XXX, LOW, LOW, UPP, UPP, UPP, UPP, UPP, SYM, SYM, XXX,
        // General Punctuation
        HSP, HSP, HSP, HSP, HSP, HSP, HSP, HSP, HSP, HSP, HSP, FMT, FMT, FMT, FMT, FMT,
        PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN,
        PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, NWL, NWL, FMT, FMT, FMT, FMT, FMT, HSP,
        MAT, MAT, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, SYM, PUN,
        PUN, SYM, PUN, PUN, MAT, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN,
        PUN, PUN, MAT, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, HSP,
        FMT, FMT, FMT, FMT, FMT, FMT, FMT, FMT, FMT, FMT, FMT, FMT, FMT, FMT, FMT, FMT,
        // Superscript and Subscript
        DIG, SYW, XXX, XXX, DIG, DIG, DIG, DIG, DIG, DIG, MAT, MAT, MAT, PUN, PUN, SYW,
        DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, MAT, MAT, MAT, PUN, PUN, XXX,
        SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW, XXX, XXX, XXX, XXX,
        // Currency Symbols
        x16(SYM), x16(SYM), x16(XXX),
        // Combining Diacritical Marks for Symbols
        x16(NMO), x16(NMO),
        NMO, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Letterlike Symbols
        SYL, SYL, SYU, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYW, SYU, SYW, SYU, SYW, SYW,
        SYW, SYU, SYU, SYW, SYL, SYU, SYL, SYL, SYW, SYU, SYU, SYU, SYU, SYU, SYL, SYU,
        SYL, SYL, SYL, SYU, SYU, SYL, SYU, SYU, SYL, SYW, SYU, SYU, SYU, SYU, SYW, SYW,
        SYU, SYU, SYU, SYU, SYW, SYL, SYL, SYL, SYL, SYW, SYU, SYL, SYW, SYW, SYU, SYU,
        SYU, SYU, SYU, SYU, SYU, SYU, SYW, SYW, SYW, SYW, SYL, SYM, SYL, SYL, SYL, SYM,
        // Number Forms
        NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM,
        UPN, UPN, UPN, UPN, UPN, UPN, UPN, UPN, UPN, UPN, UPN, UPN, UPN, UPN, UPN, UPN,
        LON, LON, LON, LON, LON, LON, LON, LON, LON, LON, LON, LON, LON, LON, LON, LON,
        LTN, LTN, LTN, UPN, LON, LTN, LTN, LTN, LTN, NUM, DIG, DIG, XXX, XXX, XXX, XXX,
        // Arrows
        MAT, MAT, MAT, MAT, MAT, SYM, SYM, SYM, SYM, SYM, MAT, MAT, SYM, SYM, SYM, SYM,
        MAT, SYM, SYM, MAT, SYM, SYM, MAT, SYM, SYM, SYM, SYM, SYM, SYM, SYM, MAT, SYM,
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM,
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, MAT, MAT,
        SYM, SYM, MAT, SYM, MAT, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM,
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM,
        SYM, SYM, SYM, SYM, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT,
        // Mathematical Operators
        x64(MAT), x64(MAT), x64(MAT), x64(MAT),
        // Miscellaneous Technical
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, MAT, MAT, MAT, MAT, SYM, SYM, SYM, SYM,
        MAT, SYM, MAT, MAT, MAT, SYM, SYM, SYM, SYM, MAT, SYM, SYM, SYM, SYM, SYM, SYM,
        MAT, MAT, SYM, SYM, SYM, SYM, SYM, SYM, SYM, PUN, PUN, SYM, SYM, SYM, SYM, SYM,
        x64(SYM),
        SYM, SYM, SYM, SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYM, MAT, SYM, SYM, SYM,
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM,
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, MAT, MAT, MAT, MAT, MAT,
        MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT,
        MAT, MAT, MAT, MAT, SYM, SYM, SYM, MAT, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM,
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM,
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, MAT, MAT, MAT, MAT,
        MAT, MAT, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM,
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM,
        // Control Pictures
        x16(SYM), x16(SYM),
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Optical Character Recognition
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Enclosed Alphanumerics
        x16(NUM), x16(NUM), x16(NUM),
        NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, SYW, SYW, SYW, SYW,
        SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW,
        SYW, SYW, SYW, SYW, SYW, SYW, SYU, SYU, SYU, SYU, SYU, SYU, SYU, SYU, SYU, SYU,
        SYU, SYU, SYU, SYU, SYU, SYU, SYU, SYU, SYU, SYU, SYU, SYU, SYU, SYU, SYU, SYU,
        SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW,
        SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW, NUM, NUM, NUM, NUM, NUM, NUM,
        NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM,
        // Box Drawing
        x64(SYM), x64(SYM),
        // Block Elements
        x16(SYM), x16(SYM),
        // Geometric Shapes
        x64(SYM), x16(SYM), x16(SYM),
        // Miscellaneous Symbols
        x64(SYM), x16(SYM), x16(SYM),
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, MAT,
        x16(SYM), x64(SYM), x64(SYM),
        // Dingbats
        x64(SYM), x16(SYM),
        SYM, SYM, SYM, PUN, PUN, PUN, SYM, PUN, SYM, SYM, SYM, PUN, PUN, PUN, PUN, PUN,
        PUN, PUN, PUN, PUN, SYM, SYM, SYM, SYM, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN,
        PUN, PUN, PUN, PUN, PUN, PUN, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM,
        NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM,
        NUM, NUM, NUM, NUM, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, SYM,
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM,
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM,
        // Miscellaneous Mathematical Symbols-A
        MAT, MAT, MAT, MAT, MAT, PUN, PUN, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT,
        MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT,
        MAT, MAT, MAT, MAT, MAT, MAT, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN,
        // Supplemental Arrows-A
        MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT,
        // Braille Patterns
        HSP, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM,
        x16(SYM), x16(SYM), x16(SYM), x64(SYM), x64(SYM), x64(SYM),
        // Supplemental Arrows-B
        x64(MAT), x64(MAT),
        // Miscellaneous Mathematical Symbols-B
        x64(MAT), x64(MAT),
        // Supplemental Mathematical Operators
        x64(MAT), x64(MAT), x64(MAT), x64(MAT),
        // Miscellaneous Symbols and Arrows
        x16(SYM), x16(SYM), x16(SYM),
        MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT, MAT,
        MAT, MAT, MAT, MAT, MAT, SYM, SYM, MAT, MAT, MAT, MAT, MAT, MAT, SYM, SYM, SYM,
        x16(SYM), x16(SYM),
        SYM, SYM, SYM, SYM, XXX, XXX, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM,
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM,
        SYM, SYM, SYM, SYM, SYM, SYM, XXX, XXX, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM,
        x64(SYM), x16(SYM), x16(SYM),
        // Glagolitic
        x16(UPP), x16(UPP),
        UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, XXX,
        x16(LOW), x16(LOW),
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, XXX,
        // Latin Extended-C
        UPP, LOW, UPP, UPP, UPP, LOW, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, UPP, UPP,
        UPP, LOW, UPP, LOW, LOW, UPP, LOW, LOW, LOW, LOW, LOW, LOW, LMO, LMO, UPP, UPP,
        // Coptic
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, LOW, SYM, SYM, SYM, SYM, SYM, SYM, UPP, LOW, UPP, LOW, NMO,
        NMO, NMO, UPP, LOW, XXX, XXX, XXX, XXX, XXX, PUN, PUN, PUN, PUN, NUM, PUN, PUN,
        // Georgian Supplement
        x16(LOW), x16(LOW),
        LOW, LOW, LOW, LOW, LOW, LOW, XXX, LOW, XXX, XXX, XXX, XXX, XXX, LOW, XXX, XXX,
        // Tifinagh
        x16(LTR), x16(LTR), x16(LTR),
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX, LMO,
        PUN, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, NMO,
        // Ethiopic Extended
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX,
        // Cyrillic Extended-A
        x16(NMO), x16(NMO),
        // Supplemental Punctuation
        x16(PUN), x16(PUN),
        PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, LMO,
        x16(PUN), x16(PUN), x16(XXX), x16(XXX), x16(XXX),
        // CJK Radicals Supplement
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM,
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, XXX, SYM, SYM, SYM, SYM, SYM,
        x64(SYM), x16(SYM),
        SYM, SYM, SYM, SYM, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Kangxi Radicals
        x64(SYM), x64(SYM), x64(SYM), x16(SYM),
        SYM, SYM, SYM, SYM, SYM, SYM, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Unallocated Range
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Ideographic Description Characters
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, XXX, XXX, XXX, XXX,
        // CJK Symbols and Punctuation
        HSP, PUN, PUN, PUN, SYM, LTR, LTR, LTN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN,
        PUN, PUN, SYM, SYM, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN,
        SYM, LTN, LTN, LTN, LTN, LTN, LTN, LTN, LTN, LTN, NMO, NMO, NMO, NMO, SMO, SMO,
        PUN, LMO, LMO, LMO, LMO, LMO, SYM, SYM, LTN, LTN, LTN, LTR, LTR, PUN, SYM, SYM,
        // Hiragana
        XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        x64(LTR),
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, NMO, NMO, SMO, SMO, LTR, LTR, LTR,
        // Katakana
        PUN, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        x64(LTR),
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, PUN, LTR, LTR, LTR, LTR,
        // Bopomofo
        XXX, XXX, XXX, XXX, XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        // Hangul Compatibility Jamo
        XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        x64(LTR),
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX,
        // Kanbun
        SYL, SYL, LTN, LTN, LTN, LTN, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL,
        // Bopomofo Extended
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX,
        // CJK Strokes
        x16(SYM), x16(SYM),
        SYM, SYM, SYM, SYM, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Katakana Phonetic Extensions
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        // Enclosed CJK Letters and Months
        SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL,
        SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, XXX,
        NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, SYL, SYL, SYL, SYL, SYL, SYL,
        SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL,
        SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM,
        SYL, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM,
        SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL,
        SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYM,
        NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, SYL, SYL, SYL, SYL, SYL, SYL,
        SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL,
        SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL,
        SYL, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM,
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYL, SYW, SYL, SYU,
        x16(SYL), x16(SYL), x16(SYL),
        // CJK Compatibility
        x64(SYL), x16(SYL),
        SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM,
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM,
        SYM, SYL, SYW, SYU, LOW, SYL, SYW, SYW, SYW, SYW, SYU, SYL, SYL, SYL, SYL, SYL,
        SYL, SYL, SYL, SYL, SYL, SYU, SYU, SYU, SYW, SYW, SYL, SYL, SYL, SYW, SYW, SYW,
        SYL, SYL, SYL, SYL, SYL, SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW,
        SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYW, SYL, SYL, SYL, SYL, SYW, SYM, SYM,
        SYW, SYW, SYW, SYW, SYL, SYL, SYL, SYL, SYL, SYU, SYL, SYL, SYL, SYL, SYL, SYU,
        SYL, SYL, SYW, SYL, SYW, SYW, SYL, SYL, SYL, SYL, SYW, SYU, SYW, SYU, SYU, SYL,
        MAT, MAT, MAT, SYW, SYW, SYW, SYW, SYL, SYW, SYU, SYU, SYW, SYL, SYL, SYL, SYL,
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM,
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYW,
        // CJK Unified Ideographs Extension A
        x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR),
        x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR), x64(LTR),  x64(LTR),
        x64(LTR),  x64(LTR),  x64(LTR),  x64(LTR),  x16(LTR),  x16(LTR),  x16(LTR),
        LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Yijing Hexagram Symbols
        x64(SYM),
        // CJK Unified Ideographs
        x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR),
        x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR),
        x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR),
        x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR),
        x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR),
        x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR), x64(LTR),  x64(LTR),
        x64(LTR),  x64(LTR),  x64(LTR),  x64(LTR),  x64(LTR),  x16(LTR),  x16(LTR),
        x16(LTR),
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Yi Syllables
        x512(LTR), x512(LTR), x64(LTR), x64(LTR),
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX,
        // Yi Radicals
        x16(SYM), x16(SYM), x16(SYM),
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Lisu
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LMO, LMO, LMO, LMO, LMO, LMO, PUN, PUN,
        // Vai
        x64(LTR), x64(LTR), x64(LTR), x64(LTR),
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, PUN, PUN, PUN,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, LTR, LTR, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Cyrillic Extended-B
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, LTR, NMO,
        NMO, NMO, NMO, PUN, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, PUN, LMO,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, LMO, LMO, NMO, NMO,
        // Bamum
        x64(LTR), x16(LTR),
        NMO, NMO, PUN, PUN, PUN, PUN, PUN, PUN, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Modifier Tone Letters
        x16(LMO), x16(LMO),
        // Latin Extended-D
        LMO, LMO, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        LOW, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        LMO, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, UPP, LOW, UPP, LOW, UPP, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, LMO, LMO, LMO, UPP, LOW, UPP, LOW, LTR,
        UPP, LOW, UPP, LOW, LOW, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, UPP, UPP, UPP, UPP, LOW,
        UPP, UPP, UPP, UPP, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW, UPP, LOW,
        XXX, XXX, UPP, LOW, UPP, UPP, UPP, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, UPP, LMO, LMO, LOW, UPP, UPP, UPP, UPP, UPP,
        // Syloti Nagri
        LTR, LTR, NMO, LTR, LTR, LTR, NMO, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, SMO, SMO, NMO, NMO, SMO, PUN, PUN, PUN, PUN, XXX, XXX, XXX, XXX,
        // Common Indic Number Forms
        NUM, NUM, NUM, NUM, NUM, NUM, NUM, SYM, SYM, SYM, XXX, XXX, XXX, XXX, XXX, XXX,
        // Phags-pa
        x16(LTR), x16(LTR), x16(LTR),
        LTR, LTR, LTR, LTR, PUN, PUN, PUN, PUN, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Saurashtra
        SMO, SMO, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, SMO, SMO, SMO, SMO, SMO, SMO, SMO, SMO, SMO, SMO, SMO, SMO,
        SMO, SMO, SMO, SMO, NMO, NMO, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, PUN, PUN,
        DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, XXX, XXX, XXX, XXX, XXX, XXX,
        // Devanagari Extended
        NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO,
        NMO, NMO, LTR, LTR, LTR, LTR, LTR, LTR, PUN, PUN, PUN, LTR, PUN, LTR, LTR, NMO,
        // Kayah Li
        DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, PUN, PUN,
        // Rejang
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, SMO, SMO, SMO, NMO, NMO, NMO, NMO, NMO, NMO,
        NMO, NMO, NMO, NMO, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, PUN,
        // Hangul Jamo Extended-A
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX,
        // Javanese
        NMO, NMO, NMO, SMO, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, NMO, SMO, SMO, NMO, NMO, SMO, SMO, SMO, SMO, NMO, SMO, SMO, SMO,
        SMO, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, XXX, LMO,
        DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, XXX, XXX, XXX, XXX, PUN, PUN,
        // Myanmar Extended-B
        LTR, LTR, LTR, LTR, LTR, LTR, LMO, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, LTR, LTR, LTR, LTR, LTR, XXX,
        // Cham
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, NMO, NMO, NMO, NMO, NMO, SMO, SMO,
        SMO, NMO, NMO, SMO, SMO, NMO, NMO, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        LTR, LTR, LTR, NMO, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, NMO, SMO, XXX, XXX,
        DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, XXX, XXX, PUN, PUN, PUN, PUN,
        // Myanmar Extended-A
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LMO, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, SMO, NMO, SMO, LTR, LTR,
        // Tai Viet
        x16(LTR), x16(LTR), x16(LTR),
        NMO, NMO, NMO, NMO, NMO, LTR, LTR, NMO, NMO, LTR, LTR, LTR, LTR, LTR, NMO, NMO,
        LTR, NMO, LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, LTR, LTR, LTR, PUN, PUN,
        // Meetei Mayek Extensions
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, SMO, NMO, NMO, SMO, SMO,
        PUN, PUN, SYM, LTR, LTR, SMO, NMO, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Ethiopic Extended-A
        XXX, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, LTR, LTR, LTR, LTR, LTR, LTR, XXX,
        XXX, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX,
        // Latin Extended-E
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, SYM, LMO, LMO, LMO, LMO,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Cherokee Supplement
        x64(LOW), x16(LOW),
        // Meetei Mayek
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, SMO, SMO, NMO, SMO, SMO, NMO, SMO, SMO, PUN, SMO, NMO, XXX, XXX,
        DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, XXX, XXX, XXX, XXX, XXX, XXX,
        // Hangul Syllables
        x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR),
        x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR),
        x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR),
        x64(LTR),  x64(LTR),  x64(LTR),  x64(LTR),  x64(LTR),  x64(LTR),  x16(LTR),
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Hangul Jamo Extended-B
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX,
        // Surrogates
        x512(SUR), x512(SUR), x512(SUR), x512(SUR),
        // Private Use Area
        x512(PRI), x512(PRI), x512(PRI), x512(PRI), x512(PRI), x512(PRI), x512(PRI),
        x512(PRI), x512(PRI), x512(PRI), x512(PRI), x512(PRI), x64(PRI),  x64(PRI),
        x64(PRI),  x64(PRI),
        // CJK Compatibility Ideographs
        x64(LTR), x64(LTR), x64(LTR), x64(LTR), x64(LTR), x16(LTR), x16(LTR),
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX,
        x64(LTR), x16(LTR), x16(LTR),
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX, XXX,
        x16(XXX), x16(XXX),
        // Alphabetic Presentation Forms
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, LOW, LOW, LOW, LOW, LOW, XXX, XXX, XXX, XXX, XXX, LTR, NMO, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, LTR, LTR, LTR, LTR, LTR, XXX, LTR, XXX,
        LTR, LTR, XXX, LTR, LTR, XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        // Arabic Presentation Forms-A
        x64(LTR), x16(LTR), x16(LTR),
        LTR, LTR, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM,
        SYM, SYM, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        x64(LTR), x64(LTR), x64(LTR), x64(LTR), x64(LTR), x16(LTR),
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, PUN, PUN,
        x16(XXX), x64(LTR),
        XXX, XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        x16(XXX), x16(XXX),
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX,
        // Variation Selectors
        NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO,
        // Vertical Forms
        PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, XXX, XXX, XXX, XXX, XXX, XXX,
        // Combining Half Marks
        NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO, NMO,
        // CJK Compatibility Forms
        x16(PUN), x16(PUN),
        // Small Form Variants
        PUN, PUN, PUN, XXX, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, PUN, SYM,
        SYM, PUN, MAT, PUN, MAT, MAT, MAT, XXX, SYM, SYM, MAT, SYM, XXX, XXX, XXX, XXX,
        // Arabic Presentation Forms-B
        LTR, LTR, LTR, LTR, LTR, XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        x64(LTR), x16(LTR), x16(LTR), x16(LTR),
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, BOM,
        // Halfwidth and Fullwidth Forms
        XXX, PUN, PUN, SYM, SYM, MAT, SYM, PUN, PUN, PUN, PUN, MAT, PUN, PUN, PUN, PUN,
        DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, PUN, PUN, MAT, MAT, MAT, PUN,
        SYM, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP,
        UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, PUN, SYM, PUN, SYM, SYM,
        SYM, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, PUN, MAT, PUN, MAT, PUN,
        PUN, PUN, PUN, PUN, PUN, PUN, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, SMO, SMO,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX,
        XXX, XXX, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, LTR, LTR, LTR, LTR, LTR, LTR,
        XXX, XXX, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, LTR, LTR, LTR, XXX, XXX, XXX,
        SYM, SYM, MAT, SYM, SYM, SYM, SYM, XXX, SYM, MAT, MAT, MAT, MAT, SYM, SYM, XXX,
        // Specials
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, FMT, FMT, FMT, SYM, SYM, XXX, XXX

        #undef x16
        #undef x64
        #undef x512
    };

    const internalCharacterClass plane1CharacterClass[65536] = // TODO: modifiers, fill, latest 2 unicode changelogs
    {
        // Macro to fill 1 line (16 entries) (_0 to _F) with the same value
        #define x16(C) C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C
        // Macro to fill 4 lines (64 entries) with the same value
        #define x64(C) x16(C), x16(C), x16(C), x16(C)
        // Macro to fill 32 lines (512 entries) with the same value
        #define x512(C) x64(C), x64(C), x64(C), x64(C), x64(C), x64(C), x64(C), x64(C)

        // Linear B Syllabary
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, LTR, LTR, XXX, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Linear B Ideograms
        x64(LTR), x16(LTR), x16(LTR), x16(LTR),
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX,
        // Aegean Numbers (10100–1013F)
        // Ancient Greek Numbers (10140–1018F)
        // Ancient Symbols (10190–101CF)
        // Phaistos Disc (101D0–101FF)
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX,
        // Unallocated Range
        x64(XXX), x64(XXX),
        // Lycian
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX,
        // Carian
        x16(LTR), x16(LTR), x16(LTR),
        LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Coptic Epact Numbers (102E0–102FF)
        NMO, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, NUM, NUM, NUM, NUM, NUM, NUM,
        NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, XXX, XXX, XXX, XXX,
        // Old Italic
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, LTR, LTR, LTR,
        // Gothic
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX,
        // Old Permic
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, NMO, NMO, NMO, NMO, NMO, XXX, XXX, XXX, XXX, XXX,
        // Ugaritic (10380–1039F)
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, // pontuação+separador
        // Old Persian (103A0–103DF)
        // Unallocated Range
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Deseret (10400–1044F)
        UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP,
        UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP,
        UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
        // Shavian (10450–1047F)
        x16(LTR),  x16(LTR),  x16(LTR),
        // Osmanya (10480–104AF)
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX,
        DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, DIG, XXX, XXX, XXX, XXX, XXX, XXX,
        // Osage (104B0–104FF)
        UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP,
        UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP, UPP,
        UPP, UPP, UPP, UPP, XXX, XXX, XXX, XXX, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW,
        LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, XXX, XXX, XXX, XXX,
        // Elbasan (10500–1052F)
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Caucasian Albanian (10530–1056F)
        x16(LTR),  x16(LTR),  x16(LTR),
        LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, PUN,
        // Unallocated Range
        x64(XXX),  x64(XXX),  x16(XXX),
        // Linear A (10600–1077F)
        x64(LTR), x64(LTR), x64(LTR), x64(LTR), x16(LTR), x16(LTR), x16(LTR),
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Unallocated Range
        x64(XXX), x64(XXX),
        // Cypriot Syllabary (10800–1083F)
        LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, LTR, XXX, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, XXX, LTR, LTR, XXX, XXX, XXX, LTR, XXX, XXX, LTR,
        // Imperial Aramaic (10840–1085F)
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, XXX, PUN, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM,
        // Palmyrene (10860–1087F)
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, SYM, SYM, NUM, NUM, NUM, NUM, NUM, NUM, NUM,
        // Nabataean (10880–108AF)
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM,
        // Unallocated Range
        x16(XXX), x16(XXX), x16(XXX),
        // Hatran (108E0–108FF)
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, XXX, LTR, LTR, XXX, XXX, XXX, XXX, XXX, NUM, NUM, NUM, NUM, NUM,
        // Phoenician (10900–1091F)
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, NUM, NUM, NUM, NUM, NUM, NUM, XXX, XXX, XXX, // pontuação+separador
        // Lydian (10920–1093F)
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX, PUN,
        // Unallocated Range
        x64(XXX),
        // Meroitic Hieroglyphs (10980–1099F)
        // Meroitic Cursive (109A0–109FF)

        // Kharoshthi (10A00–10A5F)
        // Old South Arabian (10A60–10A7F)
        // Old North Arabian (10A80–10A9F)
        // Unallocated Range
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Manichaean (10AC0–10AFF)
        // Avestan (10B00–10B3F)
        // Inscriptional Parthian (10B40–10B5F)
        // Inscriptional Pahlavi (10B60–10B7F)
        // Psalter Pahlavi (10B80–10BAF)
        // Unallocated Range
        x64(XXX), x16(XXX),
        // Old Turkic (10C00–10C4F)
        // Unallocated Range
        x16(XXX), x16(XXX), x16(XXX),
        // Old Hungarian (10C80–10CFF)
        // Hanifi Rohingya (10D00–10D3F)
        // Unallocated Range
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Rumi Numeral Symbols (10E60–10E7F)
        // Unallocated Range
        x64(XXX), x64(XXX),
        // Old Sogdian (10F00–10F2F)
        // Sogdian (10F30–10F6F)
        // Unallocated Range
        x64(XXX), x16(XXX), x16(XXX), x16(XXX),
        // Elymaic (10FE0–10FFF)
        // Brahmi (11000–1107F)
        // Kaithi (11080–110CF)
        // Sora Sompeng (110D0–110FF)
        // Chakma (11100–1114F)
        // Mahajani (11150–1117F)
        // Sharada (11180–111DF)
        // Sinhala Archaic Numbers (111E0–111FF)
        // Khojki (11200–1124F)
        // Unallocated Range
        x16(XXX), x16(XXX), x16(XXX),
        // Multani (11280–112AF)
        // Khudawadi (112B0–112FF)
        // Grantha (11300–1137F)
        // Unallocated Range
        x64(XXX), x64(XXX),
        // Newa (11400–1147F)
        // Tirhuta (11480–114DF)
        // Unallocated Range
        x64(XXX), x64(XXX), x16(XXX), x16(XXX),
        // Siddham (11580–115FF)
        // Modi (11600–1165F)
        // Unallocated Range
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Takri (11680–116CF)
        // Unallocated Range
        x16(XXX), x16(XXX), x16(XXX),
        // Ahom (11700–1173F)
        // Unallocated Range
        x64(XXX), x64(XXX), x64(XXX),
        // Dogra (11800–1184F)
        // Unallocated Range
        x64(XXX), x16(XXX),
        // Warang Citi (118A0–118FF)
        // Unallocated Range
        x64(XXX), x64(XXX), x16(XXX), x16(XXX),
        // Nandinagari (119A0–119FF)
        // Zanabazar Square (11A00–11A4F)
        // Soyombo (11A50–11AAF)
        // Unallocated Range
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Pau Cin Hau (11AC0–11AFF)
        // Unallocated Range
        x64(XXX), x64(XXX), x64(XXX), x64(XXX),
        // Bhaiksuki (11C00–11C6F)
        // Marchen (11C70–11CBF)
        // Unallocated Range
        x64(XXX),
        // Masaram Gondi (11D00–11D5F)
        // Gunjala Gondi (11D60–11DAF)
        // Unallocated Range
        x64(XXX), x64(XXX), x64(XXX), x64(XXX), x16(XXX), x16(XXX), x16(XXX),
        // Makasar (11EE0–11EFF)
        // Unallocated Range
        x64(XXX), x64(XXX), x64(XXX),
        // Tamil Supplement (11FC0–11FFF)
        // Unallocated Range
        x64(XXX), x16(XXX), x16(XXX),
        // Mongolian Supplement (11660–1167F)
        // Unallocated Range
        x512(XXX), x512(XXX), x512(XXX), x512(XXX), x64(XXX),  x64(XXX),  x64(XXX),
        x64(XXX),  x64(XXX),  x64(XXX),
        // Cuneiform (12000–123FF)
        x512(LTR), x64(LTR),  x64(LTR),  x64(LTR),  x64(LTR),  x64(LTR),  x64(LTR),
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX, XXX,
        x64(XXX),  x16(XXX),  x16(XXX),
        // Cuneiform Numbers and Punctuation (12400–1247F)
        x64(NUM),  x16(NUM),  x16(NUM),
        NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, NUM, XXX,
        PUN, PUN, PUN, PUN, PUN, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Early Dynastic Cuneiform (12480–1254F)
        x64(LTR),  x64(LTR),  x64(LTR),
        LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Unallocated Range
        x512(XXX), x512(XXX), x512(XXX), x512(XXX), x512(XXX), x64(XXX),  x64(XXX),
        x16(XXX),  x16(XXX),  x16(XXX),
        // Egyptian Hieroglyphs (13000–1342F)
        x512(LTR), x512(LTR), x16(LTR),  x16(LTR),
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX,
        // Egyptian Hieroglyph Format Controls (13430–1343F)
        FMT, FMT, FMT, FMT, FMT, FMT, FMT, FMT, FMT, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Unallocated Range
        x512(XXX), x512(XXX), x512(XXX), x512(XXX), x512(XXX), x512(XXX), x512(XXX),
        x64(XXX),  x64(XXX),  x64(XXX),  x64(XXX),  x64(XXX),  x64(XXX),  x64(XXX),
        // Anatolian Hieroglyphs (14400–1467F)
        x512(LTR), x64(LTR),
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        x16(XXX),  x16(XXX),  x16(XXX),
        // Unallocated Range
        x512(XXX), x512(XXX), x512(XXX), x512(XXX), x512(XXX), x512(XXX), x512(XXX),
        x512(XXX), x512(XXX), x512(XXX), x512(XXX), x512(XXX), x512(XXX), x512(XXX),
        x512(XXX), x512(XXX), x64(XXX),  x64(XXX),  x64(XXX),  x64(XXX),  x64(XXX),
        x64(XXX),
        // Bamum Supplement (16800–16A3F)
        x512(LTR), x16(LTR),  x16(LTR),  x16(LTR),
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Mro (16A40–16A6F)
        // Unallocated Range
        x64(XXX), x16(XXX),  x16(XXX),
        // Bassa Vah (16AD0–16AFF)
        // Pahawh Hmong (16B00–16B8F)
        // Unallocated Range
        x512(XXX), x64(XXX),  x64(XXX),  x16(XXX),  x16(XXX),  x16(XXX),
        // Medefaidrin (16E40–16E9F)
        // Unallocated Range
        x64(XXX), x16(XXX),  x16(XXX),
        // Miao (16F00–16F9F)
        // Unallocated Range
        x64(XXX),
        // Ideographic Symbols and Punctuation (16FE0–16FFF)
        LTR, LTR, PUN, LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Tangut (17000–187FF)
        x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR), x512(LTR),
        x512(LTR), x512(LTR), x512(LTR), x512(LTR), x64(LTR),  x64(LTR),  x64(LTR),
        x64(LTR),  x64(LTR),  x64(LTR),  x64(LTR),  x16(LTR),  x16(LTR),  x16(LTR),
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Tangut Components (18800–18AFF)
        x512(LTR), x64(LTR),  x64(LTR),  x64(LTR),  x16(LTR),  x16(LTR),  x16(LTR),
        LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Unallocated Range
        x512(XXX), x512(XXX), x512(XXX), x512(XXX), x512(XXX), x512(XXX), x512(XXX),
        x512(XXX), x512(XXX), x512(XXX), x512(XXX), x512(XXX), x512(XXX), x512(XXX),
        x512(XXX), x512(XXX), x512(XXX), x512(XXX), x64(XXX),  x64(XXX),  x64(XXX),
        x64(XXX),
        // Kana Supplement (1B000–1B0FF)
        x64(LTR),  x64(LTR),  x64(LTR),  x64(LTR),
        // Kana Extended-A (1B100–1B12F)
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR,
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Small Kana Extension (1B130–1B16F)
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, XXX, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Nushu (1B170–1B2FF)
        x64(LTR),  x64(LTR),  x64(LTR),  x64(LTR),  x64(LTR),  x64(LTR),
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX,
        // Unallocated Range
        x512(XXX), x512(XXX), x512(XXX), x512(XXX), x64(XXX),  x64(XXX),  x64(XXX),
        x64(XXX),
        // Duployan (1BC00–1BC9F)
        // Shorthand Format Controls (1BCA0–1BCAF)
        // Unallocated Range
        x512(XXX), x512(XXX), x512(XXX), x512(XXX), x512(XXX), x512(XXX), x512(XXX),
        x512(XXX), x512(XXX), x64(XXX),  x64(XXX),  x64(XXX),  x64(XXX),  x64(XXX),
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Byzantine Musical Symbols (1D000–1D0FF)
        // Musical Symbols (1D100–1D1FF)
        // Ancient Greek Musical Notation (1D200–1D24F)
        // Unallocated Range
        x64(XXX), x64(XXX), x16(XXX),
        // Mayan Numerals (1D2E0–1D2FF)
        // Tai Xuan Jing Symbols (1D300–1D35F)
        // Counting Rod Numerals (1D360–1D37F)
        // Unallocated Range
        x64(XXX), x64(XXX),
        // Mathematical Alphanumeric Symbols (1D400–1D7FF)
        // Sutton SignWriting (1D800–1DAAF)
        // Unallocated Range
        x512(XXX), x512(XXX), x64(XXX),  x64(XXX),  x64(XXX),  x64(XXX),  x64(XXX),
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Glagolitic Supplement (1E000–1E02F)
        // Unallocated Range
        x64(XXX), x64(XXX), x64(XXX), x16(XXX),
        // Nyiakeng Puachue Hmong (1E100–1E14F)
        // Unallocated Range
        x64(XXX), x64(XXX), x64(XXX), x64(XXX), x64(XXX), x16(XXX), x16(XXX),
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Wancho (1E2C0–1E2FF)
        // Unallocated Range
        x512(XXX), x512(XXX), x64(XXX),  x64(XXX),  x64(XXX),  x64(XXX),
        // Mende Kikakui (1E800–1E8DF)
        // Unallocated Range
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Adlam (1E900–1E95F)
        // Unallocated Range
        x512(XXX), x64(XXX),  x64(XXX),  x64(XXX),  x64(XXX),  x16(XXX),
        // Indic Siyaq Numbers (1EC70–1ECBF)
        // Unallocated Range
        x64(XXX),
        // Ottoman Siyaq Numbers (1ED00–1ED4F)
        // Unallocated Range
        x64(XXX),  x64(XXX),  x16(XXX),  x16(XXX),  x16(XXX),
        // Arabic Mathematical Alphabetic Symbols (1EE00–1EEFF)
        // Mahjong Tiles (1F000–1F02F)
        // Domino Tiles (1F030–1F09F)
        x64(SYM),  x16(SYM),  x16(SYM),
        SYM, SYM, SYM, SYM, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Playing Cards (1F0A0–1F0FF)
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, XXX,
        XXX, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM,
        XXX, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM,
        XXX, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM,
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM,
        SYM, SYM, SYM, SYM, SYM, SYM, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Enclosed Alphanumeric Supplement (1F100–1F1FF)
        // Enclosed Ideographic Supplement (1F200–1F2FF)
        // Miscellaneous Symbols and Pictographs (1F300–1F5FF)
        x64(SYM),  x64(SYM),  x64(SYM),  x16(SYM),  x16(SYM),  x16(SYM),
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, // 5 modificadores de emoji
        x512(SYM),
        // Emoticons (1F600–1F64F)
        x64(SYM),  x16(SYM),
        // Ornamental Dingbats (1F650–1F67F)
        // Transport and Map Symbols (1F680–1F6FF)
        x64(SYM),  x16(SYM),
        SYM, SYM, SYM, SYM, SYM, SYM, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, XXX, XXX, XXX,
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, XXX, XXX, XXX, XXX, XXX,
        // Alchemical Symbols (1F700–1F77F)
        // Geometric Shapes Extended (1F780–1F7FF)
        // Supplemental Arrows-C (1F800–1F8FF)
        // Supplemental Symbols and Pictographs (1F900–1F9FF)
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, XXX, SYM, SYM, SYM,
        x64(SYM),  x16(SYM),  x16(SYM),
        SYM, SYM, XXX, SYM, SYM, SYM, SYM, XXX, XXX, XXX, SYM, SYM, SYM, SYM, SYM, SYM,
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM,
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM,
        SYM, SYM, SYM, XXX, XXX, SYM, SYM, SYM, SYM, SYM, SYM, XXX, XXX, XXX, SYM, SYM,
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM,
        SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, SYM, XXX, XXX, SYM, SYM, SYM,
        x16(SYM),  x16(SYM),  x16(SYM),
        // Chess Symbols (1FA00–1FA6F)
        x64(SYM),  x16(SYM),
        SYM, SYM, SYM, SYM, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, SYL, XXX, XXX,
        // Symbols and Pictographs Extended-A (1FA70–1FAFF)
        // Unallocated Range
        x512(XXX), x512(XXX), x64(XXX),  x64(XXX),  x64(XXX),  x16(XXX),  x16(XXX),
        x16(XXX),
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX

        #undef x16
        #undef x64
        #undef x512
    };

    const internalCharacterClass plane2CharacterClass[65536] =
    {
        // Macro to fill 1 line (16 entries) (_0 to _F) with the same value
        #define x16(C) C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C
        // Macro to fill 4 lines (64 entries) with the same value
        #define x64(C) x16(C), x16(C), x16(C), x16(C)
        // Macro to fill 32 lines (512 entries) with the same value
        #define x512(C) x64(C), x64(C), x64(C), x64(C), x64(C), x64(C), x64(C), x64(C)
        // Macro to fill 32 lines (512 entries) with the same value
        #define x2048(C) x512(C), x512(C), x512(C), x512(C)

        // CJK Unified Ideographs Extension B
        x2048(LTR), x2048(LTR), x2048(LTR), x2048(LTR), x2048(LTR), x2048(LTR), x2048(LTR),
        x2048(LTR), x2048(LTR), x2048(LTR), x2048(LTR), x2048(LTR), x2048(LTR), x2048(LTR),
        x2048(LTR), x2048(LTR), x2048(LTR), x2048(LTR), x2048(LTR), x2048(LTR), x512(LTR),
        x512(LTR),  x512(LTR),  x64(LTR),   x64(LTR),   x64(LTR),   x16(LTR),
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Unallocated Range
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // CJK Unified Ideographs Extension C
        x2048(LTR), x2048(LTR), x16(LTR),   x16(LTR),   x16(LTR),
        LTR, LTR, LTR, LTR, LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // CJK Unified Ideographs Extension D
        x64(LTR), x64(LTR), x64(LTR), x16(LTR),
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX,
        // CJK Unified Ideographs Extension E
        x2048(LTR), x2048(LTR), x512(LTR),  x512(LTR),  x512(LTR),  x64(LTR),   x64(LTR),
        LTR, LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // CJK Unified Ideographs Extension F
        x2048(LTR), x2048(LTR), x2048(LTR), x512(LTR),  x512(LTR),  x64(LTR),   x64(LTR),
        x64(LTR),   x64(LTR),   x16(LTR),   x16(LTR),   x16(LTR),
        LTR, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        // Unallocated Range
        x512(XXX),  x512(XXX),  x512(XXX),  x512(XXX),  x512(XXX),  x512(XXX),  x16(XXX),
        // CJK Compatibility Ideographs Supplement
        x512(LTR), x16(LTR),
        LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, LTR, XXX, XXX,
        // Unallocated Range
        x512(XXX), x512(XXX), x64(XXX),  x64(XXX),  x64(XXX),  x64(XXX),  x64(XXX),  x64(XXX),
        x64(XXX),  x16(XXX),
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX

        #undef x16
        #undef x64
        #undef x512
    };

    const internalCharacterClass plane14CharacterClass[512] =
    {
        // Macro to fill 1 line (16 entries) (_0 to _F) with the same value
        #define x16(C) C, C, C, C, C, C, C, C, C, C, C, C, C, C, C, C
        // Macro to fill 4 lines (64 entries) with the same value
        #define x64(C) x16(C), x16(C), x16(C), x16(C)

        // Tags
        XXX, FMT, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX,
        x16(XXX), x64(FMT), x16(FMT), x16(FMT),
        // Unallocated Range
        x64(XXX), x64(XXX),
        // Vartiation Selectors Supplement
        x64(NMO), x64(NMO), x64(NMO), x16(NMO), x16(NMO), x16(NMO),
        // Unallocated Range
        XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX, XXX

        #undef x16
        #undef x64
    };

    omn::characterClass classBeyondPlane2( const uint32_t codepoint )
    {
        if ((codepoint & 65535) > 65533) return omn::characterClass::Unassigned; // Non-Character
        if (codepoint > 0x10FFFF) return omn::characterClass::Unassigned;
        if (codepoint > 0xEFFFF) return omn::characterClass::Private;
        if ((codepoint > 0xDFFFF) && (codepoint < 0xE0200))
            return (externalClassTable[plane14CharacterClass[codepoint % 65536]]);
        return omn::characterClass::Unassigned;
    }
}

namespace omn
{
    namespace unicode
    {
        characterClass classOf( const UTF32Character codepoint )
        {
            if (codepoint < 0x10000) return (externalClassTable[plane0CharacterClass[codepoint]]);
            if (codepoint < 0x20000) return (externalClassTable[plane1CharacterClass[codepoint % 65536]]);
            if (codepoint < 0x30000) return (externalClassTable[plane2CharacterClass[codepoint % 65536]]);
            return classBeyondPlane2(codepoint);
        }

        bool isNonGraphicControlCharacter( const UTF32Character codepoint )
        {
            if (codepoint < 0x10000) return (plane0CharacterClass[codepoint] == internalCharacterClass::CTR);
            return false;
        }

        bool isDigit( const UTF32Character codepoint )
        {
            if (codepoint < 0x10000) return (plane0CharacterClass[codepoint] == internalCharacterClass::DIG);
            if (codepoint < 0x20000) return (plane0CharacterClass[codepoint % 65536] == internalCharacterClass::DIG);
            return false;
        }
    }
}

namespace std
{
    ostream & operator << ( ostream & os, const omn::characterClass classOf )
    {
        switch (classOf)
        {
            case 0b00000000000000000001: os << characterClassNamesTable[1]; break;
            case 0b00000000000000001101: os << characterClassNamesTable[2]; break;
            case 0b00000000000000010101: os << characterClassNamesTable[3]; break;
            case 0b00000000000000000011: os << characterClassNamesTable[4]; break;
            case 0b00000000000000000010: os << characterClassNamesTable[5]; break;
            case 0b00000000000000000100: os << characterClassNamesTable[6]; break;
            case 0b00000000000000001100: os << characterClassNamesTable[7]; break;
            case 0b00000000000000010100: os << characterClassNamesTable[8]; break;
            case 0b00000000000000100000: os << characterClassNamesTable[9]; break;
            case 0b10000000000000000000: os << characterClassNamesTable[10]; break;
            case 0b10000000000000100000: os << characterClassNamesTable[11]; break;
            case 0b10000000000001000000: os << characterClassNamesTable[12]; break;
            case 0b10000000000011000000: os << characterClassNamesTable[13]; break;
            case 0b10000000000101000000: os << characterClassNamesTable[14]; break;
            case 0b10000000001101000000: os << characterClassNamesTable[15]; break;
            case 0b10000000110101000000: os << characterClassNamesTable[16]; break;
            case 0b10000000000100000000: os << characterClassNamesTable[17]; break;
            case 0b10000000001100000000: os << characterClassNamesTable[18]; break;
            case 0b10000000010100000000: os << characterClassNamesTable[19]; break;
            case 0b10000000110100000000: os << characterClassNamesTable[20]; break;
            case 0b10000001000000000000: os << characterClassNamesTable[21]; break;
            case 0b10000011000000000000: os << characterClassNamesTable[22]; break;
            case 0b10000101000000000000: os << characterClassNamesTable[23]; break;
            case 0b10000101000100000000: os << characterClassNamesTable[24]; break;
            case 0b00001000000000000000: os << characterClassNamesTable[25]; break;
            case 0b00011000000000000000: os << characterClassNamesTable[26]; break;
            case 0b00001000000100000000: os << characterClassNamesTable[27]; break;
            case 0b00001000001100000000: os << characterClassNamesTable[28]; break;
            case 0b00001000110100000000: os << characterClassNamesTable[29]; break;
            case 0b00100000000000000000: os << characterClassNamesTable[30]; break;
            case 0b01000000000000000000: os << characterClassNamesTable[31]; break;
            default: os << characterClassNamesTable[0]; break;
        }
        return os;
    }
}
