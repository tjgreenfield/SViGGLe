/**
 *  Copyright (c) 2015 Timothy Greenfield <tjgreenfield@gmail.com>
 *
 * This file is part of SViGGLe.
 *
 * SViGGLe is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 * SViGGLe is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with SViGGLe.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include "SubString.hh"
#include "CStrHash.hh"

#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

namespace SVGL
{
    template <typename Type>
    class KeywordMapper
    {
    public:

        typedef const std::unordered_map<SubString, Type> StringMap;

        typedef std::unordered_map<Type, const char*, std::hash<int>> IndexMap;

        typedef Type Index;

        const char* lookup(Type index)
        {
            const auto& i = indexMap.find(index);
            if (i != indexMap.end())
            {
                return i->second;
            }
            return nullptr;
        }

        Type lookup(const std::string& str)
        {
            const auto& i = stringMap.find(str.c_str());
            if (i != stringMap.end())
            {
                return i->second;
            }
            return (Type)0;
        }

        Type lookup(const SubString str)
        {
            const auto& i = stringMap.find(str);
            if (i != stringMap.end())
            {
                return i->second;
            }
            return (Type)0;
        }

        Type lookup(const char* str)
        {
            const auto& i = stringMap.find(str);
            if (i != stringMap.end())
            {
                return i->second;
            }
            return (Type)0;
        }

        KeywordMapper(StringMap&& _stringMap) :
            stringMap(std::move(_stringMap))
        {
            for (const auto& i : stringMap)
            {
                indexMap.emplace(i.second, i.first.start);
            }
        }

    protected:

        IndexMap indexMap;
        StringMap stringMap;
    };
}
