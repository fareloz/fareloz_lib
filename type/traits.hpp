#pragma once

#include <type_traits>

namespace fareloz
{
    namespace type
    {
        namespace traits
        {
            template<typename T, typename... Types>
            struct is_any : std::false_type {};

            template<typename T, typename First>
            struct is_any<T, First> : std::is_same<T, First> {};

            template<typename T, typename First, typename... Types>
            struct is_any<T, First, Types...>
                : std::integral_constant<bool, std::is_same<T, First>::value || is_any<T, Types...>::value>
            {};

            template<typename T>
            struct is_bool 
                : std::integral_constant<bool, std::is_same<T, bool>::value>
            {};

            template<typename T>
            struct is_char 
                : std::integral_constant<bool, is_any<T, char, char16_t, char32_t, wchar_t, signed char, unsigned char>::value>
            {};

            struct void_type;
            struct float_type;
            struct int_type;
            struct uint_type;
            struct char_type;

            template< typename T,
                bool is_float = std::is_floating_point<T>::value,
                bool is_signed = std::is_signed<T>::value,
                bool is_integral = std::is_integral<T>::value,
                bool is_char = is_char<T>::value,
                bool is_bool = is_bool<T>::value >
            struct numeric_type
            {
                typedef void_type type;
            };

            template<typename T> struct numeric_type<T, true, true, false, false, false>  { typedef float_type type; };
            template<typename T> struct numeric_type<T, false, false, true, false, false> { typedef int_type type;   };
            template<typename T> struct numeric_type<T, false, true, true, false, false>  { typedef uint_type type;  };
            template<typename T> struct numeric_type<T, false, true, true, true, false>   { typedef char_type type;  };
            template<typename T> struct numeric_type<T, false, false, true, true, false>  { typedef char_type type;  };
        }
    }
}