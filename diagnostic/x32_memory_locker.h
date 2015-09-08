#pragma once

#include <vector>
#include "type/primitive.h"

namespace fareloz
{
    namespace dignostic
    {
        namespace memory
        {
            class x32_memory_locker sealed
            {
            public:

                x32_memory_locker();
                ~x32_memory_locker();

            private:

                x32_memory_locker(const x32_memory_locker&) = delete;
                x32_memory_locker(x32_memory_locker&&) = delete;
                x32_memory_locker& operator=(const x32_memory_locker&) = delete;

                void lock();
                void release();
#ifdef _WIN64
                std::vector<type::mem_ptr> m_virtualAlloc;
                std::vector<type::mem_ptr> m_heapAlloc;
                std::vector<type::mem_ptr> m_malloc;
#endif
            };
        }
    }
}