#pragma once

#include <stdexcept>
#include <type_traits>

namespace fareloz 
{
    namespace math
    {
        namespace collections
        {
            template<typename T>
            class range sealed
            {
                static_assert(std::is_pod<T>::value, "Template type should be a pod-type");

            public:
                range(T _min, T _max, T _step)
                    : m_min(_min), m_max(_max), m_step(_step) {
                    if (m_step == 0) {
                        throw std::invalid_argument("Step equals zero");
                    }
                }

                range(const range<T>&) = default;
                range(range<T>&&) = default;
                range& operator=(const range<T>&) = default;
                ~range() = default;

                bool operator==(const range<T>& _obj) const {
                    return (m_max == _obj.max()) &&
                        (m_min == _obj.min()) &&
                        (m_step == _obj.step());
                }

                bool operator!=(const range<T>& _obj) const {
                    return !(this == _obj);
                }

                T operator[](size_t _index) const {
#ifdef _DEBUG
                    if (_index > size()) {
                        throw std::out_of_range("Index out-of-range");
                    }
#endif
                    return (m_min + (_index * m_step));
                }

                bool empty() const {
                    bool is_empty = ((m_max < m_min) && (m_step > 0));
                    is_empty |= ((m_max > m_min) && (m_step < 0));
                    return is_empty;
                }

                size_t size() const {
                    if (empty()) {
                        return 0;
                    }
                    return ((m_max - m_min) / m_step + 1);
                }

                T min() const { 
                    return m_min; 
                }

                T max() const {
                    return m_max;
                }

                T step() const {
                    return m_step;
                }

            private:

                T m_min;
                T m_max;
                T m_step;
            };
        }
    }
}