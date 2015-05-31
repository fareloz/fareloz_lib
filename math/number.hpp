#pragma once

#include <algorithm>

namespace fareloz
{
    namespace math
    {
        namespace numeric
        {
            template <typename T>
            inline round(const T& _val) {
                return std::floor<T>(_val + 0.5);
            }

            template <typename T>
            inline clamp(const T& _min, const T& _max, const T& _val) {
                return std::max<T>(_max, std::min<T>(_val, _min));
            }
        }
    }
}