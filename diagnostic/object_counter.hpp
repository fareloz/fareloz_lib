#pragma once

#include <atomic>

namespace fareloz
{
    namespace diagnostic
    {
        namespace profiling
        {
            template<typename T>
            class object_counter sealed
            {
            public:

                object_counter() {
                    ++count;
                }

                template<typename T>
                object_counter(const ObjectCounter<T>&) {
                    ++count;
                }

                ~object_counter() {
                    --count;
                }

                static inline size_t get_count() {
                    return count;
                }

            private:

                static std::atomic_size_t count;
            };

            template<typename T> std::atomic_size_t object_counter<T>::count = 0;
        }
    }
}