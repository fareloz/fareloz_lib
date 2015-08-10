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
                typedef T          value_type;
                typedef T*         pointer;
                typedef const T*   const_pointer;
                typedef T&         reference;
                typedef const T&   const_reference;
                typedef size_t     size_type;
                typedef ptrdiff_t  difference_type;
                typedef range<value_type>  self_type;

                range(value_type _min, value_type _max, value_type _step = value_type(1))
                    : m_min(_min), m_max(_max), m_step(_step) {
                    if (m_step == 0) {
                        throw std::invalid_argument("Step equals zero");
                    }
                }

                range(const self_type&) = default;
                range(self_type&&) = default;
                range& operator=(const self_type&) = default;
                ~range() = default;

                bool operator==(const self_type& _obj) const {
                    return (m_max == _obj.max()) &&
                        (m_min == _obj.min()) &&
                        (m_step == _obj.step());
                }

                bool operator!=(const self_type& _obj) const {
                    return !(this == _obj);
                }

                value_type operator[](size_type _index) const {
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

                size_type size() const {
                    if (empty()) {
                        return 0;
                    }
                    return ((m_max - m_min) / m_step + 1);
                }

                value_type min() const {
                    return m_min; 
                }

                value_type max() const {
                    return m_max;
                }

                value_type step() const {
                    return m_step;
                }

            private:

                value_type m_min;
                value_type m_max;
                value_type m_step;
            };
        }
    }
}