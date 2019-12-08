
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
#ifndef _OMN_ARRAY_INCLUDED
#define _OMN_ARRAY_INCLUDED

#include "globalUtilities.hpp"
#include <array>

namespace std 
{
	// adds std::hash support for std::array, consequently adding
	// std::unordered_map and std::unordered_set support for std::array as key type
    template<typename valueType, size_t size> 
	struct hash<array<valueType, size>>
	{
		private:
		
		hash<valueType> hasher;
		
		public:
		
		typedef array<valueType, size> argument_type;
        typedef size_t result_type;

        result_type operator () ( const argument_type & a ) const 
		{
            result_type result = 0;
			for(size_t i = 0; i < size; ++i)
                //result ^= hasher(a[i]) + 2654435769 + (result << 6) + (result >> 2);
				result = (result * 31) + hasher(a[i]);
            return result;
        }  
    };
    
	template <typename valueType, size_t size>
	ostream & operator << ( ostream & os, const std::array<valueType, size> & a )
	{
		os << "[";
		if (size > 0)
		{
			for (size_t i = 0; i < (size - 1); i++) os << a[i] << ", ";
			os << a[size - 1];
		}
		os << "]";
		return os;
	}
}

namespace omn
{
	template <typename valueType, size_t size>
	using array = std::array<valueType, size>;
}

#endif // _OMN_ARRAY_INCLUDED
