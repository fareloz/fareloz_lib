#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <iostream>

namespace fareloz
{
    namespace string
    {
        namespace
        {
            template<typename T> struct string_parser;
            template<> struct string_parser<std::string> { typedef std::stringstream stream_type; };
            template<> struct string_parser<std::wstring> { typedef std::wstringstream stream_type; };
        }

        template<typename T>
        std::vector<T>& split(const T& s, typename T::value_type delim, std::vector<T> &elems)
        {
            T item;
            typename string_parser<T>::stream_type ss(s);
            while (std::getline(ss, item, delim)) {
                if (!item.empty()) {
                    elems.emplace_back(item);
                }
            }
            return elems;
        }

        template<typename T>
        std::vector<T> split(const T& s, typename T::value_type delim)
        {
            std::vector<T> elems;
            return split<T>(s, delim, elems);
        }
    }
}