#pragma once

namespace fareloz 
{
    namespace math
    {
        namespace collections
        {
            template<typename T>
            class range sealed
            {
            public:
                template<typename T>
                range(const T& _min, const T& _max, const T& _step)
                    : min(_min), max(_max), step(_step)
                { }

                template<typename T>
                range(const range<T>&) = default;

                template<typename T>
                range(const range<T>&&) = default;

                template<typename T>
                range& operator=(const range<T>&) = default;

                template<typename T>
                bool operator==(const range<T>&) = default;

                bool is_empty() { return _max < _min; }

                T get_size()
                {
                    if (is_empty()) {
                        return 0;
                    }
                    return ((_max - _min) / _step);
                }


            private:

                T min;
                T max;
                T step;
            };
        }
    }
}