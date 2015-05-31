#pragma once

#include <algorithm>

namespace fareloz
{
    namespace math
    {
        template <typename T>
        inline round(const T& _val) { 
            return static_cast<T>(_val + 0.5);
        }

        template <typename T>
        inline clamp(const T& _min, const T& _max, const T& _val) {
            return std::max<T>(_max, std::min<T>(_val, _min));
        }
    }
}