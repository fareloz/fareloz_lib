#include <functional>
#include <windows.h>

#include "x32_memory_locker.h"
#include "type\data_size.h"

namespace fareloz
{
    namespace dignostic
    {
        using namespace type;

        namespace 
        {
            const __int64 LOW_MEM_LINE = 0x100000000LL;

            typedef std::function<mem_ptr(size_t)> acquire_function;
            typedef std::function<void(mem_ptr)> release_function;

            std::vector<mem_ptr> acquire(size_t start_block_size, size_t end_block_size,
                acquire_function alloc, release_function free)
            {
                std::vector<mem_ptr> acquired;
                for (size_t blockSize = start_block_size; blockSize >= end_block_size; blockSize /= 2)
                {
                    while(true)
                    {
                        mem_ptr ptr = alloc(blockSize);
                        if (!ptr)
                            break;

                        if (reinterpret_cast<size_t>(ptr) >= LOW_MEM_LINE)
                        {
                            free(ptr);
                            break;
                        }

                        acquired.push_back(ptr);
                    }
                }
                return acquired;
            }
        }

        namespace memory
        {

            x32_memory_locker::x32_memory_locker()
            {
                lock();
            }

            x32_memory_locker::~x32_memory_locker()
            {
                release();
            }

            void x32_memory_locker::lock()
            {
#ifdef _WIN64
                // if Microsoft Application verifier is detected, do nothing
                // because this code does not work well with the page heap and
                // the top down memory allocation strategy.
                if ( ::GetModuleHandle("verifier.dll") != NULL )
                    return;

                // Start by reserving large blocks of address space, and then
                // gradually reduce the size in order to capture all of the
                // fragments. 
                acquire_function virtual_alloc = [](size_t memsize) -> mem_ptr { return VirtualAlloc(0, memsize, MEM_RESERVE, PAGE_NOACCESS); };
                release_function virtual_free = std::bind(&VirtualFree, std::placeholders::_1, 0, MEM_RELEASE);
                m_virtualAlloc = acquire(256 * data_size::MEGABYTE, 4096, virtual_alloc, virtual_free);

                // Now repeat the same process but making heap allocations, to use up
                // the already reserved heap blocks that are below the 4 GB line.
                HANDLE heap = GetProcessHeap();
                acquire_function heap_alloc = std::bind(&HeapAlloc, heap, 0, std::placeholders::_1);
                release_function heap_free = std::bind(&HeapFree, heap, 0, std::placeholders::_1);
                m_heapAlloc = acquire(64 * 1024, 16, heap_alloc, heap_free);

                // Perversely enough the CRT doesn't use the process heap. Suck up
                // the memory the CRT heap has already reserved.
                m_malloc = acquire(64 * 1024, 16, malloc, free);
#endif
            }

            void x32_memory_locker::release()
            {
#ifdef _WIN64
                for (auto ptr : m_virtualAlloc)
                    VirtualFree(ptr, 0, MEM_RELEASE);
                const HANDLE hHeap = GetProcessHeap();
                for (auto ptr : m_heapAlloc)
                    HeapFree(hHeap, 0, ptr);
                for (auto ptr : m_malloc)
                    free(ptr);
#endif
            }

        }
    }
}