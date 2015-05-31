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

            template <typename T>
            inline bool in_range(const T& _val, const T& _min, cosnt T& _max) {
                return ((_val > _min) && (_val < _max))
            }

            template <typename T>
            inline bool in_closed_range(const T& _val, const T& _min, cosnt T& _max) {
                return ((_val >= _min) && (_val <= _max))
            }
        }
    }
}