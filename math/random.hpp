#pragma once

#include <type_traits>
#include <random>

#include "..\type\traits.hpp"

namespace fareloz
{
    namespace math
    {
        namespace
        {
            static std::default_random_engine& default_engine()
            {
                static std::default_random_engine e{};
                return e;
            }
        }

        namespace random
        {
            template<typename T, typename PT = type::traits::numeric_type<T>::type>
            struct generator
            {
                static T generate_value(T min, T max);
            };

            template<typename T>
            struct generator<T, type::traits::int_type>
            {
                static T generate_value(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max())
                {
                    std::uniform_int_distribution<T> d{ min, max };
                    return d(default_engine());
                }
            };

            template<typename T>
            struct generator<T, type::traits::uint_type>
            {
                static T generate_value(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max())
                {
                    std::uniform_int_distribution<T> d{ min, max };
                    return d(default_engine());
                }
            };

            template<typename T>
            struct generator<T, type::traits::float_type>
            {
                static T generate_value(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max())
                {
                    std::uniform_real_distribution<T> d{ min, max };
                    return d(default_engine());
                }
            };
        }
    }
}