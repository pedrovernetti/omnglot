
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

#pragma once
#ifndef _OMN_BAG_INCLUDED
#define _OMN_BAG_INCLUDED

#include "globalUtilities.hpp"
#include "unorderedMap.hpp"
#include "vector.hpp"
#include <algorithm>

namespace omn
{
    template <typename generic>
    class bag
    {
        public:

        using iterator = typename unorderedMap<generic, size_t>::const_iterator;
        using bagItems = vector<std::pair<generic, size_t>>;

        protected:

        unorderedMap<generic, size_t> Items;
        size_t TotalItemCount;

        static inline bool descendingCount( const std::pair<generic, size_t> first,
                                            const std::pair<generic, size_t> last )
        {
            return (first.second > last.second);
        }

        public:

        bag() :
            Items(), TotalItemCount(0)
        {
        }

        bag( const vector<generic> & items ) :
            Items(), TotalItemCount(0)
        {
            for (size_t i = 0, size = items.size(); i < size; i++)
            {
                this->Items[items[i]]++;
                this->TotalItemCount++;
            }
        }

        bag( std::iterator<std::forward_iterator_tag, generic> begin,
             std::iterator<std::forward_iterator_tag, generic> end ) :
            Items(), TotalItemCount(0)
        {
            for (;;)
            {
                this->Items[*begin]++;
                if (begin == end) break;
                begin++;
            }
        }

        inline void clear()
        {
            this->Items.clear();
            this->TotalItemCount = 0;
        }

        inline bool isEmpty() const
        {
            return this->Items.empty();
        }

        inline size_t count() const
        {
            return this->TotalItemCount;
        }

        inline size_t count( const generic & item ) const
        {
            return ((this->Items.count(item)) ? this->Items.at(item) : 0);
        }

        inline double shareOfTotal( const generic & item ) const
        {
            if (this->Items.count(item)) return (this->Items.at(item) / this->TotalItemCount);
            return 0.0;
        }

        inline size_t uniqueItemsCount() const
        {
            return this->Items.size();
        }

        inline size_t size() const
        {
            return this->Items.size();
        }

        inline void reserve( const size_t size )
        {
            this->Items.reserve(size);
        }

        inline bool contains( const generic & item ) const
        {
            return this->Items.count(item);
        }

        inline iterator begin() const
        {
            return this->Items.begin();
        }

        inline iterator end() const
        {
            return this->Items.end();
        }

        inline size_t insert( const generic & item, const size_t count = 1 )
        {
            this->TotalItemCount += count;
            this->Items[item] += count;
            return this->Items[item];
        }

        size_t remove( const generic & item )
        {
            if (this->Items.count(item))
            {
                size_t count = this->Items[item];
                if (count == 1) this->Items.erase(item);
                else (this->Items[item])--;
                this->TotalItemCount--;
                return (--count);
            }
            return 0;
        }

        size_t removeAll( const generic & item )
        {
            if (this->Items.count(item))
            {
                size_t count = this->Items[item];
                this->TotalItemCount -= count;
                this->Items.erase(item);
                return count;
            }
            return 0;
        }

        vector<generic> items() const
        {
            vector<generic> items;
            items.reserve(this->Items.size());
            for (const auto & i : this->Items) items.push_back(i.first);
            return items;
        }

        vector<size_t> counts() const
        {
            vector<size_t> items;
            items.reserve(this->Items.size());
            for (const auto & i : this->Items) items.push_back(i.second);
            return items;
        }

        vector<size_t> counts( const size_t minimum ) const
        {
            vector<size_t> items;
            items.reserve(this->Items.size());
            for (const auto & i : this->Items)
            {
                if (i.second >= minimum) items.push_back(i.second);
            }
            return items;
        }

        vector<double> sharesOfTotal() const
        {
            vector<double> items;
            items.reserve(this->Items.size());
            for (const auto & i : this->Items) items.push_back(i.second / this->TotalItemCount);
            return items;
        }

        bagItems itemsWithCount() const
        {
            return bagItems(this->Items.begin(), this->Items.end());
        }

        bagItems mostFrequentItemsWithCount( size_t N = 10, size_t minimumCount = 1 ) const
        {
            const size_t total = this->Items.size();
            if (total < N) N = total;
            bagItems pairs(this->Items.begin(), this->Items.end());
            std::sort(pairs.begin(), pairs.end(), descendingCount);
            size_t i;
            for (i = 0; i < N; i++)
            {
                if (pairs[i].second < minimumCount) break;
            }
            pairs.resize(i);
            pairs.shrink_to_fit();
            return pairs;
        }

        vector<generic> mostFrequentItems( size_t N = 10, size_t minimumCount = 1 ) const
        {
            bagItems mostFrequent = this->mostFrequentItemsWithCount(N, minimumCount);
            vector<generic> items;
            items.reserve(mostFrequent.size());
            for (const auto & i : mostFrequent) items.push_back(i.first);
            return items;
        }

        inline size_t operator [] ( const generic & item ) const
        {
            return ((this->Items.count(item)) ? this->Items.at(item) : 0);
        }
    };
}

namespace std
{
    template <typename valueType>
    ostream & operator << ( ostream & os, const omn::bag<valueType> & b )
    {
        os << "{";
        for (const auto & item : b) os << item.first << ": " << item.second << ", ";
        if (!b.isEmpty()) os << "\b\b";
        os << "}";
        return os;
    }
}

#endif // _OMN_BAG_INCLUDED
