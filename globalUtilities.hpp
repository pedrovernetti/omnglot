
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
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 
 * * Default-Included Headers:
 *
 * <cstdint>
 * <cstring>
 * <initializer_list>
 * <limits>
 * <ostream>
 * <string>
 * <type_traits>
 * <utility>
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * * Macros (either defined as positive integer literals or undefined):
 *
 * * * on the target OS:
 *
 * _COMPILING_FOR_DOS                    target OS is any version of DOS
 * _COMPILING_FOR_MSDOS                  target OS is MS-DOS
 * _COMPILING_FOR_WIN16                  target OS is Windows 3.1 or older versions
 * _COMPILING_FOR_WINDOWS                target OS is Windows (95 and newer)
 * _COMPILING_FOR_MACH                   target OS is any one based on Mach kernel
 * _COMPILING_FOR_APPLE                  target OS is any of those belonging to Apple
 * _COMPILING_FOR_WATCHOS                target OS is watchOS (Apple Watch OS)
 * _COMPILING_FOR_IOS_SIMULATOR          target OS is iOS (simulator)
 * _COMPILING_FOR_IOS                    target OS is iOS (iPhone and iPad OS)
 * _COMPILING_FOR_OSX                    target OS is Mac OS X
 * _COMPILING_FOR_ANDROID                target OS is Android
 * _COMPILING_FOR_AIX                    target OS is AIX
 * _COMPILING_FOR_QNX                    target OS is QNX
 * _COMPILING_FOR_QNXNEUTRINO            target OS is QNX Neutrino
 * _COMPILING_FOR_QNX4                   target OS is QNX 4
 * _COMPILING_FOR_IBMOS400               target OS is IBM OS/400
 * _COMPILING_FOR_DRAGONFLYBSD           target OS is DragonFly BSD
 * _COMPILING_FOR_BSDOS                  target OS is BSD/OS
 * _COMPILING_FOR_NETBSD                 target OS is NetBSD
 * _COMPILING_FOR_OPENBSD                target OS is OpenBSD
 * _COMPILINF_FOR_FREEBSD                target OS is FreeBSD
 * _COMPILING_FOR_SYLLABLE               target OS is Syllable
 * _COMPILING_FOR_ECOS                   target OS is eCos
 * _COMPILING_FOR_GNUHURD                target OS is GNU (GNU/Hurd)
 * _COMPILING_FOR_LINUX                  target OS is any one based on Linux kernel
 * _COMPILING_FOR_GNULINUX               target OS is GNU/Linux
 * _COMPILING_FOR_OTHER_UNIX_SYSTEMS     target OS is any BSD system not covered by other macros
 * _COMPILING_FOR_OTHER_UNIX_SYSTEMS     target OS is any UNIX/UNIX-like system not covered by other macros
 * _COMPILING_FOR_UNIX                   target OS is any UNIX/UNIX-like system
 * _COMPILING_FOR_BSD                    target OS is any BSD system
 * _COMPILING_FOR_POSIX_COMPLIANTS       target OS is any POSIX-compliant system
 * _COMPILING_FOR_UNKNOWN_OS             target OS is unknown (not any of the ones above)
 *
 * * * on the compiler being used:
 *
 * ...
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * * Type Aliases:
 *
 * byte                                  'unsigned char'
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * * Macro Strings (std::string("...") if _NONCPP is undefined, string literal otherwise):
 *
 * compilationDate                       date when the compilation occurred
 * compilationTime                       time when the compilation occurred
 * compilationDateAndTime                date/time when the compilation occurred (C++ code only)
 * compilerName                          name of the compiler being used
 * compilerNameAndVersion                name and version of the compiler being used
 * targetOSName                          name of the OS which is being targeted
 * thisFileName                          name/path (what the compiler takes) of the file it's within
 * thisFileModificationDateAndTime       last modification date/time of the file it's within
 * thisFunctionName                      name of the function it is in
 * thisFunctionSignature                 signature of the function it is in
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * * Macro Unsigned Integers (size_t):
 *
 * thisCodeLine                          number of the line it's placed at
 * previousCodeLine                      number of the line before the one it's placed at
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * * Namespaced aliases, constexpr utility values and base classes
 *
 * * * Type Aliases:
 *
 * omn::pair                             'std::pair'
 * omn::unicode::UTF8Character           'char8_t' if supported, 'char' otherwise
 * omn::unicode::UTF16Character          'char16_t'
 * omn::unicode::UTF32Character          'char32_t'
 * omn::unicode::UTF8String              'std::u8string' if supported, 'std::string' otherwise
 * omn::unicode::UTF16String             'std::u16string'
 * omn::unicode::UTF32String             'std::u32string'
 *
 * * * Base Classes:
 *
 * omn::stringifiable                    base class for things that can be converted to std::string
 *
 * * * Value Aliases:
 *
 * omn::math::maximumSize                '(size_t)(-1)'
 * omn::math::maximumSignedInteger       'std::numeric_limits<int>::max()'
 * omn::math::maximumShortSignedInteger  'std::numeric_limits<short int>::max()'
 * omn::math::maximumLongSignedInteger   'std::numeric_limits<long int>::max()'
 * omn::math::absoluteMaximumSignedInteger  'std::numeric_limits<intmax_t>::max()'
 * omn::math::minimumSignedInteger       'std::numeric_limits<int>::lowest()'
 * omn::math::minimumShortSignedInteger  'std::numeric_limits<short int>::lowest()'
 * omn::math::minimumLongSignedInteger   'std::numeric_limits<long int>::lowest()'
 * omn::math::absoluteMinimumSignedInteger  'std::numeric_limits<intmax_t>::lowest()'
 * omn::math::infinity                   'std::numeric_limits<double>::infinity()'
 * omn::math::floatInfinity              'std::numeric_limits<float>::infinity()'
 * omn::math::longInfinity               'std::numeric_limits<long double>::infinity()'
 * omn::math::NaN                        'std::numeric_limits<double>::quiet_NaN()'
 * omn::math::floatNaN                   'std::numeric_limits<float>::quiet_NaN()'
 * omn::math::longNaN                    'std::numeric_limits<long double>::quiet_NaN()'
 * omn::math::epsilon                    'std::numeric_limits<double>::epsilon()'
 * omn::math::floatEpsilon               'std::numeric_limits<float>::epsilon()'
 * omn::math::longEpsilon                'std::numeric_limits<long double>::epsilon()'
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#pragma once
#ifndef _OMN_GLOBALUTILITIES_INCLUDED
#define _OMN_GLOBALUTILITIES_INCLUDED

#if defined(__cplusplus)
    #include <cstring>
    #include <initializer_list>
    #include <limits>
    #include <ostream>
    #include <string>
    #include <type_traits>
    #include <utility>
    #define __PROPER_STR(a) std::string(a)
#else
    #error "this is a C++ library"
    // relic code...
    #include <string.h>
    #if __STDC_VERSION__ < 199901L
        #define _NO_C99_SUPPORT (1)
        #pragma message ( "C99 not fully supported" )
    #endif
    #define _NONCPP (1)
    #define __PROPER_STR(a) (a)
#endif

#ifndef __has_cpp_attribute
    #define __has_cpp_attribute(a) 0
#endif

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * target OS identification macros                                   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

// DOS
#if defined(__DOS__) || defined(MSDOS) || defined(_MSDOS) || defined(__MSDOS__)
    #define _COMPILING_FOR_DOS
    #if defined(MSDOS) || defined(_MSDOS) || defined(__MSDOS__)
        #define _COMPILING_FOR_MSDOS
        #define targetOSName (__PROPER_STR("MS-DOS"))
    #else
        #define targetOSName (__PROPER_STR("DOS"))
    #endif

// Windows CE
#elif defined(_WIN32_WCE)
    #define _COMPILING_FOR_WINDOWSCE
    #define targetOSName (__PROPER_STR("Windows CE"))

// Windows 3.1 and older
#elif defined(_WINDOWS) || defined(__WINDOWS__) || defined(__WINDOWS_386__)
    #define _COMPILING_FOR_WIN16
    #if defined(__WINDOWS_386__)
        #define
        #define targetOSName (__PROPER_STR("Windows (Win16 32-bit)"))
    #else
        #define targetOSName (__PROPER_STR("Windows (Win16)"))
    #endif

// Windows
#elif defined(_WIN32) || defined(_WIN64) || defined(__NT__) || defined(Q_OS_WIN32)
    #define _COMPILING_FOR_WINDOWS
    #define targetOSName (__PROPER_STR("Windows"))
    #if defined(_WIN64) || defined(Q_OS_WIN64)
        #define _COMPILING_FOR_64BITS_ARCHITECTURE
    #endif

// Mach-based systems
#elif defined(__MACH__)
    #define _COMPILING_FOR_MACH
    #if defined(__APPLE__)
        #define _COMPILING_FOR_APPLE
        #include <TargetConditionals.h>
        #if TARGET_IPHONE_SIMULATOR
            #define _COMPILING_FOR_IOS_SIMULATOR
            #define targetOSName (__PROPER_STR("iOS (simulator)"))
        #elif TARGET_OS_WATCH
            #define _COMPILING_FOR_WATCHOS
            #define targetOSName (__PROPER_STR("watchOS"))
        #elif TARGET_OS_IPHONE
            #define _COMPILING_FOR_IOS
            #define targetOSName (__PROPER_STR("iOS"))
        #else
            #define _COMPILING_FOR_OSX
            #define targetOSName (__PROPER_STR("OS X"))
        #endif
    #else
        #define targetOSName (__PROPER_STR("some Mach-based OS"))
    #endif

// Android
#elif defined(__ANDROID__) || defined(ANDROID) || defined(__ANDROID_API__) || defined(Q_OS_ANDROID)
    #define _COMPILING_FOR_ANDROID
    #define targetOSName (__PROPER_STR("Android"))

// AIX
#elif defined(_AIX) || defined(__TOS_AIX__) || defined(Q_OS_AIX)
    #define _COMPILING_FOR_AIX
    #define targetOSName (__PROPER_STR("AIX"))

// QNX
#elif defined(__QNX__) || defined(__QNXNTO__)
    #define _COMPILING_FOR_QNX
    #if defined(__QNXNTO__)
        #define _COMPILING_FOR_QNXNEUTRINO
        #define targetOSName (__PROPER_STR("QNX Neutrino"))
    #else
        #define _COMPILING_FOR_QNX4
        #define targetOSName (__PROPER_STR("QNX 4"))
    #endif

// MINIX
#elif defined(__minix)
    #define _COMPILING_FOR_MINIX
    #define targetOSName (__PROPER_STR("MINIX"))

// LynxOS
#elif defined(__Lynx__)
    #define _COMPILING_FOR_LYNXOS
    #define targetOSName (__PROPER_STR("LynxOS"))

// eCos
#elif defined(__ECOS)
    #define _COMPILING_FOR_ECOS
    #define targetOSName (__PROPER_STR("eCos"))

// Syllable
#elif defined(__SYLLABLE__)
    #define _COMPILING_FOR_SYLLABLE
    #define targetOSName (__PROPER_STR("Syllable"))

// MorphOS
#elif defined(__MORPHOS__)
    #define _COMPILING_FOR_MORPHOS
    #define targetOSName (__PROPER_STR("MorphOS"))

// BeOS
#elif defined(__BEOS__)
    #define _COMPILING_FOR_BEOS
    #define targetOSName (__PROPER_STR("BeOS"))

// AmigaOS
#elif defined(AMIGA) || defined(__amigaos__)
    #define _COMPILING_FOR_AMIGAOS
    #define targetOSName (__PROPER_STR("AmigaOS"))

// Ultrix
#elif defined(ultrix) || defined(__ultrix) || defined(__ultrix__) || (defined(unix) && defined(vax))
    #define _COMPILING_FOR_ULTRIX
    #define targetOSName (__PROPER_STR("Ultrix"))

// IBM OS/400
#elif defined(__OS400__)
    #define _COMPILING_FOR_IBMOS400
    #define targetOSName (__PROPER_STR("IBM OS/400"))

// UNICOS
#elif defined(_UNICOS)
    #define _COMPILING_FOR_UNICOS
    #define targetOSName (__PROPER_STR("UNICOS"))

// HP-UX
#elif defined(_hpux) || defined(hpux) || defined(__hpux)
    #define _COMPILING_FOR_HPUX
    #define targetOSName (__PROPER_STR("HP-UX"))

// OS/2
#elif defined(OS2) || defined(_OS2)|| defined(__OS2__)|| defined(__TOS_OS2__)
    #define _COMPILING_FOR_OS2
    #define targetOSName (__PROPER_STR("OS/2"))

// GNU/kFreeBSD
#elif defined(__FreeBSD_kernel__) && defined(__GLIBC__)
    #define _COMPILING_FOR_GNUKFREEBSD
    #define targetOSName (__PROPER_STR("GNU/kFreeBSD"))

// Dragonfly BSD
#elif defined(__DragonFly__)
    #define _COMPILING_FOR_DRAGONFLYBSD
    #define targetOSName (__PROPER_STR("DragonFly BSD"))

// BSD/OS
#elif defined(__bsdi__)
    #define _COMPILING_FOR_BSDOS
    #define targetOSName (__PROPER_STR("BSD/OS"))

// NetBSD
#elif defined(__NetBSD__)
    #define _COMPILING_FOR_NETBSD
    #define targetOSName (__PROPER_STR("NetBSD"))

// OpenBSD
#elif defined(__OpenBSD__)
    #define _COMPILING_FOR_OPENBSD
    #define targetOSName (__PROPER_STR("OpenBSD"))

// FreeBSD
#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
    #define _COMPILING_FOR_FREEBSD
    #define targetOSName (__PROPER_STR("FreeBSD"))

// GNU/Linux
#elif defined(__linux) || defined(__linux__) || defined(__LINUX__) || defined(linux) || defined(Q_OS_LINUX)
    #define _COMPILING_FOR_LINUX
    #if defined(__gnu_linux__)
        #define _COMPILING_FOR_GNULINUX
        #define targetOSName (__PROPER_STR("GNU/Linux"))
    #else
        #define targetOSName (__PROPER_STR("some Linux-based OS"))
    #endif

// GNU (GNU/Hurd)
#elif defined(__gnu_hurd__) || defined(__GNU__)
    #define _COMPILING_FOR_GNUHURD
    #define targetOSName (__PROPER_STR("GNU/Hurd"))

// uncovered BSD systems
#elif defined(BSD)
    #define _COMPILING_FOR_OTHER_BSD_SYSTEMS
    #define targetOSName (__PROPER_STR("some BSD system"))

// uncovered UNIX systems
#elif defined(__unix) || defined(__unix__) || defined(__UNIX__) || defined(unix) || defined(Q_OS_UNIX)
    #define _COMPILING_FOR_OTHER_UNIX_SYSTEMS
    #define targetOSName (__PROPER_STR("some UNIX system"))
#endif

// BSD systems (all)
#if defined(BSD) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__) || defined(__DragonFly__)
    #define _COMPILING_FOR_BSD
#endif

// UNIX systems (all)
#if defined(__unix) || defined(__unix__) || defined(__UNIX__) || defined(unix) || defined(Q_OS_UNIX)
    #define _COMPILING_FOR_UNIX
#endif

// POSIX-compliant systems
#if defined(__posix)
    #define _COMPILING_FOR_POSIX_COMPLIANTS
    #ifndef targetOSName
        #define targetOSName (__PROPER_STR("some POSIX-compliant OS"))
    #endif
#endif

// Unknown OS
#ifndef targetOSName
    #define _COMPILING_FOR_UNKNOWN_OS
    #pragma message ( "unknown target OS" )
    #define targetOSName (__PROPER_STR("unknown OS"))
#endif

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * compiler identification macros                                    *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

#define compilerNameAndVersion (__PROPER_STR("?"))
#define compilerLongName (__PROPER_STR("?"))
#define compilerShortName (__PROPER_STR("?"))

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * type aliases                                                      *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

#ifdef _NONCPP
    #include <stdint.h>
    typedef unsigned char byte;
#else
    #include <cstdint>
    using byte = unsigned char;
#endif

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * utility macro strings                                             *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

#if defined(__FUNCTION__)
    #define thisFunctionName (__PROPER_STR(__FUNCTION__))
#else
    #define thisFunctionName (__PROPER_STR("?"))
#endif
#if defined(__funcsig__)
    #define thisFunctionSignature (__PROPER_STR(__funcsig__))
#else
    #define thisFunctionSignature currentFunctionName
#endif
#define compilationDate (__PROPER_STR(__DATE__))
#define compilationTime (__PROPER_STR(__TIME__))
#ifndef _NONCPP
    #define compilationDateAndTime (__PROPER_STR(__PROPER_STR(__DATE__) + " " + __TIME__))
#endif
#define thisFileName (__PROPER_STR(__FILE__))
#define thisFileModificationDateAndTime (__PROPER_STR(__TIMESTAMP__))

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * utility macro unsigned integers                                   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

#define thisCodeLine ((size_t)(__LINE__))
#define previousCodeLine ((size_t)((__LINE__ > 0) ? (__LINE__ - 1) : 0))

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * (namespaced) aliases, constexpr utility values and base classes   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

namespace omn
{
    // omn aliases for std types
    template <typename type1, typename type2>
    using pair = std::pair<type1, type2>;

    // omn aliases for math-related std values
    namespace math
    {
        constexpr size_t maximumSize = (size_t)(-1);
        constexpr int maximumSignedInteger = std::numeric_limits<int>::max();
        constexpr short int maximumShortSignedInteger = std::numeric_limits<short int>::max();
        constexpr long int maximumLongSignedInteger = std::numeric_limits<long int>::max();
        constexpr intmax_t absoluteMaximumSignedInteger = std::numeric_limits<intmax_t>::max();

        constexpr int minimumSignedInteger = std::numeric_limits<int>::lowest();
        constexpr short int minimumShortSignedInteger = std::numeric_limits<short int>::lowest();
        constexpr long int minimumLongSignedInteger = std::numeric_limits<long int>::lowest();
        constexpr intmax_t absoluteMinimumSignedInteger = std::numeric_limits<intmax_t>::lowest();

        constexpr double infinity = std::numeric_limits<double>::infinity();
        constexpr float floatInfinity = std::numeric_limits<float>::infinity();
        constexpr long double longInfinity = std::numeric_limits<long double>::infinity();

        constexpr double NaN = std::numeric_limits<double>::quiet_NaN();
        constexpr float floatNaN = std::numeric_limits<float>::quiet_NaN();
        constexpr long double longNaN = std::numeric_limits<long double>::quiet_NaN();

        constexpr double epsilon = std::numeric_limits<double>::epsilon();
        constexpr float floatEpsilon = std::numeric_limits<float>::epsilon();
        constexpr long double longEpsilon = std::numeric_limits<long double>::epsilon();
    }

    // type aliases for unicode strings and characters
    namespace unicode
    {
        #if __has_cpp_attribute(__cpp_char8_t) || (__cpp_char8_t >= 201811)
        using UTF8Character = char8_t;
        using UTF8String = std::u8string;
        #else
        using UTF8Character = char;
        using UTF8String = std::string;
        #endif
        using UTF16Character = char16_t;
        using UTF16String = std::u16string;
        using UTF32Character = char32_t;
        using UTF32String = std::u32string;
    }

    // base classes
    class stringifiable
    {
        public:

        virtual std::string stringified() const = 0;

        inline operator std::string () const
        {
            return this->stringified();
        }
    };
}

// support for stringifiable base class and other printables
namespace std
{
    template <typename type1, typename type2>
    inline ostream & operator << ( ostream & os, const pair<type1, type2> & p )
    {
        os << "(" << p.first << ", " << p.second << ")";
        return os;
    }

    inline string to_string( const omn::stringifiable & stringifiableObject )
    {
        return stringifiableObject.stringified();
    }

    inline ostream & operator << ( ostream & os, const omn::stringifiable & stringifiableObject )
    {
        os << stringifiableObject.stringified();
        return os;
    }
};

#endif // _OMN_GLOBALUTILITIES_INCLUDED

