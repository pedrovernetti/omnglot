
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
 * Author: Pedro Vernetti G.
 * Name: omnglot
 * Description:
 *    This program identifies the language a given text is in. Run it without any arguments
 *    to get a help message. It can read from a file or from pipe/stdin (if input is "-").
 *    It can use both letter N-grams and stopwords language identification models and you
 *    can choose one (first argument "-s" for stopwords or "-n" for N-grams) or both of them
 *    (first argument "-2"). Languages in the output are given in the form of ISO 639-2B
 *    language codes and the values preceding the codes stand for the result's confidence.
 *
 * In order to compile and run this program, have gcc (8+) and make installed (install using
 * your package manager, in case one is missing), then run:
 *
 * $ cd THE_DIRECTORY_THIS_FILE_IS_IN
 * $ make
 * $ ./omnglot
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <iostream>
#include <iomanip>
#include <fstream>

#include "globalUtilities.hpp"
#if defined(_COMPILING_FOR_POSIX_COMPLIANTS) || defined(_COMPILING_FOR_UNIX)
#include <sys/stat.h>
#elif defined(_COMPILING_FOR_WINDOWS)
#include <windows.h>
#endif

#include "charEncoding.hpp"
#include "characterTransformations.hpp"
#include "tokenization.hpp"

#include "stopwordsBasedLanguageIdentification.hpp"
#include "NGramsBasedLanguageIdentification.hpp"

constexpr bool validMode( char * argv[] )
{
    return ((argv[1][0] == '-') && ((argv[1][1] == 'n') || (argv[1][1] == 's') || (argv[1][1] == '2')));
}

bool validInputFile( int argc, char * argv[] )
{
    const std::string path = argv[argc - 1];
    #if defined(_COMPILING_FOR_POSIX_COMPLIANTS) || defined(_COMPILING_FOR_UNIX)
    struct stat buffer;
    return ((!stat(path.data(), &buffer)) &&
            ((S_ISREG(buffer.st_mode)) || (S_ISLNK(buffer.st_mode))));
    #else
    FILE * fileHandle = std::fopen(path.data(), "r+");
    if (fileHandle)
    {
        std::fclose(fileHandle);
        return true;
    }
    return false;
    #endif
}

inline void usageHelp( char * argv[] )
{
    std::cout << "Usage: '" << argv[0] << "' -n|-s|-2 INPUT_FILE|-\n";
    exit(1);
}

int main( int argc, char * argv[] )
{
    if (argc != 3) usageHelp(argv);

    if (!validMode(argv)) usageHelp(argv);
    bool useNGrams = !std::strcmp(argv[1], "-n");
    bool useStopwords = !std::strcmp(argv[1], "-s");
    if (!std::strcmp(argv[1], "-2")) useNGrams = useStopwords = true;

    omn::unicode::UTF32String input = U"";
    if (validInputFile(argc, argv))
    {
        std::ifstream f(argv[argc - 1]);
        input = omn::unicode::UTF8::decode(
            std::string(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>()));
        f.close();
    }
    else if (!std::strcmp(argv[argc - 1], "-"))
    {
        if (std::cin.peek() == EOF) return 0;
        omn::unicode::UTF8String pipeLine;
        while (std::getline(std::cin, pipeLine)) input += omn::unicode::UTF8::decode(pipeLine);
        pipeLine.clear();
    }
    else usageHelp(argv);

    omn::tokenization::tokenizedString tokens = omn::tokenization::tokenize(input);

    omn::languageIdentification::minimumAcceptableConfidence = 0.2;
    if (useStopwords)
    {
        auto stopwordsBasedResults = omn::languageIdentification::stopwordsBased::identify(tokens);
        if (stopwordsBasedResults.empty())
            stopwordsBasedResults.push_back(std::make_pair(omn::ISO6392LanguageCode::und, 1.0));
        std::cout << "by stopwords: " << stopwordsBasedResults[0].second << " " << stopwordsBasedResults[0].first;
    }
    if (useNGrams)
    {
        auto NGramsBasedResults = omn::languageIdentification::NGramsBased::identify(tokens);
        if (NGramsBasedResults.empty())
            NGramsBasedResults.push_back(std::make_pair(omn::ISO6392LanguageCode::und, 1.0));
        if (useStopwords) std::cout << ", ";
        std::cout << "by N-grams: " << NGramsBasedResults[0].second << " " << NGramsBasedResults[0].first;
    }
    std::cout << "\n";
}
