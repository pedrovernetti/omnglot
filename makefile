
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
#* Copyright 2019 Pedro Vernetti G.
#*
#* Permission is hereby granted, free of charge, to any person obtaining a copy of this 
#* software and associated documentation files (the "Software"), to deal in the Software
#* without restriction, including without limitation the rights to use, copy, modify, merge,
#* publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons
#* to whom the Software is furnished to do so, subject to the following conditions:
#*
#* The above copyright notice and this permission notice shall be included in all copies or
#* substantial portions of the Software.
#*
#* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
#* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
#* PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
#* FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
#* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
#* DEALINGS IN THE SOFTWARE.
#*
#* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

CPP=g++-8
CPPFLAGS=-std=c++17 -O0 -g -pthread
LDFLAGS=-std=c++17 -O0 -g
LDLIBS=

GLOBAL=globalUtilities.hpp
SRCS=main.cpp characterClass.cpp characterTransformations.cpp charEncoding.cpp NGramsBasedLanguageIdentification.cpp stopwords.cpp stopwordsBasedLanguageIdentification.cpp tokenization.cpp 
HDRS=$(wildcard *.hpp) 
OBJS=$(subst .cpp,.o,$(SRCS))

main: $(OBJS)
	rm -f main
	rm -f omnglot
	$(CPP) $(LDFLAGS) -o omnglot $(OBJS) $(LDLIBS) 
	
main.o: $(HDRS) main.cpp
	$(CPP) $(CPPFLAGS) -c main.cpp
	
characterClass.o: $(GLOBAL) characterClass.hpp characterClass.cpp
	$(CPP) $(CPPFLAGS) -c characterClass.cpp

characterTransformations.o: $(GLOBAL) characterClass.hpp characterTransformations.hpp characterTransformations.cpp
	$(CPP) $(CPPFLAGS) -c characterTransformations.cpp

charEncoding.o: $(GLOBAL) charEncoding.hpp charEncoding.cpp
	$(CPP) $(CPPFLAGS) -c charEncoding.cpp

NGramsBasedLanguageIdentification.o: $(GLOBAL) ISO639.hpp characterClass.hpp map.hpp vector.hpp languageIdentification.hpp charEncoding.hpp characterTransformations.hpp unorderedMap.hpp bag.hpp array.hpp letterNGrams.hpp unorderedMap.hpp set.hpp tokenization.hpp NGramsBasedLanguageIdentification.hpp NGramsBasedLanguageIdentification.cpp
	$(CPP) $(CPPFLAGS) -c NGramsBasedLanguageIdentification.cpp

stopwords.o: $(GLOBAL) ISO639.hpp characterClass.hpp vector.hpp tokenization.hpp unorderedMap.hpp set.hpp stopwords.hpp stopwords.cpp
	$(CPP) $(CPPFLAGS) -c stopwords.cpp

stopwordsBasedLanguageIdentification.o: $(GLOBAL) ISO639.hpp characterClass.hpp map.hpp vector.hpp languageIdentification.hpp tokenization.hpp unorderedMap.hpp set.hpp stopwords.hpp stopwordsBasedLanguageIdentification.hpp stopwordsBasedLanguageIdentification.cpp
	$(CPP) $(CPPFLAGS) -c stopwordsBasedLanguageIdentification.cpp

tokenization.o: $(GLOBAL) characterClass.hpp vector.hpp tokenization.hpp tokenization.cpp
	$(CPP) $(CPPFLAGS) -c tokenization.cpp
